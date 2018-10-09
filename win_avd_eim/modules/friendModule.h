#ifndef LOGIN_MODULE_H
#define LOGIN_MODULE_H
#include "api/client.h"
#include "login.h"
#include "serializeUserData.h"
#include <QObject>
class LoginModule:QObject
{
	Q_OBJECT
public:
	LoginModule();
	~LoginModule();
	void init();
	void showLoginPage(bool show=true);
	//call back
	void cb_loginRes(Result res,const tee3::eim::OtherSpotsType&others);

	public slots:
	void slot_login();
private:
	LoginPage* m_loginPage;
	CSerializeUserData* m_userData;
};

#endif