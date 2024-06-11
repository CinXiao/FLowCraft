#include "PortAssignor.h"

namespace Globe {
	QString PortAssignor::PortValueParsing(PortDataType dataType, QVariant var)
	{
		QString result{ "NULL" };
		switch (dataType)
		{
		case Globe::Int:
			result = QString::number(var.toInt());
			break;
		case Globe::Float:
			result = QString::number(var.toDouble());
			break;
		case Globe::Bool:
			result = QString::number(var.toDouble());
			break;
		case Globe::String:
			result = var.toString();
			break;
		case Globe::Vector:
		{
			QList<float> dat = var.value<Vector_Type>().data;
			result = "Vec" + QString::number(dat.count());
		}break;
		case Globe::Matrix:
		{
			Matrix_Type Matrixdat = var.value<Matrix_Type>();
			if (Matrixdat.data.count() > 0)
			{
				if (Matrixdat.data[0].data.count() > 0)
				{
					result = "Mat" + QString::number(Matrixdat.data.count())
						+ "*"
						+ QString::number(Matrixdat.data[0].data.count());
				}
			}



		}
		break;
		default: result = var.toString();
			break;
		}

		return result;
	}
}
