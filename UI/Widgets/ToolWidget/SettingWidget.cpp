#include "SettingWidget.h"
#include <QDir>
#include<QSpinBox>

SettingWidget::SettingWidget(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.photo->setVisible(false);

	//遍历所有主题文件
	QDir dir(RuningConfig::CurrentRuningPath + "/config/Them");
	QStringList filters;
	filters << "*"; // 匹配所有文件和文件夹  
	dir.setNameFilters(filters);
	dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot); // 只处理目录，不包括"."和".."  
	QFileInfoList list = dir.entryInfoList();
	for (const QFileInfo& fileInfo : list) {
		if (fileInfo.isDir()) {
			ui.them->addItem(fileInfo.fileName());
		}
	}
	ui.them->setCurrentText(RuningConfig::ThemName);
	//改变主题
	connect(ui.them, &QComboBox::currentIndexChanged, [=]()
		{
			RuningConfig::ThemName = ui.them->currentText();
			//刷新配置文件路径
			Globe::updateConfigfilePath();
			Globe::initGlobeMap();
			Globe::InitRuningConfig();
		});
	ui.audio->setChecked(RuningConfig::AudioAllowPlay);

	ui.clock->setValue(RuningConfig::UnitStepDelay);
	connect(ui.clock, &QSpinBox::valueChanged, [=](int var) {
		RuningConfig::UnitStepDelay = var;
		});


}

SettingWidget::~SettingWidget()
{}




void SettingWidget::on_clock_valueChanged(int arg1)
{
	if (arg1 == 1314)
		ui.photo->setVisible(true);
	else
		ui.photo->setVisible(false);


}

