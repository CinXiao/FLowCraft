#include "RubberEntity.h"

namespace GraphicsModule {

	RubberEntity::RubberEntity(QGraphicsItem* tragetItem)
		:TargetItem(tragetItem) {
		if (tragetItem != nullptr)
		{
			//创建预览框
			PreViewRect = new GraphicsPreviewItem();
			PreViewRect->Info.backgroundSize = tragetItem->boundingRect();
			PreViewRect->setPos(tragetItem->pos());
			QGraphicsScene* scene = tragetItem->scene();
			scene->addItem(PreViewRect);
		}
	}

	RubberEntity::~RubberEntity()
	{
		QGraphicsScene* scene = TargetItem->scene();
		//从场景中删除预览
		scene->removeItem(PreViewRect);
		//销毁预览框和橡皮筋线
		if (PreViewRect != nullptr)
		{
			delete PreViewRect;
		}
		PreViewRect = nullptr;
	}

	void RubberEntity::Adjust(QPointF offset)
	{
		if (PreViewRect)
			PreViewRect->setPos(PreViewRect->pos() + offset);
	}

	void RubberEntity::AdjustTargetPos()
	{
		if (TargetItem)
			TargetItem->setPos(PreViewRect->pos());
	}

}