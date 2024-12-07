#pragma once

#include <QGraphicsView>


namespace vpin::editor
{

   class Bumper;
   class TableEdit;
   class PlayfieldTheme;

   class Playfield final
      : public QGraphicsView
   {
      public:
         Playfield(PlayfieldTheme* theme, TableEdit* table, QWidget* parent=nullptr);

      private:
         void addBumperItem(Bumper* bumper);

         void mousePressEvent(QMouseEvent* event) override;
         void mouseReleaseEvent(QMouseEvent* event) override;
         void mouseMoveEvent(QMouseEvent* event) override;
         void wheelEvent(QWheelEvent* event) override;

      private:
         QGraphicsScene* m_scene;
         PlayfieldTheme* m_theme;
         TableEdit* m_table;

         bool m_isDragging = false;
         QPoint m_dragStartPosition;
   };
}
