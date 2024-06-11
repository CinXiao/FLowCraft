#include "GraphicsLabelFactory.h"

namespace Common {
	GraphicsLabelFactory::GraphicsLabelFactory(LabelInfo info) :Info(info)
	{
	}
	QGraphicsItem* GraphicsLabelFactory::CreatSelfGraphicsItem()
	{
		return new GraphicsLabel(Info);
	}
}