#pragma once
#include<QPainter>
#include<QGraphicsitem>
#include<QGraphicsView>
#include<QGraphicsSceneMouseEvent>
#include<QFont>
#include<QMutex>
#include <QTimer>
#include<QMutexLocker>
#include<QObject>
namespace GraphicsModule
{
	class GraphicsTip :public QGraphicsItem
	{
	public:
		static void showTips(QGraphicsView *view,QString tip);  // 获取单例实例的静态方法  
	protected:
		// QGraphicsItem的必须重写函数  
		QRectF boundingRect() const override;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	
	private:
		QTimer timer{};  // 定时器
		inline static GraphicsTip* instancePtr{nullptr};  // 指向单例实例的指针  
		QRectF rect;
		GraphicsTip();
		QString tip;
	};
}