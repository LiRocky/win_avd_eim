#include "deptInfoHeader.h"

#include <QVBoxLayout>
#include <QPainter>
DeptInfoHeaderWidget::DeptInfoHeaderWidget(QWidget* parent) :QWidget(parent)
{
	init();

}

DeptInfoHeaderWidget::~DeptInfoHeaderWidget()
{

}

void DeptInfoHeaderWidget::init()
{
	setMouseTracking(true);
	m_btn = new QPushButton(this);
	m_btn->setObjectName("btn_chatHistory");
}

void DeptInfoHeaderWidget::setIcon(QPixmap icon)
{
	m_icon = icon;
	repaint();
}

void DeptInfoHeaderWidget::setTitle(QString title)
{
	m_title = title;
	repaint();
}

void DeptInfoHeaderWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QPen pen(QColor(218, 218, 218));
	QRect rc = geometry();
	QBrush brush(QColor(50, 150, 250));
	
	QFont font = painter.font();
	painter.setPen(pen);
	painter.drawLine(rc.topLeft(), rc.topRight());
	painter.drawLine(rc.bottomLeft(), rc.bottomRight());

	//icon 
	painter.drawPixmap(12, 12, m_icon);

	//to do draw picture

	//draw tile
	painter.save();
	pen.setColor(Qt::black);
	painter.setPen(pen);
	font.setPixelSize(16);
	font.setBold(true);
	painter.setFont(font);
	QRectF rcTitle(60, 12, width() / 2, 40);
	QFontMetrics fm = painter.fontMetrics();
	QString strText = m_title;
	QString strElidedText = fm.elidedText(strText, Qt::ElideRight, rcTitle.width(), Qt::TextShowMnemonic);
	painter.drawText(rcTitle, Qt::AlignLeft|Qt::AlignVCenter, strElidedText);
	painter.restore();		
}

void DeptInfoHeaderWidget::resizeEvent(QResizeEvent *event)
{
	QRect rcWidget = geometry();
	m_btn->setGeometry(rcWidget.right() - 40, rcWidget.top() + 20, 20, 20);
}

void DeptInfoHeaderWidget::mouseMoveEvent(QMouseEvent *event)
{
	event->ignore();
}
