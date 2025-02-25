#pragma once

#include "FileLogger.hpp"
#include "Enumerations.h"

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

public:
	RegisterDialog( QWidget* parent = nullptr );
	~RegisterDialog();

private:
	void InitUi();
	void InitSlots();
	void InitHttpHandlers();

	void UpdateLabelError( const QString& msg, const std::string& state );

private:
	std::unique_ptr<Ui::RegisterDialogClass> ui;

	QMap<EnumRequestType, std::function<void(const QJsonObject&)>> http_handlers;

private slots:
	void Slot_OnSendVerificationCode();

	void Slot_OnRegisterDialogClose( EnumRequestType req_type, QString result, EnumError error );
};
