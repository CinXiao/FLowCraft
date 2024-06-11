#include "NodeTreeWidget.h"
#include <QMessageBox>
#include <qinputdialog.h>


NodeTreeWidget::NodeTreeWidget(QWidget* parent) : QTreeWidget(parent) {

	setDragEnabled(true);
	header()->hide();

}

void NodeTreeWidget::populateTree(const QDir& dir)
{
	targetDir = dir;
	this->clear();
	populateTree(targetDir, nullptr);
}


void NodeTreeWidget::populateTree(const QDir& dir, QTreeWidgetItem* parentItem)
{
	QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
	for (const QFileInfo& entry : entries) {
		QTreeWidgetItem* item = new QTreeWidgetItem();
		item->setText(0, entry.fileName());
		item->setData(0, Qt::UserRole, entry.absoluteFilePath()); // 存储文件路径  

		// 设置图标  
		if (entry.isDir()) {
			item->setIcon(0, folderIcon); // 如果是文件夹，则设置文件夹图标  
		}
		else {
			//设置图标
			if (entry.suffix() == "xs")
				item->setIcon(0, scriptIcon);
			else if (entry.suffix() == "png" || entry.suffix() == "jpg")
				item->setIcon(0, pictureIcon);
			else  if (entry.suffix() == "json")
				item->setIcon(0, jsonIcon);
			else
				item->setIcon(0, fileIcon);


		}
		if (parentItem) {
			parentItem->addChild(item);
		}
		else {
			this->addTopLevelItem(item);
		}

		if (entry.isDir()) {
			item->setExpanded(true);
			populateTree(entry.absoluteFilePath(), item);
		}
	}
}

void NodeTreeWidget::mousePressEvent(QMouseEvent* event)
{


	QTreeWidget::mousePressEvent(event);
	if (event->button() == Qt::RightButton) {
		// 获取当前选中的项  
		QTreeWidgetItem* currentItem = this->currentItem();



		if (currentItem) {
			QPoint globalPos = this->viewport()->mapToGlobal(event->pos());
			QString path = currentItem->data(0, Qt::UserRole).toString();

			QMenu menu;//菜单
			QAction* copyAction = menu.addAction("复制");
			copyAction->setIcon(copyIcon);
			QAction* pasteAction = menu.addAction("粘贴");
			pasteAction->setIcon(pasteIcon);
			if (clipboard.isEmpty())
			{
				pasteAction->setVisible(false);
			}
			QAction* renameAction = menu.addAction("重命名");
			renameAction->setIcon(renameIcon);
			QAction* newFolderAction = menu.addAction("新建文件夹");
			newFolderAction->setIcon(folderIcon);
			QAction* newFileAction = menu.addAction("新建节点");
			newFileAction->setIcon(fileIcon);
			QAction* newscriptFileAction = menu.addAction("新建XS脚本");
			newscriptFileAction->setIcon(scriptIcon);
			QAction* deleteAction = menu.addAction("删除");
			deleteAction->setIcon(deleteIcon);

			QFileInfo  currentSelectInfo(path);
			// 检查当前项是否存在
			if (currentSelectInfo.exists())
			{
				// 显示上下文菜单  
				QAction* selectedAction = menu.exec(globalPos);
				//重命名
				if (selectedAction == renameAction) {
					QString newname = QInputDialog::getText(nullptr, "重命名", "请输入新名称:");
					QString CurrentSelectDirPath;
					if (currentSelectInfo.isDir())
					{
						// 获取当前选择项的目录路径
						QString currentSelectDirPath = currentSelectInfo.absoluteFilePath();
						// 构建新的目录路径
						QString newDirPath = currentSelectInfo.dir().absolutePath() + QDir::separator() + newname;
						QDir().rename(currentSelectDirPath, newDirPath);
					}
					else //文件
					{
						CurrentSelectDirPath = currentSelectInfo.dir().path();
						QFile::rename(currentSelectInfo.filePath(), CurrentSelectDirPath + QDir::separator() + newname);
					}


				}
				else if (selectedAction == newscriptFileAction) {
					//新建节点
					// 显示输入框并获取用户输入的文本
					QString filename = QInputDialog::getText(nullptr, "新建脚本", "请输入脚本名称:");
					QString CurrentSelectDirPath;
					if (currentSelectInfo.isDir())
					{
						CurrentSelectDirPath = currentSelectInfo.absoluteFilePath();
					}
					else //文件
					{
						CurrentSelectDirPath = currentSelectInfo.dir().path();
					}
					// 创建节点文件
					QFile file(CurrentSelectDirPath + QDir::separator() + filename + ".xs");
					QDir destinationDir(CurrentSelectDirPath + QDir::separator() + filename);
					// 打开文件以写入模式
					if (file.open(QIODevice::WriteOnly)) {
						file.close();
					}
					else {
						// 文件创建失败
						QMessageBox::warning(nullptr, "警告", "脚本文件创建失败");
					}
				}
				else if (selectedAction == newFileAction)
				{	//新建节点
					// 显示输入框并获取用户输入的文本
					QString filename = QInputDialog::getText(nullptr, "新建节点", "请输入节点名称:");
					QString CurrentSelectDirPath;
					if (currentSelectInfo.isDir())
					{
						CurrentSelectDirPath = currentSelectInfo.absoluteFilePath();
					}
					else //文件
					{
						CurrentSelectDirPath = currentSelectInfo.dir().path();
					}
					// 创建节点文件
					QFile file(CurrentSelectDirPath + QDir::separator() + filename);
					QDir destinationDir(CurrentSelectDirPath + QDir::separator() + filename);
					// 打开文件以写入模式
					if (file.open(QIODevice::WriteOnly)) {
						file.close();
					}
					else {
						// 文件创建失败
						QMessageBox::warning(nullptr, "警告", "文件创建失败");
					}


				}
				else if (selectedAction == newFolderAction)
				{
					// 显示输入框并获取用户输入的文本
					QString dirname = QInputDialog::getText(nullptr, "新建文件夹", "请输入文件夹名称:");
					QString CurrentSelectDirPath;
					if (currentSelectInfo.isDir())
					{
						CurrentSelectDirPath = currentSelectInfo.absoluteFilePath();
					}
					else //文件
					{
						CurrentSelectDirPath = currentSelectInfo.dir().path();
					}
					// 创建目标目录
					QDir destinationDir(CurrentSelectDirPath + QDir::separator() + dirname);
					if (!destinationDir.exists()) {
						destinationDir.mkpath(".");
					}
					else
					{
						QMessageBox::warning(nullptr, "警告", "文件夹已存在");
					}


				}
				else if (selectedAction == deleteAction) {

					QString path = currentSelectInfo.filePath();
					//如果是目录
					if (currentSelectInfo.isDir())
					{
						// 弹出确认对话框
						if (QMessageBox::question(nullptr, "确认删除", QString("确定删除目录 %1 吗？").arg(path), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
						{
							QDir dir(path);
							dir.removeRecursively();
						}
					}//如果是文件
					else if (currentSelectInfo.isFile())
					{
						// 弹出确认对话框
						if (QMessageBox::question(nullptr, "确认删除", QString("你确定删除文件 %1 吗？").arg(path), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
						{
							QFile file(path);
							if (file.exists())
							{
								if (!file.remove())
								{
									QMessageBox::critical(nullptr, "删除失败", QString("无法删除文件 %1.").arg(path));
								}
							}
						}
					}

				}
				//复制路径
				else if (selectedAction == copyAction)
				{
					clipboard = path;
				}
				else if (selectedAction == pasteAction)
				{
					//剪贴板上的文件信息
					QFileInfo clipboardInfo(clipboard);
					QString destinationDirPath;
					QString CurrentSelectDirPath;
					if (currentSelectInfo.isDir())
					{
						CurrentSelectDirPath = currentSelectInfo.absoluteFilePath();
					}
					else
					{
						CurrentSelectDirPath = currentSelectInfo.dir().path();
					}
					//源路径
					QString sourceDirPath = clipboard;
					//需要拷贝到的目标目录
					destinationDirPath = CurrentSelectDirPath + QDir::separator() + clipboardInfo.fileName() + "copy";

					if (clipboardInfo.isDir())
					{
						//判断目标目录是否已经存在如果存在则再在后面加copy
						while (QDir(destinationDirPath).exists())
						{
							destinationDirPath += "copy";
						}
						// 创建目标目录
						QDir destinationDir(destinationDirPath);
						if (!destinationDir.exists()) {
							destinationDir.mkpath(".");
						}
						// 递归地拷贝文件夹及其子文件
						QDir sourceDir(sourceDirPath);
						if (sourceDir.exists()) {
							QStringList fileList = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
							for (const QString& fileName : fileList)
							{
								QString filePath = sourceDirPath + QDir::separator() + fileName;
								QString destinationFilePath = destinationDirPath + QDir::separator() + fileName;
								//需要判断是不是刚刚创建的目标文件夹
								if (filePath != destinationDirPath)
								{
									if (QFileInfo(filePath).isDir()) {
										QDir().mkpath(destinationFilePath);
										QDir(sourceDirPath + QDir::separator() + fileName).rename(filePath, destinationFilePath);
									}
									else {
										// 如果是文件，直接拷贝
										QFile::copy(filePath, destinationFilePath);
									}
								}

							}
						}

					}//剪贴板内容为文件
					else if (clipboardInfo.isFile())
					{
						while (QFile(destinationDirPath).exists())
						{
							destinationDirPath += "copy";
						}
						QFile::copy(clipboardInfo.filePath(), destinationDirPath);
					}

				}

				//重新生成目录树
				populateTree(targetDir);
			}


		}

	}
}





bool NodeTreeWidget::dropMimeData(QTreeWidgetItem* parent, int index, const QMimeData* data, Qt::DropAction action)
{
	return false;
}

QMimeData* NodeTreeWidget::mimeData(const QList<QTreeWidgetItem*>& items) const
{
	QMimeData* mimeData = new QMimeData;
	QString filePath = items[0]->data(0, Qt::UserRole).toString();
	QUrl fileUrl(QUrl::fromLocalFile(filePath));
	QFileInfo fileInfo(filePath);
	if (fileInfo.exists())
	{
		mimeData->setUrls(QList<QUrl>() << fileUrl);
	}
	return mimeData;
}
