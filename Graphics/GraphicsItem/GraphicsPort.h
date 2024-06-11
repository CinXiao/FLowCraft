#pragma once
#include <QPainter>
#include <QGraphicsObject>
#include<QPainter>
#include<QMutexLocker>
#include"GraphicsItem.h"
#include"../Info/PortInfo.h"
namespace GraphicsModule {

	class GraphicsPort : public GraphicsItem
	{
	public:
		GraphicsPort(PortInfo info);
		~GraphicsPort();

		QRectF boundingRect() const;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
		PortInfo& GetPortInfo();
		void SetPortText(const QString& text);
		QString GetPortText() const;
	private:
		QString PortText{ "" };
		PortInfo m_PortInfo;
		// 创建一个互斥锁来保护PortText  
		mutable QMutex portTextMutex;
	};
}