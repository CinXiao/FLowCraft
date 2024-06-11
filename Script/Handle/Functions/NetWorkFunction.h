#pragma once

#include "../../../Entity/GraphicsNodeControlBlock.h"
#include <qnetworkrequest.h>
#include <QNetworkReply>
typedef Entity::GraphicsNodeControlBlock GNCB;
namespace ScriptModule
{
	class NetWorkFunction
	{


	public:
		inline static QVariant SendPostRequest(const QStringList& arg, GNCB* gncb)
		{

            // 处理响应
            QString responseResult;
			QVariant result;
			if (arg.count() == 2)
			{
                QNetworkAccessManager manager;
				QString url = gncb->VarTypeSolved(arg[0]).toString();

               
                QString data= gncb->VarTypeSolved(arg[1]).toString();

				QString jsonData = data;
                // 创建POST请求
                QNetworkRequest request;
                request.setUrl(QUrl(url));
                request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                // 发送POST请求
                QNetworkReply* reply = manager.post(request, jsonData.toUtf8());
                // 事件循环，等待请求完成
                QEventLoop loop;
                QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
                loop.exec();
                if (reply->error() == QNetworkReply::NoError) {
                    QByteArray responseData = reply->readAll();
                    responseResult = QString::fromUtf8(responseData);
               
                }
                else {
                    responseResult = "Error:" + reply->errorString();
                }
                // 释放资源
                reply->deleteLater();
			
			}
            result = responseResult;
			return result;
		}
	};
	


}