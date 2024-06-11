#include "graphicsview.h"
#include "../../Globe/Loader.h"


namespace GraphicsModule {

	GraphicsView::GraphicsView()
	{
		// 设置框选模式
		setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);

		setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing
			| QPainter::LosslessImageRendering);
		setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

		//设置缓冲背景，加速渲染
		setCacheMode(QGraphicsView::CacheBackground);

		setDragMode(QGraphicsView::ScrollHandDrag);

		// 启用框选功能
		setDragMode(QGraphicsView::RubberBandDrag);

		//设置接受拖放
		setAcceptDrops(true);

		//初始化场景
		QGraphicsScene* scene = new QGraphicsScene();

		scene->setBackgroundBrush(RuningConfig::gridBackColor);

		setScene(scene);

		//添加预览线
		PreLine = new GraphicsLineItemBeziercurveitem();
		scene->addItem(PreLine);
		PreLine->setVisible(false);

		//实例化图元创建器
		ItemCreator = GraphicsItemCreator::getInstance();
		//初始化图元管理器
		Manager = new GraphicsItemManager(this);
		//初始化运行管理器
		builter = new BuiltRunManager();

		//加载器加载场景
		Loader::LoadView(this);
	}

	GraphicsView::~GraphicsView()
	{
		//图元管理器
		delete Manager;
		delete builter;
	}


	void GraphicsView::wheelEvent(QWheelEvent* event)
	{
		QGraphicsView::wheelEvent(event);
	}

	void GraphicsView::mouseMoveEvent(QMouseEvent* event)
	{
		if (Tool == DeleteLine && IsLeftButtonPress)
		{
			if (RuningConfig::IsRuning)
			{
				GraphicsTip::showTips(this, "运行过程中禁止删除连接线");
				return;
			}
			GraphicsLineItem* selectedItem = dynamic_cast<GraphicsLineItem*>(itemAt(event->pos()));
			if (selectedItem)
			{

				Manager->RemoveLine(selectedItem);
				AudioPlayer::Play(AudioType::Delete);
			}
			return;
		}
		else if (Tool == DeleteNode && IsLeftButtonPress)
		{
			if (RuningConfig::IsRuning)
			{
				GraphicsTip::showTips(this, "运行过程中禁止删除节点!");
				return;
			}
			GraphicsNode* selectedItem = dynamic_cast<GraphicsNode*>(itemAt(event->pos()));
			if (selectedItem)
			{
				Manager->RemoveNode(selectedItem);
				AudioPlayer::Play(AudioType::Delete);
			}
			return;
		}

		//拖动预览模式下
		if (IsDragPreview)
		{
			//偏移量
			QPointF offset = mapToScene(event->pos()) - MouseMovePos;
			//调整预览图元位置
			for (RubberEntity* rubber : RubberList)
			{
				rubber->Adjust(offset);
			}
		}
		//端口连接模式下
		else if (IsPortConnection)
		{
			PreLine->SetFinishPos(mapToScene(event->pos()));
		}




		MouseMovePos = mapToScene(event->pos());
		QGraphicsView::mouseMoveEvent(event);
	}

	void GraphicsView::mousePressEvent(QMouseEvent* event)
	{

		QGraphicsView::mousePressEvent(event);
		if (event->button() == Qt::LeftButton)
		{
			IsLeftButtonPress = true;
		}

		if (Tool == Select)
		{
			setDragMode(QGraphicsView::RubberBandDrag);
		}
		else
		{
			setDragMode(QGraphicsView::NoDrag);
			return;
		}

		//记录鼠标点击位置场景坐标
		MousePressPos = mapToScene(event->pos());
		//记录鼠标移动的开始点，点击以后鼠标移动的点也更新
		MouseMovePos = mapToScene(event->pos());

		//鼠标点击位置图元
		QGraphicsItem* selectedItem = itemAt(event->pos());

		//如果图元存在
		if (selectedItem != nullptr)
		{
			selectedItem->setSelected(true);
			GraphicsPort* port = dynamic_cast<GraphicsPort*>(selectedItem);
			GraphicsText* input = dynamic_cast<GraphicsText*>(selectedItem);

			//如果是端口
			if (port != nullptr)
			{
				IsPortConnection = true;
				SelectPort = port;
				PreLine->setVisible(true);
				PreLine->Info.LineColorPen.setColor(port->GetPortInfo().normalBorder.color());
				PreLine->UpdateLine(mapToScene(event->pos()), mapToScene(event->pos()));
			}
			else if (input != nullptr && input->parentItem() != nullptr)
			{
				input->setTextInteractionFlags(Qt::TextEditable);
				input->setFocus(Qt::OtherFocusReason);
				return;
			}

			GraphicsItemProperty property;
			//找到这个图元的最高父节点
			QGraphicsItem* parent = selectedItem;
			property.SelectItem = selectedItem;
			while (parent->parentItem())
			{
				parent = parent->parentItem();
			}
			property.ParentItem = parent;
			property.children = parent->childItems();
			//如果是GNCB添加GNCB信息
			for (auto gncb : Manager->GetGNCBList())
			{
				if (gncb.GetNode() == selectedItem)
				{
					property.gncb = gncb;
				}
			}
			//发出选中图元信息
			SelectItem(property);
		}
		if (scene()->selectedItems().count() >= 0 && selectedItem != nullptr && !IsPortConnection)
		{
			IsDragPreview = true;
			for (QGraphicsItem* item : scene()->selectedItems())
			{
				//排除线
				if (dynamic_cast<GraphicsLineItem*>(item) != nullptr)
					continue;
				//创建橡皮筋预览加入到列表
				RubberEntity* rubber = new RubberEntity(item);
				RubberList.append(rubber);
			}
		}


	}

	void GraphicsView::mouseReleaseEvent(QMouseEvent* event)
	{
		//记录鼠标释放的位置
		MouseReleasePos = mapToScene(event->pos());
		//拖动预览模式下
		if (IsDragPreview)
		{
			//遍历橡皮筋预览图元列表，让目标和预览框位置一致
			for (RubberEntity* rubber : RubberList)
			{
				rubber->AdjustTargetPos();
				//尝试更新节点(主要是与节点连接的线)
				Manager->UpdateNode(rubber->TargetItem);
				delete rubber;
			}
			//清空预览列表
			RubberList.clear();

		}
		//端口连接模式下
		else if (IsPortConnection)
		{
			PreLine->setVisible(false);
			if (RuningConfig::IsRuning)
			{
				GraphicsTip::showTips(this, "运行过程中禁止端口连接!");
				IsDragPreview = false;
				IsPortConnection = false;
				SelectPort = nullptr;
				return;
			}
			//鼠标位置图元

			QGraphicsItem* selectedItem = itemAt(event->pos());
			//如果图元存在
			if (selectedItem != nullptr)
			{
				selectedItem->setSelected(true);
				GraphicsPort* port = dynamic_cast<GraphicsPort*>(selectedItem);
				if (port != nullptr && SelectPort != nullptr)
				{
					//连接两个端口
					Manager->ConnectPort(SelectPort, port);
				}

			}


		}



		IsLeftButtonPress = false;
		IsDragPreview = false;
		IsPortConnection = false;
		SelectPort = nullptr;
		QGraphicsView::mouseReleaseEvent(event);
	}



	void GraphicsView::keyReleaseEvent(QKeyEvent* event)
	{

		if (event->key() == Qt::Key_Delete) {

			if (RuningConfig::IsRuning)
			{
				GraphicsTip::showTips(this, "运行过程中该操作被禁止!");
				return;
			}
			if (IsDragPreview || IsPortConnection)
			{
				GraphicsTip::showTips(this, "请勿在拖动或连线过程中删除节点!");
				return;
			}

			QList<QGraphicsItem*>selectItems;


			for (auto item : scene()->selectedItems())
			{
				GraphicsLineItem* line = dynamic_cast<GraphicsLineItem*>(item);
				if (line)
					continue;
				selectItems.append(item);
			}
			//有删除的东西才播放音效
			if (selectItems.count())
				AudioPlayer::Play(AudioType::Delete);
			for (auto item : selectItems)
			{
				GraphicsNode* node = dynamic_cast<GraphicsNode*>(item);
				if (node)
				{
					Manager->RemoveNode(node);
				}
				else
				{
					if (item)
						Manager->Remove(item);
				}
			}

		}
		emit DeleteItem();
		QGraphicsView::keyReleaseEvent(event);
	}

	void GraphicsView::contextMenuEvent(QContextMenuEvent* event)
	{

		event->accept();
	}

	void GraphicsView::dragEnterEvent(QDragEnterEvent* event)
	{

		scene()->clearSelection();
		IsDragItem = false;
		//如果是url,设置拖放图元标识
		DragData = event->mimeData();
		if (DragData->hasUrls())
		{
			IsDragItem = true;
			QString path = DragData->urls().at(0).toLocalFile();
			PreCreatitem = ItemCreator->CreatGraphicsItem(path);
			//预览,PreCreatitem有可能为空
			if (PreCreatitem)
			{
				PreViewPreCreatitem = new GraphicsPreviewItem(PreCreatitem->boundingRect());
				Manager->AddItem(PreViewPreCreatitem);
			}
		}


		QGraphicsView::dragEnterEvent(event);
	}

	void GraphicsView::dragMoveEvent(QDragMoveEvent* event)
	{
		MouseDragMovePos = event->posF();
		if (IsDragItem && PreViewPreCreatitem)
		{
			PreViewPreCreatitem->setPos(mapToScene(MouseDragMovePos.x(), MouseDragMovePos.y()));
			QGraphicsView::dragMoveEvent(event);
		}


	}

	void GraphicsView::dragLeaveEvent(QDragLeaveEvent* event)
	{
		if (IsDragItem && PreCreatitem != nullptr)
		{
			QPointF pos = mapToScene(MouseDragMovePos.x(), MouseDragMovePos.y());
			PreCreatitem->setPos(pos);
			Manager->AddItem(PreCreatitem);
			IsDragItem = false;
			Manager->Remove(PreViewPreCreatitem);
			PreViewPreCreatitem = nullptr;


			AudioPlayer::Play(AudioType::Built);
		}
		IsDragItem = false;
		QGraphicsView::dragLeaveEvent(event);
	}

	void GraphicsView::drawBackground(QPainter* painter, const QRectF& rect)
	{

		// 设置网格线的颜色和样式
		QPen pen(RuningConfig::gridColor, RuningConfig::gridWidth, Qt::DotLine);
		painter->setPen(pen);
		painter->setBrush(RuningConfig::gridBackColor);
		//先绘制背景保证背景颜色
		QGraphicsView::drawBackground(painter, rect);

		// 计算水平和垂直网格线的位置
		int gridSize = RuningConfig::gridSize; // 网格大小
		int left = rect.left();
		int right = rect.right();
		int top = rect.top();
		int bottom = rect.bottom();
		// 绘制水平网格线
		for (int y = top; y < bottom; y += gridSize) {
			painter->drawLine(QPointF(left, y), QPointF(right, y));
		}
		// 绘制垂直网格线
		for (int x = left; x < right; x += gridSize) {
			painter->drawLine(QPointF(x, top), QPointF(x, bottom));
		}
	}


	void GraphicsView::RunOrStop()
	{
		builter->SetGNCCB(this->Manager->GetGNCCB());
		if (RuningConfig::IsRuning)
		{
			builter->Stop();
		}
		else
		{
			builter->Run();
		}
	}

	void GraphicsView::RunOnce()
	{

		builter->SetGNCCB(this->Manager->GetGNCCB());
		builter->RunOnce();
	}


	void GraphicsView::scaleView(qreal scaleFactor)
	{
		scale(scaleFactor, scaleFactor);
	}

}
