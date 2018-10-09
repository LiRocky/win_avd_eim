#ifndef SESSION_CONTENT_H
#define SESSION_CONTENT_H

#include <QWidget>
#include <QTextEdit>
#include <QTabWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QListWidget>
#include <QDateTime>
class SessionContent:public QWidget
{
	Q_OBJECT
public:
	SessionContent(QWidget* parent = NULL);
	~SessionContent();
	void init();
	void addMsgItem(QString strMsg,quint32 timeStamp,bool selfMsg=true);
	void addTimeTip(quint32 timeStamp);
protected:
	void resizeEvent(QResizeEvent *event);
private:
	QVBoxLayout* m_layout;
	QListWidget* m_msgItemList;
};


#endif // !SESSION_CONTENT_H
