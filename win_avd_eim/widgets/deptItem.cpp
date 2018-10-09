#include "deptItem.h"
#include <QPainter>
#include "base.h"

#include <QBitmap>
static QPixmap PixmapToRound(QPixmap &src, int radius)
{
	if (src.isNull()) {
		return QPixmap();
	}

	QSize size(2 * radius, 2 * radius);
	QBitmap mask(size);
	QPainter painter(&mask);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
	painter.setBrush(QColor(0, 0, 0));
	painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);

	QPixmap image = src.scaled(size);
	image.setMask(mask);
	return image;
}


DeptItemWidget::DeptItemWidget(QWidget* parent/*=NULL*/)
{
	//this->setFixedSize(QSize(200, 64));
	
}

DeptItemWidget::DeptItemWidget(QString title) :m_title(title)
{
	
}

DeptItemWidget::~DeptItemWidget()
{

}

void DeptItemWidget::setType(ItemType type)
{
	m_type = type;
	//userPath为图片地址
	QPixmap pixmap_userIcon;
	QString sIcon;
	switch (m_type)
	{
	case DeptItemWidget::GroupItem:
		sIcon = "custom/images/groupItem.png";
		break;
	case DeptItemWidget::FriendItem:
		sIcon = "custom/images/friendItem.png";
		break;
	case DeptItemWidget::DeptItem:
		sIcon = "custom/images/deptItem.png";
		break;
	default:
		break;
	}
	pixmap_userIcon.load(GetRootPath() + sIcon);

	//将图片剪裁压缩成20x20大小的图
	QPixmap fitpixmap_userIcon = pixmap_userIcon.scaled(40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	fitpixmap_userIcon = PixmapToRound(fitpixmap_userIcon, 20);
	m_icon = fitpixmap_userIcon;
}

void DeptItemWidget::setReadTipVisible(bool value)
{
	{ m_showReadedTip = value; }
	repaint();
}

void DeptItemWidget::setReadedFlag(bool value)
{
	{ m_readed = value; }
	repaint();
}

void DeptItemWidget::paintEvent(QPaintEvent *event)
{
	QPainter pai(this);
	pai.drawPixmap(12, 12, m_icon);
	
	QPainter painter(this);
	QBrush brush(QColor(50, 150, 250));
	QPen pen(QColor(50, 150, 250));
	QFont font = painter.font();
	//drawIcon(painter);
	
	//title
	pen.setColor(Qt::black);
	painter.setPen(pen);
	font.setPixelSize(12);
	font.setBold(true);
	painter.setFont(font);
	QRectF rcTitle(60, 12, width() - 100, 40);
	QFontMetrics fm = painter.fontMetrics();
	QString strText = m_title;
	QString strElidedText = fm.elidedText(strText, Qt::ElideRight,rcTitle.width(), Qt::TextShowMnemonic);

	painter.drawText(rcTitle, Qt::AlignLeft|Qt::AlignVCenter, strElidedText);		
}

void DeptItemWidget::resizeEvent(QResizeEvent *event)
{
	repaint();
}





void DeptItemWidget::drawIcon(QPainter& painter)
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

	
	
}
