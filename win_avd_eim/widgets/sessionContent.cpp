#include "sessionContent.h"
#include "messageItem.h"
#include "base.h"
#include <QListWidgetItem>
SessionContent::SessionContent(QWidget* parent) :QWidget(parent)
{
	init();	
}

SessionContent::~SessionContent()
{
	DELETE_IF(m_layout)
}

void SessionContent::init()
{
	setContentsMargins(0, 0,0,0);
	m_layout = new QVBoxLayout(this);
	m_msgItemList = new QListWidget(this);
	m_layout->addWidget(m_msgItemList);	
	m_msgItemList->setObjectName("chatContent");
	m_msgItemList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void SessionContent::addMsgItem(QString strMsg,quint32 timeStamp,bool selfMsg/* =true */)
{
	if (strMsg.isEmpty())
	{
		return;
	}
	addTimeTip(timeStamp);
	ChatMessageItem* msgitem = new ChatMessageItem(m_msgItemList);
	QListWidgetItem*  listitem = new QListWidgetItem(m_msgItemList);
	

	msgitem->setFixedWidth(this->width());
	QSize size = msgitem->fontRect(strMsg);
	listitem->setSizeHint(size);

	msgitem->setText(strMsg, timeStamp, size,
		selfMsg?ChatMessageItem::User_Me:ChatMessageItem::User_Other);
	m_msgItemList->setItemWidget(listitem, msgitem);
	m_msgItemList->scrollToBottom();
}

void SessionContent::addTimeTip(quint32 time)
{
	bool needTimeTip = false;
	if (m_msgItemList->count() > 0)
	{
		QListWidgetItem* lastItem = m_msgItemList->item(m_msgItemList->count() - 1);
		ChatMessageItem* lastMsgItem = (ChatMessageItem*)m_msgItemList->itemWidget(lastItem);
		if (NULL != lastMsgItem)
		{
			quint32 lastMsgTime = lastMsgItem->time();
			needTimeTip = (time - lastMsgTime > 10) ?  true : false;
		}

	}
	if (needTimeTip)
	{
		QListWidgetItem* item = new QListWidgetItem(m_msgItemList);
		ChatMessageItem* timeItem = new ChatMessageItem(m_msgItemList);
		
		QSize size = QSize(this->width(), 40);
		timeItem->resize(size);
		item->setSizeHint(size);
		timeItem->setText("time", QDateTime::currentDateTime().toTime_t(), size, ChatMessageItem::User_Time);
		m_msgItemList->setItemWidget(item, timeItem);
		
	}
}
#include <QResizeEvent>
void SessionContent::resizeEvent(QResizeEvent *event)
{
	int nCount = m_msgItemList->count();
	
	for (int i = 0; i < nCount;i++)
	{
		QListWidgetItem* item = m_msgItemList->item(i);
		ChatMessageItem* msgItem = (ChatMessageItem*)m_msgItemList->itemWidget(item);
		if (NULL != msgItem)
		{		
			msgItem->setFixedWidth(event->size().width());
			msgItem->fontRect(msgItem->text());			
		}
	}

}
