#include"GraphicsPictureBoxFactory.h"


namespace Common {
	GraphicsPictureBoxFactory::GraphicsPictureBoxFactory(PictureBoxInfo info) :info(info)
	{
	}
	QGraphicsItem* GraphicsPictureBoxFactory::CreatSelfGraphicsItem()
	{
		return new GraphicsPictureBox(info);
	}
}