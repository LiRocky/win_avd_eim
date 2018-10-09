#ifndef CONCRETE_DEPTITEM_H
#define CONCRETE_DEPTITEM_H
/*
***********具体列表项，包含组群，好友以及组织结构
*/
#include <QWidget>


class ConcreteDeptItem:public QWidget
{
	Q_OBJECT
public:
	enum ItemType
	{
		friendItem,
		groupItem,
		deptItem,
		childDeptItem,
	};
	ConcreteDeptItem(QString name,QString title,QString descri="",ItemType type=ItemType::deptItem);
	~ConcreteDeptItem();
	void setTitle(QString title){ m_title = title; }
	void setDecription(QString descri){ m_description = descri; }
	void setName(QString name){ m_name = name; }
	void setId(int id){ m_id = id; }

	int getId(){ return m_id; }
	
protected:
	void paintEvent(QPaintEvent *event);
	void drawIcon(QPainter& painter);
	void mousePressEvent(QMouseEvent *event);
signals:
	void sig_itemClick(int, ConcreteDeptItem::ItemType);
private:
	QString m_title;
	QString m_description;
	QString m_name;
	int m_id;
	ItemType m_type;
};
#include <QVector>
#include <QRect>
#include <QMap>
class DeptNavigatorItem:public QWidget
{
	Q_OBJECT
public:
	DeptNavigatorItem();
	~DeptNavigatorItem();
	void addParentDept(int dId, QString dName);
signals:
	void sig_naviItemClick(int);
protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
private:
	
	QVector<int> m_depts;
	QMap<int, QString> m_nameMap;
	QMap< int,QRect> m_areaMap;
};
#endif // !CONCRETE_DEPTITEM_H
