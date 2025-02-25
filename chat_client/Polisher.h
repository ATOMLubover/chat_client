#pragma once

#include <QWidget>
#include <QStyle>

class Polisher
{
public:
	static Polisher* GetInstance();

public:
	Polisher( const Polisher& ) = delete;
	Polisher& operator=( const Polisher& ) = delete;

	void Repolish( QWidget* widget );

private:
	Polisher() = default;
	~Polisher() = default;
};
