#pragma once

#include <QGraphicsItem>


namespace vpin::editor {

   class Bumper;
   class DragHandle;
   class PlayfieldTheme;

   class BumperItem
      : public QGraphicsItem
   {
      public:
         BumperItem(PlayfieldTheme* theme, Bumper* bumper);

         QRectF boundingRect() const override;
         void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

      private:
         PlayfieldTheme* m_theme;
         Bumper* m_bumper;

         DragHandle* m_radiusHandle;
   };

}
