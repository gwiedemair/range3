/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   draw_engine.cpp                                          *
 *  GROUP:  Range                                                    *
 *  TYPE:   source file (*.cpp)                                      *
 *  DATE:   26-th September 2014                                     *
 *                                                                   *
 *  DESCRIPTION: Draw engine class definition                        *
 *********************************************************************/

#include <rblib.h>

#include "draw_engine.h"
#include "session.h"

DrawEngine::DrawEngine(QObject *parent) :
    QObject(parent)
{
}

void DrawEngine::start(void)
{
    if (this->isRunning)
    {
        throw RError(R_ERROR_APPLICATION,R_ERROR_REF,"Engine is already running");
    }
}

void DrawEngine::stop(void)
{
    if (!this->isRunning)
    {
        throw RError(R_ERROR_APPLICATION,R_ERROR_REF,"Engine is not running");
    }

}

void DrawEngine::processObjects(const QList<uint> &modelIDs, bool mergeNearNodes, double tolerance, bool findNearest)
{
    for (int i=0;i<modelIDs.size();i++)
    {
        Session::getInstance().storeCurentModelVersion(modelIDs[i],tr("Draw object"));
        for (int j=0;j<this->objects.size();j++)
        {
            Session::getInstance().getModel(modelIDs[i]).insertModel(this->objects[j]->getModel(),mergeNearNodes,tolerance,findNearest);
        }
        Session::getInstance().setModelChanged(modelIDs[i]);
    }
    this->objects.clear();
    emit this->objectsRemoved();
}

void DrawEngine::addObject(DrawEngineObject *object)
{
    object->setParent(this);
    this->objects.push_back(object);
    emit this->objectAdded();
}

void DrawEngine::removeObject(uint position)
{
    DrawEngineObject *pObject = this->objects[position];
    this->objects.removeAt(position);
    delete pObject;
    emit this->objectRemoved(position);
}

uint DrawEngine::getNObjects(void) const
{
    return uint(this->objects.size());
}

const DrawEngineObject *DrawEngine::getObject(uint position) const
{
    return this->objects[position];
}

DrawEngineObject *DrawEngine::getObject(uint position)
{
    return this->objects[position];
}

void DrawEngine::setObjectChanged(uint position)
{
    emit this->objectChanged(position);
}
