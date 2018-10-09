#include "mainwindow.h"
#include "widgets/chatItem.h"
#include <QListWidgetItem>
#include <QPainter>
#include <QIcon>
#include "widgets/sessionLayout.h"
#include "widgets/chatWidget.h"
#include "widgets/deptWdiget.h"
#include "base.h"
MainWindow::MainWindow(QWidget *parent)
: QWidget(parent),m_tray(NULL)
{
	ui.setupUi(this);
	init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
	setObjectName("mainWindow");
	setWindowFlags(windowFlags()  | Qt::FramelessWindowHint);


	this->setStyleSheet(GetQss("custom/qss/mainWindow.qss"));
	this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
	setMouseTracking(true);
	createSystemTray();
	resize(940, 860);
	
	m_chatWidget = new ChatWidget(this);
	m_deptWidget = new DeptWidget(this);
	ui.stackedWidget->addWidget(m_chatWidget);
	ui.stackedWidget->addWidget(m_deptWidget);
	//ui.stackedWidget->widget(0)->layout()->setMargin(0);
	ui.stackedWidget->setCurrentWidget(m_chatWidget);

	ui.btn_min->setCursor(QCursor(Qt::PointingHandCursor));
	ui.btn_max->setCursor(QCursor(Qt::PointingHandCursor));
	ui.btn_close->setCursor(QCursor(Qt::PointingHandCursor));
	ui.btn_chatPage->setCursor(QCursor(Qt::PointingHandCursor));
	ui.btn_deptPage->setCursor(QCursor(Qt::PointingHandCursor));
	ui.btn_restore->setCursor(QCursor(Qt::PointingHandCursor));
	ui.btn_restore->hide();

	ui.frameLeftwidget->setMouseTracking(true);
	ui.stackedWidget->setMouseTracking(true);
	ui.widget_2->setMouseTracking(true);
	m_chatWidget->setMouseTracking(true);
	//
	m_cursorPos = 0;

	//connect
	connect(ui.btn_min, SIGNAL(clicked()), this, SLOT(showMinimized()));
	connect(ui.btn_max, SIGNAL(clicked()), this, SLOT(slot_showMaximized()));
	connect(ui.btn_restore, SIGNAL(clicked()), this, SLOT(slot_showNormal()));
	connect(ui.btn_chatPage, SIGNAL(clicked()), this, SLOT(slot_chatPage()));
	connect(ui.btn_deptPage, SIGNAL(clicked()), this, SLOT(slot_departmentPage()));

	connect(m_action_open, SIGNAL(triggered()), this, SLOT(slot_action_open()));
	connect(m_action_quit, SIGNAL(triggered()), this, SLOT(slot_action_quit()));
	connect(m_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActived(QSystemTrayIcon::ActivationReason)));
}

void MainWindow::createSystemTray()
{
	m_tray = new QSystemTrayIcon(this);
	m_tray->setObjectName("systemtray");
	QIcon icon = QIcon(GetRootPath() + "/custom/images/tray_icon.png");
	m_tray->setIcon(icon);
	m_tray->setToolTip("AVD_IM");
	m_trayMenu = new QMenu;
	m_action_open =new QAction("open", m_trayMenu);
	m_action_quit = new QAction("quit", m_trayMenu);
	m_trayMenu->addAction(m_action_open);
	m_trayMenu->addAction(m_action_quit);
	m_tray->setContextMenu(m_trayMenu);
	m_tray->hide();
}


void MainWindow::showSystemTray(bool show/*=true*/)
{
	show ? m_tray->show() : m_tray->hide();
}

void MainWindow::showSystemTrayTip(bool show/*=true*/)
{
	if (show)
	{
		if (m_trayTipTimer>0)
		{
			killTimer(m_trayTipTimer);
		}
		m_trayTipTimer = startTimer(1000);
	}
	else
	{
		killTimer(m_trayTipTimer);
		showSystemTray(true);
	}
}

int MainWindow::countFlag(QPoint p, int row)
{
	if (p.y()<MARGIN)
		return 10 + row;
	else if (p.y()>this->height() - MARGIN)
		return 30 + row;
	else
		return 20 + row;		
}

void MainWindow::setCursorType(int flag)
{
	Qt::CursorShape cursor;
	switch (flag)
	{
	case 11:
	case 33:
		cursor = Qt::SizeFDiagCursor; break;
	case 13:
	case 31:
		cursor = Qt::SizeBDiagCursor; break;
	case 21:
	case 23:
		cursor = Qt::SizeHorCursor; break;
	case 12:
	case 32:
		cursor = Qt::SizeVerCursor; break;
	case 22:
		cursor = Qt::ArrowCursor; break;
	default:
		//  QApplication::restoreOverrideCursor();//恢复鼠标指针性状
		break;

	}
	setCursor(cursor);		
}

int MainWindow::countRow(QPoint p)
{
	return (p.x()<MARGIN) ? 1 : (p.x()>(this->width() - MARGIN) ? 3 : 2);		
}

void MainWindow::selectChatItem(QString sid, SessionType type)
{
	m_chatWidget->SelectChatItem(sid, ChatItemWidget::ItemType(type));
	slot_chatPage();
}

void MainWindow::slot_action_open()
{	
	show();
	raise();
	this->setWindowState(Qt::WindowActive);
	activateWindow();
	
}
#include "api/mdepartment.h"
void MainWindow::slot_action_quit()
{
	tee3::eim::Client* client = tee3::eim::Client::instance();
	tee3::eim::IDepartment* dept = tee3::eim::IDepartment::obtain(client);
	tee3::eim::Department dpitem;
	tee3::eim::UsersType users;
	dept->getDepartment(3, dpitem);
	dept->getDepartmentUserInfos(1, users);
	dept->getDepartmentUserInfos(2, users);
	dept->getDepartmentUserInfos(3, users);
	tee3::eim::DepartmentsType subs;
	dept->getDepartmentChilds(1, subs);
	dept->getDepartmentChilds(2, subs);
	QString sName = QString::fromUtf8(dpitem.getName().c_str());
	dept->getDepartmentChilds(3, subs);
	sName = QString::fromUtf8(dpitem.getName().c_str());
}

void MainWindow::trayActived(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Unknown:
		break;
	case QSystemTrayIcon::Context:
		break;
	case QSystemTrayIcon::DoubleClick:
		slot_action_open();
		break;
	case QSystemTrayIcon::Trigger:
		slot_action_open();
		break;
	case QSystemTrayIcon::MiddleClick:
		break;
	default:
		break;
	}
}

void MainWindow::slot_showMaximized()
{
	showMaximized();
	ui.btn_max->hide();
	ui.btn_restore->show();
}

void MainWindow::slot_showNormal()
{
	showNormal();
	ui.btn_max->show();
	ui.btn_restore->hide();
}
#include "api/mdepartment.h"
#include "api/mgroup.h"
#include "api/mchat.h"
void MainWindow::slot_chatPage()
{
	tee3::eim::Client* client = tee3::eim::Client::instance();
	tee3::eim::IDepartment* dept = tee3::eim::IDepartment::obtain(client);
	tee3::eim::Department dpitem;
	tee3::eim::DepartmentsType dptTypes;
	dept->getDepartmentChilds(0, dptTypes);
	while (dptTypes.size()>0)
	{		
		dept->getDepartmentChilds(dptTypes[0].getId(), dptTypes);
	}
	tee3::eim::GroupsType groups;
	tee3::eim::IGroup* gp = tee3::eim::IGroup::obtain(client);
	gp->getAllMyGroups(groups);
	tee3::eim::IChat* chat = tee3::eim::IChat::obtain(client);
	chat->deleteAllSessions(true);
	tee3::eim::UserInfo item = client->getUser(14);
	tee3::eim::UserInfo in = client->getSelf();
	if (item.isValid()) {
		chat->deleteAllSessions(true);
		tee3::eim::SessionsType aaa;
		chat->getLastSessions(100, aaa);
		tee3::eim::Message msg;
		msg.setSessionId(item.getId());
		msg.setContent("abcde");
		chat->sendMessage(msg);
	}
	
	ui.stackedWidget->setCurrentWidget(m_chatWidget);
}

void MainWindow::slot_departmentPage()
{
	ui.stackedWidget->setCurrentWidget(m_deptWidget);
	m_deptWidget->updateDeptInfo();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{	
	if (event->type() == QEvent::ToolTip)
	{
		slot_action_open();
	}
	return false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	int poss = countFlag(event->pos(), countRow(event->pos()));
	setCursorType(poss);
	if (mouse_press)
	{
		QPoint move_pos = event->globalPos();
		


		//if (isMaximized()) {
		//	//this->showNormal(); // 拖动最大化的窗口是否需要变成正常？
		//	//resize(800, 600);
		//	//move(x, y);
		//	//isMaxWindow = false;
		//	//m_windowPos = point;
		//}
		//QRect clientRect = QApplication::desktop()->availableGeometry();
		//if (event->globalY() < 4){ // 鼠标拖动窗体到屏幕顶端最大化窗体
		//	slot_showMaximized();
		//	move(0, 0);
		//	//isMaxWindow = true;
		//}
		//if (event->globalX() < 4){// 鼠标拖动窗体到屏幕最左端窗体占左半边屏幕大小
		//	resize(clientRect.width() / 2, clientRect.height());
		//	move(0, 0);
		//	//isMaxWindow = false;
		//}
		//if (event->globalX() > clientRect.width() - 4){// 鼠标拖动窗体到屏幕最右端窗体占右半边屏幕大小
		//	resize(clientRect.width() / 2, clientRect.height());
		//	move(clientRect.width() / 2, 0);
		//	//isMaxWindow = false;
		//}
		QPoint ptemp = move_pos - m_lastCursorPoint;
		if (m_cursorPos!=22)
		{
			QRect wid = geometry();

			switch (m_cursorPos)//改变窗口的大小
			{

			case 11:wid.setTopLeft(wid.topLeft() + ptemp); break;//左上角
			case 13:wid.setTopRight(wid.topRight() + ptemp); break;//右上角
			case 31:wid.setBottomLeft(wid.bottomLeft() + ptemp); break;//左下角
			case 33:wid.setBottomRight(wid.bottomRight() + ptemp); break;//右下角
			case 12:wid.setTop(wid.top() + ptemp.y()); break;//中上角
			case 21:wid.setLeft(wid.left() + ptemp.x()); break;//中左角
			case 23:wid.setRight(wid.right() + ptemp.x()); break;//中右角
			case 32:wid.setBottom(wid.bottom() + ptemp.y()); break;//中下角
			}
			setGeometry(wid);	
			m_lastCursorPoint = event->globalPos();
		}
		else
		{
			move(move_pos - move_point);
		}
	}
	else
	{
		QRect rcTray = m_tray->geometry();
		if (rcTray.contains(QCursor::pos()))
		{
			slot_action_open();
		}
	}
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		mouse_press = true;
		m_cursorPos = countFlag(event->pos(), countRow(event->pos()));
		m_lastCursorPoint = event->globalPos();
	}
	move_point = event->globalPos() - pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
	mouse_press = false;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
	QRect rc = ui.widget_2->geometry();
	QPoint pt = ui.widget_2->mapFromGlobal(QCursor::pos());
	if (rc.contains(pt))
	{
		if (isMaximized())
		{
			slot_showNormal();
		}
		else
		{
			slot_showMaximized();
		}
	}
}

void MainWindow::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);

	QPainter painter(this);
	painter.save();
	QPen pen(QColor(75, 150, 250));
	QBrush brush(QColor(75, 150, 250));
	painter.setBrush(brush);
	painter.setPen(pen);
	QRect rcleft = ui.frameLeftwidget->geometry();
	painter.drawRoundedRect(rcleft,5,5);
	rcleft.adjust(rcleft.right() - 5, rcleft.top(), 0, 0);
	painter.drawRect(rcleft);
	painter.restore();
}

void MainWindow::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_trayTipTimer)
	{
		static bool bv = true;
		QIcon icon = bv?QIcon(GetRootPath() + "/custom/images/tray_icon.png"):QIcon();
		m_tray->setIcon(icon);
		bv = !bv;
	}
}

void MainWindow::resizeEvent(QResizeEvent *event)
{

}


