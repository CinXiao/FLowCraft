#include "GraphicsButton.h"

namespace GraphicsModule {
	GraphicsButton::GraphicsButton(ButtonInfo info) :Info(info)
	{
		setAcceptHoverEvents(true); // 开启鼠标悬停事件  

		GraphicsItem::Info.GraphicsItemType = Button;
	}
	QRectF GraphicsButton::boundingRect() const
	{
		return Info.buttonSize;
	}


	void GraphicsButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		if (ishover)
		{
			painter->setBrush(Info.buttonPressColor);
			painter->setPen(Info.buttonTextColor);
			//画矩形
			painter->drawRoundedRect(Info.buttonSize, 5, 5);
			//画文字
			painter->setPen(Info.buttonTextColor);
			painter->drawText(Info.buttonSize, Info.buttonText, { Qt::AlignCenter });
		}
		else
		{
			painter->setPen(Qt::NoPen);
			painter->setBrush(Info.buttonColor);
			//画矩形
			painter->drawRoundedRect(Info.buttonSize, 3, 3);
			//画文字
			painter->setPen(Info.buttonTextColor);
			painter->drawText(Info.buttonSize, Info.buttonText, { Qt::AlignCenter });
		}

	}
	void GraphicsButton::mousePressEvent(QGraphicsSceneMouseEvent* event)
	{
		if (event->button() == Qt::LeftButton) {
			//运行中点击才有效
			if (RuningConfig::IsRuning)
			{
				//设置按钮信息已经点击
				Info.Clicked = true;
			}
		}

	}
	void GraphicsButton::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
	{
		ishover = true;
	}
	void GraphicsButton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
	{
		ishover = false;
	}
}