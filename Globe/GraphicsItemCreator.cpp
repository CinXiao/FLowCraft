#include "GraphicsItemCreator.h"
using namespace::Globe;
namespace Globe {
	GraphicsItemCreator* GraphicsItemCreator::getInstance()
	{
		if (!instance) {
			instance.reset(new GraphicsItemCreator());
		}
		return instance.get();
	}

	QGraphicsItem* GraphicsItemCreator::CreatGraphicsItem(GraphicsItemInfoConfig configInfo)
	{
		GraphicsFactory* factory = configInfo.GetConfigFactory();
		if (factory)
		{
			return factory->GetGraphicsItem();
		}
		return nullptr;
	}

}