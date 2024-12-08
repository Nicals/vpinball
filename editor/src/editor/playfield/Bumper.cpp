#include <adapter/Bumper.h>

#include "Bumper.h"


namespace vpin::editor {

   Bumper::Bumper(vpin::adapter::Bumper* bumper, QObject* parent)
      : m_bumper{bumper},
        PlayfieldElement{parent}
   {
   }

   void Bumper::setName(const QString& name)
   {
      if (name == getName()) {
         return;
      }

      m_bumper->setName(name.toStdString());
      emit changed();
   }

   const QString Bumper::getName() const
   {
      QString name{m_bumper->getName().c_str()};
      return name;
   }

   QPointF Bumper::getPosition() const
   {
      auto pos = m_bumper->getPosition();
      return QPointF{pos.x, pos.y};
   }

   void Bumper::setPosition(QPointF position)
   {
      if (position == getPosition()) {
         return;
      }
      m_bumper->setPosition(vpin::adapter::Point2D{float(position.x()), float(position.y())});
      emit changed();
   }

   float Bumper::getRadius() const
   {
      return m_bumper->getRadius();
   }

   void Bumper::setRadius(float radius)
   {
      if (qFuzzyCompare(radius, getRadius())) {
         return;
      }
      m_bumper->setRadius(radius);
      emit changed();
   }

   Angle Bumper::getOrientation() const
   {
      return Angle::fromDegrees(m_bumper->getOrientation());
   }

   void Bumper::setOrientation(const Angle& orientation)
   {
      if (getOrientation() == orientation) {
         return;
      }
      m_bumper->setOrientation(orientation.degrees());
      emit changed();
   }

}
