#pragma once
#include"GraphicsFactory.h"
#include"../../Graphics/GraphicsItem/GraphicsSwitchButton.h"
#include"../../Graphics/Info/SwitchButtonInfo.h"

namespace Common {
	class GraphicsSwitchButtonFactory :public GraphicsFactory
	{
	public:
		GraphicsSwitchButtonFactory(SwitchButtonInfo info = SwitchButtonInfo{});
		~GraphicsSwitchButtonFactory();

		// 通过 GraphicsFactory 继承
		QGraphicsItem* CreatSelfGraphicsItem() override;

		SwitchButtonInfo info;
	};
}