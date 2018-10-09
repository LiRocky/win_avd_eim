#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMainWindow>
#include "ui_login.h"
#include <QPoint>
#include <QMouseEvent>
#include <QDebug>

class LoginPage :public QMainWindow
{
	Q_OBJECT
public:
	LoginPage();
	~LoginPage();
	QString getPwd();
	QString getUserName();
	void setUserName(QString userName);
	void setPwd(QString pwd);
protected:
	void init();
	public slots:
	void slot_minWnd();
	void slot_closeWnd();
	void slot_setting();
	void slot_loginClick();

	protected slots:
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void paintEvent(QPaintEvent *event);
signals:
	void sig_login();
private:
	Ui::login ui;

	bool mouse_press;
	QPoint move_point;
};

#endif