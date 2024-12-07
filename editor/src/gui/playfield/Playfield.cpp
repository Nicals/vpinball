#include <QMouseEvent>
#include <QWheelEvent>

#include <playfield/commands/SetElementPositionCommand.h>
#include <TableEdit.h>

#include <playfield/Bumper.h>
#include <playfield/PlayfieldElement.h>
#include <playfield/PlayfieldTheme.h>
#include "BumperItem.h"
#include "Playfield.h"


namespace vpin::editor {

   Playfield::Playfield(PlayfieldTheme *theme, TableEdit* table, QWidget* parent)
      : m_theme{theme},
        m_table{table},
        QGraphicsView{parent}
   {
      // XXX: Scroll bar always on just to help the dev process. This should
      //      be removed when we are done.
      setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
      setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

      m_scene = new QGraphicsScene;

      setScene(m_scene);

      for (auto obj: m_table->getElements()) {
         if (QString{obj->metaObject()->className()} == "vpin::editor::Bumper") {
            addBumperItem(qobject_cast<Bumper*>(obj));
         }
         else
         {
            qCritical() << "No playfield item implemented for" << obj->metaObject()->className();
         }
      }

      // Refresh the scene when the theme changes
      connect(m_theme, &PlayfieldTheme::changed, this, [this]() {
         this->m_scene->update();
      });
   }

   void Playfield::addBumperItem(Bumper* bumper)
   {
      BumperItem* item = new BumperItem(m_theme, bumper);
      item->setPos(bumper->getPosition());
      item->setFlag(QGraphicsItem::ItemIsMovable, true);
      item->setFlag(QGraphicsItem::ItemIsSelectable, true);

      connect(item, &BumperItem::hasBeenMoved, [this, bumper](QPointF position) {
         QString name = bumper->getName();
         auto cmd = new SetElementPositionCommand(m_table, bumper->getName(), position);
         m_table->getUndoStack()->push(cmd);
      });

      connect(bumper, &Bumper::changed, [item, bumper]() {
         item->setPos(bumper->getPosition());
      });

      m_scene->addItem(item);
   }

   void Playfield::mousePressEvent(QMouseEvent* event)
   {
      if (event->button() == Qt::MiddleButton) {
         m_isDragging = true;
         m_dragStartPosition = event->pos();
         setCursor(Qt::ClosedHandCursor);
      }

      QGraphicsView::mousePressEvent(event);
   }

   void Playfield::mouseReleaseEvent(QMouseEvent* event)
   {
      if (event->button() == Qt::MiddleButton) {
         m_isDragging = false;
         setCursor(Qt::ArrowCursor);
      }

      QGraphicsView::mouseReleaseEvent(event);
   }

   void Playfield::mouseMoveEvent(QMouseEvent* event)
   {
      if (m_isDragging) {
         // XXX: This is a naive approach. The scene bounding rect is too
         //      narrow to allow proper dragging. This needs to be fixed.
         QPoint delta = event->pos() - m_dragStartPosition;

         QPointF newCenter = mapToScene(viewport()->rect().center()) - delta * 0.7;

         centerOn(newCenter);
         m_dragStartPosition = event->pos();
      }

      QGraphicsView::mouseMoveEvent(event);
   }

   void Playfield::wheelEvent(QWheelEvent* event)
   {
      float zoomFactor = 1.2;
      if (event->angleDelta().y() <= 0) {
         zoomFactor = 1. / zoomFactor;
      }

      scale(zoomFactor, zoomFactor);
   }

}
