#include "login.h"
#include "base.h"
#include <QPainter>
LoginPage::LoginPage()
{
	ui.setupUi(this);
	
	init();
}

LoginPage::~LoginPage()
{

}

QString LoginPage::getPwd()
{
	return ui.edit_pwd->text();
}

QString LoginPage::getUserName()
{
	return ui.edit_userName->text();
}

void LoginPage::setUserName(QString userName)
{
	ui.edit_userName->setText(userName);
}

void LoginPage::setPwd(QString pwd)
{
	ui.edit_pwd->setText(pwd);
}

void LoginPage::init()
{
	//for ui
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);
	ui.edit_userName->setPlaceholderText(QString::fromLocal8Bit("请输入用户名"));
	ui.edit_pwd->setPlaceholderText(QString::fromLocal8Bit("请输入密码"));
	ui.label_title->setText(QString::fromLocal8Bit("佳会"));
	this->setStyleSheet(GetQss("custom/qss/login.qss"));
	this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明

	ui.btn_close->setCursor(QCursor(Qt::PointingHandCursor));
	ui.btn_min->setCursor(QCursor(Qt::PointingHandCursor));
	ui.btn_setting->setCursor(QCursor(Qt::PointingHandCursor));
	ui.btn_login->setCursor(QCursor(Qt::PointingHandCursor));

	//built connection
	connect(ui.btn_setting, SIGNAL(clicked()), this, SLOT(slot_setting()));
	connect(ui.btn_min, SIGNAL(clicked()), this, SLOT(slot_minWnd()));
	connect(ui.btn_close, SIGNAL(clicked()), this, SLOT(slot_closeWnd()));
	connect(ui.btn_login, SIGNAL(clicked()), this, SLOT(slot_loginClick()));

}

void LoginPage::slot_minWnd()
{
	qDebug() << __FUNCTION__;
}

void LoginPage::slot_closeWnd()
{
	//this->close();
	QCoreApplication::exit(0);
}

void LoginPage::slot_setting()
{
	qDebug() << __FUNCTION__;
}

void LoginPage::slot_loginClick()
{
	qDebug() << __FUNCTION__;

	//check input
	if (getUserName().isEmpty())
	{
	}
	if (getPwd().isEmpty())
	{
	}

	emit sig_login();
}

void LoginPage::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		mouse_press = true;
	}
	move_point = event->globalPos() - pos();
}

void LoginPage::mouseReleaseEvent(QMouseEvent *)
{
	mouse_press = false;
}

void LoginPage::mouseMoveEvent(QMouseEvent *event)
{
	//移动窗口
	if (mouse_press)
	{
		QPoint move_pos = event->globalPos();
		move(move_pos - move_point);
	}
}

void LoginPage::paintEvent(QPaintEvent *event)
{
	

	QPainter painter(this);
	painter.save();
	QPen pen(QColor(75, 150, 250));
	QBrush brush(QColor(75, 150, 250));
	painter.setBrush(brush);
	painter.setPen(pen);
	QRect rcleft(0, 0, width(), 45);
	painter.drawRoundedRect(rcleft, 5, 5);
	//rcleft.adjust(rcleft.right() - 5, rcleft.top(), 0, 0);
	//painter.drawRect(rcleft);
	painter.restore();

	pen.setColor(QColor(247, 247, 247));
	brush.setColor(QColor(247, 247, 247));
	painter.setBrush(brush);
	painter.setPen(pen);
	QRect rcBack(0, 40, width(), height()-40);
	painter.drawRect(rcBack);
	//draw edit border
	pen.setColor(Qt::gray);	
	painter.setPen(pen);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QRect rcEdituser = ui.edit_userName->geometry();
	QRect rcEditPwd = ui.edit_pwd->geometry();
	QRect rcEdBoder(rcEdituser.left() - 30, rcEdituser.top(),
		rcEditPwd.width()+30, rcEditPwd.height());
	painter.drawRoundedRect(rcEdBoder, 5, 5);
	rcEdBoder.moveTop(rcEditPwd.top());
	painter.drawRoundedRect(rcEdBoder,5,5);
	

}
