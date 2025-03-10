#include "global.h"

#include "ChatClient.h"
#include "HttpMgr.h"
#include <QtWidgets/QApplication>

void LoadQss( QApplication& app )
{
	QFile qfile_qss( "./style/style_sheet.qss" );

	if ( qfile_qss.open( QFile::ReadOnly ) )
	{
		// logger.Log( hatsuiki::SyncFileLogger::EnumLevel::Info, "qss file is opened successfully" );
		std::cout << "qss file open failed" << std::endl;

		QString qstr_style = QLatin1String( qfile_qss.readAll() );
		app.setStyleSheet( qstr_style );

		qfile_qss.close();
	}
	else
	{
		// logger.Log( hatsuiki::SyncFileLogger::EnumLevel::Error, "qss file fails to open" );
		std::cout << "qss file open failed" << std::endl;
	}
}

void LoadConfig()
{
	QString path_app = QDir::currentPath();
	QString filename_config = "config.ini";
	QString path_config = path_app + QDir::separator() + filename_config;
	path_config = QDir::toNativeSeparators( path_config );

	std::cout << path_app.toStdString() << std::endl;

	QSettings setting( path_config, QSettings::IniFormat );

	QString host = setting.value( "GateServer/host" ).toString();
	QString port = setting.value( "GateServer/port" ).toString();

	gate_url_prefix = "http://" + host + ":" + port;
}

#include <windows.h>

int main( int argc, char* argv[] )
{
	SetConsoleOutputCP( CP_UTF8 );

	QApplication app( argc, argv );

	LoadQss( app );
	LoadConfig();

	ChatClient win;
	win.show();

	return app.exec();
}
