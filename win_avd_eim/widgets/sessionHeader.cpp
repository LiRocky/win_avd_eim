#include "sessionheader.h"
#include <QVBoxLayout>
#include <QPainter>
SessionHeaderWidget::SessionHeaderWidget(QWidget* parent) :QWidget(parent)
{
	init();
	
}

SessionHeaderWidget::~SessionHeaderWidget()
{

}

void SessionHeaderWidget::init()
{
	setMouseTracking(true);
	m_btn = new QPushButton(this);
	m_btn->setObjectName("btn_chatHistory");
}

void SessionHeaderWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QPen pen(QColor(218,218,218));
	QRect rc = geometry();
	painter.setPen(pen);
	painter.drawLine(rc.topLeft(), rc.topRight());
	painter.drawLine(rc.bottomLeft(), rc.bottomRight());

	//icon 
	painter.save();
	QBrush brush(QColor(50, 150, 250));
	pen.setColor(QColor(50, 150, 250));
	QFont font = painter.font();
	painter.setPen(pen);
	painter.setBrush(brush);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QRectF rectangle(10, 10, 40, 40);
	painter.drawRoundedRect(rectangle, 20, 20);

	//名字
	pen.setColor(QColor(255, 255, 255));
	painter.setPen(pen);
	painter.drawText(rectangle, Qt::AlignCenter, "HA");
	painter.restore();

	//draw tile
	painter.save();
	pen.setColor(Qt::black);
	painter.setPen(pen);
	font.setPixelSize(16);
	font.setBold(true);
	painter.setFont(font);
	QRectF rcTitle(60, 12, width() /2, 16);
	QFontMetrics fm = painter.fontMetrics();
	QString strText = QStringLiteral("青春不老，奋斗不止！-纯正开源之美，有趣、好玩、靠谱。。。");
	QString strElidedText = fm.elidedText(strText, Qt::ElideRight, rcTitle.width(), Qt::TextShowMnemonic);
	painter.drawText(rcTitle, Qt::AlignLeft, strElidedText);
	painter.restore();

	//description	
	QRectF rcMsg(60 , 34, width() - 100 , 16);
	QString m_msg = QStringLiteral("极速打卡成功，进入钉钉查看详情");
	strElidedText = fm.elidedText(m_msg, Qt::ElideRight, rcMsg.width(), Qt::TextShowMnemonic);
	pen.setColor(Qt::gray);
	painter.setPen(pen);
	painter.drawText(rcMsg, Qt::AlignLeft | Qt::AlignVCenter, strElidedText);
}

void SessionHeaderWidget::resizeEvent(QResizeEvent *event)
{
	QRect rcWidget = geometry();
	m_btn->setGeometry(rcWidget.right() - 40, rcWidget.top() + 20, 20, 20);
}

void SessionHeaderWidget::mouseMoveEvent(QMouseEvent *event)
{
	event->ignore();
}
