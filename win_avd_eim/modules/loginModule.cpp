#include "loginModule.h"
#include "base.h"

using namespace tee3::eim;
LoginModule::LoginModule()
{
	
	init();
}

LoginModule::~LoginModule()
{
	Client* client = Client::instance();
	client->logout(0);
	//client->destroy();
	DELETE_IF(m_loginPage)
	if (m_userData)
	{
		m_userData->SaveData();
		DELETE_IF(m_userData)
	}
}

void LoginModule::init()
{	
	m_loginPage = new LoginPage();
	m_userData = new CSerializeUserData;
	m_userData->ReadData();
	m_loginPage->setUserName(m_userData->GetUserData().loginUsrName);
	m_loginPage->setPwd(m_userData->GetUserData().loginUserPwd);
	//connect
	connect(m_loginPage, SIGNAL(sig_login()), this, SLOT(slot_login()));
	
}

void LoginModule::showLoginPage(bool show/*=true*/)
{
	if (m_loginPage)
	{
		show?m_loginPage->show():m_loginPage->hide();
	}
}

void LoginModule::cb_loginRes(Result res, const tee3::eim::OtherSpotsType&others)
{	
	emit sig_logResult(res);
	if (res == 0)
	{
		m_userData->GetUserData().loginUsrName = m_loginPage->getUserName();
		m_userData->GetUserData().loginUserPwd = m_loginPage->getPwd();
		m_userData->SaveData();
	}
}

void LoginModule::slot_login()
{
	tee3::eim::OtherSpotsType others;
	//cb_loginRes(0, others);
	//return;
	Client* client = Client::instance();

	const std::string eim_server_address = "60.12.6.42:6195";
	client->setParam(cp_serveraddress, eim_server_address);	
	client->start();
	Result result_ = 0;
	result_ = client->login(m_loginPage->getUserName().toStdString(),
		m_loginPage->getPwd().toStdString(),
		"d",
		std::bind(&LoginModule::cb_loginRes,
		this,
		std::placeholders::_1,
		std::placeholders::_2));
	
}
