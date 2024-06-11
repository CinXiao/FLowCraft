#include "JsonUtility.h"
namespace Utility {

	QString JsonUtility::GetJsonStringFromFile(const QString& filePath)
	{
		{
			QFile file(filePath);
			if (!file.exists())
				return "";
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
				return QString();
			}
			QTextStream in(&file);
			QString jsonString = in.readAll();
			file.close();
			return jsonString;
		}
	}

	QString JsonUtility::GetJsonStringByProperty(const QString& jsonString, const QString& PropertyName)
	{
		QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
		if (doc.isNull()) {
			return QString();
		}
		QJsonObject jsonObject = doc.object();
		if (!jsonObject.contains(PropertyName)) {
			return QString();
		}
		QJsonObject obj = jsonObject[PropertyName].toObject();
		return QJsonDocument(obj).toJson(); // 将数组转换为格式化的JSON字符串  
	}

	QJsonArray JsonUtility::GetArrayByProperty(const QString& jsonString, const QString& PropertyName)
	{

		// 解析 JSON 字符串  
		QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
		if (doc.isNull()) {
			// 处理无效的 JSON 字符串  
			return QJsonArray();
		}
		// 获取顶层对象  
		QJsonObject jsonObject = doc.object();
		// 检查对象是否包含指定的数组属性  
		if (!jsonObject.contains(PropertyName)) {
			// 处理找不到指定属性的情况  
			return QJsonArray();
		}
		if (!jsonObject[PropertyName].isArray()) {
			// 不是json数组
			return QJsonArray();
		}

		return jsonObject[PropertyName].toArray();
	}

	QJsonValue JsonUtility::GetJsonValue(const QString& jsonString, const QString& arrayPropertyName)
	{

		// 解析 JSON 字符串  
		QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
		if (doc.isNull()) {
			// 处理无效的 JSON 字符串  
			return QJsonValue();
		}
		// 获取顶层对象  
		QJsonObject jsonObject = doc.object();
		// 检查对象是否包含指定的数组属性  
		if (!jsonObject.contains(arrayPropertyName)) {
			// 处理找不到指定属性的情况  
			return QJsonValue();
		}
		return jsonObject[arrayPropertyName];
	}

	QRectF JsonUtility::GetRectFromJson(const QString& jsonString, const QString& ColorPropertyName)
	{
		QJsonArray arr = GetJsonValue(jsonString, ColorPropertyName).toArray();
		if (arr.size() != 4)
		{
			return QRectF();
		}
		return QRectF(arr[0].toDouble(), arr[1].toDouble(), arr[2].toDouble(), arr[3].toDouble());
	}



	QColor JsonUtility::GetColorFromJson(const QString& jsonString, const QString& ColorPropertyName)
	{
		//16进制颜色
		QString colorstr = GetJsonValue(jsonString, ColorPropertyName).toString();
		if (colorstr.isEmpty())
			return QColor(Qt::black);

		return QColor(colorstr);
	}

	bool JsonUtility::JsonStringHasProperty(const QString& jsonString, const QString& propertyName)
	{
		// 将 JSON 字符串解析成 QJsonDocument
		QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());

		// 检查 JSON 文档是否为对象
		if (!jsonDocument.isObject()) {
			qDebug() << "JSON字符串不是一个有效的JSON对象";
			return false;
		}

		// 获取根对象
		QJsonObject rootObject = jsonDocument.object();
		// 检查属性是否存在
        if (rootObject.contains(propertyName)) {
			return true;
		}
        else {
			return false;
		}
	}

	void JsonUtility::saveToJson(const QJsonDocument& jsonDocument, QString path)
	{
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			qDebug() << "Could not open file for writing:" << file.errorString();
			return;
		}
		file.write(jsonDocument.toJson());
		file.close();
   
	}

}
