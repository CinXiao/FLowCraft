#include "GraphicsPictureBox.h"

namespace GraphicsModule {
	GraphicsPictureBox::GraphicsPictureBox(PictureBoxInfo info) :info(info)
	{
		info.GraphicsItemType = PictureBox;
		image = QPixmap(info.imgPath);

		GraphicsItem::Info.GraphicsItemType = PictureBox;
	}
	QRectF GraphicsPictureBox::boundingRect() const
	{
		return info.backgroundSize;
	}
	void GraphicsPictureBox::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		//绘制图片
		painter->drawPixmap(info.backgroundSize.x(), info.backgroundSize.y(), image); // 从(0,0)位置开始绘制整个pixmap  
	}
}