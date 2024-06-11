#pragma once


#include"../Utility/JsonUtility/JsonUtility.h"
#include"Enum.h"
#include"../Graphics/GraphicsView/Graphicsview.h"
#include"GraphicsItemParser.h"

using namespace::GraphicsModule;
using namespace::Utility;
namespace Globe {
	class Loader
	{
	public:
		static void LoadView(GraphicsView *view);
	};
}