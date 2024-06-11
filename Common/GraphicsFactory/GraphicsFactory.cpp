#include "GraphicsFactory.h"

namespace Common {
	QGraphicsItem* GraphicsFactory::GetGraphicsItem()
	{
		//主控件
		QGraphicsItem* self = CreatSelfGraphicsItem();
		//子控件
		for (auto sub : SubFactory)
		{
			if (sub)
			{
				QGraphicsItem* subitem = sub->CreatSelfGraphicsItem();
				//设置子控件不可移动
				subitem->setFlag(QGraphicsItem::ItemIsMovable, false);
				//设置子控件不选中
				subitem->setFlag(QGraphicsItem::ItemIsSelectable, false);
				subitem->setParentItem(self);
			}
		}
		return self;
	}
}