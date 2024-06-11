#pragma once
#include"GraphicsItem.h"
namespace GraphicsModule
{
    class GraphicsPreviewItem:public GraphicsItem
    {
    public:
        GraphicsPreviewItem(ItemInfo Info=ItemInfo());

        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
    };


}
