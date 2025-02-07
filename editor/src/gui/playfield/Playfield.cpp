#include <QMouseEvent>
#include <QWheelEvent>

#include <playfield/commands/SetElementPositionCommand.h>
#include <TableEdit.h>

#include <playfield/PlayfieldElement.h>
#include <playfield/PlayfieldTheme.h>

#include "BumperItem.h"
#include "ItemFactory.h"
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

      m_itemFactories = new ItemFactoryRegister{this};
      m_itemFactories->registerFactory(new BumperItemFactory{m_table, m_theme});

      for (auto element: m_table->getElements()) {
         QGraphicsObject* object = m_itemFactories->createGraphicsObject(element);
         if (object == nullptr) {
            qCritical() << "No playfield item implemented for" << element->metaObject()->className();
            continue;
         }

         object->setFlag(QGraphicsItem::ItemIsMovable, true);
         object->setFlag(QGraphicsItem::ItemIsSelectable, true);

         m_scene->addItem(object);
         connect(element, &QObject::destroyed, [object, this]() {
            m_scene->removeItem(object);
         });
      }

      // Refresh the scene when the theme changes
      connect(m_theme, &PlayfieldTheme::changed, this, [this]() {
         this->m_scene->update();
      });
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
