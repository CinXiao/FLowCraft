#include "GraphicsPreviewItem.h"


namespace GraphicsModule {
GraphicsPreviewItem::GraphicsPreviewItem(ItemInfo Info):GraphicsItem(Info)
 {
    this->Info.selectBorder=QPen(Qt::white,3,Qt::DashLine);

     setFlag(QGraphicsItem::ItemIsSelectable, false);
}

void GraphicsPreviewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(widget)
    painter->setPen(Info.selectBorder);
    painter->setBrush(Info.selectBrush);
    //绘制边框
    QRectF backgroud = boundingRect();
    painter->drawRoundedRect(backgroud,Info.radius,Info.radius);
}
}
