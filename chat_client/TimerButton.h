#pragma once

#include "IHasSlots.h"

#include <QPushButton>
#include <QTimer>
#include <QString>
#include <QMouseEvent>

#include <string>

// 点击后会禁用一段时间的按钮
class TimerButton
	: IHasSlots
	, public QPushButton
{ 
public:
	TimerButton( QWidget* parent = nullptr );
	~TimerButton();

	void SetBasicText( const std::string& new_text );

	void InitSlots() override;

	// 按下（释放时）释放信号，并且不可用一段时间
	void mouseReleaseEvent( QMouseEvent* event_mouse ) override;

private:
	static const int COUNT_TIME;

	std::string basic_text;

	QTimer* timer;
	int counter;
};