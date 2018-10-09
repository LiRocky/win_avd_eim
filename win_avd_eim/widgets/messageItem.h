#ifndef MSG_ITEM_H
#define MSG_ITEM_H
#include <QWidget>
#include <QDateTime>
class QPaintEvent;
class QPainter;
class QLabel;
class QMovie;

class ChatMessageItem : public QWidget
{
	Q_OBJECT
public:
	explicit ChatMessageItem(QWidget *parent = nullptr);

	enum User_Type{
		User_System,//系统
		User_Me,    //自己
		User_Other,   //用户
		User_Time,  //时间
	};
	void setTextSuccess();
	void setText(QString text, quint32 time, QSize allSize, User_Type userType);

	QSize getRealString(QString src);
	QSize fontRect(QString str);

	void setIcon(QString iconPath);

	inline QString text() { return m_msg; }
	inline quint32 time() { return m_time; }
	inline User_Type userType() { return m_userType; }
protected:
	void paintEvent(QPaintEvent *event);
	void drawIcon(QPainter* painter);
private:
	QString m_msg;
	quint32 m_time;
	QString m_curTime;

	QString m_iconPath;
	QString m_name;

	QSize m_allSize;
	User_Type m_userType = User_System;

	int m_kuangWidth;
	int m_textWidth;
	int m_spaceWid;
	int m_lineHeight;

	QRect m_iconLeftRect;
	QRect m_iconRightRect;
	QRect m_sanjiaoLeftRect;
	QRect m_sanjiaoRightRect;
	QRect m_kuangLeftRect;
	QRect m_kuangRightRect;
	QRect m_textLeftRect;
	QRect m_textRightRect;
	QPixmap m_icon;
	//QPixmap m_leftPixmap;
	//QPixmap m_rightPixmap;
	QLabel* m_loading = Q_NULLPTR;
	QMovie* m_loadingMovie = Q_NULLPTR;
	bool m_isSending = false;
};




/////////////////////////////
#include <QDebug>
class IDelegate
{
public:
	virtual ~IDelegate(){};
	virtual void invoke()=0;
protected:
private:
};

class CstaticDelegate :public IDelegate
{
	typedef void(*myfunc)();
public:
	CstaticDelegate();
	~CstaticDelegate();
	virtual void invoke(){  func(); }
private:
	myfunc func;
};



template<class T>
class MemberDelegate :public IDelegate
{
	typedef void (T::*memFunc)();
public:
	MemberDelegate(T* object, memFunc method) :func(method), mobj(object){};

	virtual void invoke(){ (mobj->*func)(); }
private:
	T* mobj;
	memFunc func;
};

class A
{
public:
	void test(){ qDebug() << "test"; };
};
#endif // !MSG_ITEM_H
