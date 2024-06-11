#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QMainWindow>

class testwidget : public QMainWindow
{
    Q_OBJECT

public:
    testwidget(QWidget *parent = nullptr);
    ~testwidget();
};
#endif // TESTWIDGET_H
