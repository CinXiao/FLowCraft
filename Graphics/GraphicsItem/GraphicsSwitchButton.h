#pragma once
#include <QPainter>
#include <QGraphicsObject>
#include<QPainter>
#include"GraphicsItem.h"
#include"../Info/SwitchButtonInfo.h"
#include<QRectF>
#include<QGraphicsSceneMouseEvent>
#include"../../Globe/RuningConfig.h"
using namespace Globe;
namespace GraphicsModule {
	class GraphicsSwitchButton : public GraphicsItem
	{
	public:
		GraphicsSwitchButton(SwitchButtonInfo Info);
		QRectF boundingRect() const;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
		void mousePressEvent(QGraphicsSceneMouseEvent* event)override;

		SwitchButtonInfo Info;
	};
}