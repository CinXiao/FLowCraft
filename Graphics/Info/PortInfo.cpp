#include "PortInfo.h"
namespace GraphicsModule {
	//端口编号表

	PortInfo::PortInfo(PortType portType, PortDataType portDataType) :
		portType(portType), portDataType(portDataType)
	{
		GraphicsItemType = GraphicsItemType::Port;
		static unsigned portnumbercounter = 0;
		portNumber = portnumbercounter++;
		Update();
	}

	void PortInfo::Update()
	{
		//如果是数据端口，要设置成对应数据端口的颜色
		if (portType == PortType::DataInput || portType == PortType::DataOutput)
		{
			normalBorder = QPen(Map::PortDataTypeColorMap[portDataType], 3);
		}
		else
		{
			//如果是其他端口，要设置成对应端口的颜色
			normalBorder = QPen(Map::PortTypeColorMap[portType], 3);
		}

	}

	PortInfo::PortInfo()
	{
	}

}