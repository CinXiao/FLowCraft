#include "MainWindow.h"
#include "ui_MainWindow.h"



MainWindow::MainWindow(QString projectPath, QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	//隐藏视图对象浏览器标签
	ui->GraphicsObjectTree->header()->hide();
	//隐藏设计文件浏览器标签
	ui->resourceTreeWidget->header()->hide();
	ui->test_nodelist->header()->hide();



	//初始化
	QFile file(projectPath);
	if (file.exists())
	{
		Globe::RuningConfig::CurrentRuningPath = projectPath;
		Globe::updateConfigfilePath();
		Globe::initGlobeMap();
		Globe::InitRuningConfig();
		file.close();
	}
	//###################测试页面

	if (ui->testcodeEdit)
	{
		ui->testcodeEdit->close();
		delete ui->testcodeEdit;
		ui->testcodeEdit = nullptr;
	}
	ui->testcodeEdit = new CodeEditor(ui->widget);
	ui->testcodeEdit->setObjectName("testcodeEdit");
	ui->gridLayout_7->addWidget(ui->testcodeEdit, 5, 0, 1, 1);
	XScriptHighlighter* testxsHightlight = new  XScriptHighlighter(ui->testcodeEdit->document());
	testnodetree = new NodeTreeWidget();
	if (ui->test_nodelist)
	{
		ui->test_nodelist->close();
		delete ui->test_nodelist;
		ui->test_nodelist = nullptr;
	}


	QGraphicsScene* Testscene = new  QGraphicsScene();
	Testscene->setBackgroundBrush(RuningConfig::gridBackColor);
	ui->testView->setScene(Testscene);

	testnodetree->populateTree(QDir(RuningConfig::CurrentRuningPath + "/nodes"));
	ui->test_nodelist = testnodetree;
	ui->test_nodelist->setObjectName("test_nodelist");
	ui->test_nodelist->setMaximumSize(QSize(200, 16777215));
	ui->test_nodelist->setMaximumSize(QSize(200, 16777215));
	ui->gridLayout_6->addWidget(ui->test_nodelist, 0, 0, 2, 1);
	connect(testnodetree, &NodeTreeWidget::itemClicked, [=](QTreeWidgetItem* item) {
		GraphicsItemCreator* creator = GraphicsItemCreator::getInstance();
		QString path = item->data(0, Qt::UserRole).toString();
		if (TestGraphicsItem != nullptr)
		{
			TestGraphicsItem->scene()->removeItem(TestGraphicsItem);
			delete TestGraphicsItem;
			TestGraphicsItem = nullptr;
		}
		TestGraphicsItem = creator->CreatGraphicsItem({ path });
		if (TestGraphicsItem != nullptr)
		{
			QPointF pos = ui->testView->rect().center() - TestGraphicsItem->boundingRect().center();
			TestGraphicsItem->setPos(ui->testView->mapToScene(pos.toPoint()));
			Testscene->addItem(TestGraphicsItem);
		}
		});

	//点击测试按钮
	connect(ui->pushButton, &QPushButton::clicked, [&]() {
		//构建控制块
		GraphicsNode* node = dynamic_cast<GraphicsNode*>(TestGraphicsItem);
		if (node)
		{
			RuningConfig::IsRuning = true;
			GraphicsItem* graphicsItem = dynamic_cast<GraphicsItem*>(node);
			//重新设置节点为开始节点
			graphicsItem->Info.GraphicsItemType = Start;
			GraphicsNodeControlBlock block(node);
			//添加测试代码
			if (ui->testcodeahead->isChecked())
				block.scriptObject.Script = ui->testcodeEdit->toPlainText() + "\n" + block.scriptObject.Script;
			else if (ui->testcodeback->isChecked())
				block.scriptObject.Script += "\n" + ui->testcodeEdit->toPlainText();
			else if (ui->onlytestcode->isChecked())
				block.scriptObject.Script = ui->testcodeEdit->toPlainText();
			block.Execute();
			block.Updata();
			RuningConfig::IsRuning = false;
		}



		});


	//##################设计器
		//设计器文本框编辑
	if (ui->designTextEdit)
	{
		ui->designTextEdit->close();
		delete ui->designTextEdit;
		ui->designTextEdit = nullptr;
	}
	ui->designTextEdit = new CodeEditor(ui->tab_2);
	ui->designTextEdit->setObjectName("designTextEdit");
	ui->gridLayout_4->addWidget(ui->designTextEdit, 1, 1, 1, 1);
	XScriptHighlighter* xsHightlight = new  XScriptHighlighter(ui->designTextEdit->document());

	//编辑器安装事件过滤器
	installEventFilter(this);


	//隐藏设计预览
	ui->designView->hide();
	ui->designView->setRenderHints(QPainter::Antialiasing
		| QPainter::SmoothPixmapTransform
		| QPainter::TextAntialiasing
		| QPainter::LosslessImageRendering);
	designViewscene = new  QGraphicsScene();
	designViewscene->setBackgroundBrush(RuningConfig::gridBackColor);
	ui->designView->setScene(designViewscene);
	//设计器文件浏览器
	if (ui->resourceTreeWidget)
	{
		ui->resourceTreeWidget->close();
		delete ui->resourceTreeWidget;
		ui->resourceTreeWidget = nullptr;
	}

	filetree = new NodeTreeWidget(ui->centralwidget);
	ui->resourceTreeWidget = filetree;
	ui->resourceTreeWidget->setObjectName("resourceTreeWidget");
	ui->resourceTreeWidget->setMinimumSize(QSize(250, 0));
	ui->resourceTreeWidget->setMaximumSize(QSize(250, 16777215));
	ui->gridLayout_4->addWidget(ui->resourceTreeWidget, 0, 0, 2, 1);
	filetree->populateTree(QDir(RuningConfig::CurrentRuningPath));
	//选择文件列表中的文件
	connect(filetree, &NodeTreeWidget::itemClicked, [=](QTreeWidgetItem* item) {
		//编辑器打开文件内容
		QString path = item->data(0, Qt::UserRole).toString();
		currentdesinFilePath = path;
		QFile file(path);
		if (file.exists())
		{

			file.open(QIODevice::ReadWrite);
			ui->designTextEdit->setPlainText(file.readAll());
			file.close();

		}
		//预览器加载节点（如果节点存在）
		GraphicsItemCreator* creator = GraphicsItemCreator::getInstance();
		if (designGraphicsItem != nullptr)
		{
			designGraphicsItem->scene()->removeItem(designGraphicsItem);
			delete designGraphicsItem;
			designGraphicsItem = nullptr;
		}
		designGraphicsItem = creator->CreatGraphicsItem({ path });
		if (designGraphicsItem != nullptr)
		{
			ui->designView->show();
			QPointF pos = ui->designView->rect().center() - designGraphicsItem->boundingRect().center();
			designGraphicsItem->setPos(ui->designView->mapToScene(pos.toPoint()));
			designViewscene->addItem(designGraphicsItem);
		}
		else
		{
			ui->designView->hide();
		}

		});
	//##################设计器



	//###############帮助页面







	//#####################主视图预览视图初始化
		/********************************/
	QGraphicsScene* scene = new  QGraphicsScene();
	scene->setBackgroundBrush(RuningConfig::gridBackColor);
	ui->preview->setScene(scene);

	//主视图节点属性页面初始化
	/********************************/
	PropertyBrowser = new QtTreePropertyBrowser();
	if (ui->PropertyBrowser)
	{
		ui->PropertyBrowser->close();
		delete ui->PropertyBrowser;
		ui->PropertyBrowser = nullptr;
	}
	ui->PropertyBrowser = PropertyBrowser;
	ui->PropertyBrowser->setObjectName("PropertyBrowser");
	ui->PropertyBrowser->setParent(ui->attribute);
	ui->gridLayout_2->addWidget(ui->PropertyBrowser, 1, 0, 1, 1);

	//初始化节点浏览器
	/********************************/
	nodetree = new NodeTreeWidget(ui->centralwidget);
	nodetree->setObjectName("nodeslist");
	nodetree->setMinimumSize(QSize(250, 0));
	nodetree->setMaximumSize(QSize(250, 16777215));
	ui->gridLayout_5->addWidget(nodetree, 1, 0, 1, 1);
	nodetree->populateTree(QDir(RuningConfig::CurrentRuningPath + "/nodes"));


	//初始化主视图页面
	/********************************/
	view = new GraphicsView();
	view->setRenderHints(QPainter::Antialiasing
		| QPainter::SmoothPixmapTransform
		| QPainter::TextAntialiasing
		| QPainter::LosslessImageRendering);
	ui->gridLayout_3->addWidget(view, 0, 1, 1, 1);

	//选中图元
	connect(view, &GraphicsView::SelectItem, [&](GraphicsItemProperty property)
		{
			//没有运行时
			if (!RuningConfig::IsRuning&& RuningConfig::showPropertyBrowser)
			{
				ui->attribute->show();
				if (currentSelectGraphicsItem == property.SelectItem)
					return;
				//生成
				objectTree = GeneratorObjectTreeBrowser(property);
				PropertyBrowser = GeneratorPropertyBrowser(dynamic_cast<GraphicsItem*>(property.SelectItem));
				updateObjectTreeBrowser(objectTree);
				updatePropertyBrowser(PropertyBrowser);
				currentSelectGraphicsItem = property.SelectItem;
			}

		});
	//删除图元
	connect(view, &GraphicsView::DeleteItem, [&]()
		{
			if (PropertyBrowser)
				PropertyBrowser->clear();
			if (objectTree)
				objectTree->clear();
		});





	//选择列表中的节点
	connect(nodetree, &NodeTreeWidget::itemClicked, [=](QTreeWidgetItem* item) {
		GraphicsItemCreator* creator = GraphicsItemCreator::getInstance();
		QString path = item->data(0, Qt::UserRole).toString();
		if (PreItem != nullptr)
		{
			PreItem->scene()->removeItem(PreItem);
			delete PreItem;
			PreItem = nullptr;
		}
		PreItem = creator->CreatGraphicsItem({ path });
		if (PreItem != nullptr)
		{
			QPointF pos = ui->preview->rect().center() - PreItem->boundingRect().center();
			PreItem->setPos(ui->preview->mapToScene(pos.toPoint()));
			scene->addItem(PreItem);
		}
		});

	//添加图标
	QToolButton* select = new QToolButton();
	select->setIcon(QIcon(":/NodeData/icon/select.png"));
	ui->toolBar->addWidget(select);
	connect(select, &QToolButton::clicked, [=]() {
		QPixmap cursorPixmap(":/NodeData/icon/select.png");
		cursorPixmap = cursorPixmap.scaled(32, 32);
		QCursor customCursor(cursorPixmap, 0, 0);
		QApplication::setOverrideCursor(customCursor);
		view->Tool = Select;
		});
	QToolButton* delLine = new QToolButton();
	delLine->setIcon(QIcon(":/NodeData/icon/deleteLine.png"));
	connect(delLine, &QToolButton::clicked, [=]() {
		QPixmap cursorPixmap(":/NodeData/icon/deleteLine.png");
		cursorPixmap = cursorPixmap.scaled(32, 32);
		QCursor customCursor(cursorPixmap, 0, 0);
		QApplication::setOverrideCursor(customCursor);
		view->Tool = DeleteLine;
		});

	ui->toolBar->addWidget(delLine);
	QToolButton* delNode = new QToolButton();
	delNode->setIcon(QIcon(":/NodeData/icon/deleteNode.png"));
	ui->toolBar->addWidget(delNode);
	connect(delNode, &QToolButton::clicked, [=]() {
		QPixmap cursorPixmap(":/NodeData/icon/deleteNode.png");
		cursorPixmap = cursorPixmap.scaled(32, 32);
		QCursor customCursor(cursorPixmap, 0, 0);
		QApplication::setOverrideCursor(customCursor);
		view->Tool = DeleteNode;
		});
	//默认选中选中按钮
	select->click();

	//单次运行
	connect(ui->actionrunonce, &QAction::triggered, [=]() {

		ui->tabWidget->setCurrentIndex(0);
		this->ui->attribute->setEnabled(false);
		this->ui->actionRun->setEnabled(false);
		this->ui->projectSetting->setEnabled(false);
		this->ui->actionrunonce->setEnabled(false);
		view->RunOnce();
		this->ui->actionRun->setEnabled(true);
		this->ui->projectSetting->setEnabled(true);
		this->ui->actionrunonce->setEnabled(true);
		this->ui->attribute->setEnabled(true);
		}
	);

	//运行
	connect(ui->actionRun, &QAction::triggered, [=]() {
		isruning = !isruning;
		ui->tabWidget->setCurrentIndex(0);
		if (isruning)
		{
			ui->leftwidget->show();
			ui->attribute->show();
			this->ui->projectSetting->setEnabled(true);
			this->ui->actionrunonce->setEnabled(true);
			ui->actionRun->setText("运行");
			ui->actionRun->setIcon(QIcon(":/NodeData/icon/run.png"));
		}
		else
		{
			AudioPlayer::Play(AudioType::Run);
			ui->attribute->hide();

			ui->leftwidget->hide();
			this->ui->projectSetting->setEnabled(false);
			this->ui->actionrunonce->setEnabled(false);
			ui->actionRun->setText("停止");
			ui->actionRun->setIcon(QIcon(":/NodeData/icon/stop.png"));
		}
		view->RunOrStop();
		});




	//关闭按钮，保存后 返回到启动器
	connect(ui->actionclose, &QAction::triggered, [=]() {
		(	new Launcher())->show();

			Saver::AutoSave(view);
			this->close();
		});


	//节点编辑器
	connect(this->ui->actionNodeEditor, &QAction::triggered, [=]() {
		(new NodeEditorWidget())->show();
		});


	//项目设置
	connect(this->ui->projectSetting, &QAction::triggered, [=]() {
		SettingWidget* s = new SettingWidget();
		s->exec();
		//设置视图背景
		if (view->scene())
		{
			view->scene()->setBackgroundBrush(RuningConfig::gridBackColor);
		}
		//预览视图
		scene->setBackgroundBrush(RuningConfig::gridBackColor);
		update();
		});


	//标签页切换
	connect(ui->tabWidget, &QTabWidget::currentChanged, [&](int index) {
		if (index == 0)
		{
			//更新节点浏览器
			nodetree->populateTree(QDir(RuningConfig::CurrentRuningPath + "/nodes"));
		}
		else if (index == 1)
		{
			//更新设计节点浏览器
			filetree->populateTree(QDir(RuningConfig::CurrentRuningPath));
		}
		else if (index == 2)
		{
			//更新测试节点浏览器
			testnodetree->populateTree(QDir(RuningConfig::CurrentRuningPath + "/nodes"));
		}
		});


	//帮助页面加载HTML文件

	ui->helpTextBrower->setSource({ "qrc:/HelpFile/HelpPage/index.html" });

	connect(ui->helpTextBrower, &QTextBrowser::anchorClicked, [&](const QUrl& url) {
		ui->helpTextBrower->setSource(url);
		});



}

MainWindow::~MainWindow()
{

	delete view;
	delete objectTree;
	delete nodetree;
	delete filetree;
	delete testnodetree;
	delete ui;
}

QTreeWidget* MainWindow::GeneratorObjectTreeBrowser(GraphicsItemProperty item)
{
	GraphicItem_TreeItemList.clear();
	QTreeWidget* objtree = new QTreeWidget();
	objtree->header()->hide();
	disconnect(objtree, &QTreeWidget::itemClicked, nullptr, nullptr);
	GraphicsItem* graphicsItem = dynamic_cast<GraphicsItem*>(item.ParentItem);
	if (graphicsItem)
	{
		//创建顶级图元项（一般为Node）
		QTreeWidgetItem* TopItem = new QTreeWidgetItem({ Map::GraphicsItemTypeNameMapChinese[graphicsItem->Info.GraphicsItemType] });
		objtree->addTopLevelItem(TopItem);
		TopItem->setIcon(0, QIcon(Map::ItemTypeIconMap[graphicsItem->Info.GraphicsItemType]));
		GraphicItem_TreeItemList.push_back({ TopItem ,graphicsItem });

		//创建子控件项目
		for (auto child : item.children)
		{
			GraphicsItem* childItem = dynamic_cast<GraphicsItem*>(child);
			if (childItem)
			{
				QTreeWidgetItem* childTreeItem = new QTreeWidgetItem({ Map::GraphicsItemTypeNameMapChinese[childItem->Info.GraphicsItemType] });
				childTreeItem->setIcon(0, QIcon(Map::ItemTypeIconMap[childItem->Info.GraphicsItemType]));
				TopItem->addChild(childTreeItem);
				GraphicItem_TreeItemList.push_back({ childTreeItem ,childItem });
			}
		}
	}
	//对象树领域展开！！！！！
	objtree->expandAll();

	connect(objtree, &QTreeWidget::itemClicked, [=](QTreeWidgetItem* item, int column)
		{
			for (auto Listitem : GraphicItem_TreeItemList)
			{
				if (Listitem.treeitem == item)
				{
					if (currentSelectGraphicsItem == Listitem.graphicsItem)
						return;
					currentSelectGraphicsItem = Listitem.graphicsItem;
					QtTreePropertyBrowser* Browser = GeneratorPropertyBrowser(Listitem.graphicsItem);
					updatePropertyBrowser(Browser);
				}
			}
		});
	return objtree;
}

void MainWindow::updateObjectTreeBrowser(QTreeWidget* item)
{
	static QTreeWidget* objtree = ui->GraphicsObjectTree;
	objtree->close();
	if (objtree)
	{
		delete objtree;
		objtree = nullptr;
	}
	objtree = item;
	objtree->setObjectName("GraphicsObjectTree");
	objtree->setParent(ui->attribute);
	ui->gridLayout_2->addWidget(objtree, 0, 0, 1, 1);
}

void MainWindow::updatePropertyBrowser(QtTreePropertyBrowser* Browser)
{
	static QtTreePropertyBrowser* PropertyBrowser = dynamic_cast<QtTreePropertyBrowser*>(ui->PropertyBrowser);
	PropertyBrowser->clear();
	PropertyBrowser->close();
	if (PropertyBrowser)
	{
		delete PropertyBrowser;
		PropertyBrowser = nullptr;
	}
	PropertyBrowser = Browser;
	PropertyBrowser->setObjectName("PropertyBrowser");
	PropertyBrowser->setParent(ui->attribute);
	ui->gridLayout_2->addWidget(PropertyBrowser, 1, 0, 1, 1);

}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{

	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->modifiers() & Qt::ControlModifier)
		{
			if (keyEvent->key() == Qt::Key_S)
			{
				switch (ui->tabWidget->currentIndex()) {
				case 0://视图页面
				{
					qDebug() << "MainView Save";

				} break;
				case 1://设计页面
				{
					//写入文件
					QFile file(currentdesinFilePath);
					if (file.exists())
					{
						file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
						file.write(ui->designTextEdit->toPlainText().toUtf8());
						file.close();
					}

					//预览器加载节点（如果节点存在）
					GraphicsItemCreator* creator = GraphicsItemCreator::getInstance();
					if (designGraphicsItem != nullptr)
					{
						designGraphicsItem->scene()->removeItem(designGraphicsItem);
						delete designGraphicsItem;
						designGraphicsItem = nullptr;
					}
					designGraphicsItem = creator->CreatGraphicsItem({ currentdesinFilePath });
					qDebug() << currentdesinFilePath;
					qDebug() << designGraphicsItem;
					if (designGraphicsItem != nullptr)
					{
						ui->designView->show();
						QPointF pos = ui->designView->rect().center() - designGraphicsItem->boundingRect().center();
						designGraphicsItem->setPos(ui->designView->mapToScene(pos.toPoint()));
						designViewscene->addItem(designGraphicsItem);
					}
					else
					{
						ui->designView->hide();
					}

				} break;
				default:
					break;
				}
			}
		}
	}
	return QMainWindow::eventFilter(obj, event);
}



QtTreePropertyBrowser* MainWindow::GeneratorPropertyBrowser(GraphicsItem* item)
{
	if (!item)
		return nullptr;
	QtTreePropertyBrowser* propertyBrowser = new QtTreePropertyBrowser();
	propertyBrowser->setPropertiesWithoutValueMarked(true);
	//可编辑属性管理器
	QtVariantPropertyManager* PropertyManager = new QtVariantPropertyManager(propertyBrowser);
	//不可编辑属性管理器
	QtVariantPropertyManager* PropertyManagerNotEnable = new QtVariantPropertyManager(propertyBrowser);
	//枚举属性编辑管理器
	QtEnumPropertyManager* enumManager = new QtEnumPropertyManager(propertyBrowser);
	// 创建颜色属性管理器
	QtColorPropertyManager* colorManager = new QtColorPropertyManager(propertyBrowser);


	//没有父对象生成坐标属性
	if (!item->parentItem())
	{
		QtProperty* posGroup = PropertyManager->addProperty(QtVariantPropertyManager::groupTypeId(), "位置");
		QtVariantProperty* pos_x = PropertyManager->addProperty(QVariant::Int, QStringLiteral("X"));
		pos_x->setValue(item->x());
		QtVariantProperty* pos_y = PropertyManager->addProperty(QVariant::Int, QStringLiteral("Y"));
		pos_y->setValue(item->y());
		posGroup->addSubProperty(pos_x);
		posGroup->addSubProperty(pos_y);
		propertyBrowser->addProperty(posGroup);
		//XY属性值变化后事件
		connect(PropertyManager, &QtVariantPropertyManager::valueChanged, [=](QtProperty* property, const QVariant& value) {
			if (property->propertyName() == "X")
			{
				item->setX(value.toInt());
			}
			else if (property->propertyName() == "Y")
			{
				item->setY(value.toInt());
			}
			});
	}




	switch (item->Info.GraphicsItemType)
	{
		//带GNCB的控件
	case Start:
	case Node:
	{
		//节点
		GraphicsNode* node = dynamic_cast<GraphicsNode*>(item);
		QtProperty* nodeGroup = PropertyManager->addProperty(QtVariantPropertyManager::groupTypeId(), "节点");

		//节点名称
		QtVariantProperty* nameName = PropertyManager->addProperty(QVariant::String, "节点名称");
		nameName->setValue(node->Info.nodeName);
		nodeGroup->addSubProperty(nameName);
		connect(PropertyManager, &QtVariantPropertyManager::valueChanged, [=](QtProperty* property, const QVariant& value) {
			if (property->propertyName() == "节点名称")
			{
				node->Info.nodeName = value.toString();
				node->update();
			}
			});
		//背景颜色1
		QtProperty* backcolorProperty1 = colorManager->addProperty("背景颜色1");
		colorManager->setValue(backcolorProperty1, node->Info.backgroundColor1);
		connect(colorManager, &QtColorPropertyManager::valueChanged, [=](QtProperty* property, const QVariant& value) {
			if (property->propertyName() == "背景颜色1")
			{
				node->Info.backgroundColor1 = colorManager->value(backcolorProperty1);
			}
			});
		nodeGroup->addSubProperty(backcolorProperty1);
		//背景颜色2
		QtProperty* backcolorProperty2 = colorManager->addProperty("背景颜色2");
		colorManager->setValue(backcolorProperty2, node->Info.backgroundColor2);
		connect(colorManager, &QtColorPropertyManager::valueChanged, [=](QtProperty* property, const QVariant& value) {
			if (property->propertyName() == "背景颜色2")
			{
				node->Info.backgroundColor2 = colorManager->value(backcolorProperty2);
			}
			});
		nodeGroup->addSubProperty(backcolorProperty2);
		//标题背景颜色1
		QtProperty* titlebackcolorProperty1 = colorManager->addProperty("标题背景颜色1");
		colorManager->setValue(titlebackcolorProperty1, node->Info.titleBackgroundColor1);
		connect(colorManager, &QtColorPropertyManager::valueChanged, [=](QtProperty* property, const QVariant& value) {
			if (property->propertyName() == "标题背景颜色1")
			{
				node->Info.titleBackgroundColor1 = colorManager->value(titlebackcolorProperty1);
			}
			});
		nodeGroup->addSubProperty(titlebackcolorProperty1);
		//标题背景颜色2
		QtProperty* titlebackcolorProperty2 = colorManager->addProperty("标题背景颜色1");
		colorManager->setValue(titlebackcolorProperty2, node->Info.titleBackgroundColor2);
		connect(colorManager, &QtColorPropertyManager::valueChanged, [=](QtProperty* property, const QVariant& value) {
			if (property->propertyName() == "标题背景颜色1")
			{
				node->Info.titleBackgroundColor2 = colorManager->value(titlebackcolorProperty2);
			}
			});

		nodeGroup->addSubProperty(titlebackcolorProperty2);
		propertyBrowser->addProperty(nodeGroup);
	}break;
	case Port:
	{
		QtProperty* portGroup = PropertyManager->addProperty(QtVariantPropertyManager::groupTypeId(), "端口");
		GraphicsPort* port = dynamic_cast<GraphicsPort*>(item);

		if (port)
		{
			QtVariantProperty* active = PropertyManager->addProperty(QVariant::Bool, "激活");
			active->setValue(port->GetPortInfo().IsActive);
			portGroup->addSubProperty(active);

			QtVariantProperty* connect = PropertyManagerNotEnable->addProperty(QVariant::String, "连接状态");
			if (port->GetPortInfo().IsConnection)
				connect->setValue("已连接");
			else
				connect->setValue("空闲");
			portGroup->addSubProperty(connect);

			//端口类型
			QtProperty* portType = enumManager->addProperty("端口类型");
			QStringList porttypeoptions;
			for (auto datatype : Map::PortTypeNameMapChinese)
			{
				porttypeoptions.append(datatype);
			}
			enumManager->setEnumNames(portType, porttypeoptions);
			QString porttype = Map::PortTypeNameMapChinese[port->GetPortInfo().portType];
			enumManager->setValue(portType, porttypeoptions.indexOf(porttype));
			portGroup->addSubProperty(portType);
			//端口数据类型
			QtProperty* dataTypeEnumProperty = enumManager->addProperty("端口数据类型");
			QStringList portdatatypeoptions;
			for (auto datatype : Map::PortDataTypeNameMapChinese)
			{
				portdatatypeoptions.append(datatype);
			}
			enumManager->setEnumNames(dataTypeEnumProperty, portdatatypeoptions);
			QString type = Map::PortDataTypeNameMapChinese[port->GetPortInfo().portDataType];
			enumManager->setValue(dataTypeEnumProperty, portdatatypeoptions.indexOf(type));
			portGroup->addSubProperty(dataTypeEnumProperty);



			QObject::connect(enumManager, &QtEnumPropertyManager::valueChanged,
				[=](QtProperty* property, int value) {
					if (property->propertyName() == "端口数据类型")
					{
						//改变端口数据类型，先断开断开连接
						if (port->GetPortInfo().IsConnection)
							view->Manager->DisConnectPort(port);
						port->GetPortInfo().portDataType = Map::PortDataTypeNameMapChinese.key(portdatatypeoptions.value(value));
						port->GetPortInfo().Update();
						port->update();
					}
					else if (property->propertyName() == "端口类型")
					{
						//改变端口数据类型，先断开断开连接
						if (port->GetPortInfo().IsConnection)
							view->Manager->DisConnectPort(port);
						port->GetPortInfo().portType = Map::PortTypeNameMapChinese.key(porttypeoptions.value(value));
						port->GetPortInfo().Update();
						port->update();
					}
				});


		}
		propertyBrowser->addProperty(portGroup);
	}break;
	case Button: {
		GraphicsButton* button = dynamic_cast<GraphicsButton*>(item);
		QtProperty* buttonGroup = PropertyManager->addProperty(QtVariantPropertyManager::groupTypeId(), "按钮");
		//按钮文本
		QtVariantProperty* buttontext = PropertyManager->addProperty(QVariant::String, "文本");
		buttontext->setValue(button->Info.buttonText);
		buttonGroup->addSubProperty(buttontext);
		connect(PropertyManager, &QtVariantPropertyManager::valueChanged, [=](QtProperty* property, const QVariant& value) {
			if (property->propertyName() == "文本")
			{
				button->Info.buttonText = value.toString();
				button->update();
			}
			});
		//文本颜色
		QtProperty* textcolorProperty = colorManager->addProperty("文本颜色");
		colorManager->setValue(textcolorProperty, button->Info.buttonTextColor);
		connect(colorManager, &QtColorPropertyManager::valueChanged, [=](QtProperty* property, const QVariant& value) {
			if (property->propertyName() == "文本颜色")
			{
				button->Info.buttonTextColor = colorManager->value(textcolorProperty);
				button->update();
			}
			});
		buttonGroup->addSubProperty(textcolorProperty);

		//按钮正常颜色状态颜色
		QtProperty* buttonnormalcolorProperty = colorManager->addProperty("按钮颜色");
		colorManager->setValue(buttonnormalcolorProperty, button->Info.buttonColor);
		connect(colorManager, &QtColorPropertyManager::valueChanged, [=](QtProperty* property, const QVariant& value) {
			if (property->propertyName() == "按钮颜色")
			{
				button->Info.buttonColor = colorManager->value(buttonnormalcolorProperty);
				button->update();
			}
			});
		buttonGroup->addSubProperty(buttonnormalcolorProperty);
		//按钮按钮点击颜色状态颜色
		QtProperty* buttclickcolorProperty = colorManager->addProperty("按钮点击颜色");
		colorManager->setValue(buttclickcolorProperty, button->Info.buttonPressColor);
		connect(colorManager, &QtColorPropertyManager::valueChanged, [=](QtProperty* property, const QVariant& value) {
			if (property->propertyName() == "按钮点击颜色")
			{
				button->Info.buttonPressColor = colorManager->value(buttclickcolorProperty);
				button->update();
			}
			});
		buttonGroup->addSubProperty(buttclickcolorProperty);




		propertyBrowser->addProperty(buttonGroup);
	}break;
	case SwitchButton: {

		GraphicsSwitchButton* switchbutton = dynamic_cast<GraphicsSwitchButton*>(item);
		QtProperty* switchGroup = PropertyManager->addProperty(QtVariantPropertyManager::groupTypeId(), "开关");





		propertyBrowser->addProperty(switchGroup);
	}break;
	case Chart: {

		GraphicsChart* switchbutton = dynamic_cast<GraphicsChart*>(item);
		QtProperty* chartGroup = PropertyManager->addProperty(QtVariantPropertyManager::groupTypeId(), "图表");

		propertyBrowser->addProperty(chartGroup);
	}break;
	case GraphicsItemType::Label: {
		GraphicsLabel* switchbutton = dynamic_cast<GraphicsLabel*>(item);
		QtProperty* labelGroup = PropertyManager->addProperty(QtVariantPropertyManager::groupTypeId(), "标签");


		propertyBrowser->addProperty(labelGroup);
	}break;

	default:
		break;
	}


	//设置工厂
	QtEnumEditorFactory* enumFactory = new QtEnumEditorFactory(propertyBrowser);
	QtVariantEditorFactory* edit_factory = new QtVariantEditorFactory(propertyBrowser);
	QtColorEditorFactory* colorFactory = new QtColorEditorFactory(propertyBrowser);

	propertyBrowser->setFactoryForManager(colorManager, colorFactory);
	propertyBrowser->setFactoryForManager(enumManager, enumFactory);
	propertyBrowser->setFactoryForManager(PropertyManager, edit_factory);

	return propertyBrowser;
}


void MainWindow::on_actionsave_triggered()
{
    //保存

	Saver::AutoSave(view);

}

