#pragma once
namespace Globe {

	//端口类型
	enum PortType
	{
		DataInput,
		DataOutput,
		TriggerInput,
		TriggerOutput,
		ProgramControlInput,
		ProgramControlOutput
	};
	//图表类型
	enum  ChartType {
		SquareWave,//方波
		Straight,//正常直线折现
		BesselCurve,//贝塞尔曲线
		ColumnChart,//柱形图
		PieChart//饼图
	};

	//线类型
	enum  LineType {
		StraightLine,//直线
		BezierLine,//贝塞尔
		Polyline,//折线
	};


	//端口数据类型
	enum PortDataType
	{
		Int,
		Float,
		Bool,
		String,
		Bit,
		Vector,
		Matrix

	};

	//图元类型
	enum GraphicsItemType {
		Null,
		Start,
		Node,
		Chart,
		Button,
		SwitchButton,
		Text,
		Line,
		Group,
		Port,
		PictureBox,
		Label,

	};

	//错误码
	enum ErrorCode
	{


	};

	//工具枚举
	enum ToolType
	{
		Select,
		DeleteLine,
		DeleteNode
	};

	//音频枚举
	enum AudioType
	{
		Built,
		Delete,
		Connect,
		Run,
	};
}