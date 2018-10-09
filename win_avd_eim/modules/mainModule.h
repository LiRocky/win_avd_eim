#ifndef MAIN_MODULE_H
#define MAIN_MODULE_H
#include <QObject>
#include "api/combase.h"
class LoginModule;
class MainWindow;
class UserInfoWidget;
using namespace tee3::eim;
class MainModule :QObject
{
	Q_OBJECT
public:
	MainModule();
	~MainModule();
public:
	static MainModule* Instance();	
	void init();
	void showLoginPage(bool show = true);
	void showMainWindow(bool show = true, bool showTray = true);
	void setCurrentSession(int sid, tee3::eim::SessionType st);
	void showUserInfoWidget(int);
	public slots:
	void slot_loginRes(Result res);
	void slot_clickUserInfoWidget(int);
private:
	LoginModule* m_loginModule;
	MainWindow* m_mainWindow;
	UserInfoWidget* m_userInfoWidget;
};

#endif