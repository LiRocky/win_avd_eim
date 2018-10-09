#ifndef SESSION_BOTTOM_H
#define SESSION_BOTTOM_H

#include <QWidget>
#include <QTextEdit>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
class SessionBottom:public QWidget
{
	Q_OBJECT
public:
	SessionBottom(QWidget* parent = NULL);
	~SessionBottom();
	void init();
	QString getText();
protected:
	void resizeEvent(QResizeEvent *event);
	protected slots:
	void slot_clickSendMsgBtn();
signals:
	void sig_sendMsgbtnClicked();
private:
	QTextEdit* m_msgEdit;	//消息输入框
	QPushButton* m_sendMsgBtn; //消息发送按钮
	QVBoxLayout* m_layout;
};


#endif // !SESSION_BOTTOM_H
