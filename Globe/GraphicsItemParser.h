#pragma once
#include<qjsonobject.h>
#include "../Graphics/GraphicsItem/GraphicsItem.h"
#include"../Common/GraphicsFactory/GraphicsFactory.h"
#include"../Entity/GraphicsItemInfoConfig.h"
using namespace::GraphicsModule;
using namespace::Entity;
namespace Globe {
	class GraphicsItemParser
	{
		public:
			static  QJsonObject GraphicsItemToJsonObject(GraphicsItem *item);
			static  QJsonObject GraphicsItemToJsonObject(GraphicsText* text);
	};
}