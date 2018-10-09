#pragma once
#include "base.h"

#define SERIA_FILE "ikeep.data"
struct LoginUserInfo
{
	QString loginUsrName;
	QString loginUserPwd;
	QString lastShowJoinUserName;
	QList<QString> roomIds;

	LoginUserInfo()
	{
		init();
	}
	void init()
	{
		loginUsrName.clear();
		loginUserPwd.clear();
		lastShowJoinUserName.clear();
		roomIds.clear();
	}

	void operator =(const LoginUserInfo& cp)
	{
		loginUsrName = cp.loginUsrName;
		loginUserPwd = cp.loginUserPwd;
		lastShowJoinUserName = cp.lastShowJoinUserName;
		int sz = cp.roomIds.size() > 3 ? 3 : cp.roomIds.size();
		roomIds.clear();
		for (int i = 0; i < sz; ++i)
		{
			roomIds.push_back(cp.roomIds[i]);
		}
	}
};

class CSerializeUserData
{
public:
	CSerializeUserData();
	~CSerializeUserData();
	void ReadData();
	void SaveData();

	QString encryData(QString data);
	QString decryData(QString data);
	void copydata(const LoginUserInfo& dt){ _userInfo = dt; }

	void SetUserNamePwd(QString user, QString pwd);
	LoginUserInfo& GetUserData(){ return _userInfo; }
	bool FindRoomIdisexist(QString roomid);
private:
	LoginUserInfo _userInfo;

};

