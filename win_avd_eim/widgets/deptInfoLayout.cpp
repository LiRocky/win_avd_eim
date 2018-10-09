#include "deptInfoLayout.h"
#include "base.h"
#include <QListWidgetItem>
#include "concreteDetpItem.h"
#include "../modules/deptModule.h"
DeptInfoLayout::DeptInfoLayout(QWidget* parent) :QWidget(parent)
{
	init();
}

DeptInfoLayout::~DeptInfoLayout()
{
	DELETE_IF(m_layout)
	DELETE_IF(m_infoHeader)
	DELETE_IF(m_stakedWidget)
//	DELETE_IF(m_friendItemList)
	//DELETE_IF(m_groupItemList)
	//DELETE_IF(m_deptItemList)
}

void DeptInfoLayout::init()
{
	m_layout = NULL;
	m_deptItemList = NULL;
	m_groupItemList = NULL;
	m_friendItemList = NULL;
	m_infoHeader = NULL;
	m_layout = new QVBoxLayout(this);	
	m_infoHeader = new DeptInfoHeaderWidget(this);
	m_stakedWidget = new QStackedWidget(this);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);
	m_layout->addWidget(m_infoHeader);
	m_layout->addWidget(m_stakedWidget);
	m_groupItemList = new QListWidget;
	m_friendItemList = new QListWidget;
	m_deptItemList = new QListWidget;
	m_stakedWidget->addWidget(m_groupItemList);
	m_stakedWidget->addWidget(m_friendItemList);
	m_stakedWidget->addWidget(m_deptItemList);
	m_infoHeader->setMinimumHeight(55);
}

void DeptInfoLayout::showGroupInfo()
{
	//if need update
	m_stakedWidget->setCurrentWidget(m_groupItemList);
	updateGroupInfo();
}

void DeptInfoLayout::showDeptInfo(int dId)
{
	m_stakedWidget->setCurrentWidget(m_deptItemList);
	updateDeptInfo(dId);
}

void DeptInfoLayout::showFriendInfo()
{
	m_stakedWidget->setCurrentWidget(m_friendItemList);
	updateFriendInfo();
}

void DeptInfoLayout::updateGroupInfo()
{
	m_groupItemList->clear();
	for (int i = 0; i < 10;i++)
	{
		QListWidgetItem* item = new QListWidgetItem(m_groupItemList);
		ConcreteDeptItem* depItem = new ConcreteDeptItem("haha", "Rourke", "123", ConcreteDeptItem::groupItem);
		QSize size = QSize(this->width(), 60);		
		item->setSizeHint(size);		
		m_groupItemList->setItemWidget(item, depItem);
		connect(depItem,
			SIGNAL(sig_itemClick(int, ConcreteDeptItem::ItemType)),
			this,
			SLOT(slot_concreteItemClick(int, ConcreteDeptItem::ItemType)));

	}
}

void DeptInfoLayout::updateDeptInfo(int dId)
{
	m_deptItemList->clear();
	DeptModule module;
	//navigator item
	DeptNavigatorItem* naviItem = new DeptNavigatorItem;
	QListWidgetItem* item = new QListWidgetItem(m_deptItemList);
	Department deptInfo;
	int pid=dId;
	do
	{
		module.getDeptInfo(pid, deptInfo);
		int did = deptInfo.getId();
		QString dName = QString::fromUtf8(deptInfo.getName().c_str());
		naviItem->addParentDept(did, dName);				
		pid = deptInfo.getParentId();
	} while (pid != 0);
	QSize size = QSize(this->width(), 60);
	item->setSizeHint(size);
	m_deptItemList->setItemWidget(item, naviItem);
	connect(naviItem,
		SIGNAL(sig_naviItemClick(int)),
		this,
		SLOT(slot_navigatorItemClick(int)));

	//child department
	tee3::eim::DepartmentsType subs;
	module.getChildDeptInfo(dId, subs);
	for each (Department deptInfo in subs)
	{
		QString sName = QString::fromUtf8(deptInfo.getName().c_str());
	
		QListWidgetItem* item = new QListWidgetItem(m_deptItemList);
		ConcreteDeptItem* depItem = new ConcreteDeptItem(sName, sName, "", ConcreteDeptItem::childDeptItem);
		depItem->setId(deptInfo.getId());
		QSize size = QSize(this->width(), 60);
		item->setSizeHint(size);
		m_deptItemList->setItemWidget(item, depItem);
		connect(depItem,
			SIGNAL(sig_itemClick(int, ConcreteDeptItem::ItemType)),
			this,
			SLOT(slot_concreteItemClick(int, ConcreteDeptItem::ItemType)));
	}
	//users in department
	tee3::eim::UsersType users;
	module.getDeptUsersInfo(dId, users);
	for each (UserInfo user in users)
	{
		QString uName = QString::fromUtf8(user.getName().c_str());
		QListWidgetItem* item = new QListWidgetItem(m_deptItemList);
		ConcreteDeptItem* depItem = new ConcreteDeptItem(uName, uName, "",ConcreteDeptItem::friendItem);
		depItem->setId(user.getId());
		QSize size = QSize(this->width(), 60);
		item->setSizeHint(size);
		m_deptItemList->setItemWidget(item, depItem);
		connect(depItem, 
				SIGNAL(sig_itemClick(int, ConcreteDeptItem::ItemType)),
				this,
				SLOT(slot_concreteItemClick(int, ConcreteDeptItem::ItemType)));
	}
}

void DeptInfoLayout::updateFriendInfo()
{
	m_friendItemList->clear();
	for (int i = 0; i < 10; i++)
	{
		QListWidgetItem* item = new QListWidgetItem(m_friendItemList);
		ConcreteDeptItem* depItem = new ConcreteDeptItem("dept", "Rourke", "", ConcreteDeptItem::friendItem);
		QSize size = QSize(this->width(), 60);
		item->setSizeHint(size);
		//QListWidgetItem* item = new QListWidgetItem(QString("friend:") + QString::number(i));
		m_friendItemList->setItemWidget(item, depItem);
		connect(depItem,
			SIGNAL(sig_itemClick(int, ConcreteDeptItem::ItemType)),
			this,
			SLOT(slot_concreteItemClick(int, ConcreteDeptItem::ItemType)));

	}
}
#include "../modules/mainModule.h"
void DeptInfoLayout::slot_concreteItemClick(int sid, ConcreteDeptItem::ItemType type)
{
	//group item
	switch (type)
	{
	case ConcreteDeptItem::friendItem:
		MainModule::Instance()->showUserInfoWidget(sid);
		break;
	case ConcreteDeptItem::groupItem:
		MainModule::Instance()->setCurrentSession(sid, SessionType(type));
		break;
	case ConcreteDeptItem::deptItem:
		break;
	case ConcreteDeptItem::childDeptItem:
		updateDeptInfo(sid);
		break;
	default:
		break;
	}
}

void DeptInfoLayout::slot_navigatorItemClick(int dId)
{
	updateDeptInfo(dId);
}
