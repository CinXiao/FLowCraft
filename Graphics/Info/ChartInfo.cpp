#include "ChartInfo.h"

#pragma once

namespace GraphicsModule {
	ChartInfo::ChartInfo()
	{

		GraphicsItemType = GraphicsItemType::Chart;
	}

	void ChartInfo::InsertValueList(QList<QVariant> ValueList)
	{
		//折线图通过X，Y坐标
		if (chatyType == Straight && ValueList.count() == 2)
		{
			QPointF pos{ ValueList[0].toFloat(),ValueList[1].toFloat() };
			DataList.append(pos);
		}
		else if (chatyType == SquareWave && ValueList.count() == 1)
		{
			float number = ValueList[0].toFloat();
			if (number != 0)
				number = 1;
			else
				number = 0;
			QPointF pos{ 0,number };

			while (DataList.count() * 20 > RectSize.width())
				DataList.pop_front();

			DataList.append(pos);
		}
	}

};