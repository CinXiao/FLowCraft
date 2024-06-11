#pragma once
#include"../../Graphics/GraphicsItem/GraphicsItem.h"
#include <thread>
using namespace::GraphicsModule;
namespace Common {
	class GraphicsFactory
	{
	public:
		QGraphicsItem* GetGraphicsItem();
		QList<GraphicsFactory*>SubFactory;//子工厂
	private:
		virtual QGraphicsItem* CreatSelfGraphicsItem() = 0;
	};
}