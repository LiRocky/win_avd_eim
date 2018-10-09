#include "login.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include "base.h"
#include "..\inc\api\client.h"
#include "login.h"
#include "modules/mainModule.h"
using namespace tee3::eim;
void cb2(Result res, const OtherSpotsType& others)
{
	qDebug() << res;
}
typedef std::function<void (int)> test_cb;
class myCb
{
public:
	void test(int i){
		int k = i;
		qDebug() << "this is a test"<<i;
	}

private:

};

class CTest
{
public:
	void setCb(test_cb* cb){ m_cb = cb; }
	void invoke(){ (*m_cb)(3); }
private:
	test_cb* m_cb;
};

int main(int argc, char *argv[])
{
	qRegisterMetaType<Result>("Result");
#if 1
	QApplication a(argc, argv);
	/*Client* client = Client::instance();

	const std::string eim_server_address = "60.12.6.42:6195";
	client->setParam(cp_serveraddress, eim_server_address);
	bool   called_ = false;
	Result result_ = 0;
	result_ = client->login("pengli", "123456", "d", [&called_, &result_](Result result, const OtherSpotsType& others) {
		called_ = true;
		result_ = result;
	});*/
	MainModule* module = MainModule::Instance();
	module->showLoginPage();
	InitLogFile();
	delExpiredLogs();
	qInstallMessageHandler(myMessageOutput);
	qDebug() << "fuck";
	a.exec();
	closeLogFile();
	
#endif
#if 0
	myCb cb;
	CTest test;
	test_cb tcb = std::bind(&myCb::test, &cb, std::placeholders::_1);
	//test.setCb(cb.tcb);
	test.setCb((test_cb*)(&std::bind(&myCb::test, &cb, std::placeholders::_1)));
	test.invoke();
#endif
	
	return 0;
}
