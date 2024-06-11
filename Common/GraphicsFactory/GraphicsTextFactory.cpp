#include "GraphicsTextFactory.h"
namespace Common {
	GraphicsTextFactory::GraphicsTextFactory(TextInfo info) :info(info)
	{


	}

	GraphicsTextFactory::~GraphicsTextFactory()
	{}

	QGraphicsItem* GraphicsTextFactory::CreatSelfGraphicsItem()
	{
		return new GraphicsText(info);
	}
}