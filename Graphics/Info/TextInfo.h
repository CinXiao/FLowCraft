#pragma once
#include"ItemInfo.h"
#include"../../Globe/Enum.h"
#include"../../Globe/Map.h"

#include<QColor>
using namespace Globe;
namespace GraphicsModule {
	class TextInfo :public ItemInfo
	{
	public:
		TextInfo();
		QColor  BackgroundColor{ Qt::black };
		QColor  TextColor{ Qt::white };
		QString Text{ "text" };
		int index{ -1 };
		int MaxWidth{ 50 };
	};
}