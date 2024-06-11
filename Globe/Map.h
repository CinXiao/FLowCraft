#pragma once
#include"../Utility/JsonUtility/JsonUtility.h"
#include"RuningConfig.h"
#include"DataType.h"
#include"Enum.h"
#include<QString>
#include<QColor>
#include<qimage.h>
#include<qfile.h>
#include <QVariant>
using namespace::Utility;
namespace Globe {

	class Map
	{
	public:
		inline  static QString PortTypeJson{};
		inline  static QString PortDataTypeJson{};

		//端口类型颜色表
		inline static QMap<PortType, QColor> PortTypeColorMap{};
		//端口数据类型颜色表
		inline static QMap<PortDataType, QColor> PortDataTypeColorMap{};

		//图元类型枚举和字符串表
		inline static QMap<GraphicsItemType, QString> GraphicsItemTypeNameMap{};

		inline static QMap<GraphicsItemType, QString> GraphicsItemTypeNameMapChinese{};

		//端口类型枚举和字符串表
		inline static QMap<PortType, QString> PortTypeNameMap{};
		inline static QMap<PortType, QString> PortTypeNameMapChinese{};

		inline static QMap<PortDataType, QString> PortDataTypeNameMap{};
		inline static QMap<PortDataType, QString> PortDataTypeNameMapChinese{};

		inline static QMap<ChartType, QString> ChartTypeNameMap{};

		//端口数据类型和真实数据类型表
		inline static QMap<PortDataType, QVariant> PortDataTypeMap{};

		//音乐和音乐路径表
		inline static QMap<AudioType, QString>AudioMap{};

		//控件和控件icon路径表
		inline static QMap<GraphicsItemType, QString>ItemTypeIconMap{};

	};



	static void initGlobeMap()
	{

		//注册数据类型
		qRegisterMetaType<Vector_Type>();
		qRegisterMetaType<Matrix_Type>();

		//读取端口类型颜色配置Json数据
		Map::PortTypeJson = JsonUtility::GetJsonStringByProperty(
			JsonUtility::GetJsonStringFromFile(RuningConfig::PortColorConfigFilePath),
			"PortTypeColor");
		//读取端口数据类型颜色Json配置数据
		Map::PortDataTypeJson = JsonUtility::GetJsonStringByProperty(
			JsonUtility::GetJsonStringFromFile(RuningConfig::PortColorConfigFilePath),
			"PortDataTypeColor");

		//设置端口类型颜色表
		Map::PortTypeColorMap = {
			{DataInput,JsonUtility::GetColorFromJson(Map::PortTypeJson,"DataInput")},
			{DataOutput,JsonUtility::GetColorFromJson(Map::PortTypeJson,"DataOutput")},
			{ProgramControlInput,JsonUtility::GetColorFromJson(Map::PortTypeJson,"ProgramControlInput")},
			{ProgramControlOutput,JsonUtility::GetColorFromJson(Map::PortTypeJson,"ProgramControlOutput")},
			{TriggerInput,JsonUtility::GetColorFromJson(Map::PortTypeJson,"TriggerInput")},
			{TriggerOutput,JsonUtility::GetColorFromJson(Map::PortTypeJson,"TriggerOutput")},
		};

		//设置端口数据类型颜色表
		Map::PortDataTypeColorMap = {
			{Int,JsonUtility::GetColorFromJson(Map::PortDataTypeJson,"Int")},
			{Float,JsonUtility::GetColorFromJson(Map::PortDataTypeJson,"Float")},
			{Bool,JsonUtility::GetColorFromJson(Map::PortDataTypeJson,"Bool")},
			{String,JsonUtility::GetColorFromJson(Map::PortDataTypeJson,"String")},
			{Bit,JsonUtility::GetColorFromJson(Map::PortDataTypeJson,"Bit")},
			{Vector,JsonUtility::GetColorFromJson(Map::PortDataTypeJson,"Vector")},
			{Matrix,JsonUtility::GetColorFromJson(Map::PortDataTypeJson,"Matrix")},
		};
		//图表类型字符串表
		Map::ChartTypeNameMap = {
			{ChartType::SquareWave,"SquareWave"},
			{ChartType::Straight,"Discounted"},
			{ChartType::BesselCurve,"BesselCurve"},
			{ChartType::ColumnChart,"ColumnChart"},
			{ChartType::PieChart,"PieChart"},
		};


		//设置图元类型名称表
		Map::GraphicsItemTypeNameMap = {
		{Null,"Null"},
		{Start,"Start"},
		{Node,"Node"},
		{Chart,"Chart"},
		{Button,"Button"},
		{SwitchButton,"SwitchButton"},
		{Text,"Text"},
		{Line,"Line"},
		{Group,"Group"},
		{Port,"Port"},
		{PictureBox,"PictureBox" },
		{Label,"Label" }
		};
		Map::GraphicsItemTypeNameMapChinese =
		{
		{Null,"未知"},
		{Start,"开始节点"},
		{Node,"节点"},
		{Chart,"图表"},
		{Button,"按钮"},
		{SwitchButton,"开关"},
		{Text,"文本输入框"},
		{Line,"线"},
		{Group,"组"},
		{Port,"端口"},
		{PictureBox,"图片" },
		{Label,"标签" }
		};
		//端口类型名字表
		Map::PortTypeNameMap = {
			{PortType::DataInput,"DataInput"},
			{PortType::DataOutput,"DataOutput"},
			{PortType::ProgramControlInput,"ProgramControlInput"},
			{PortType::ProgramControlOutput,"ProgramControlOutput"},
			{PortType::TriggerInput,"TriggerInput"},
			{PortType::TriggerOutput,"TriggerOutput"},
		};
		Map::PortTypeNameMapChinese = {
			{PortType::DataInput,"数据输入端口"},
			{PortType::DataOutput,"数据输出端口"},
			{PortType::ProgramControlInput,"程序流输入"},
			{PortType::ProgramControlOutput,"程序流输出"},
			{PortType::TriggerInput,"触发器输入"},
			{PortType::TriggerOutput,"触发器输出"},

		};


		//端口数据类型名称表
		Map::PortDataTypeNameMap = {
			{Int,"Int"},
			{Float,"Float"},
			{Bool,"Bool"},
			{String,"String"},
			{Bit,"Bit"},
			{Vector,"Vector"},
			{Matrix,"Matrix"}
		};
		//端口数据类型中文名称表
		Map::PortDataTypeNameMapChinese = {
			{Int,"整数"},
			{Float,"小数"},
			{Bool,"布尔值"},
			{String,"字符串"},
			{Bit,"比特位"},
			{Vector,"向量"},
			{Matrix,"矩阵"}

		};

		//端口数据类型和真实数据类型表
		//QVariant 
		Map::PortDataTypeMap = {
			{Int,QVariant(QVariant::Int)},
			{Float,QVariant(QVariant::Double)},
			{Bool,QVariant(QVariant::Bool)},
			{String,QVariant(QVariant::String)},
			{Vector,QVariant::fromValue(Vector_Type())},
			{Matrix,QVariant::fromValue(Matrix_Type())}
		};

		//音频文件表
		Map::AudioMap = {
			{Built,"qrc:/NodeData/music/built.mp3"},
			{Delete,"qrc:/NodeData/music/delete.mp3"},
			{Connect,"qrc:/NodeData/music/connect.mp3"},
			{Run,"qrc:/NodeData/music/run.mp3"}
		};

		//控件和控件icon路径表
		Map::ItemTypeIconMap = {
			{Null,"Null"},
			{Start,"Start"},
			{Node,":/NodeData/icon/node.png"},
			{Chart,":/NodeData/icon/chart.png"},
			{Button,":/NodeData/icon/button.png"},
			{SwitchButton,":/NodeData/icon/switch.png"},
			{Text,"Text"},
			{Line,"Line"},
			{Group,"Group"},
			{Port,":/NodeData/icon/port.png"},
			{PictureBox,":/NodeData/icon/picturebox.png" },
			{Label,":/NodeData/icon/label.png" }
		};



	}
}
