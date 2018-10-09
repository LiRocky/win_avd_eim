#include "sessionLayout.h"
#include "sessionContent.h"
#include "sessionBottom.h"
SessionLayout::SessionLayout(QWidget* parent) :QWidget(parent)
{
	init();
	//show();
}

SessionLayout::~SessionLayout()
{

}

void SessionLayout::init()
{
	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);
	m_sessionHeadBar = new SessionHeaderWidget(this);
	m_sessionWidgets = new QStackedWidget;

	m_sendDescription = new SessionBottom;
	m_spliter = new QSplitter(this);
	m_sessionWidgets->move(0, 0);
	m_sendDescription->setFixedHeight(55);
	m_layout->insertWidget(0, m_sessionHeadBar);
	m_layout->insertWidget(1, m_spliter);


	m_spliter->setOrientation(Qt::Orientation::Vertical);
	m_spliter->addWidget(m_sessionWidgets);
	m_spliter->addWidget(m_sendDescription);
	m_spliter->setStretchFactor(0, 3);
	m_spliter->setStretchFactor(3, 4);
	m_spliter->setHandleWidth(0);
	m_spliter->setChildrenCollapsible(false);

	m_sessionHeadBar->setMinimumHeight(55);
	m_sessionWidgets->setMinimumHeight(200);
	m_sendDescription->setMaximumHeight(500);
	m_sendDescription->setMinimumHeight(200);
	

	//connect
	connect(m_sendDescription, SIGNAL(sig_sendMsgbtnClicked()), this, SLOT(slot_sendMsg()));

	setCurrntSessionId("s");
}

void SessionLayout::slot_sendMsg()
{
	currentSession()->addMsgItem(m_sendDescription->getText(), QDateTime::currentDateTime().toTime_t());
	currentSession()->addMsgItem(m_sendDescription->getText(), QDateTime::currentDateTime().toTime_t(), false);
}

void SessionLayout::slot_recvMsg(QString user,QString strMsg, QDateTime strTime)
{

}

SessionContent* SessionLayout::currentSession()
{
	return m_curSession;
}

void SessionLayout::setCurrntSessionId(QString seesion_id)
{
	if (seesion_id.isEmpty())
	{
		return;
	}
	auto session = m_contentWidMap.find(seesion_id);
	if (session == m_contentWidMap.end())
	{
		SessionContent* newSession = new SessionContent;
		m_contentWidMap.insert(seesion_id, newSession);
		session = m_contentWidMap.find(seesion_id);
	}
	m_curSession = *session;

	//ÇÐ»»ÁÄÌì¿ò
	int index = m_sessionWidgets->indexOf(m_curSession);
	if (index == -1)
	{
		m_sessionWidgets->addWidget(m_curSession);
		m_curSession->layout()->setMargin(0);
	}
	m_sessionWidgets->setCurrentWidget(m_curSession);
}
