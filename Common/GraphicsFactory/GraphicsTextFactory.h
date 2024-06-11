#pragma once
#include"GraphicsFactory.h"

#include"../../Graphics/GraphicsItem/GraphicsText.h"
#include"../../Graphics/Info/TextInfo.h"
namespace Common {
	class GraphicsTextFactory :public GraphicsFactory
	{
	public:
		GraphicsTextFactory(TextInfo info = TextInfo{});
		~GraphicsTextFactory();

		// 通过 GraphicsFactory 继承
		QGraphicsItem* CreatSelfGraphicsItem() override;
		TextInfo info;
	};
}