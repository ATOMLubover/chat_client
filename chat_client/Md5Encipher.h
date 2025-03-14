#pragma once

#include <QString>
#include <QCryptographichash>

// MD5 字符串加密器
class Md5Encipher
{
public:
	static QString Encrypt( const QString& input )
	{
		QByteArray bytes_input = input.toUtf8(); // 将输入字符串转换为字节数组
		QByteArray hash = QCryptographicHash::hash( 
			bytes_input, QCryptographicHash::Md5 ); // 使用 MD5 进行加密
		return QString( hash.toHex() ); // 返回十六进制格式的加密结果
	}
};