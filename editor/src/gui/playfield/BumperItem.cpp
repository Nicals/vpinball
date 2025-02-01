#include <QtMath>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <TableEdit.h>
#include <playfield/Bumper.h>
#include <playfield/PlayfieldTheme.h>
#include <playfield/commands/SetElementPositionCommand.h>

#include "DragHandle.h"
#include "BumperItem.h"


namespace vpin::editor {

   BumperItem::BumperItem(PlayfieldTheme* theme)
      : m_theme{theme}
   {
      m_radiusHandle = new DragHandle{m_theme, this};

      setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
   }

   void BumperItem::setRadius(float radius)
   {
      m_radius = radius;
      updateRadiusHandle();
   }

   void BumperItem::setOrientation(const Angle& orientation)
   {
      m_orientation = orientation;
      updateRadiusHandle();
   }

   void BumperItem::updateRadiusHandle()
   {
      m_radiusHandle->setPos(
         m_radius * qCos(m_orientation.radians()),
         m_radius * qSin(m_orientation.radians())
      );
   }

   QRectF BumperItem::boundingRect() const
   {
      return QRectF{-m_radius, -m_radius, m_radius * 2, m_radius * 2};
   }

   void BumperItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
   {
      // Paint center
      painter->setPen(m_theme->getHandlePen(isSelected()));
      painter->setBrush(m_theme->getHandleBrush(isSelected()));
      painter->drawEllipse(QRectF{-10.0, -10.0, 20.0, 20.0});

      // Paint radius
      painter->setPen(m_theme->getRadiusPen());
      painter->drawEllipse(QRectF{-m_radius, -m_radius, m_radius * 2, m_radius * 2});
   }

   void BumperItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
   {
      QGraphicsItem::mouseReleaseEvent(event);

      emit hasBeenMoved(pos());
   }

   QVariant BumperItem::itemChange(GraphicsItemChange change, const QVariant& value)
   {
      if (change == GraphicsItemChange::ItemPositionChange) {
         // Prevent item to be moved to negative position
         QPointF newPosition = value.toPointF();
         if (newPosition.x() < 0) {
            newPosition.setX(0);
         }

         if (newPosition.y() < 0) {
            newPosition.setY(0);
         }

         return newPosition;
      }

      return QGraphicsItem::itemChange(change, value);
   }

   BumperItemFactory::BumperItemFactory(TableEdit* table, PlayfieldTheme* theme)
      : m_table{table},
        m_theme{theme}
   {
   }

   QGraphicsObject* BumperItemFactory::createGraphicsObject(PlayfieldElement* element) const
   {
      Bumper* bumper = qobject_cast<Bumper*>(element);
      if (bumper == nullptr) {
         return nullptr;
      }

      BumperItem* item = new BumperItem{m_theme};
      item->setPos(bumper->getPosition());
      item->setRadius(bumper->getRadius());
      item->setOrientation(bumper->getOrientation());

      connect(bumper, &Bumper::changed, [item, bumper]() {
         item->setPos(bumper->getPosition());
         item->setRadius(bumper->getRadius());
         item->setOrientation(bumper->getOrientation());
         item->update();
      });

      connect(item, &BumperItem::hasBeenMoved, [this, bumper](QPointF position) {
         auto cmd = new SetElementPositionCommand{m_table, bumper->getName(), position};
         m_table->getUndoStack()->push(cmd);
      });

      return item;
   }

}
