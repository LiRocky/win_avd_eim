#ifndef DEPTINFO_HADER_H
#define DEPTINFO_HADER_H

#include <QWidget>
#include <QTextEdit>
#include <QTabWidget>
#include <QSplitter>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
class DeptInfoHeaderWidget :public QWidget
{
	Q_OBJECT
public:
	DeptInfoHeaderWidget(QWidget* parent = NULL);
	~DeptInfoHeaderWidget();
	void init();
	void setIcon(QPixmap icon);
	void setTitle(QString title);
protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
private:
	QPushButton* m_btn;
	QString m_title;
	QLabel* m_details;
	QPixmap	m_icon;
};


#endif // !DEPTINFO_HADER_H
