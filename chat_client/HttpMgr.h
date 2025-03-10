#pragma once

#include "Singleton.h"
#include "global.h"
#include "FileLogger.hpp"

#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QNetworkReply>
#include <QMap>

#include <functional>

class HttpMgr
	: public QObject
	, public std::enable_shared_from_this<HttpMgr>
	, public Singleton<HttpMgr>
{ 
	Q_OBJECT

public:
	friend class Singleton<HttpMgr>;

public:
	~HttpMgr();

	void PostRequest( QUrl url, QJsonObject json, EnumRequestType req_type, EnumModule mod );

private:
	HttpMgr();

	void InitSlots();

private:
	QNetworkAccessManager manager;

private slots:
	void Slot_OnHttpSendFinished( EnumRequestType req_type, QString result, // result is in json format
								  EnumError error, EnumModule mod );

signals:
	void Signal_HttpSendFinished( EnumRequestType req_type, QString result, // result is in json format
								  EnumError error, EnumModule mod );
	void SignalOut_ToReg_HttpFinished( EnumRequestType req_type, QString result, EnumError error );
};