#pragma once

#include "../../../Entity/GraphicsNodeControlBlock.h"
typedef Entity::GraphicsNodeControlBlock GNCB;
namespace ScriptModule
{
	/// <summary>
	/// ÊýÑ§¿â
	/// </summary>
	class MathFunction
	{
	public:
        inline static QVariant Add(const QStringList& arg, GNCB* gncb)
		{
			QVariant result;
			if (arg.count() == 2)
			{
				result = gncb->ArithmeticExpression(arg[0]+"+"+arg[1]);
			}
			return result;
		}

		inline static QVariant Sub(const QStringList& arg, GNCB* gncb)
		{
			QVariant result;
			if (arg.count() == 2)
			{
				result = gncb->ArithmeticExpression(arg[0] + "-" + arg[1]);
			}
			return result;
		}

	};
}
