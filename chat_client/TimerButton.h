#pragma once

#include "IHasSlots.h"

#include <QPushButton>
#include <QTimer>
#include <QString>
#include <QMouseEvent>

#include <string>

// ���������һ��ʱ��İ�ť
class TimerButton
	: IHasSlots
	, public QPushButton
{ 
public:
	TimerButton( QWidget* parent = nullptr );
	~TimerButton();

	void SetBasicText( const std::string& new_text );

	void InitSlots() override;

	// ���£��ͷ�ʱ���ͷ��źţ����Ҳ�����һ��ʱ��
	void mouseReleaseEvent( QMouseEvent* event_mouse ) override;

private:
	static const int COUNT_TIME;

	std::string basic_text;

	QTimer* timer;
	int counter;
};