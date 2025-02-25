#include "RegisterDialog.h"

#include "Polisher.h"
#include "HttpMgr.h"

extern hatsuiki::SyncFileLogger logger;

RegisterDialog::RegisterDialog( QWidget* parent )
	: QDialog( parent )
	, ui( std::make_unique<Ui::RegisterDialogClass>() )
{
	ui->setupUi( this );

	InitUi();
	InitSlots();
	InitHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
	logger.Log( hatsuiki::SyncFileLogger::EnumLevel::Info, "register dialog destructed" );
}

void RegisterDialog::InitUi()
{
	ui->edit_password->setEchoMode( QLineEdit::Password );
	ui->edit_comfirm_password->setEchoMode( QLineEdit::Password );

	UpdateLabelError( "error_tip", "normal" );
}

void RegisterDialog::InitSlots()
{ 
	connect( ui->button_get_verify, &QPushButton::clicked,
			 this, &RegisterDialog::Slot_OnSendVerificationCode );

	connect( HttpMgr::GetInstance().get(), &HttpMgr::Signal_RegisterModuleFinish,
			 this, &RegisterDialog::Slot_OnRegisterDialogClose );
}

void RegisterDialog::InitHttpHandlers()
{ 
	http_handlers.insert( EnumRequestType::GetVerificationCode,
						  [this] ( const QJsonObject& json )
						  {
							  int err = json[ "error" ].toInt();

							  if ( err != (int) EnumError::Success )
							  {
								  UpdateLabelError( tr( "wrong argument" ), "error" );
								  return;
							  }

							  QString email = json[ "email" ].toString();
							  UpdateLabelError( tr( "verification code has been sent to your email" ), "normal" );

							  
						  } );
}

void RegisterDialog::UpdateLabelError( const QString& msg, const std::string& state )
{ 
	ui->label_error->setText( msg );
	ui->label_error->setProperty( "state", state.c_str() );
	Polisher::GetInstance()->Repolish( ui->label_error );
}

void RegisterDialog::Slot_OnSendVerificationCode()
{
	QString email = ui->edit_mail->text();

	QRegularExpression regex_mail_fmt( R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)" );
	bool is_match = regex_mail_fmt.match( email ).hasMatch();
	if ( is_match )
	{
		// TODO: send http verification code
	}
	else
	{
		UpdateLabelError( "Invalid email address", "error" );
	}
}

void RegisterDialog::Slot_OnRegisterDialogClose( EnumRequestType req_type, QString result, EnumError error )
{
	if ( error != EnumError::Success )
	{
		UpdateLabelError( tr( "network request failed" ), "error" );
		return;
	}

	QJsonDocument doc_json = QJsonDocument::fromJson( result.toUtf8() );
	if ( doc_json.isNull() || !doc_json.isObject())
	{
		UpdateLabelError( tr( "unable to interpret json" ), "error" );
		return;
	}

	http_handlers[ req_type ]( doc_json.object() );
}