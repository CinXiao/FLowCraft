#pragma once
#include<QString>
#include<QColor>

#include"../Utility/JsonUtility/JsonUtility.h"
#include"Enum.h"
using namespace::Utility;
namespace Globe {
	class RuningConfig
	{
	public:

		//项目路径
		inline static QString CurrentRuningPath{ "" };
		//主题文件名
		inline static QString ThemName{ "默认" };
		//端口颜色配置文件路径
		inline static QString PortColorConfigFilePath{ CurrentRuningPath + "/config/Them/" + ThemName + "/PortColorConfig.json" };
		//视图配置文件路径
		inline static QString GraphicsViewConfigFilePath{ CurrentRuningPath + "/config/Them/" + ThemName + "/GraphicsViewConfig.json" };

		inline static bool IsRuning{ false };//运行标识符
		inline static bool IsOnceRuning{ false };//单次运行标识符

		inline static int UnitStepDelay{ 400 };//时钟间隔
		inline static bool AudioAllowPlay{ true };//音效标识符

		inline static LineType lineType{ LineType::Polyline };//连接线样式

		inline static bool gridEnable{ true };//是否启用网格
		inline static int gridSize{ 20 };//视图网格大小
		inline static int gridWidth{ 1 };//视图网格线宽
		inline static QColor gridColor{ Qt::gray };//视图网格颜色
		inline static QColor gridBackColor{ Qt::darkGray };//视图背景颜色
		inline static bool showPropertyBrowser{true};//属性页显示

	};

	static void updateConfigfilePath()
	{
		RuningConfig::PortColorConfigFilePath = { RuningConfig::CurrentRuningPath + "/config/Them/" + RuningConfig::ThemName + "/PortColorConfig.json" };
		//视图配置文件路径
		RuningConfig::GraphicsViewConfigFilePath = { RuningConfig::CurrentRuningPath + "/config/Them/" + RuningConfig::ThemName + "/GraphicsViewConfig.json" };


	}

	static void InitRuningConfig()
	{
		QString BackgroundConfig = JsonUtility::GetJsonStringByProperty(
			JsonUtility::GetJsonStringFromFile(RuningConfig::GraphicsViewConfigFilePath),
			"BackgroundConfig");
		RuningConfig::gridEnable = JsonUtility::GetJsonValue(BackgroundConfig, "gridEnable").toBool();
		RuningConfig::gridSize = JsonUtility::GetJsonValue(BackgroundConfig, "gridSize").toInt();
		RuningConfig::gridWidth = JsonUtility::GetJsonValue(BackgroundConfig, "gridWidth").toInt();
		RuningConfig::gridColor = JsonUtility::GetColorFromJson(BackgroundConfig, "gridColor");
		RuningConfig::gridBackColor = JsonUtility::GetColorFromJson(BackgroundConfig, "backColor");
	}//初始化
}
