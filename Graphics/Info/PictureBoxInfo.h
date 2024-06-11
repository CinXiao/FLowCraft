#pragma once
#include"ItemInfo.h"
#include"../../Globe/Enum.h"
#include"../../Globe/Map.h"
using namespace Globe;

namespace GraphicsModule {


	class PictureBoxInfo :public ItemInfo
	{
	public:
		PictureBoxInfo();
		~PictureBoxInfo();
		QString imgPath;
		QSize imgSize;
	};
}
