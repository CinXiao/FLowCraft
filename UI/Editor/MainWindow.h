#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QGraphicsScene>
#include<QLabel>
#include <QToolButton>
#include<qradiobutton.h>
#include<QTreeWidgetItem>
#include"../Widgets/NodeTreeWidget.h"
#include"../../Graphics/GraphicsView/Graphicsview.h"
#include"../../Globe/GraphicsItemCreator.h"
#include"../../Globe/Saver.h"

#include"../../UI/Widgets/ToolWidget/nodeeditorwidget.h"
#include"../../UI/Widgets/ToolWidget/SettingWidget.h"
#include"../Launcher/Launcher.h"
#include "../../qtpropertybrowser/qttreepropertybrowser.h"
#include "../../qtpropertybrowser/qtpropertymanager.h"
#include "../../qtpropertybrowser/qteditorfactory.h"
#include "../../qtpropertybrowser/qtvariantproperty.h"
#include"../Widgets/CodeEditor/CodeEditor.h"

#include"../Widgets/CodeEditor/Highlighter.h"

#include"../../Globe/BuiltRunManager.h"
#include"../../Entity/GraphicsNodeControlBlock.h"

using namespace GraphicsModule;
using namespace Globe;
namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT


public:
	explicit MainWindow(QString projectPath, QWidget* parent = nullptr);
	~MainWindow();
	QGraphicsItem* PreItem{ nullptr };

	//生成对象书
	QTreeWidget* GeneratorObjectTreeBrowser(GraphicsItemProperty item);
	//生成属性
	QtTreePropertyBrowser* GeneratorPropertyBrowser(GraphicsItem* item);

	//更新属性和对象书
	void updateObjectTreeBrowser(QTreeWidget* item);
	void updatePropertyBrowser(QtTreePropertyBrowser* item);

protected:
	bool eventFilter(QObject* obj, QEvent* event) override;
private slots:
    void on_actionsave_triggered();

private:
	Ui::MainWindow* ui;
	GraphicsView* view;
	inline static bool isruning{ true };

	QString currentdesinFilePath{ "" };//当前编辑的设计文件

	//属性和树项表
	class GraphicItem_TreeItem
	{
	public:
		GraphicItem_TreeItem(QTreeWidgetItem* treeItem, GraphicsItem* graphicsItem)
			: treeitem(treeItem), graphicsItem(graphicsItem) {};
		QTreeWidgetItem* treeitem{ nullptr };
		GraphicsItem* graphicsItem{ nullptr };
	};

	QList<GraphicItem_TreeItem>GraphicItem_TreeItemList{};
	QGraphicsItem* currentSelectGraphicsItem{ nullptr };
	inline static QGraphicsItem* designGraphicsItem{ nullptr };
	inline static QGraphicsItem* TestGraphicsItem{ nullptr };
	QGraphicsScene* designViewscene;
	QtTreePropertyBrowser* PropertyBrowser{ nullptr };
	QTreeWidget* objectTree{ nullptr };//节点控件对象树
	NodeTreeWidget* nodetree{ nullptr };//节点列表
	NodeTreeWidget* filetree{ nullptr };
	NodeTreeWidget* testnodetree{ nullptr };
};

#endif // MAINWINDOW_H
