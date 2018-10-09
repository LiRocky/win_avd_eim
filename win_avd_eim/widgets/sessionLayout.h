#ifndef SESSION_LAYOUT_H
#define SESSION_LAYOUT_H

#include <QWidget>
#include <QTextEdit>
#include <QStackedWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QMap>
#include <QDateTime>

#include "sessionHeader.h"
class SessionContent;
class SessionBottom;

class SessionLayout:public QWidget
{
	Q_OBJECT
public:
	SessionLayout(QWidget* parent=NULL);
	~SessionLayout();
	void init();
	SessionContent* currentSession();
	void setCurrntSessionId(QString seesion_id);

	
	public slots:
	void slot_sendMsg();
	void slot_recvMsg(QString user, QString strMsg, QDateTime strTime);


protected:
	
private:
	SessionHeaderWidget* m_sessionHeadBar;	//顶部
	QStackedWidget* m_sessionWidgets;
	SessionBottom* m_sendDescription; //发送信息输入框
	QVBoxLayout* m_layout;
	QSplitter* m_spliter;

	SessionContent* m_curSession;
	QMap<QString, SessionContent*> m_contentWidMap;
};


#endif // !SESSION_LAYOUT_H
