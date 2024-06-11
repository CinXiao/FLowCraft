#pragma once
#include"NodeInfo.h"
#include<QVariant>
namespace GraphicsModule
{



	//图表类型
	class ChartInfo :ItemInfo
	{
	public:
		ChartInfo();
		//图表类型
		ChartType chatyType{ Straight };
		QRectF RectSize;
		//图表内数据
		QList <QPointF>DataList;
		void InsertValueList(QList<QVariant> ValueList);

		float stepDistance{ 2 };//(膨胀系数)单位长度距离,各个图项之间的距离
		QColor axisColor{ Qt::green };
		QColor lineColor{ Qt::green };
		bool drawPoint{ true };
		bool drawLine{ true };
		QColor pointColor{ Qt::green };
		int pointSize{ 2 };
		int chartIndex{ -1 };

	};


}