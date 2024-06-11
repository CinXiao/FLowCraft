#pragma once
#include <QPainter>
#include <QGraphicsObject>
#include<QPainter>
#include"GraphicsItem.h"
#include"../Info/ButtonInfo.h"
#include<QRectF>
#include<QGraphicsSceneMouseEvent>
#include"../../Globe/RuningConfig.h"
using namespace Globe;
namespace GraphicsModule {
	class GraphicsButton : public GraphicsItem
	{
	public:
		GraphicsButton(ButtonInfo info);
		QRectF boundingRect() const;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
		void mousePressEvent(QGraphicsSceneMouseEvent* event)override;
		void hoverMoveEvent(QGraphicsSceneHoverEvent* event)override;
		void hoverLeaveEvent(QGraphicsSceneHoverEvent* event)override;
		bool ishover{ false };
		ButtonInfo Info;
	};
}