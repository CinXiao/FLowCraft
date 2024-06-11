#include "GroupInfo.h"

namespace GraphicsModule {

	GroupInfo::GroupInfo()
	{
		GraphicsItemType = GraphicsItemType::Group;
        normalBrush=QBrush(QColor(60,100,100,100));
        selectBrush=QBrush(QColor(60,100,100,150));
	}
}
