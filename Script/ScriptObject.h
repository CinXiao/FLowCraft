#pragma once
#include<QString>

namespace ScriptModule
{
	class ScriptObject
	{
	public:
		ScriptObject(QString Path);
		ScriptObject();
		//脚本路径
		QString ScriptPath{};
		//脚本
		QString Script;

	};
}