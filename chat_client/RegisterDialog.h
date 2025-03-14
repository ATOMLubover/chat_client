#pragma once

#include "FileLogger.hpp"
#include "global.h"

#include <QDialog>
#include <QRegularExpression>
#include <QString>
#include <QMap>
#include <QJsonObject>
#include "ui_RegisterDialog.h"

#include <memory>
#include <functional>

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterDialogClass; };
QT_END_NAMESPACE

class RegisterDialog : public QDialog
{
	Q_OBJECT

private:
	enum class EnumLabelError { Normal, Error };

public:
	RegisterDialog( QWidget* parent = nullptr );
	~RegisterDialog();

private:
	void InitUi();
	void InitSlots();
	void InitHttpHandlers();

	void UpdateLabelError( const QString& msg, EnumLabelError state );

private:
	std::unique_ptr<Ui::RegisterDialogClass> ui;

	QMap<EnumRequestType, std::function<void(const QJsonObject&)>> http_handlers;

	QMap<TipErr, QString> _tip_errs;

private slots:
	void Slot_OnSendVerificationCode();
	void Slot_OnConfirm();
	bool Slot_CheckAccountValid();
	bool Slot_CheckEmailValid();
	bool Slot_CheckPwdValid();
	bool Slot_CheckConfirmPwdValid();
	bool Slot_CheckVerificationValid();

	void Slot_HandleWhenHttpFinished( EnumRequestType req_type, QString result, EnumError error );
};
