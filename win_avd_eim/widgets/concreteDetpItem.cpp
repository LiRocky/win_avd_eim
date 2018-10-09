#include "concreteDetpItem.h"
#include <QPainter>


ConcreteDeptItem::ConcreteDeptItem(QString name, QString title, QString descri/*=""*/, ItemType type/*=ItemType::deptItem*/) :
m_name(name), m_title(title), m_description(descri), m_type(type)
{

}

ConcreteDeptItem::~ConcreteDeptItem()
{

}

void ConcreteDeptItem::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QBrush brush(QColor(50, 150, 250));
	QPen pen(QColor(50, 150, 250));
	QFont font = painter.font();
	pen.setColor(Qt::black);
	painter.setPen(pen);
	font.setPixelSize(12);
	font.setBold(true);
	painter.setFont(font);
	QRectF rcTitle(60, 12, width() - 100, 40);
	if (m_type == childDeptItem)
	{
		painter.drawText(rcTitle, Qt::AlignLeft | Qt::AlignVCenter, m_title);
		return;
	}

	drawIcon(painter);

	//title	
	
	if (!m_description.isEmpty())
	{
		rcTitle.setHeight(16);
	}
	QFontMetrics fm = painter.fontMetrics();
	QString strText = m_title;
	QString strElidedText = fm.elidedText(strText, Qt::ElideRight, rcTitle.width(), Qt::TextShowMnemonic);

	painter.drawText(rcTitle, Qt::AlignLeft | Qt::AlignVCenter, strElidedText);
	
	//description
	if (!m_description.isEmpty())
	{
		pen.setColor(Qt::gray);
		painter.setPen(pen);
		font.setPixelSize(10);
		font.setBold(false);
		painter.setFont(font);
		QRectF rcDescri(60, 34, width() - 100, 16);
		painter.drawText(rcDescri, Qt::AlignLeft | Qt::AlignVCenter, m_description);
	}
}

void ConcreteDeptItem::drawIcon(QPainter& painter)
{
	//icon
	painter.save();
	QBrush brush(QColor(50, 150, 250));
	QPen pen(QColor(50, 150, 250));
	QFont font = painter.font();
	painter.setPen(pen);
	painter.setBrush(brush);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QRectF rectangle(12, 12, 40, 40);
	painter.drawRoundedRect(rectangle, 20, 20);
	painter.restore();
}

void ConcreteDeptItem::mousePressEvent(QMouseEvent *event)
{
	emit sig_itemClick(m_id, m_type);
}

DeptNavigatorItem::DeptNavigatorItem()
{
	

}

DeptNavigatorItem::~DeptNavigatorItem()
{

}

void DeptNavigatorItem::addParentDept(int dId, QString dName)
{	
	m_depts.push_front(dId);
	m_nameMap[dId] = dName;
}

void DeptNavigatorItem::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QBrush brush(QColor(50, 150, 250));
	QPen pen(QColor(50, 150, 250));
	QFont font = painter.font();
	pen.setColor(Qt::black);
	painter.setPen(pen);
	font.setPixelSize(12);	
	painter.setFont(font);
	QRect rcTitle(60, 12, 50, 40);
	
	//title	
	QFontMetrics fm = painter.fontMetrics();
	for each (int did in m_depts)
	{
		QString strText = m_nameMap[did];
		int wid = fm.width(strText);
		rcTitle.setWidth(wid+10);
		painter.drawText(rcTitle, Qt::AlignLeft | Qt::AlignVCenter, strText);
		//m_areaMap[rcTitle] = did;
		const QRect rc = rcTitle;
		const int id = did;
		m_areaMap.insert( id,rc);
		rcTitle.moveLeft(rcTitle.right());
	}
}
#include <QMouseEvent>
void DeptNavigatorItem::mousePressEvent(QMouseEvent *event)
{
	QPoint pt = event->pos();	
	QMap<int, QRect>::const_iterator i = m_areaMap.constBegin();
	while (i != m_areaMap.constEnd()) {	
		if (i.value().contains(pt))
		{
			int did = i.key();
			emit sig_naviItemClick(did);
			break;
		}
		++i;
	}	
}
