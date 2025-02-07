#pragma once

#include <QGraphicsView>


namespace vpin::editor
{

   class TableEdit;
   class PlayfieldElement;
   class PlayfieldTheme;
   class ItemFactoryRegister;

   class Playfield final
      : public QGraphicsView
   {
      Q_OBJECT;

      public:
         Playfield(PlayfieldTheme* theme, TableEdit* table, QWidget* parent=nullptr);

      private:
         void mousePressEvent(QMouseEvent* event) override;
         void mouseReleaseEvent(QMouseEvent* event) override;
         void mouseMoveEvent(QMouseEvent* event) override;
         void wheelEvent(QWheelEvent* event) override;

         void notifyItemSelected();

      signals:
         void elementSelected(QList<PlayfieldElement*> elements);

      private:
         QGraphicsScene* m_scene;
         PlayfieldTheme* m_theme;
         TableEdit* m_table;

         ItemFactoryRegister* m_itemFactories;

         bool m_isDragging = false;
         QPoint m_dragStartPosition;
   };
}
