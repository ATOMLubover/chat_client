#include "TimerButton.h"

#include <iostream>

const int TimerButton::COUNT_TIME = 10;

TimerButton::TimerButton( QWidget* parent )
	: QPushButton( parent ) // base class
	, basic_text( "Get" )
	, timer( new QTimer( this ) ), counter( COUNT_TIME )
{
	InitSlots();
}

TimerButton::~TimerButton()
{ 
	timer->stop();
}

void TimerButton::SetBasicText( const std::string& new_text )
{
	basic_text = new_text;
}

void TimerButton::InitSlots()
{
	connect( timer, &QTimer::timeout,
			 this, [this] ()
			 {
				 counter--;
				 if ( counter <= 0 )
				 {
					 timer->stop();

					 counter = COUNT_TIME;
					 this->setText( basic_text.c_str() );
					 this->setEnabled( true );

					 return;
				 }

				 this->setText( QString::number( counter ) );
			 } );
}

void TimerButton::mouseReleaseEvent( QMouseEvent* event_mouse )
{ 
	if ( event_mouse->button() == Qt::LeftButton )
	{
		std::cout << "鼠标左键释放" << std::endl;

		this->setEnabled( false );
		this->setText( QString::number( counter ) );
		timer->start( 1000 );
		
		//emit clicked(); 貌似在基类的函数中会自动调用
	}
	// 最后还要调用基类的事件，保证按钮本身的效果不会消失
	QPushButton::mouseReleaseEvent( event_mouse );
}
