#include "GraphicsNodeFactory.h"
#include "GraphicsPortFactory.h"

namespace Common {

	GraphicsPortFactory::GraphicsPortFactory(PortInfo info) :info(info)
	{
	}

	GraphicsPortFactory::~GraphicsPortFactory()
	{}

	QGraphicsItem* GraphicsPortFactory::CreatSelfGraphicsItem()
	{
		return new GraphicsPort(info);
	}
}