#include "GraphicsSwitchButtonFactory.h"

namespace Common {
	GraphicsSwitchButtonFactory::GraphicsSwitchButtonFactory(SwitchButtonInfo info) :info(info)
	{}

	GraphicsSwitchButtonFactory::~GraphicsSwitchButtonFactory()
	{}

	QGraphicsItem* GraphicsSwitchButtonFactory::CreatSelfGraphicsItem()
	{
		return new GraphicsSwitchButton(info);
	}
}