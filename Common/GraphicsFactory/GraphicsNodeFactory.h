#pragma once

#include<QGraphicsitem>
#include"GraphicsFactory.h"
#include"../../Graphics/GraphicsItem/GraphicsNode.h"
#include"../../Graphics/Info/NodeInfo.h"
namespace Common {
	class GraphicsNodeFactory :public GraphicsFactory
	{

	public:
		GraphicsNodeFactory(NodeInfo info = {});
		~GraphicsNodeFactory();
		// 通过 GraphicsFactory 继承
		QGraphicsItem* CreatSelfGraphicsItem() override;
		NodeInfo info;

	};
}