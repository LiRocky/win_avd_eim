#include "chatItem.h"
#include <QPainter>
ChatItemWidget::ChatItemWidget(QWidget* parent/*=NULL*/)
{
	//this->setFixedSize(QSize(200, 64));
}

ChatItemWidget::~ChatItemWidget()
{

}

void ChatItemWidget::setReadTipVisible(bool value)
{
	{ m_showReadedTip = value; }
	repaint();
}

void ChatItemWidget::setReadedFlag(bool value)
{
	{ m_readed = value; }
	repaint();
}

void ChatItemWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QBrush brush(QColor(50, 150, 250));
	QPen pen(QColor(50, 150, 250));
	QFont font = painter.font();
	drawIcon(painter);
	//time
	pen.setColor(Qt::gray);
	painter.setPen(pen);
	font.setPixelSize(10);
	painter.setFont(font);
	QRectF rcTime(width() - 40, 12, 30, 16);
	painter.drawText(rcTime, Qt::AlignLeft, "09:12");
	
	//title
	pen.setColor(Qt::black);
	painter.setPen(pen);
	font.setPixelSize(12);
	font.setBold(true);
	painter.setFont(font);
	QRectF rcTitle(60, 12, width() - 100, 16);
	QFontMetrics fm = painter.fontMetrics();
	QString strText = m_title;// QStringLiteral("青春不老，奋斗不止！-纯正开源之美，有趣、好玩、靠谱。。。");
	QString strElidedText = fm.elidedText(strText, Qt::ElideRight,rcTitle.width(), Qt::TextShowMnemonic);

	painter.drawText(rcTitle, Qt::AlignLeft, strElidedText);

	//msg
		//readed tip
	int readedTipPadding = 0;
	if (m_selfMsg)
	{
		if (m_showReadedTip)
		{
			readedTipPadding = 34;
			QRectF rcReadedtip(60, 34, 34, 16);
			QString strReaded = m_readed ? QString::fromLocal8Bit("[已读]") : QString::fromLocal8Bit("[未读]");
			pen.setColor(m_readed ? Qt::gray : QColor(50, 150, 250));
			font.setBold(false);
			painter.setPen(pen);
			painter.setFont(font);
			painter.drawText(rcReadedtip, Qt::AlignCenter, strReaded);
		}
	}

	pen.setColor(Qt::gray);
	painter.setPen(pen);
	font.setPixelSize(12);
	font.setBold(false);
	painter.setFont(font);
	QRectF rcMsg(60+readedTipPadding, 34, width() - 100-readedTipPadding, 16);
	fm = painter.fontMetrics();
	//m_msg = QStringLiteral("极速打卡成功，进入钉钉查看详情");
	strElidedText = fm.elidedText(m_msg, Qt::ElideRight, rcMsg.width(), Qt::TextShowMnemonic);
	painter.drawText(rcMsg, Qt::AlignLeft | Qt::AlignVCenter, strElidedText);

	//unread msg count tip
	if (m_readed == false)
	{

		brush = QBrush(QColor(255, 0, 0));
		pen = QPen(QColor(255, 0, 0));
		painter.setPen(pen);
		painter.setBrush(brush);
		painter.setRenderHint(QPainter::Antialiasing, true);
		QRectF rcMsgCount(width() - 30, 34, 16, 16);
		painter.drawRoundedRect(rcMsgCount, 8, 8);
		pen.setColor(Qt::white);
		painter.setPen(pen);
		font.setPixelSize(9);
		painter.setFont(font);
		painter.drawText(rcMsgCount, Qt::AlignCenter, "10");
	}
}

void ChatItemWidget::resizeEvent(QResizeEvent *event)
{
	repaint();
}

void ChatItemWidget::drawIcon(QPainter& painter)
{
	//icon
	QBrush brush(QColor(50, 150, 250));
	QPen pen(QColor(50, 150, 250));
	QFont font = painter.font();
	painter.setPen(pen);
	painter.setBrush(brush);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QRectF rectangle(12, 12, 40, 40);
	painter.drawRoundedRect(rectangle, 20, 20);

	//名字
	pen.setColor(QColor(255, 255, 255));
	painter.setPen(pen);
	if (m_type == FriendItem)
	{
		painter.drawText(rectangle, Qt::AlignCenter, "123456");
		return;
	}
	

	//group
	int groupSize = m_name.length();
	if (groupSize == 1)
	{
		painter.save();
		pen.setColor(Qt::gray);
		brush.setColor(Qt::gray);
		painter.setPen(pen);
		painter.setBrush(brush);
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.drawRoundedRect(rectangle, 20, 20);
		painter.restore();
		painter.drawEllipse(17, 17, 30, 30);
		painter.drawText(rectangle, Qt::AlignCenter, m_name);
	}
	if (groupSize == 2)
	{
		painter.drawLine(32, 12, 32, 52);		
		QRectF rc1(12, 12, 20, 40);
		QRectF rc2(32, 12, 20, 40);	

		font.setPixelSize(12);
		painter.setFont(font);
		painter.drawText(rc1, Qt::AlignCenter, QString::fromLocal8Bit("吗"));
		painter.drawText(rc2, Qt::AlignCenter, "V");		
	}
	if (groupSize == 3)
	{
		painter.drawLine(32, 12, 32, 52);
		painter.drawLine(32, 32, 52, 32);
		QRectF rc1(14, 12, 20, 40);
		QRectF rc2(30, 12, 20, 20);		
		QRectF rc3(30, 30, 20, 20);

		font.setPixelSize(10);
		painter.setFont(font);
		painter.drawText(rc1, Qt::AlignCenter, QString::fromLocal8Bit("吗"));
		painter.drawText(rc2, Qt::AlignCenter, "V");		
		painter.drawText(rc3, Qt::AlignCenter, "V");
	}
	if (groupSize == 4)
	{
		painter.drawLine(32, 12, 32, 52);
		painter.drawLine(12, 32, 52, 32);
		QRectF rc1(14, 12, 20, 20);
		QRectF rc2(30, 12, 20, 20);
		QRectF rc3(14, 30, 20, 20);
		QRectF rc4(30, 30, 20, 20);

		font.setPixelSize(10);
		painter.setFont(font);
		painter.drawText(rc1, Qt::AlignCenter, QString::fromLocal8Bit("吗"));
		painter.drawText(rc2, Qt::AlignCenter, "V");
		painter.drawText(rc3, Qt::AlignCenter, "V");
		painter.drawText(rc4, Qt::AlignCenter, "V");
	}
}
