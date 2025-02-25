#include "LoginDialog.h"

extern hatsuiki::SyncFileLogger logger;

LoginDialog::LoginDialog( QWidget* parent )
	: QDialog( parent )
	, ui( std::make_unique<Ui::LoginDialogClass>() )
{
	ui->setupUi( this );

	InitSlots();
}

LoginDialog::~LoginDialog()
{ 
	logger.Log( hatsuiki::SyncFileLogger::EnumLevel::Info, "login dialog destructed" );
}

void LoginDialog::InitUi()
{ 
	ui->edit_password->setEchoMode( QLineEdit::Password );
}

void LoginDialog::InitSlots()
{
	connect( ui->button_register, &QPushButton::clicked,
			 this, &LoginDialog::Signal_SwitchToRegisterDialog );
}
