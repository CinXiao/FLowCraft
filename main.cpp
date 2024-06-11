#include"Graphics/GraphicsView/graphicsview.h"
#include <QApplication>
#include<QWidget>
#include<QGraphicsScene>
#include"UI/Launcher/Launcher.h"
#include"Globe/DataType.h"
#include"UI/Widgets/CodeEditor/CodeEditor.h"
#include"UI/Widgets/CodeEditor/Highlighter.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
using namespace GraphicsModule;
using namespace Utility;
int main(int argc, char* argv[])
{
    QLocale::setDefault(QLocale(QLocale::Chinese, QLocale::China));
    QApplication a(argc, argv);


 
 

    Launcher* launcher = new Launcher();
    launcher->show();


    return a.exec();
}
