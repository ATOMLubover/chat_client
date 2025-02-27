#include "FileLogger.hpp"

#include "ChatClient.h"
#include <QtWidgets/QApplication>
#include <QFile>

// hatsuiki::SyncFileLogger logger( "log.txt" );

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

int main( int argc, char* argv[] )
{
	QApplication app( argc, argv );
	LoadQss( app );

	ChatClient win;
	win.show();

	return app.exec();
}
