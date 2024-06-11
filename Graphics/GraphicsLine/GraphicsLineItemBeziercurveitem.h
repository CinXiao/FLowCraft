#pragma once
#include <QPointF>
#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include "../../Globe/RuningConfig.h"
#include "GraphicsLineItem.h"
using namespace Globe;
namespace GraphicsModule
{
	class GraphicsLineItemBeziercurveitem : public GraphicsLineItem
	{
	public:
		GraphicsLineItemBeziercurveitem();
		GraphicsLineItemBeziercurveitem(QPointF startPos, QPointF finishPos);
		QRectF boundingRect() const override;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
		void mousePressEvent(QGraphicsSceneMouseEvent* event);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

		void UpdateLine(QPointF startPos, QPointF finishPos);
		void SetFinishPos(QPointF finishPos);
		void SetStartPos(QPointF startPos);
		void SetPen(QPen pen);
	private:
		//贝塞尔控制点
		QPointF control1;
		QPointF control2;
	};
}
