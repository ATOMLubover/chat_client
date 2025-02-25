#include "HttpMgr.h"

extern hatsuiki::SyncFileLogger logger;

HttpMgr::~HttpMgr()
{ }

HttpMgr::HttpMgr()
{ 
	InitSlots();
}

void HttpMgr::InitSlots()
{ 
	connect( this, &HttpMgr::Signal_HttpSendFinished,
			 this, &HttpMgr::Slot_OnHttpSendFinished );
}

void HttpMgr::PostRequest( QUrl url, QJsonObject json, EnumRequestType req_type, EnumModule mod )
{ 
	QByteArray data = QJsonDocument( json ).toJson();

	QNetworkRequest request( url );
	request.setHeader( QNetworkRequest::ContentTypeHeader, "application/json" );
	request.setHeader( QNetworkRequest::ContentLengthHeader, QByteArray::number( data.length() ) ); // automatically endian set

	auto self = shared_from_this(); // keeps the object from being deconstructed

	QNetworkReply* reply = manager.post( request, data );
	connect( reply, &QNetworkReply::finished,
			 [ self, reply, url, req_type, mod ] ()
			 {
				 if ( reply->error() != QNetworkReply::NoError )
				 {
					 logger.Log( hatsuiki::SyncFileLogger::EnumLevel::Error,
								 "net error on url \"{}\"", QString( url.toString() ).toStdString() );
					 emit self->Signal_HttpSendFinished( req_type, "", EnumError::ErrNetwork, mod );

					 reply->deleteLater();

					 return;
				 }

				 QString result = reply->readAll();
				 emit self->Signal_HttpSendFinished( req_type, result, EnumError::Success, mod );

				 reply->deleteLater();
			 } );
}

void HttpMgr::Slot_OnHttpSendFinished( EnumRequestType req_type, QString result,
									   EnumError error, EnumModule mod )
{
	if ( mod == EnumModule::RegisterMod )
	{
		// notify specific module http respondance finished
		emit Signal_RegisterModuleFinish( req_type, result, error );
	}
}