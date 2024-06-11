#pragma once
#include<qrandom.h>
#include"ItemInfo.h"
#include"../../Globe/Enum.h"
#include"../../Globe/Map.h"
using namespace Globe;

namespace GraphicsModule {



	class PortInfo :public ItemInfo
	{
	public:
		PortInfo(PortType portType, PortDataType portDataType);

		void Update();
		PortInfo();
		PortType portType{ PortType::DataInput };
		PortDataType portDataType{ PortDataType::Int };
		unsigned portIndex{ 0 };
		bool IsConnection{ false };
		bool IsActive{ true };
		unsigned portNumber;
		

	};
}