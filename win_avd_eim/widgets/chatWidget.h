#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QSplitter>
#include "sessionLayout.h"
#include <QListWidget>
#include "chatItem.h"
class ChatWidget:public QSplitter
{
	Q_OBJECT
public:
	ChatWidget(QWidget* parent = NULL);
	~ChatWidget();
	void init();
	ChatItemWidget* addChatItem(QString name, QString title, QString time, QString msg, int index = -1);
	void SelectChatItem(QString sid, ChatItemWidget::ItemType type);
	protected slots:
	void slot_SelectedchatItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
protected:
	bool eventFilter(QObject *obj, QEvent *ev);
private:
	QListWidget* m_listWidget;	//用户&分组会话列表
	SessionLayout* m_sessionLayout;
};


#endif // !CHATWIDGET_H
