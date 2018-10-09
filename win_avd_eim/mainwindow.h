#ifndef WIN_AVD_EIM_H
#define WIN_AVD_EIM_H

#include <QtWidgets/QMainWindow>
#include <QListWidget>
#include <Qlist>
#include <QSplitter>
#include <QTextEdit>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>
#include "api/combase.h"
#define MARGIN 20
using namespace tee3::eim;

class ChatWidget;
class DeptWidget;
class MainWindow:public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	void init();
	void createSystemTray();
	void showSystemTray(bool show=true);
	void showSystemTrayTip(bool show=true);
	int countFlag(QPoint p, int row);
	void setCursorType(int flag);
	int countRow(QPoint p);
	void selectChatItem(QString sid, SessionType type);
	public slots:
	void slot_action_open();
	void slot_action_quit();
	void trayActived(QSystemTrayIcon::ActivationReason reason);
	void slot_showMaximized();
	void slot_showNormal();
	void slot_chatPage();
	void slot_departmentPage();
protected:	
	virtual bool eventFilter(QObject *watched, QEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	virtual void paintEvent(QPaintEvent *event);
	virtual void timerEvent(QTimerEvent *event);
	virtual void resizeEvent(QResizeEvent *event);
private:
	Ui::mainwindow ui;
	QSystemTrayIcon* m_tray;
	QMenu* m_trayMenu;
	QAction* m_action_open;
	QAction* m_action_quit;
	int m_trayTipTimer;
	ChatWidget* m_chatWidget;	
	DeptWidget* m_deptWidget;

	bool mouse_press;
	QPoint move_point;
	QPoint m_lastCursorPoint;
	int m_cursorPos;
};



/////////////////

#include <QHBoxLayout>
#include <QVBoxLayout>

#endif // WIN_AVD_EIM_H
