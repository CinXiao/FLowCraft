#pragma once
#include"Enum.h"
#include"DataType.h"
#include<QString>
#include<QVariant>
namespace Globe {
	class PortAssignor
	{
	public:
		static QString PortValueParsing(PortDataType dataType, QVariant var);

	};
}