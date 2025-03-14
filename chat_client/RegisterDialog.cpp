#include "RegisterDialog.h"

#include "Polisher.h"
#include "HttpMgr.h"
#include "Encipher.h"

RegisterDialog::RegisterDialog( QWidget* parent )
	: QDialog( parent )
	, ui( std::make_unique<Ui::RegisterDialogClass>() )
{
	ui->setupUi( this );

	InitUi();
	InitHttpHandlers();

	InitSlots();

	std::cout << "RegisterDialog construted" << std::endl;
}

RegisterDialog::~RegisterDialog()
{ 
	std::cout << "RegisterDialog deconstruted" << std::endl;
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

	connect( ui->button_confirm, &QPushButton::clicked,
			 this, &RegisterDialog::Slot_OnConfirm );

	connect( HttpMgr::GetInstance().get(), &HttpMgr::SignalOut_ToReg_HttpFinished,
			 this, &RegisterDialog::Slot_HandleWhenHttpFinished );
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
							  UpdateLabelError(
								  tr( "已发送验证码" ), "normal" );
							  std::cout << "发到邮箱：" << email.toStdString() << std::endl;
						  } );

	http_handlers.insert( EnumRequestType::RegisterUser,
						  [this] ( const QJsonObject& json )
						  {
							  int error = json[ "error" ].toInt();
							  if ( error != (int) EnumError::Success ) {
								  UpdateLabelError( tr( "参数错误" ), "error" );
								  return;
							  }
							  auto email = json[ "email" ].toString();
							  auto uid = json[ "uid" ].toString();
							  UpdateLabelError( tr( "用户注册成功" ), "normal" );
							  std::cout
								  << "email returned: " << email.toStdString() << std::endl
								  << "uid returned: " << uid.toStdString() << std::endl;
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

	std::cout << "发送到邮箱：" << email.toStdString() << std::endl;

	QRegularExpression regex_mail_fmt( R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)" );
	bool is_match = regex_mail_fmt.match( email ).hasMatch();
	if ( is_match )
	{
		QJsonObject json_data;
		json_data.insert( "email", email );

		HttpMgr::GetInstance()->PostRequest( QUrl( gate_url_prefix + "/get_verification_code" ),
											 json_data,
											 EnumRequestType::GetVerificationCode,
											 EnumModule::RegisterMod );

		UpdateLabelError( "Verification code has been sent to your email!", "normal" );
	}
	else
	{
		UpdateLabelError( "Invalid email address", "error" );
	}
}

void RegisterDialog::Slot_OnConfirm()
{
	if ( ui->edit_account->text() == "" ) {
		UpdateLabelError( tr( "用户名不能为空" ), "error" );
		return;
	}

	if ( ui->edit_mail->text() == "" ) {
		UpdateLabelError( tr( "邮箱不能为空" ), "error" );
		return;
	}

	if ( ui->edit_password->text() == "" ) {
		UpdateLabelError( tr( "密码不能为空" ), "error" );
		return;
	}

	if ( ui->edit_comfirm_password->text() == "" ) {
		UpdateLabelError( tr( "确认密码不一致" ), "error" );
		return;
	}

	if ( ui->edit_comfirm_password->text() != ui->edit_password->text() ) {
		UpdateLabelError( tr( "密码和确认密码不匹配" ), "error" );
		return;
	}

	if ( ui->edit_verify->text() == "" ) {
		UpdateLabelError( tr( "验证码不能为空" ), "error" );
		return;
	}

	//day11 发送http请求注册用户
	QJsonObject json_obj;
	json_obj[ "user" ] = ui->edit_account->text();
	json_obj[ "email" ] = ui->edit_mail->text();
	json_obj[ "password" ] = Encipher:: ui->edit_comfirm_password->text();
	json_obj[ "verify_code" ] = ui->edit_verify->text();

	HttpMgr::GetInstance()->PostRequest( QUrl( gate_url_prefix + "/user_register" ),
										 json_obj,
										 EnumRequestType::RegisterUser, 
										 EnumModule::RegisterMod );
}

void RegisterDialog::Slot_HandleWhenHttpFinished( EnumRequestType req_type, QString result, EnumError error )
{
	std::cout << "slot RegisterDialog Handle" << std::endl;
	if ( error != EnumError::Success )
	{
		UpdateLabelError( tr( "network request failed" ), "error" );
		return;
	}

	QJsonDocument doc_json = QJsonDocument::fromJson( result.toUtf8() );
	if ( doc_json.isNull() || !doc_json.isObject() )
	{
		UpdateLabelError( tr( "unable to interpret json" ), "error" );
		return;
	}

	//std::cout << "handler called" << std::endl;
	http_handlers[ req_type ]( doc_json.object() );
}