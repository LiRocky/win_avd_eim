#include "loginModule.h"
#include "base.h"

using namespace tee3::eim;
LoginModule::LoginModule()
{
	
	init();
}

LoginModule::~LoginModule()
{
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

}

void LoginModule::slot_login()
{
	Client* client = Client::instance();

	const std::string eim_server_address = "60.12.6.42:6195";
	client->setParam(cp_serveraddress, eim_server_address);	
	Result result_ = 0;
	result_ = client->login("pengli", "123456", "d",
		std::bind(&LoginModule::cb_loginRes,
		this,
		std::placeholders::_1,
		std::placeholders::_2));
	m_userData->GetUserData().loginUsrName = m_loginPage->getUserName();
	m_userData->GetUserData().loginUserPwd = m_loginPage->getPwd();
}
