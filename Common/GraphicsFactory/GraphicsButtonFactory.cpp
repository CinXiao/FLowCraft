#include "GraphicsButtonFactory.h"

namespace Common {
	GraphicsButtonFactory::GraphicsButtonFactory(ButtonInfo info) :info(info)
	{
	}
	GraphicsButtonFactory::~GraphicsButtonFactory()
	{
	}
	QGraphicsItem* GraphicsButtonFactory::CreatSelfGraphicsItem()
	{
		return new GraphicsButton(info);
	}
}