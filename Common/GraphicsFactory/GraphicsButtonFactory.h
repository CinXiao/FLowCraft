#pragma once
#include"GraphicsFactory.h"
#include"../../Graphics/GraphicsItem/GraphicsSwitchButton.h"
#include"../../Graphics/Info/ButtonInfo.h"

#include"../../Graphics/GraphicsItem/GraphicsButton.h"
namespace Common {
	class GraphicsButtonFactory :public GraphicsFactory
	{
	public:
		GraphicsButtonFactory(ButtonInfo info);
		~GraphicsButtonFactory();

		ButtonInfo info;

		// 通过 GraphicsFactory 继承
		QGraphicsItem* CreatSelfGraphicsItem() override;
	};
}