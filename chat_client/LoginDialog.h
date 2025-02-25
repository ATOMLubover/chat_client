#pragma once

#include <FileLogger.hpp>

#include <QDialog>
#include "ui_LoginDialog.h"

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialogClass; };
QT_END_NAMESPACE

class LoginDialog : public QDialog
{
	Q_OBJECT

public:
	LoginDialog( QWidget* parent = nullptr );
	~LoginDialog();

private:
	void InitUi();
	void InitSlots();

private:
	std::unique_ptr<Ui::LoginDialogClass> ui;

signals:
	void Signal_SwitchToRegisterDialog();
};
