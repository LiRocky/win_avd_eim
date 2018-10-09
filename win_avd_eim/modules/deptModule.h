#ifndef DEPT_MODULE_H
#define DEPT_MODULE_H
#include "api/mdepartment.h"

#include <QObject>
using namespace tee3::eim;
class DeptModule:public QObject
{
	Q_OBJECT
public:
	DeptModule();
	~DeptModule();
	void getDeptInfo(DepartmentId did, Department& deptinfo);
	void getChildDeptInfo(DepartmentId did, DepartmentsType& children);
	void getDeptUsersInfo(DepartmentId dId, UsersType& users);
private:

};
#endif