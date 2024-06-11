#include"GraphicsGroup.h"

namespace GraphicsModule {
	GraphicsGroup::GraphicsGroup(GroupInfo info, QGraphicsItem* parent) :QGraphicsItemGroup(parent),
		Info(info)
	{
		setFlag(QGraphicsItem::ItemIsSelectable, true);

	}

	void GraphicsGroup::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		Q_UNUSED(widget)
			// 选中边框绘制
			if (option->state & QStyle::State_Selected) {
				painter->setPen(Info.selectBorder);
				painter->setBrush(Info.selectBrush);
			}
			else
			{
				painter->setPen(Info.normalBorder);
				painter->setBrush(Info.normalBrush);
			}

		int Radius = Info.radius;
		painter->drawRoundedRect(option->rect, Radius, Radius); // 绘制矩形边框

	}
}
