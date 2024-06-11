#include "nodeeditorwidget.h"
#include "ui_nodeeditorwidget.h"
#include "../../../Globe/GraphicsItemCreator.h"
using namespace GraphicsModule;

NodeEditorWidget::NodeEditorWidget(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::NodeEditorWidget)
{
	ui->setupUi(this);

	scene = new  QGraphicsScene();
	ui->View->setScene(scene);
	//填充树形控件
	ui->treelist->populateTree(QDir(RuningConfig::CurrentRuningPath + "/nodes"));
	//选择了节点列表
	connect(this->ui->treelist, &QTreeWidget::itemClicked, [=](QTreeWidgetItem* item)
		{
			GraphicsItemCreator* creator = GraphicsItemCreator::getInstance();
			QString path = item->data(0, Qt::UserRole).toString();
			if (PreItem != nullptr)
			{
				PreItem->scene()->removeItem(PreItem);
				delete PreItem;
				PreItem = nullptr;
			}
			NodePath = path;
			PreItem = creator->CreatGraphicsItem({ NodePath });
			if (PreItem != nullptr)
			{
				GraphicsNode* node = dynamic_cast<GraphicsNode*>(PreItem);
				if (node)
				{
					ScriptPath = node->Info.ScriptPath;
				}
				QPointF pos = ui->View->rect().center() - PreItem->boundingRect().center();
				PreItem->setPos(ui->View->mapToScene(pos.toPoint()));
				scene->addItem(PreItem);
			}
			QFileInfo info(NodePath);
			if (info.isFile())
			{
				QFile file(NodePath);
				file.open(QIODevice::ReadWrite);
				ui->nodetextEdit->setText(file.readAll());
				file.close();
			}
			QFileInfo scriptinfo(ScriptPath);
			if (scriptinfo.isFile())
			{
				QFile file(ScriptPath);
				file.open(QIODevice::ReadWrite);
				ui->scripttextEdit->setText(file.readAll());
				file.close();
			}
		});


}

NodeEditorWidget::~NodeEditorWidget()
{
	delete ui;
}

void NodeEditorWidget::on_Refresh_clicked()
{

}

void NodeEditorWidget::keyPressEvent(QKeyEvent* event)
{
	if (event->modifiers() & Qt::ControlModifier && event->key() == Qt::Key_S)
	{

		//保存
		QFileInfo nodeinfo(NodePath);
		if (nodeinfo.isFile())
		{
			QFile file(NodePath);
			file.open(QIODevice::WriteOnly);
			file.write(ui->nodetextEdit->toPlainText().toUtf8());
			file.close();
		}

		QFileInfo scriptinfo(ScriptPath);
		if (scriptinfo.isFile())
		{
			QFile file(ScriptPath);
			file.open(QIODevice::WriteOnly);
			file.write(ui->scripttextEdit->toPlainText().toUtf8());
			file.close();
		}

		//刷新
		if (PreItem != nullptr)
		{
			PreItem->scene()->removeItem(PreItem);
			delete PreItem;
			PreItem = nullptr;
		}
		GraphicsItemCreator* creator = GraphicsItemCreator::getInstance();
		PreItem = creator->CreatGraphicsItem({ NodePath });
		if (PreItem != nullptr)
		{
			QPointF pos = ui->View->rect().center() - PreItem->boundingRect().center();
			PreItem->setPos(ui->View->mapToScene(pos.toPoint()));
			scene->addItem(PreItem);
		}


	}
}

