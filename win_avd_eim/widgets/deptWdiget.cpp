#include "deptWdiget.h"
#include "deptItem.h"
#include <QVBoxLayout>
#include <QListWidgetItem>
#include "base.h"
#include "../modules/deptModule.h"
DeptWidget::DeptWidget(QWidget* parent) :QWidget(parent)
{
	init();
	//show();
}

DeptWidget::~DeptWidget()
{
	DELETE_IF(m_listWidget)
	
}

void DeptWidget::init()
{	
	m_listWidget = new QListWidget(this);
	m_deptInfoLayout = new DeptInfoLayout(this);
	m_layout = new QHBoxLayout(this);
	m_layout->setSpacing(0);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->addWidget(m_listWidget);
	m_layout->addWidget(m_deptInfoLayout);
	m_listWidget->setMinimumWidth(270);
	m_listWidget->setMaximumWidth(270);
	m_listWidget->installEventFilter(this);
	m_listWidget->show();

	//connection	
	connect(m_listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
		this, SLOT(slot_SelDeptItemChanged(QListWidgetItem*, QListWidgetItem*)));

	//init data	
	//updateDeptInfo();
}

DeptItemWidget* DeptWidget::addDeptItem(QString name)
{
	DeptItemWidget* chatitem = new DeptItemWidget(name);
	QListWidgetItem* item = new QListWidgetItem();
	item->setSizeHint(QSize(200, 65));
	m_listWidget->insertItem(0, item);
	m_listWidget->setItemWidget(item, chatitem);
	return chatitem;
}

void DeptWidget::updateDeptInfo()
{
	m_listWidget->clear();
	addDeptItem(QStringLiteral("my friends"))->setType(DeptItemWidget::FriendItem);
	addDeptItem(QStringLiteral("我的群组"))->setType(DeptItemWidget::GroupItem);
	//addDeptItem(QStringLiteral("杭州三体科技网络有限公司"))->setType(DeptItemWidget::DeptItem);
	tee3::eim::DepartmentsType subs;
	DeptModule module;
	module.getChildDeptInfo(0, subs);
	for each (Department deptInfo in subs)
	{
		QString sName = QString::fromUtf8(deptInfo.getName().c_str());
		DeptItemWidget* item = addDeptItem(sName);
		item->setType(DeptItemWidget::DeptItem);
		item->setId(deptInfo.getId());
	}
}

void DeptWidget::slot_SelDeptItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

	if (current)
	{
		DeptItemWidget* curChatItem = (DeptItemWidget*)m_listWidget->itemWidget(current);
		//curChatItem->setReadedFlag(true);
		//curChatItem->setReadTipVisible(false);
		DeptItemWidget::ItemType ty;
		switch (curChatItem->getItemType())
		{
		case DeptItemWidget::ItemType::DeptItem:
			m_deptInfoLayout->showDeptInfo(curChatItem->getId());			
			break;
		case DeptItemWidget::ItemType::FriendItem:
			m_deptInfoLayout->showFriendInfo();
			break;
		case DeptItemWidget::ItemType::GroupItem:
			m_deptInfoLayout->showGroupInfo();
			break;
		default:
			break;
		}
		m_deptInfoLayout->getHeader()->setIcon(curChatItem->getIcon());
		m_deptInfoLayout->getHeader()->setTitle(curChatItem->getTitle());
	}
}

bool DeptWidget::eventFilter(QObject *obj, QEvent *event)
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
