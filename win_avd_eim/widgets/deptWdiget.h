#ifndef DEPTWIDGET_H
#define DEPTWIDGET_H

#include <QSplitter>
#include "sessionLayout.h"
#include <QListWidget>
#include <QHBoxLayout>
#include "deptInfoLayout.h"
class DeptItemWidget;
class DeptWidget:public QWidget
{
	Q_OBJECT
public:
	DeptWidget(QWidget* parent = NULL);
	~DeptWidget();
	void init();
	DeptItemWidget* addDeptItem(QString name);
	void updateDeptInfo();
	protected slots:
	void slot_SelDeptItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
protected:
	bool eventFilter(QObject *obj, QEvent *ev);
private:
	QListWidget* m_listWidget;	//用户&分组会话列表
	QHBoxLayout* m_layout;
	//SessionLayout* m_sessionLayout;
	DeptInfoLayout* m_deptInfoLayout;
};


#endif // !DEPTWIDGET_H
