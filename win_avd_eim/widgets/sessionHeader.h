#ifndef SESSION_HADER_H
#define SESSION_HADER_H

#include <QWidget>
#include <QTextEdit>
#include <QTabWidget>
#include <QSplitter>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
class SessionHeaderWidget:public QWidget
{
	Q_OBJECT
public:
	SessionHeaderWidget(QWidget* parent = NULL);
	~SessionHeaderWidget();
	void init();
protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
private:
	QPushButton* m_btn;
	QLabel* m_tile;
	QLabel* m_details;

};


#endif // !SESSION_HADER_H
