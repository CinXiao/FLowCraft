#pragma once
#include"../../Graphics/GraphicsItem/GraphicsPort.h"
#include"../../Graphics/Info/PortInfo.h"
#include"../../Graphics/Info/NodeInfo.h"
#include"../../Graphics/Info/TextInfo.h"
#include"../../Graphics/Info/ButtonInfo.h"
#include"../../Graphics/Info/ChartInfo.h"
#include"../../Graphics/GraphicsItem/GraphicsChart.h"
#include"../../Graphics/GraphicsItem/GraphicsSwitchButton.h"
#include"GraphicsFactory.h"
namespace Common {
	class GraphicsChartFactory :public GraphicsFactory
	{
	public:
		GraphicsChartFactory(ChartInfo info = {});
		~GraphicsChartFactory();

		// 通过 GraphicsFactory 继承
		QGraphicsItem* CreatSelfGraphicsItem() override;
		ChartInfo info;
	};
}