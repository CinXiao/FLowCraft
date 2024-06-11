#include "GraphicsTip.h"

namespace GraphicsModule
{
	void GraphicsTip::showTips(QGraphicsView* view, QString tip)
	{
		if (!instancePtr) {  // 如果单例指针为空，则创建实例  
			instancePtr = new GraphicsTip();
			view->scene()->addItem(instancePtr);
		}
		instancePtr->tip = tip;
		instancePtr->setZValue(2);
		QPointF pos{ view->mapToScene(view->rect().left(),view->rect().height() / 2 - 75) };
		instancePtr->rect = QRectF{ pos.x(),pos.y(),(float)view->width(),150.0f };
		instancePtr->setVisible(true);

	}
	QRectF GraphicsTip::boundingRect() const
	{
		return rect;
	}
	void GraphicsTip::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		QColor backcolor = Qt::black;
		backcolor.setAlpha(150);
		painter->setBrush(backcolor);
		painter->drawRect(rect);
		// 设置字体大小和样式  
		QFont font;
		font.setPointSize(25); // 设置字体大小，你可以根据需要调整这个值  
		font.setBold(true); // 设置为粗体（如果需要）  
		painter->setFont(font); // 应用字体到painter  
		// 绘制文本  
		painter->setPen(Qt::white);
		painter->drawText(boundingRect(), Qt::AlignCenter, tip);
	}
	GraphicsTip::GraphicsTip()
	{
		this->setVisible(true);
		QObject::connect(&timer, &QTimer::timeout, [=]() {
			this->setVisible(false);
			});
		timer.start(3000);  // 设置定时器间隔 
	}
}