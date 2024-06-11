#include "GraphicsItemInfoConfig.h"
namespace Entity {

	GraphicsItemInfoConfig::GraphicsItemInfoConfig(QString fonfigfilepath)
	{
		QFile file(fonfigfilepath);
		if (file.exists())
			//打开对应的json文件，获取json数据
			m_itemconfigstr = JsonUtility::GetJsonStringFromFile(fonfigfilepath);
	}

	GraphicsItemInfoConfig::GraphicsItemInfoConfig(QJsonObject jsondoc)
	{
		QJsonDocument jsonDoc(jsondoc);
		m_itemconfigstr = jsonDoc.toJson();

	}

	GraphicsFactory* GraphicsItemInfoConfig::GetConfigFactory()
	{
		if (m_itemconfigstr.isEmpty())return nullptr;
		//获取主控件,生成主工厂
		QString maincontrol = JsonUtility::GetJsonStringByProperty(m_itemconfigstr, "mainControl");
		factory = GenerateControlFactory(maincontrol);
		//获取子控件信息,得到子工厂
		QList<GraphicsFactory*>controlsFactory;
		QJsonArray controls = JsonUtility::GetArrayByProperty(m_itemconfigstr, "controls");
		for (QJsonValue control : controls)
		{
			GraphicsFactory* f{ nullptr };
			f = GenerateControlFactory(QJsonDocument(control.toObject()).toJson());
			if (f)
				controlsFactory.append(f);
		}
		if (factory)
		{
			//设置工厂子工厂
			factory->SubFactory = controlsFactory;
			return factory;
		}
		return nullptr;
	}

	GraphicsFactory* GraphicsItemInfoConfig::GenerateControlFactory(QString controlInfoStr)
	{
		GraphicsFactory* factory{ nullptr };
		//获取控件类型信息
		GraphicsItemType controlType{ Null };
		if (JsonUtility::JsonStringHasProperty(controlInfoStr, "controlType"))
			controlType = Map::GraphicsItemTypeNameMap.key(JsonUtility::GetJsonValue(controlInfoStr, "controlType").toString());
		if (JsonUtility::JsonStringHasProperty(controlInfoStr, "type"))
			controlType = Map::GraphicsItemTypeNameMap.key(JsonUtility::GetJsonValue(controlInfoStr, "type").toString());
		QString controlInfo;
		if (JsonUtility::JsonStringHasProperty(controlInfoStr, "info"))
			controlInfo = JsonUtility::GetJsonStringByProperty(controlInfoStr, "info");

		//根据控件类型生成对应的工厂
		switch (controlType)
		{
		case Null:
			break;
		case Start:
		case Node:
		{
			//获取节点信息
			NodeInfo info;
			//设置节点类型
			info.GraphicsItemType = controlType;

			//设置脚本路径
			if (JsonUtility::JsonStringHasProperty(controlInfo, "scriptPath"))
				info.ScriptPath = RuningConfig::CurrentRuningPath + "/" + JsonUtility::GetJsonValue(controlInfo, "scriptPath").toString();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "script"))
				info.ScriptPath = RuningConfig::CurrentRuningPath + "/" + JsonUtility::GetJsonValue(controlInfo, "script").toString();

			//设置节点信息
			if (JsonUtility::JsonStringHasProperty(controlInfo, "x"))
				info.backgroundSize.setX(JsonUtility::GetJsonValue(controlInfo, "x").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "y"))
				info.backgroundSize.setY(JsonUtility::GetJsonValue(controlInfo, "y").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "w"))
				info.backgroundSize.setWidth(JsonUtility::GetJsonValue(controlInfo, "w").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "h"))
				info.backgroundSize.setHeight(JsonUtility::GetJsonValue(controlInfo, "h").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "width"))
				info.backgroundSize.setWidth(JsonUtility::GetJsonValue(controlInfo, "width").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "height"))
				info.backgroundSize.setHeight(JsonUtility::GetJsonValue(controlInfo, "height").toInt());


			if (JsonUtility::JsonStringHasProperty(controlInfo, "normalBorder"))
				info.normalBorder = JsonUtility::GetColorFromJson(controlInfo, "normalBorder");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "normalBrush"))
				info.normalBrush = JsonUtility::GetColorFromJson(controlInfo, "normalBrush");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "radius"))
				info.radius = JsonUtility::GetJsonValue(controlInfo, "radius").toInt();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "selectBorder"))
				info.selectBorder = JsonUtility::GetColorFromJson(controlInfo, "selectBorder");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "selectBrush"))
				info.selectBrush = JsonUtility::GetColorFromJson(controlInfo, "selectBrush");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backgroundSize"))
				info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "backgroundSize");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backgroundColor1"))
				info.backgroundColor1 = JsonUtility::GetColorFromJson(controlInfo, "backgroundColor1");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backgroundColor2"))
				info.backgroundColor2 = JsonUtility::GetColorFromJson(controlInfo, "backgroundColor2");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backgroundColorGradient"))
				info.backgroundColorGradient = JsonUtility::GetJsonValue(controlInfo, "backgroundColorGradient").toBool();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "nodeName"))
				info.nodeName = JsonUtility::GetJsonValue(controlInfo, "nodeName").toString();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "name"))
				info.nodeName = JsonUtility::GetJsonValue(controlInfo, "name").toString();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "node"))
				info.nodeName = JsonUtility::GetJsonValue(controlInfo, "node").toString();

			if (JsonUtility::JsonStringHasProperty(controlInfo, "titleBackgroundColor1"))
				info.titleBackgroundColor1 = JsonUtility::GetJsonValue(controlInfo, "titleBackgroundColor1").toString();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "titleColor1"))
				info.titleBackgroundColor1 = JsonUtility::GetJsonValue(controlInfo, "titleColor1").toString();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "titleBackgroundColor2"))
				info.titleBackgroundColor2 = JsonUtility::GetJsonValue(controlInfo, "titleBackgroundColor2").toString();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "titleColor2"))
				info.titleBackgroundColor2 = JsonUtility::GetJsonValue(controlInfo, "titleColor2").toString();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "titleBackgroundColorGradient"))
				info.titleBackgroundColorGradient = JsonUtility::GetJsonValue(controlInfo, "titleBackgroundColorGradient").toBool();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "titleSize"))
				info.titleSize = JsonUtility::GetRectFromJson(controlInfo, "titleSize");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "tx"))
				info.titleSize.setX(JsonUtility::GetJsonValue(controlInfo, "tx").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "ty"))
				info.titleSize.setY(JsonUtility::GetJsonValue(controlInfo, "ty").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "tw"))
				info.titleSize.setWidth(JsonUtility::GetJsonValue(controlInfo, "tw").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "th"))
				info.titleSize.setHeight(JsonUtility::GetJsonValue(controlInfo, "th").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "titleWidth"))
				info.titleSize.setWidth(JsonUtility::GetJsonValue(controlInfo, "titleWidth").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "titleHeight"))
				info.titleSize.setHeight(JsonUtility::GetJsonValue(controlInfo, "titleHeight").toInt());




			factory = new GraphicsNodeFactory(info);
		}
		break;
		case Port:
		{
			PortDataType datatype{ Int };
			PortType porttype{ DataInput };
			if (JsonUtility::JsonStringHasProperty(controlInfo, "portDataType"))
				datatype = Map::PortDataTypeNameMap.key(JsonUtility::GetJsonValue(controlInfo, "portDataType").toString());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "dataType"))
				datatype = Map::PortDataTypeNameMap.key(JsonUtility::GetJsonValue(controlInfo, "dataType").toString());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "portType"))
				porttype = Map::PortTypeNameMap.key(JsonUtility::GetJsonValue(controlInfo, "portType").toString());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "type"))
				porttype = Map::PortTypeNameMap.key(JsonUtility::GetJsonValue(controlInfo, "type").toString());

			PortInfo info(porttype, datatype);
			if (JsonUtility::JsonStringHasProperty(controlInfo, "portSize"))
				info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "portSize");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "size"))
				info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "size");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backgroundSize"))
				info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "backgroundSize");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backSize"))
				info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "backSize");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "x"))
				info.backgroundSize.setX(JsonUtility::GetJsonValue(controlInfo, "x").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "y"))
				info.backgroundSize.setY(JsonUtility::GetJsonValue(controlInfo, "y").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "w"))
				info.backgroundSize.setWidth(JsonUtility::GetJsonValue(controlInfo, "w").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "h"))
				info.backgroundSize.setHeight(JsonUtility::GetJsonValue(controlInfo, "h").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "width"))
				info.backgroundSize.setWidth(JsonUtility::GetJsonValue(controlInfo, "width").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "height"))
				info.backgroundSize.setHeight(JsonUtility::GetJsonValue(controlInfo, "height").toInt());

			if (JsonUtility::JsonStringHasProperty(controlInfo, "portIndex"))
				info.portIndex = JsonUtility::GetJsonValue(controlInfo, "portIndex").toInt();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "index"))
				info.portIndex = JsonUtility::GetJsonValue(controlInfo, "index").toInt();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "portNumber"))
				info.portNumber = JsonUtility::GetJsonValue(controlInfo, "portNumber").toInt();

			factory = new GraphicsPortFactory(info);
		}break;
		case Text:
		{
			TextInfo info;
			if (JsonUtility::JsonStringHasProperty(controlInfo, "inputSize"))
				info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "inputSize");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backgroundSize"))
				info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "backgroundSize");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "size"))
				info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "size");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backSize"))
				info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "backSize");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "text"))
				info.Text = JsonUtility::GetJsonValue(controlInfo, "text").toString();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "textColor"))
				info.TextColor = JsonUtility::GetColorFromJson(controlInfo, "textColor");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "color"))
				info.TextColor = JsonUtility::GetColorFromJson(controlInfo, "color");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backgroundColor"))
				info.BackgroundColor = JsonUtility::GetJsonValue(controlInfo, "backgroundColor").toString();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backColor"))
				info.BackgroundColor = JsonUtility::GetJsonValue(controlInfo, "backColor").toString();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "inputIndex"))
				info.index = JsonUtility::GetJsonValue(controlInfo, "inputIndex").toInt();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "index"))
				info.index = JsonUtility::GetJsonValue(controlInfo, "index").toInt();

			factory = new GraphicsTextFactory(info);
		}
		break;
		case Chart:
		{
			ChartInfo info;
			info.chatyType = Map::ChartTypeNameMap.key(JsonUtility::GetJsonValue(controlInfo, "chatyType").toString());
			info.RectSize = JsonUtility::GetRectFromJson(controlInfo, "chartSize");
			info.axisColor = JsonUtility::GetColorFromJson(controlInfo, "axisColor");
			info.lineColor = JsonUtility::GetColorFromJson(controlInfo, "lineColor");
			info.pointColor = JsonUtility::GetColorFromJson(controlInfo, "pointColor");
			info.drawLine = JsonUtility::GetJsonValue(controlInfo, "drawLine").toBool();
			info.drawPoint = JsonUtility::GetJsonValue(controlInfo, "drawPoint").toBool();
			info.chartIndex = JsonUtility::GetJsonValue(controlInfo, "chartIndex").toInt();
			factory = new GraphicsChartFactory(info);
		}
		break;
		case Button:
		{
			ButtonInfo info;
			info.buttonColor = JsonUtility::GetColorFromJson(controlInfo, "buttonColor");
			info.buttonPressColor = JsonUtility::GetColorFromJson(controlInfo, "buttonPressColor");
			info.buttonSize = JsonUtility::GetRectFromJson(controlInfo, "buttonSize");
			info.buttonText = JsonUtility::GetJsonValue(controlInfo, "buttonText").toString();
			info.buttonTextColor = JsonUtility::GetColorFromJson(controlInfo, "buttonTextColor");
			info.buttonTextPressColor = JsonUtility::GetColorFromJson(controlInfo, "buttonTextPressColor");
			info.buttonIndex = JsonUtility::GetJsonValue(controlInfo, "buttonIndex").toInt();
			factory = new GraphicsButtonFactory(info);
		}
		break;
		case SwitchButton:
		{
			SwitchButtonInfo info{};
			info.buttonColor = JsonUtility::GetColorFromJson(controlInfo, "buttonColor");
			info.buttonOpenColor = JsonUtility::GetColorFromJson(controlInfo, "buttonOpenColor");
			info.switchButtonSize = JsonUtility::GetRectFromJson(controlInfo, "switchButtonSize");
			info.switchColor = JsonUtility::GetColorFromJson(controlInfo, "switchColor");
			info.buttonIndex = JsonUtility::GetJsonValue(controlInfo, "buttonIndex").toInt();
			const QString textValue = JsonUtility::GetJsonValue(controlInfo, "text").toString();
			info.text = !textValue.isEmpty() ? textValue : "";
			factory = new GraphicsSwitchButtonFactory(info);
		}
		break;
		case PictureBox:
		{
			PictureBoxInfo info;
			info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "imageSize");
			info.imgPath = RuningConfig::CurrentRuningPath + JsonUtility::GetJsonValue(controlInfo, "imagePath").toString();
			info.imgSize = info.backgroundSize.size().toSize();
			factory = new GraphicsPictureBoxFactory(info);

		}break;
		case Label:
		{
			LabelInfo info;
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backgroundSize"))
				info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "backgroundSize");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "size"))
				info.backgroundSize = JsonUtility::GetRectFromJson(controlInfo, "size");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "x"))
				info.backgroundSize.setX(JsonUtility::GetJsonValue(controlInfo, "x").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "y"))
				info.backgroundSize.setY(JsonUtility::GetJsonValue(controlInfo, "y").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "w"))
				info.backgroundSize.setWidth(JsonUtility::GetJsonValue(controlInfo, "w").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "h"))
				info.backgroundSize.setHeight(JsonUtility::GetJsonValue(controlInfo, "h").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "width"))
				info.backgroundSize.setWidth(JsonUtility::GetJsonValue(controlInfo, "width").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "height"))
				info.backgroundSize.setHeight(JsonUtility::GetJsonValue(controlInfo, "height").toInt());
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backgroundColor"))
				info.BackgroundColor = JsonUtility::GetColorFromJson(controlInfo, "backgroundColor");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "backColor"))
				info.BackgroundColor = JsonUtility::GetColorFromJson(controlInfo, "backColor");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "textColor"))
				info.TextColor = JsonUtility::GetColorFromJson(controlInfo, "textColor");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "Color"))
				info.TextColor = JsonUtility::GetColorFromJson(controlInfo, "Color");
			if (JsonUtility::JsonStringHasProperty(controlInfo, "index"))
				info.index = JsonUtility::GetJsonValue(controlInfo, "index").toInt();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "text"))
				info.Text = JsonUtility::GetJsonValue(controlInfo, "text").toString();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "textSize"))
				info.textSize = JsonUtility::GetJsonValue(controlInfo, "textSize").toInt();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "bold"))
				info.isbold = JsonUtility::GetJsonValue(controlInfo, "bold").toBool();
			if (JsonUtility::JsonStringHasProperty(controlInfo, "radius"))
				info.radius = JsonUtility::GetJsonValue(controlInfo, "radius").toInt();

			factory = new GraphicsLabelFactory(info);
		}
		break;
		case Line:
		{

		}
		break;
		case Group:
		{

		}
		break;
		}

		return factory;
	}





}