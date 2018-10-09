#include "base.h"
#include <QFileInfo> 
#include <QTextStream>  


QString GetRootPath() {
	static bool bFirst = true;
	static QString rootPath;
	if (bFirst)
	{
		QString filePath = QCoreApplication::applicationFilePath();
		QFileInfo fileinfo(filePath);
		rootPath = fileinfo.absolutePath();
		rootPath += "/";
		bFirst = false;
	}
	return rootPath;
}


QString GetQss(QString qssFile) {
	QString rootPath = GetRootPath();
	QFile styleSheet(rootPath + qssFile);
	QString qssStr;
	styleSheet.open(QIODevice::ReadOnly);
	if (styleSheet.isOpen()) {
		qssStr = styleSheet.readAll();
		qssStr.replace("ABSOLUTE_PATH", rootPath);
		styleSheet.close();
	}
	return qssStr;
}


QFile* g_logFile = NULL;
QMutex mutex;
bool InitLogFile()
{
	QDir logDir(LOG_FILES_DIR);
	if (!logDir.exists())
	{
		logDir.mkpath("./");
	}
	//ROOM_PROFILE->SetSDKLogPath(LOG_FILES_DIR);
	QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_hhmmss");
	QString logFile = LOG_FILES_DIR + strDateTime + ".txt";
	mutex.lock();
	g_logFile = new QFile(logFile);
	if (g_logFile == NULL)
	{
		return false;
	}
	if (!g_logFile->open(QIODevice::ReadWrite | QIODevice::Append))
	{
		return false;
	}
	mutex.unlock();
	return true;
}

void closeLogFile()
{
	if (g_logFile->isOpen())
	{
		g_logFile->close();
	}
	DELETE_IF(g_logFile);
}

void writeLog(const QString& strMsg)
{
	if (g_logFile == NULL)
	{
		InitLogFile();
	}
	mutex.lock();
	if (g_logFile != NULL && g_logFile->isOpen())
	{
		QTextStream stream(g_logFile);
		stream << strMsg << "\r\n";
		g_logFile->flush();
	}
	mutex.unlock();
}

void delExpiredLogs()
{//删除过期的日志
	QDir logDir(LOG_FILES_DIR);
	if (logDir.exists())
	{
		QDateTime timeToDel = QDateTime::currentDateTime().addDays(-PERIOD_TO_STORE);
		QFileInfoList fileInfos = logDir.entryInfoList(QDir::Files, QDir::Time);
		for (QFileInfo file : fileInfos)
		{
			if (file.lastModified() < timeToDel)
			{
				logDir.remove(file.fileName());
			}
		}
	}
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {

	QByteArray localMsg = msg.toLocal8Bit();
	QString strMsg("");
	switch (type) {
	case QtDebugMsg:
		strMsg = QString("Debug:");
		break;
	case QtWarningMsg:
		strMsg = QString("Warning:");
		break;
	case QtCriticalMsg:
		strMsg = QString("Critical:");
		break;
	case QtFatalMsg:
		strMsg = QString("Fatal:");
		break;
	}
	// 设置输出信息格式	
	QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	QString strMessage = QString("[%5][%2][%4]==[%1]")
		.arg(localMsg.constData()).arg(context.file).arg(context.function).arg(strDateTime);
	writeLog(strMessage);
	return;
}