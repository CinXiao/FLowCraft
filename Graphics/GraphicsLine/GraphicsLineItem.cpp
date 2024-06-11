#include "GraphicsLineItem.h"
namespace GraphicsModule
{
	GraphicsLineItem::GraphicsLineItem(LineInfo info, QGraphicsItem* parent) :
		QGraphicsLineItem(parent), Info(info)
	{
	}

	GraphicsLineItem::~GraphicsLineItem()
	{}


	void GraphicsLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		Q_UNUSED(widget)
			painter->setPen(Info.LineColorPen);
		painter->drawLine(Info.startPos, Info.FinishPos);
	}
}