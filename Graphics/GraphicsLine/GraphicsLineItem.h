#pragma once
#include "../Info/LineInfo.h"
#include<QGraphicsLineItem>
#include<QPainter>
namespace GraphicsModule
{
	class GraphicsLineItem :public QGraphicsLineItem
	{
	public:
		GraphicsLineItem(LineInfo info = LineInfo(), QGraphicsItem* parent = nullptr);

		~GraphicsLineItem();
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;;
		LineInfo Info;
	};
}