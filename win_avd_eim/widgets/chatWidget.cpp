#include "chatWidget.h"
#include "chatItem.h"
#include <QVBoxLayout>
#include <QListWidgetItem>
#include "base.h"
ChatWidget::ChatWidget(QWidget* parent) :QSplitter(parent)
{
	init();
	//show();
}

ChatWidget::~ChatWidget()
{
	DELETE_IF(m_listWidget)
	DELETE_IF(m_sessionLayout)
}

void ChatWidget::init()
{	
	m_listWidget = new QListWidget;
	m_sessionLayout = new SessionLayout;
	this->addWidget(m_listWidget);
	this->addWidget(m_sessionLayout);
	m_listWidget->setMinimumWidth(210);
	m_listWidget->setMaximumWidth(350);
	m_listWidget->installEventFilter(this);
	this->move(40, 60);
	this->setStretchFactor(0, 3);
	this->setStretchFactor(1, 5);
	//thisr->setFixedSize(800, 800);
	this->setChildrenCollapsible(false);
	this->show();
	this->setHandleWidth(0);

	//connection	
	connect(m_listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
		this, SLOT(slot_SelectedchatItemChanged(QListWidgetItem*, QListWidgetItem*)));

	//init data
	addChatItem("M", "HAHAH", "14,13", "this is for you");
	addChatItem("Ma", QStringLiteral("成都研发"), "14,13", "this is for you");
	addChatItem("Mac", QStringLiteral("杭州三体科技网络有限公司"), "14,13", "this is for you,asdfasdfasdfaasdfawef");
	addChatItem("Macs", QStringLiteral("杭州三体科技网络有限公司"), "14,13", "this is for you,asdfasdfasdfaasdfawef");

}

ChatItemWidget* ChatWidget::addChatItem(QString name, QString title, QString time, QString msg, int index /*= -1*/)
{
	ChatItemWidget* chatitem = new ChatItemWidget;
	chatitem->setName(name);
	chatitem->setTime(time);
	chatitem->setTitle(title);
	chatitem->setMsgContent(msg);
	QListWidgetItem* item = new QListWidgetItem();
	item->setSizeHint(QSize(200, 65));
	m_listWidget->insertItem(0, item);
	m_listWidget->setItemWidget(item, chatitem);
	return chatitem;
}

void ChatWidget::SelectChatItem(QString sid, ChatItemWidget::ItemType type)
{
	
	//find item by id
	ChatItemWidget* chatItem = NULL;
	int nCount = m_listWidget->count();
	for (int i = 0; i < nCount;i++)
	{
		QListWidgetItem* listItem = m_listWidget->item(i);
		if (listItem)
		{
			chatItem = (ChatItemWidget*)m_listWidget->itemWidget(listItem);
			if (chatItem && chatItem->getChatId()==sid&&
				chatItem->getItemType() == type)
			{
				m_listWidget->setCurrentItem(listItem);
				break;
			}
			chatItem = NULL;
		}
	}
	//not exists,add new item
	if (NULL == chatItem)
	{//get session inof
		ChatItemWidget* item =addChatItem("", "new", "1245", "asf");
		item->setChatId(sid);
		item->setItemType(type);
		//m_listWidget->setCurrentItem(item);
	}
}

void ChatWidget::slot_SelectedchatItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
#if 1
	if (current)
	{
		ChatItemWidget* curChatItem = (ChatItemWidget*)m_listWidget->itemWidget(current);
		curChatItem->setReadedFlag(true);
		curChatItem->setReadTipVisible(false);
	}
	if (previous)
	{
		ChatItemWidget* preChatItem = (ChatItemWidget*)m_listWidget->itemWidget(previous);
		preChatItem->setReadedFlag(false);
		preChatItem->setReadTipVisible(true);
		
	}
	m_sessionLayout->setCurrntSessionId(QString(m_listWidget->row(current)));
#endif
}

bool ChatWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == m_listWidget)
	{
		if (event->type() == QEvent::Enter) 
		{
			setCursor(Qt::ArrowCursor);
			return true;
		}
		else
		{
			return false;
		}
	}
	else {
		// pass the event on to the parent class
		return QWidget::eventFilter(obj, event);
	}
}
