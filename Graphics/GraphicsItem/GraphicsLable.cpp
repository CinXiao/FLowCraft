#include "GraphicsLable.h"

namespace GraphicsModule
{
	GraphicsLabel::GraphicsLabel(LabelInfo info) :Info(info)
	{
		info.GraphicsItemType = Label;

		GraphicsItem::Info.GraphicsItemType = Label;
	}
	QRectF GraphicsLabel::boundingRect() const
	{
		return Info.backgroundSize;
	}
	void GraphicsLabel::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		painter->setPen(Qt::NoPen);
		painter->setBrush(Info.BackgroundColor);
		//绘制矩形框
		painter->drawRoundedRect(Info.backgroundSize, Info.radius, Info.radius);

		painter->setPen(Info.TextColor);
		QFont f;
		f.setBold(Info.isbold);
		f.setPointSize(Info.textSize);
		painter->setFont(f);
		//绘制文本
		painter->drawText(Info.backgroundSize, Info.Text, { Qt::AlignCenter });

	}
}