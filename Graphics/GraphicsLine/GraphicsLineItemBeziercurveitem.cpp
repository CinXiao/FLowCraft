#include "GraphicsLineItemBeziercurveitem.h"
#include <QGraphicsSceneHoverEvent>
namespace GraphicsModule
{
	GraphicsLineItemBeziercurveitem::GraphicsLineItemBeziercurveitem()
	{
		setFlag(GraphicsItemFlag::ItemIsSelectable, true);
		setAcceptHoverEvents(true);
	}

	GraphicsLineItemBeziercurveitem::GraphicsLineItemBeziercurveitem(QPointF startPos, QPointF finishPos)
	{
		setFlag(GraphicsItemFlag::ItemIsSelectable, true);
		setAcceptHoverEvents(true);
		UpdateLine(startPos, finishPos);
	}

	QRectF GraphicsLineItemBeziercurveitem::boundingRect() const
	{
		// 返回包围贝塞尔曲线的矩形
		qreal minX = qMin(qMin(Info.startPos.x(), Info.FinishPos.x()), qMin(control1.x(), control2.x()));
		qreal minY = qMin(qMin(Info.startPos.y(), Info.FinishPos.y()), qMin(control1.y(), control2.y()));
		qreal maxX = qMax(qMax(Info.startPos.x(), Info.FinishPos.x()), qMax(control1.x(), control2.x()));
		qreal maxY = qMax(qMax(Info.startPos.y(), Info.FinishPos.y()), qMax(control1.y(), control2.y()));
		return QRectF(minX, minY, maxX - minX, maxY - minY);
	}

	void GraphicsLineItemBeziercurveitem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		Q_UNUSED(option);
		Q_UNUSED(widget);
		setZValue(-1);
		QPen pen(Info.LineColorPen);
		if (isSelected())
			pen.setWidth(12);
		else
			pen.setWidth(8);
		painter->setPen(pen);
		if (RuningConfig::lineType == LineType::BezierLine)
		{
			if (Info.startPos.x() >= Info.FinishPos.x())
			{
				control1 = QPointF(Info.startPos.x() - 30, Info.startPos.y()); // 偏离起点的第一个控制点
				control2 = QPointF(Info.FinishPos.x() + 30, Info.FinishPos.y());   // 偏离终点的第二个控制点
			}
			else
			{
				control1 = QPointF(Info.startPos.x() + 60, Info.startPos.y()); // 偏离起点的第一个控制点
				control2 = QPointF(Info.FinishPos.x() - 60, Info.FinishPos.y());   // 偏离终点的第二个控制点
			}
			// 贝塞尔曲线
			QPainterPath bezierPath;
			bezierPath.moveTo(Info.startPos);
			bezierPath.cubicTo(control1, control2, Info.FinishPos);
			painter->drawPath(bezierPath);
		}
		else if (RuningConfig::lineType == LineType::StraightLine)
		{
			painter->drawLine(Info.startPos, Info.FinishPos);
		}
		else if (RuningConfig::lineType == LineType::Polyline)
		{
			float midX = (Info.startPos.x() + Info.FinishPos.x()) / 2.0f;

			painter->drawLine(Info.startPos, { midX,Info.startPos.y() });
			painter->drawLine(Info.FinishPos, { midX, Info.FinishPos.y() });
			painter->drawLine(QPointF{ midX,Info.startPos.y() }, QPointF{ midX,Info.FinishPos.y() });
		}

	}

	void GraphicsLineItemBeziercurveitem::mousePressEvent(QGraphicsSceneMouseEvent* event)
	{


		QGraphicsItem::mousePressEvent(event);
	}

	void GraphicsLineItemBeziercurveitem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
	{
		QPainterPath bezierPath;
		bezierPath.moveTo(Info.startPos);
		bezierPath.cubicTo(control1, control2, Info.FinishPos);
		if (bezierPath.intersects(QRectF(event->pos(), QSizeF(8, 8))))
			setSelected(true);
		else
			setSelected(false);
		event->ignore();
	}

	void GraphicsLineItemBeziercurveitem::UpdateLine(QPointF startPos, QPointF finishPos)
	{
		Info.startPos = startPos;
		Info.FinishPos = finishPos;
		setLine(startPos.x(), startPos.y(), finishPos.x(), finishPos.y());
	}

	void GraphicsLineItemBeziercurveitem::SetFinishPos(QPointF finishPos)
	{
		Info.FinishPos = finishPos;
		setLine(Info.startPos.x(), Info.startPos.y(), finishPos.x(), finishPos.y());

	}

	void GraphicsLineItemBeziercurveitem::SetStartPos(QPointF startPos)
	{
		Info.startPos = startPos;
		setLine(startPos.x(), startPos.y(), Info.FinishPos.x(), Info.FinishPos.y());

	}

	void GraphicsLineItemBeziercurveitem::SetPen(QPen pen)
	{
		Info.LineColorPen = pen;

	}





}