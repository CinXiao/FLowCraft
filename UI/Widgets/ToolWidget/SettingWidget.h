#pragma once

#include <QDialog>
#include "ui_SettingWidget.h"
#include"../../../Globe/RuningConfig.h"

#include"../../../Globe/Map.h"
using namespace::Globe;
class SettingWidget : public QDialog
{
	Q_OBJECT

public:
	SettingWidget(QWidget *parent = nullptr);
	~SettingWidget();


private slots:
    void on_clock_valueChanged(int arg1);

private:
	Ui::SettingWidgetClass ui;
};
