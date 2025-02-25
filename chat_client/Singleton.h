#pragma once

#include <memory>
#include <mutex>
#include <format>
#include <iostream>

template<class T>
class Singleton
{
public:
	static std::shared_ptr<T> GetInstance()
	{
		std::once_flag flag;
		std::call_once( flag, [&] () { instance = std::shared_ptr<T>( new T ); } );

		return instance;
	}

public:
	Singleton( const Singleton& ) = delete;
	Singleton& operator=( const Singleton& ) = delete;

	void PrintAddress() const
	{
		std::cout << std::format( "singleton address: {:p}\n", instance.get() );
	}

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

protected:
	static std::shared_ptr<T> instance;
};

template<class T>
std::shared_ptr<T> Singleton<T>::instance = nullptr;