#pragma once

#include <FileLogger.hpp>

#include "LoginDialog.h"
#include "RegisterDialog.h"

#include <QtWidgets/QMainWindow>
#include "ui_ChatClient.h"

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class ChatClientClass; };
QT_END_NAMESPACE

class ChatClient : public QMainWindow
{
	Q_OBJECT

private:
	struct Widgets
	{
		LoginDialog* dialog_login;
		RegisterDialog* dialog_register;
	};

public:
	ChatClient( QWidget* parent = nullptr );
	~ChatClient();

	void Start();

private: // initilizations
	void InitProperties();
	void InitWidgets();

	void InitSlots();

private:
	std::unique_ptr<Ui::ChatClientClass> ui;

	Widgets widgets;

private slots:
	void Slot_OnSwitchToRegisterDialog();
};
