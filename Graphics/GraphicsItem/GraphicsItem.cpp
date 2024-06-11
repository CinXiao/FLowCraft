#include "GraphicsItem.h"
namespace GraphicsModule {
	GraphicsItem::GraphicsItem(ItemInfo info, QGraphicsItem* parent) :Info(info), QGraphicsItem(parent)
	{
		setFlag(QGraphicsItem::ItemIsSelectable, true);
	}

	QRectF GraphicsItem::boundingRect() const
	{
		return Info.backgroundSize;
	}

	GraphicsItem::~GraphicsItem()
	{
	}

	void GraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		Q_UNUSED(widget)
			// 选中边框绘制
			if (option->state & QStyle::State_Selected) {
				QPen pen = Info.selectBorder;
				pen.setWidth(5);
				painter->setPen(pen);
				painter->setBrush(Qt::NoBrush);
			}
			else
			{
				painter->setPen(Qt::NoPen);
				painter->setBrush(Qt::NoBrush);
			}
		//绘制框
		QRectF backgroud = boundingRect();
		painter->drawRoundedRect(backgroud, Info.radius, Info.radius);
		painter->setPen(Qt::NoPen);
		painter->setBrush(Qt::NoBrush);

	}
}
