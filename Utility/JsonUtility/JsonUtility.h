#pragma once
#include <QJsonDocument>  
#include <QJsonObject>  
#include <QJsonArray>  
#include <QJsonValue>  
#include <QDebug>
#include<QString>
#include<Qfile>
#include<QColor>
#include<QRectF>
namespace Utility {
	class JsonUtility
	{
	public:
		//从文件中获取json字符串
		static QString GetJsonStringFromFile(const QString& filePath);
		//获取json指定属性的json字符串
		static QString GetJsonStringByProperty(const QString& jsonString, const QString& PropertyName);
		//获取json指定属性的json数组
		static QJsonArray GetArrayByProperty(const QString& jsonString, const QString& PropertyName);
		//获取json字符串指定属性的值
		static QJsonValue GetJsonValue(const QString& jsonString, const QString& ColorPropertyName);
		//通过属性获取QRectF
		static QRectF GetRectFromJson(const QString& jsonString, const QString& ColorPropertyName);

		//通过属性名获取颜色
		static QColor GetColorFromJson(const QString& jsonString, const QString& PropertyName);
		// 判断json字符串存不存在某个属性
		static bool JsonStringHasProperty(const QString& jsonString, const QString& propertyName);
	
		//把json文件保存到指定路径
		static void  saveToJson(const QJsonDocument& jsonDocument, QString path);

	
	};
}