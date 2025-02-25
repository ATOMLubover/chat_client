#include "ChatClient.h"

extern hatsuiki::SyncFileLogger logger;

ChatClient::ChatClient( QWidget* parent )
	: QMainWindow( parent )
	, ui( std::make_unique<Ui::ChatClientClass>() )
{
	ui->setupUi( this );

	InitProperties();
	InitSlots();
}

ChatClient::~ChatClient()
{
	logger.Log( hatsuiki::SyncFileLogger::EnumLevel::Info, "mainwindow destructed" );
}

void ChatClient::Start()
{ }

void ChatClient::InitProperties()
{ 
	InitWidgets();
}

void ChatClient::InitWidgets()
{
	// init login dialog
	{
		widgets.dialog_login = new LoginDialog( this );

		widgets.dialog_login->setWindowFlags( Qt::CustomizeWindowHint | Qt::FramelessWindowHint );

		setCentralWidget( widgets.dialog_login );
		widgets.dialog_login->show();
	}

	// init register dialog
	{
		widgets.dialog_register = new RegisterDialog( this );

		widgets.dialog_register->setWindowFlags( Qt::CustomizeWindowHint | Qt::FramelessWindowHint );
	}
}

void ChatClient::InitSlots()
{
	connect( widgets.dialog_login, &LoginDialog::Signal_SwitchToRegisterDialog,
			 this, &ChatClient::Slot_OnSwitchToRegisterDialog );
}

void ChatClient::Slot_OnSwitchToRegisterDialog()
{
	// logger.Log( hatsuiki::SyncFileLogger::EnumLevel::Info, "switches to register dialog ( in mainwindow ) " );

	widgets.dialog_login->hide();
	// takeCentralWidget();

	setCentralWidget( widgets.dialog_register);
	widgets.dialog_register->show();
}
