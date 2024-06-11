#pragma once
#include"GraphicsFactory.h"

#include"../../Graphics/GraphicsItem/GraphicsPort.h"
#include"../../Graphics/Info/PortInfo.h"

namespace Common {
	class GraphicsPortFactory :public GraphicsFactory
	{
	public:
		GraphicsPortFactory(PortInfo info = PortInfo{});
		~GraphicsPortFactory();
		// 通过 GraphicsFactory 继承
		QGraphicsItem* CreatSelfGraphicsItem() override;
		PortInfo info;
	};
}