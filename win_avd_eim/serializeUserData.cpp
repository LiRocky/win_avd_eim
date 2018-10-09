#include "SerializeUserData.h"
#include <qDebug>
#include <QDataStream>
#define KEY 'X'

char encrypt(char plainText, char key)
{
	return plainText ^ key;
}

// 
char decrypt(char cipherText, char key)
{
	return cipherText ^ key;
}

QString iencryData(QString indata)
{
	std::string s = indata.toStdString();
	std::string sout;
	int sz = s.size();
	for (int i = 0; i < sz; ++i)
	{
		sout += encrypt(s[i], KEY);
	}

	return sout.c_str();
}

QString idecryData(QString indata)
{
	std::string s = indata.toStdString();
	std::string sout;
	int sz = s.size();
	for (int i = 0; i < sz; ++i)
	{
		sout += decrypt(s[i], KEY);
	}

	return sout.c_str();
}
CSerializeUserData::CSerializeUserData()
{
}


CSerializeUserData::~CSerializeUserData()
{

}

void CSerializeUserData::ReadData()
{
	QFile file(GetRootPath() + SERIA_FILE);

	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug() << "readdata open failed.";
		return;
	}

	QDataStream in(&file);    // read the data serialized from the file  

	int roomsnum = 0;
	QString tmpstr;
	in >> tmpstr;
	_userInfo.loginUsrName = decryData(tmpstr);
	in >> tmpstr;
	_userInfo.loginUserPwd = decryData(tmpstr);
	in >> tmpstr;
	_userInfo.lastShowJoinUserName = tmpstr;// decryData(tmpstr);
	in >> roomsnum;
	while (roomsnum > 0)
	{
		in >> tmpstr;
		QString roomd = decryData(tmpstr);
		if (!roomd.isEmpty() && !roomd.isNull() && (roomd != ""))
			_userInfo.roomIds.push_back(roomd);
		roomsnum--;
	}

	file.close();
}
void CSerializeUserData::SaveData()
{
	QFile sFile(GetRootPath() + SERIA_FILE);

	if (sFile.exists())
		sFile.remove();

	if (!sFile.open(QIODevice::WriteOnly))
	{
		qDebug() << "save date failed.";
		return;
	}

	QDataStream out(&sFile);   // we will serialize the data into the file  

	//if (!_userInfo.loginUsrName.isNull())
	out << encryData(_userInfo.loginUsrName);   // serialize a string  
	//if (!_userInfo.loginUserPwd.isNull())
	out << encryData(_userInfo.loginUserPwd);        // 
	//if (!_userInfo.lastShowJoinUserName.isNull())
	out << _userInfo.lastShowJoinUserName;// encryData(_userInfo.lastShowJoinUserName);

	int s = _userInfo.roomIds.size();
	out << s;
	for (int i = 0; i < s; ++i)
		out << encryData(_userInfo.roomIds[i]);

	sFile.close();
}
void CSerializeUserData::SetUserNamePwd(QString user, QString pwd)
{
	_userInfo.loginUsrName = user;
	_userInfo.loginUserPwd = pwd;
}
bool CSerializeUserData::FindRoomIdisexist(QString roomid)
{
	if (_userInfo.roomIds.indexOf(roomid, 0) >= 0)
		return true;
	else
		return false;
}
QString CSerializeUserData::encryData(QString data)
{
	if (!data.isEmpty() && !data.isNull())
		return iencryData(data);
	else
		return "";
}
QString CSerializeUserData::decryData(QString data)
{
	if (!data.isEmpty() && !data.isNull())
		return idecryData(data);
	else
		return "";
}

