#include"GraphicsNode.h"

namespace GraphicsModule {
	GraphicsNode::GraphicsNode(NodeInfo nodeInfo) :Info(nodeInfo), GraphicsItem(nodeInfo)
	{
		GraphicsItem::Info.GraphicsItemType = nodeInfo.GraphicsItemType;

	}



	void GraphicsNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		Q_UNUSED(widget)
			GraphicsItem::paint(painter, option, widget);

		int Radius = Info.radius;
		QRectF titleback = Info.titleSize;
		QRectF backgroud = Info.backgroundSize;
		//绘制节点背景
		//背景是否以渐变的颜色绘制
		if (Info.backgroundColorGradient)
		{
			QLinearGradient gradient(backgroud.topLeft(), backgroud.bottomLeft());
			gradient.setColorAt(0, Info.backgroundColor1); // 起始颜色
			gradient.setColorAt(1, Info.backgroundColor2);   // 终止颜色
			QBrush titleBarBrush(gradient);
			painter->setBrush(titleBarBrush);
		}
		else
		{
			painter->setBrush(Info.backgroundColor1);
		}
		painter->drawRoundedRect(backgroud, Radius, Radius);

		//绘制节点标题栏
		//节点标题栏是否渐变
		if (Info.titleBackgroundColorGradient)
		{
			QLinearGradient gradient(titleback.topLeft(), titleback.bottomLeft());
			gradient.setColorAt(0, Info.titleBackgroundColor1); // 起始颜色
			gradient.setColorAt(1, Info.titleBackgroundColor2);   // 终止颜色
			QBrush titleBarBrush(gradient);
			painter->setBrush(titleBarBrush);
		}
		else
		{
			painter->setBrush(Info.titleBackgroundColor1);
		}
		//绘制标题
		painter->drawRoundedRect(titleback, Radius, Radius);
		//绘制标题文字
		painter->setPen(Qt::white);
		painter->drawText({ 30,0,
			Info.titleSize.width() - 60,
			Info.titleSize.height() - 10 },
			Info.nodeName, { Qt::AlignCenter });
	}



	

}
