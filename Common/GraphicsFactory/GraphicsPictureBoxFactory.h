#pragma once
#include"GraphicsFactory.h"
#include"../../Graphics/GraphicsItem/GraphicsPictureBox.h"
#include"../../Graphics/Info/PictureBoxInfo.h"
namespace Common
{
	class GraphicsPictureBoxFactory :public GraphicsFactory
	{
	public:
		GraphicsPictureBoxFactory(PictureBoxInfo info = PictureBoxInfo{});

		// 通过 GraphicsFactory 继承
		QGraphicsItem* CreatSelfGraphicsItem() override;

		PictureBoxInfo info;
	};


}