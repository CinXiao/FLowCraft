#pragma once

#include <QPointF>
#include <QPen>

#include"ItemInfo.h"
namespace GraphicsModule {
	class LineInfo :public ItemInfo
	{
	public:
		LineInfo();
		QPointF startPos;
		QPointF FinishPos;
		QPen LineColorPen{ QPen(Qt::white,8,Qt::SolidLine) };//线的颜色


	};
}