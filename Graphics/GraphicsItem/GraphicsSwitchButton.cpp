#include "GraphicsSwitchButton.h"

namespace GraphicsModule {
	GraphicsSwitchButton::GraphicsSwitchButton(SwitchButtonInfo Info) :Info(Info)
	{

		GraphicsItem::Info.GraphicsItemType = SwitchButton;
	}
	QRectF GraphicsSwitchButton::boundingRect() const
	{
		return Info.switchButtonSize;
	}
	void GraphicsSwitchButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		painter->setPen(Qt::NoPen);
		//没有打开
		if (!Info.IsOpen)
		{
			painter->setBrush(Info.buttonColor);
			//画矩形
			painter->drawRoundedRect(Info.switchButtonSize, Info.switchButtonSize.height() / 2, Info.switchButtonSize.height() / 2);
			//画圆形
			painter->setBrush(Info.switchColor);
			double r = Info.switchButtonSize.height() / 2.0f;
			QRectF rect = { Info.switchButtonSize.x(),Info.switchButtonSize.y() , Info.switchButtonSize.height(), Info.switchButtonSize.height() };
			painter->drawEllipse(rect.center(), r, r);

		}
		else
		{
			painter->setBrush(Info.buttonOpenColor);
			//画矩形
			painter->drawRoundedRect(Info.switchButtonSize, Info.switchButtonSize.height() / 2, Info.switchButtonSize.height() / 2);
			//画圆形
			painter->setBrush(Info.switchColor);
			double r = Info.switchButtonSize.height() / 2.0f;
			QRectF rect = { Info.switchButtonSize.width() - Info.switchButtonSize.height() / 2,Info.switchButtonSize.y() , Info.switchButtonSize.height(), Info.switchButtonSize.height() };
			painter->drawEllipse(rect.center(), r, r);
		}
		//画文字
		painter->setPen(Info.switchColor);
		QRectF rect{ Info.switchButtonSize.right(),Info.switchButtonSize.top(),
					Info.switchButtonSize.width(),Info.switchButtonSize.height() };
		painter->drawText(rect, Info.text, { Qt::AlignCenter });


	}
	void GraphicsSwitchButton::mousePressEvent(QGraphicsSceneMouseEvent* event)
	{
		Info.IsOpen = !Info.IsOpen;
		update();
	}
}