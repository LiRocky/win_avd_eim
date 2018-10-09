#ifndef BASE_DEF_H
#define BASE_DEF_H

#include <QtWidgets/QApplication>
#include <QString>
#include <QFile>
#include <QDir>
#include <QDateTime>

#define  PERIOD_TO_STORE 7				//日志保存天数
#define  LOG_FILES_DIR GetRootPath()+"./custom/logs/"
#define DELETE_IF(pobj) {if(pobj!=NULL){delete pobj;pobj=NULL;}}

QString GetRootPath();
QString GetQss(QString qssFile);

bool InitLogFile();
void closeLogFile();
void writeLog(const QString& strMsg);
void delExpiredLogs();
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
#endif