#include "sessionBottom.h"

SessionBottom::SessionBottom(QWidget* parent) :QWidget(parent)
{
	init();
	
}

SessionBottom::~SessionBottom()
{

}

void SessionBottom::init()
{
	m_layout = new QVBoxLayout(this);
	m_msgEdit = new QTextEdit(this);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->insertWidget(0,m_msgEdit);
	m_msgEdit->setFontPointSize(15);
	m_sendMsgBtn = new QPushButton(this);

	connect(m_sendMsgBtn, SIGNAL(clicked()), this, SIGNAL(sig_sendMsgbtnClicked()));
}

QString SessionBottom::getText()
{
	return m_msgEdit->toPlainText();
}

void SessionBottom::resizeEvent(QResizeEvent *event)
{
	m_sendMsgBtn->setGeometry(width() - 70, height() - 50, 50, 30);
}

void SessionBottom::slot_clickSendMsgBtn()
{
	emit sig_sendMsgbtnClicked();
}
