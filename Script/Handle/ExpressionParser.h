#pragma once
#include "../../Entity/GraphicsNodeControlBlock.h"
typedef Entity::GraphicsNodeControlBlock GNCB;
namespace ScriptModule
{

	class ExpressionParser
	{
	public:
		ExpressionParser(QString exp, GNCB* gncb);
		QVariant parse();

		//������ͺ���������
         inline static QMap<QString, std::function<QVariant(const QStringList&, GNCB*)>>functionMap;
	private:
		GNCB* gncb{ nullptr };
		QString functionName{ "" };
		QStringList argumentList{};
	};


}
