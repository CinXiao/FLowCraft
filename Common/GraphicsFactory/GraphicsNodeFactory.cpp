#include "GraphicsNodeFactory.h"

namespace Common {


	GraphicsNodeFactory::GraphicsNodeFactory(NodeInfo info)
		:info(info)
	{


	}

	GraphicsNodeFactory::~GraphicsNodeFactory()
	{}
	QGraphicsItem* GraphicsNodeFactory::CreatSelfGraphicsItem()
	{
		return new GraphicsNode(info);
	}
}