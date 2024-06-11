#ifndef LAUNCHER_H
#define LAUNCHER_H
#include<QUrl>
#include <QDialog>
#include"CreatNewProject.h"
#include"../Editor/MainWindow.h"
#include"../Widgets/ToolWidget/ProjectItem.h"
namespace Ui {
class Launcher;
}

class Launcher : public QDialog
{
    Q_OBJECT


public:
    explicit Launcher(QWidget *parent = nullptr);
    ~Launcher();

private slots:
    void on_commandLinkButton_clicked();

    void on_CreatProject_clicked();

    void on_pushButton_clicked();

private:
    Ui::Launcher *ui;
};

#endif // LAUNCHER_H
