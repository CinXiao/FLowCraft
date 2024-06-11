#pragma once
#include <QPainter>
#include <QGraphicsObject>
#include<QPainter>
#include"GraphicsItem.h"
#include"../Info/ChartInfo.h"

namespace GraphicsModule {
	class GraphicsChart : public GraphicsItem
	{
	public:
		GraphicsChart(ChartInfo info);
		QRectF boundingRect() const;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;

		~GraphicsChart();
		ChartInfo Info;
	};
}
