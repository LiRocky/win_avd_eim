#ifndef USERINFO_WIDGET_H
#define  USERINFO_WIDGET_H
#include "ui_userInfoWnd.h"
#include <QWidget>

class UserInfoWidget:public QWidget
{
	Q_OBJECT
public:
	UserInfoWidget();
	~UserInfoWidget();
	void setId(int id){ m_id = id; }
	int getId(){ return m_id; }
	public slots:
	void slot_sendMsgBtnClick();
signals:
	void sig_sendMsgBtnClicked(int);
private:
	Ui::userInfoWnd ui;
	int m_id;

};


#endif // !USERINFO_WIDGET_H
