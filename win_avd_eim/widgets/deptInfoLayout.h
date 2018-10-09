#ifndef DEPT_INFO_LAYOUT_H
#define DEPT_INFO_LAYOUT_H
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include "deptInfoHeader.h"
#include "concreteDetpItem.h"
class DeptInfoLayout:public QWidget
{
	Q_OBJECT
public:
	DeptInfoLayout(QWidget* parent);
	~DeptInfoLayout();
	void init();
	void showGroupInfo();
	void showDeptInfo(int dId = 0);
	void showFriendInfo();
	DeptInfoHeaderWidget* getHeader(){ return m_infoHeader; }
protected:
	void updateGroupInfo();
	void updateDeptInfo(int dId=0);
	void updateFriendInfo();

public slots :;
void slot_concreteItemClick(int, ConcreteDeptItem::ItemType);
void slot_navigatorItemClick(int);
private:
	QVBoxLayout* m_layout;
	DeptInfoHeaderWidget* m_infoHeader;
	QStackedWidget* m_stakedWidget;
	QListWidget*	m_groupItemList;
	QListWidget*	m_deptItemList;
	QListWidget*	m_friendItemList;
};

#endif