#pragma once

#include<QPen>
#include"../../Globe/Enum.h"
using namespace Globe;
namespace GraphicsModule {
	class ItemInfo
	{
	public:
		ItemInfo();
		ItemInfo(QRectF rect);
		QRectF backgroundSize{ 0,0,20,20 };//图元大小
		QPen normalBorder{ QPen(Qt::NoPen) };//普通边框
		QPen selectBorder{ QPen(Qt::white,5,Qt::SolidLine) };//选中时候的边框
		QBrush normalBrush{ QBrush(Qt::NoBrush) };//普通填充
		QBrush selectBrush{ QBrush(Qt::NoBrush) };//选中时的填充
		int radius{ 8 };//圆角
		GraphicsItemType GraphicsItemType{ Null };//图元类型
	};
}
