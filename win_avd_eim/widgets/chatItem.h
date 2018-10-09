#ifndef CHATITEM_H
#define CHATITEM_H
#include <QWidget>
#include <QMultiMap>
class ChatItemWidget:public QWidget
{
	Q_OBJECT
public:
	enum ItemType
	{
		FriendItem,
		GroupItem,
		
	};
	typedef QMultiMap<QString, QString> IconMap;
	ChatItemWidget(QWidget* parent=NULL);
	~ChatItemWidget();
	void setTitle(QString title){ m_title = title; }
	void setTime(QString time){ m_time = time; }
	void setName(QString name){ m_name = name; }
	void setMsgContent(QString msg){ m_msg = msg; }
	void setItemType(ItemType type){ m_type = type; }
	void setChatId(QString id){ m_id = id; }
	QString getTitle(){ return m_title; }
	IconMap getIconMap(){ return m_iconMap; }
	ItemType getItemType(){ return m_type; }
	QString getChatId(){ return m_id; }
	void setReadTipVisible(bool value); //已读提示是否可见
	void setReadedFlag(bool value);//记录是否已读

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	void drawIcon(QPainter& painter);
private:
	QString m_title;
	QString m_name;
	QString m_msg;
	QString m_time;
	QString m_id;
	bool m_readed; //他人的信息是否已读
	bool m_selfMsg; //显示的信息是否是自己发送的，
	bool m_showReadedTip;
	ItemType m_type;
	IconMap m_iconMap; //名字和头像路径
};



#endif