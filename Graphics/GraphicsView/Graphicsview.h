#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QMenu>
#include<QtTypes>
#include<QPainter>
#include <QAction>
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include<QMap>
#include<QDebug>
#include<QMimeData>
#include<QMediaPlayer>

#include"../../Globe/AudioPlayer.h"
#include"../GraphicsItem/GraphicsPort.h"
#include "../Entity/RubberEntity.h"
#include"../../Globe/GraphicsItemCreator.h"
#include"../../Globe/GraphicsItemManager.h"
#include"../../Globe/BuiltRunManager.h"
#include"../GraphicsItem/GraphicsText.h"
#include"../GraphicsItem/GraphicsTip.h"
namespace GraphicsModule {
	class GraphicsItemProperty
	{
	public:
		QList<QGraphicsItem*> children;
		QGraphicsItem* ParentItem{ nullptr };
		QGraphicsItem* SelectItem{ nullptr };
		GNCB gncb;
	};


	class GraphicsView : public QGraphicsView
	{
		Q_OBJECT
	public:
		GraphicsView();
		~GraphicsView();
		void scaleView(qreal scaleFactor);

		void wheelEvent(QWheelEvent* event)override;
		void mouseMoveEvent(QMouseEvent* event)override;
		void mousePressEvent(QMouseEvent* event)override;
		void mouseReleaseEvent(QMouseEvent* event)override;
		void keyReleaseEvent(QKeyEvent* event) override;
		void contextMenuEvent(QContextMenuEvent* event)override;

		void dragEnterEvent(QDragEnterEvent* event) override;
		void dragMoveEvent(QDragMoveEvent* event)override;
		void dragLeaveEvent(QDragLeaveEvent* event)override;

		//背景重绘
		void drawBackground(QPainter* painter, const QRectF& rect) override;
		//运行和停止
		void RunOrStop();
		//运行一次
		void RunOnce();

		//当前选中的工具
		ToolType Tool{ Select };

		//预览框列表
		QList<RubberEntity*> RubberList;
		//图元创建器
		GraphicsItemCreator* ItemCreator{ nullptr };
		//图元管理器
		GraphicsItemManager* Manager{ nullptr };
		//运行管理器
		BuiltRunManager* builter{ nullptr };


	signals:
		void SelectItem(GraphicsItemProperty ProPerty);
		void DeleteItem();

	private:
		QPointF MousePressPos;
		QPointF MouseReleasePos;
		QPointF MouseMovePos;
		QPointF MouseDragMovePos;
		const QMimeData* DragData;//拖入的数据

		bool IsDragPreview{ false };//拖动预览标识
		bool IsPortConnection{ false };//端口连接标识
		bool IsDragItem{ false };//拖放节点进入场景
		bool IsLeftButtonPress{ false };//按下左键


		QGraphicsItem* PreCreatitem{ nullptr };//预创建的图元
		QGraphicsItem* PreViewPreCreatitem{ nullptr };//预创建的图元的预览

		GraphicsPort* SelectPort{ nullptr };//选中的端口
		GraphicsLineItemBeziercurveitem* PreLine{ nullptr };//连接时的预览线


	};

}

#endif // GRAPHICSVIEW_H
