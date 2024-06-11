#include "GraphicsChartFactory.h"

namespace Common {
	GraphicsChartFactory::GraphicsChartFactory(ChartInfo info) :info(info)
	{

	}
	GraphicsChartFactory::~GraphicsChartFactory()
	{

	}
	QGraphicsItem* GraphicsChartFactory::CreatSelfGraphicsItem()
	{
		return new GraphicsChart(info);
	}
}