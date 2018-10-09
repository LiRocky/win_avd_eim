#include "userInfoWidget.h"

UserInfoWidget::UserInfoWidget()
{
	ui.setupUi(this);

	//connect
	connect(ui.btn_sendMsg, SIGNAL(clicked()), this, SLOT(slot_sendMsgBtnClick()));
}

UserInfoWidget::~UserInfoWidget()
{

}

void UserInfoWidget::slot_sendMsgBtnClick()
{
	emit sig_sendMsgBtnClicked(m_id);
}
