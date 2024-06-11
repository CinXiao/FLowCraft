#pragma once
#include <memory>  
#include<qgraphicsitem.h>
#include "../Graphics/GraphicsItem/GraphicsItem.h"
#include"../Common/GraphicsFactory/GraphicsFactory.h"
#include"../Entity/GraphicsItemInfoConfig.h"
using namespace::GraphicsModule;
using namespace::Entity;
/// <summary>
/// 
/// 2024.3.15 By XiaoYongYang
/// 
/// GraphicsItemCreator 类是一个用于创建 GraphicsItem 实例的单例类。
/// 它实现了单例模式，确保在整个应用程序中只存在一个 GraphicsItemCreator 实例，
/// 并提供全局访问点 getInstance() 来获取该实例。
/// </summary>

namespace Globe {
	class GraphicsItemCreator
	{
	private:
		inline static std::unique_ptr<GraphicsItemCreator> instance{nullptr};
		GraphicsItemCreator() = default;
		GraphicsItemCreator(const GraphicsItemCreator&) = delete;
	public:
		static GraphicsItemCreator* getInstance();
		QGraphicsItem* CreatGraphicsItem(GraphicsItemInfoConfig configInfo);

	};
}