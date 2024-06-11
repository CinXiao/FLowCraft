#include "Launcher.h"
#include "ui_Launcher.h"

#include <QFileDialog>
void processFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    // 读取所有行到 QStringList  
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        lines.append(in.readLine().trimmed()); // trimmed() 去除行尾空白字符  
    }
    file.close();
    // 使用 QSet 去除重复行  
    QSet<QString> uniqueLines(lines.begin(), lines.end());
    // 将去重后的内容写回文件  
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    foreach(const QString & line, uniqueLines) {
        QStringList projectInfo= line.split("#");
        if(projectInfo.count()==2)
        {
            QDir dir(projectInfo[1]);
            if(dir.exists())
            {
                out << line << "\n";
            }

        }
    }
    file.close();
}
Launcher::Launcher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Launcher)
{
    ui->setupUi(this);
    //读取项目文件
    processFile("projectlist.txt");
    QFile file("projectlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString project= in.readLine();
        QStringList projectInfo= project.split("#");
        QListWidgetItem* item = new QListWidgetItem();
        if(projectInfo.count()==2)
        {
            ProjectItem*proitem=new ProjectItem(projectInfo[0],projectInfo[1]);

            ui->projectList->addItem(item);
            ui->projectList->setItemWidget(item,proitem);
        }
    }
    file.close();
    connect(ui->projectList,&QListWidget::itemDoubleClicked,[=](QListWidgetItem *Widgetitem){
        ProjectItem* item=dynamic_cast<ProjectItem*>(ui->projectList->itemWidget(Widgetitem));
        if(item)
        {
            (new MainWindow(item->ProjectPath))->show();
            this->close();
        }
    });


}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::on_commandLinkButton_clicked()
{

}


void Launcher::on_CreatProject_clicked()
{
    CreatNewProject *dialog = new CreatNewProject(this);
    connect(dialog, &CreatNewProject::stringReturned, this, [=](const QString &str) {
        QUrl url;
        url.setUrl(str);
        if(url.isValid())
        {
            this->close();
            (new MainWindow(str))->show();
        }
        dialog->deleteLater(); // 清理对话框对象
    });
    dialog->exec();
}


void Launcher::on_pushButton_clicked()
{
    // 创建一个文件对话框，并设置其为目录选择模式
    QFileDialog dialog(this, "选择项目");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly); // 仅显示目录
    // 显示对话框并获取用户的选择
    if (dialog.exec()) {
        QStringList fileNames = dialog.selectedFiles();
        if (!fileNames.isEmpty()) {
            QString selectedPath = fileNames.first(); // 获取第一个（也是唯一的）选择的路径
        }
    }
}

