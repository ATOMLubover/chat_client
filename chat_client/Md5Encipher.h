#pragma once

#include <QString>
#include <QCryptographichash>

// MD5 �ַ���������
class Md5Encipher
{
public:
	static QString Encrypt( const QString& input )
	{
		QByteArray bytes_input = input.toUtf8(); // �������ַ���ת��Ϊ�ֽ�����
		QByteArray hash = QCryptographicHash::hash( 
			bytes_input, QCryptographicHash::Md5 ); // ʹ�� MD5 ���м���
		return QString( hash.toHex() ); // ����ʮ�����Ƹ�ʽ�ļ��ܽ��
	}
};