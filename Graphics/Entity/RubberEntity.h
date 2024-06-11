#pragma once
#include"../GraphicsItem/GraphicsPreviewItem.h"
#include"../GraphicsItem/GraphicsItem.h"
#include "../GraphicsLine/GraphicsRubberLine.h"
#include<QGraphicsScene>
/// <summary>
/// 用于进行拖动图元时预览
/// </summary>

namespace GraphicsModule {
	class RubberEntity
	{
	public:
		RubberEntity(QGraphicsItem* tragetItem);
		~RubberEntity();
		//调整预览框和目标位置
		void Adjust(QPointF offset);
		//调整目标图元位置到预览框
		void AdjustTargetPos();

		//用于建立视图中某个图元和预览框和橡皮筋之间的关系
		QGraphicsItem* TargetItem{ nullptr };
		GraphicsPreviewItem* PreViewRect{ nullptr };


	};
}