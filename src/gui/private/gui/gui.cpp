#include "gui/gui.h"

FuseGui::FuseGui(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::FuseGui)
{
	ui->setupUi(this);
}

FuseGui::~FuseGui()
{
	delete ui;
}
