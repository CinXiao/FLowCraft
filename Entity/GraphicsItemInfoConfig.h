#pragma once
#include<QString>
#include "../Graphics/GraphicsItem/GraphicsItem.h"
#include "../Graphics/Info/ItemInfo.h"
#include "../Graphics/Info/NodeInfo.h"
#include "../Graphics/Info/PortInfo.h"
#include "../Graphics/Info/GroupInfo.h"
#include "../Graphics/Info/GroupInfo.h"
#include "../Graphics/Info/LineInfo.h"
#include "../Graphics/Info/SwitchButtonInfo.h"
#include "../Graphics/Info/PictureBoxInfo.h"
#include "../Graphics/Info/TextInfo.h"
#include "../Graphics/Info/LabelInfo.h"

#include"../Common/GraphicsFactory/GraphicsPortFactory.h"
#include"../Common/GraphicsFactory/GraphicsNodeFactory.h"
#include"../Common/GraphicsFactory/GraphicsTextFactory.h"
#include"../Common/GraphicsFactory/GraphicsSwitchButtonFactory.h"
#include"../Common/GraphicsFactory/GraphicsFactory.h"
#include"../Common/GraphicsFactory/GraphicsChartFactory.h"
#include"../Common/GraphicsFactory/GraphicsButtonFactory.h"
#include"../Common/GraphicsFactory/GraphicsPictureBoxFactory.h"
#include"../Common/GraphicsFactory/GraphicsLabelFactory.h"

#include"../Utility/JsonUtility/JsonUtility.h"
#include"../Globe/Enum.h"
#include<QColor>

using namespace::Common;
using namespace::Utility;
using namespace::GraphicsModule;
namespace Entity {
	class GraphicsItemInfoConfig
	{
	public:
		GraphicsItemInfoConfig(QString fonfigfilepath);
		GraphicsItemInfoConfig(QJsonObject jsondoc);

		GraphicsFactory* GetConfigFactory();

	private:
		GraphicsFactory* GenerateControlFactory(QString controlInfoStr);
		QString m_itemconfigstr;
		GraphicsFactory* factory{ nullptr };

	};
}