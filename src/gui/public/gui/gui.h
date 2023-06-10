#pragma once

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class FuseGui; }
QT_END_NAMESPACE

class FuseGui : public QMainWindow
{
	Q_OBJECT

public:

	FuseGui(QWidget *parent = nullptr);
	~FuseGui();

private:

	Ui::FuseGui *ui;
};
