#pragma once

#include"../Utility/JsonUtility/JsonUtility.h"
#include"Enum.h"
#include"../Graphics/GraphicsView/Graphicsview.h"
#include"GraphicsItemParser.h"

using namespace::GraphicsModule;
using namespace::Utility;
namespace Globe {
	class Saver
	{
	public:
		//自动保存，用于自动保存
		static void AutoSave(GraphicsView* view);

		
	};
}