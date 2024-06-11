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

            // ������Ӧ
            QString responseResult;
			QVariant result;
			if (arg.count() == 2)
			{
                QNetworkAccessManager manager;
				QString url = gncb->VarTypeSolved(arg[0]).toString();

               
                QString data= gncb->VarTypeSolved(arg[1]).toString();

				QString jsonData = data;
                // ����POST����
                QNetworkRequest request;
                request.setUrl(QUrl(url));
                request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                // ����POST����
                QNetworkReply* reply = manager.post(request, jsonData.toUtf8());
                // �¼�ѭ�����ȴ��������
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
                // �ͷ���Դ
                reply->deleteLater();
			
			}
            result = responseResult;
			return result;
		}
	};
	


}