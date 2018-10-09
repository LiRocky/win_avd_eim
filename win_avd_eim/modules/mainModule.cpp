#include "mainModule.h"
#include "api/mdepartment.h"
#include "api/object.h"
#include "loginModule.h"
#include "../mainwindow.h"
#include "./widgets/userInfoWidget.h"
MainModule::MainModule()
{
	init();
}

MainModule::~MainModule()
{
	DELETE_IF(m_loginModule)
	DELETE_IF(m_mainWindow)
}

MainModule* MainModule::Instance()
{
	static MainModule module;
	return &module;
}

void MainModule::init()
{
	m_loginModule = new LoginModule;
	m_mainWindow = new MainWindow;
	m_userInfoWidget = new UserInfoWidget;
	//connection 
	bool br = connect(m_loginModule, SIGNAL(sig_logResult(Result)), this, SLOT(slot_loginRes(Result)));
	connect(m_userInfoWidget, SIGNAL(sig_sendMsgBtnClicked(int)), this, SLOT(slot_clickUserInfoWidget(int)));
}

void MainModule::showLoginPage(bool show/*=true*/)
{
	m_loginModule->showLoginPage(show);
}

void MainModule::showMainWindow(bool show /*= true*/, bool showTray /*= true*/)
{
	m_mainWindow->show();
	m_mainWindow->showSystemTray();
	//获取聊天信息，部门信息，恢复之前的聊天内容
}

void MainModule::setCurrentSession(int sid, SessionType st)
{
	m_mainWindow->selectChatItem(QString::number(sid),st);
}

void MainModule::showUserInfoWidget(int id)
{
	m_userInfoWidget->show();
	m_userInfoWidget->setId(id);
}

#include "api/mgroup.h"
void MainModule::slot_loginRes(Result res)
{
	if (res == 0)
	{
		showLoginPage(false);
		showMainWindow();
		tee3::eim::Client* client = tee3::eim::Client::instance();
		tee3::eim::IDepartment* dept = tee3::eim::IDepartment::obtain(client);
		tee3::eim::Department dpitem;
		dept->getDepartment(1, dpitem);
		
		tee3::eim::IGroup* igrp = tee3::eim::IGroup::obtain(client);
		tee3::eim::GroupsType grps;
		igrp->getAllMyGroups(grps);
	}
}

void MainModule::slot_clickUserInfoWidget(int sId)
{
	setCurrentSession(sId, SessionType::st_peers);
}
