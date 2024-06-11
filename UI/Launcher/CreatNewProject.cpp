#include "CreatNewProject.h"
#include "ui_CreatNewProject.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <warning.h>

bool copyDirectory(const QString &sourceDir, const QString &destinationDir) {
    QDir source(sourceDir);
    QDir destination(destinationDir);
    if (!destination.exists()) {
        if (!destination.mkpath(destinationDir)) {
            qDebug() << "无法创建目标目录：" << destinationDir;
            return false;
        }
    }

    QStringList files = source.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &file : files) {
        QFileInfo fileInfo(source.filePath(file));
        QString sourceFilePath = fileInfo.absoluteFilePath();
        QString destinationFilePath = destination.filePath(file);

        if (fileInfo.isDir()) {
            // 如果是目录，递归拷贝
            if (!copyDirectory(sourceFilePath, destinationFilePath)) {
                return false;
            }
        } else {
            // 如果是文件，直接拷贝
            if (!QFile::copy(sourceFilePath, destinationFilePath)) {
                qDebug() << "拷贝文件失败：" << sourceFilePath << "到" << destinationFilePath;
                return false;
            }
        }
    }
    return true;
}

CreatNewProject::CreatNewProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatNewProject)
{
    ui->setupUi(this);

    QDir dir(QApplication::applicationDirPath()+"/ProjectTemplate");
    QStringList subdirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);


    for (const QString &subdir : subdirs) {
        QFileInfo fileInfo(dir.filePath(subdir));

        QString templatePath=fileInfo.absoluteFilePath();
        //获取标签
        QFile tagfile(templatePath+"/.tag");
        tagfile.open(QIODevice::ReadOnly);
        QString tags;
        if(tagfile.exists())
        {
             tags=tagfile.readAll();
        }
        //获取介绍
        QFile descriptionfile(templatePath+"/.description");
        descriptionfile.open(QIODevice::ReadOnly);
        QString des;
        if(descriptionfile.exists())
        {
            des=descriptionfile.readAll();
        }
        //获取信息，
        QListWidgetItem *item = new QListWidgetItem(ui->templateList);
        TemplateItemWidget *templateItem=new TemplateItemWidget(fileInfo.baseName(),des,tags.split("\n"));
        ui->templateList->setItemWidget(item,templateItem);
        templateItem->templatePath=templatePath;
        QListWidgetItemList.append(templateItem);
        connect(templateItem,&TemplateItemWidget::Selected,[=]()
         {
            for(auto item:QListWidgetItemList)
            {
                    item->DisSelect();
            }
                templateItem->Select();
            selectTemplate=templateItem;
            ui->projectName->setText(fileInfo.baseName()+"项目");
        });

    }









}

CreatNewProject::~CreatNewProject()
{
    delete ui;
}

void CreatNewProject::on_selectPath_clicked()
{
    // 创建一个文件对话框，并设置其为目录选择模式
    QFileDialog dialog(this, "选择目录");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly); // 仅显示目录
    // 显示对话框并获取用户的选择
    if (dialog.exec()) {
        QStringList fileNames = dialog.selectedFiles();
        if (!fileNames.isEmpty()) {
            QString selectedPath = fileNames.first(); // 获取第一个（也是唯一的）选择的路径
            ui->projectPath->setText(selectedPath);
        }
    }
}


void CreatNewProject::on_pushButton_3_clicked()
{
    if(selectTemplate)
    {
        QString folderPath = ui->projectPath->text()+"/"+ui->projectName->text();
        qDebug()<<folderPath;
        QDir dir;
        if (!dir.exists(folderPath)) {
            if (!dir.mkdir(folderPath)) {
                QMessageBox::warning(this, "错误", "文件夹创建失败，请检查路径或权限。");
            }
        } else {
            QMessageBox::information(this, "提示", "该目录下已有同名文件夹");
        }


        // 指定要追加写入的文件projectlist.txt
        QString filePath = QDir::currentPath() + "/projectlist.txt";
        QFile file(filePath);
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            // 如果文件打开失败（例如，没有权限或磁盘空间不足），显示错误消息
            QMessageBox::warning(this, "错误", "无法打开文件以追加写入。");
            return;
        }
        QTextStream out(&file);
        out <<ui->projectName->text()+"#"+folderPath+"\n";
        file.close(); // 关闭文件
        //拷贝模板
        copyDirectory(selectTemplate->templatePath,folderPath);
        this->close();
        emit stringReturned(folderPath);
    }

}
