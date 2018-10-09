#ifndef DEPTITEM_H
#define DEPTITEM_H
#include <QWidget>
#include <QMultiMap>
#include <QLabel>
class DeptItemWidget:public QWidget
{
	Q_OBJECT
public:
	enum ItemType
	{
		GroupItem,
		FriendItem,
		DeptItem,
	};
	typedef QMultiMap<QString, QString> IconMap;
	DeptItemWidget(QWidget* parent = NULL);
	DeptItemWidget(QString title);
	~DeptItemWidget();
	void setTitle(QString title){ m_title = title; }
	void setTime(QString time){ m_time = time; }
	void setName(QString name){ m_name = name; }
	void setMsgContent(QString msg){ m_msg = msg; }
	void setId(int id){ m_id = id; }
	int getId(){ return m_id; }
	QString getTitle(){ return m_title; }
	IconMap getIconMap(){ return m_iconMap; }
	DeptItemWidget::ItemType getItemType(){ return m_type; }
	QPixmap getIcon(){ return m_icon; }
	void setType(DeptItemWidget::ItemType type);
	void setReadTipVisible(bool value); //�Ѷ���ʾ�Ƿ�ɼ�
	void setReadedFlag(bool value);//��¼�Ƿ��Ѷ�

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	void drawIcon(QPainter& painter);
private:
	QString m_title;
	QString m_name;
	QString m_msg;
	QString m_time;
	int m_id;
	
	bool m_readed; //���˵���Ϣ�Ƿ��Ѷ�
	bool m_selfMsg; //��ʾ����Ϣ�Ƿ����Լ����͵ģ�
	bool m_showReadedTip;
	ItemType m_type;
	IconMap m_iconMap; //���ֺ�ͷ��·��
	QPixmap m_icon;
};



#endif