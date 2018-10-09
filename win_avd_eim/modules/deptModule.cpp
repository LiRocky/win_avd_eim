#include "deptModule.h"

DeptModule::DeptModule()
{

}

DeptModule::~DeptModule()
{

}

void DeptModule::getDeptInfo(DepartmentId dId, Department& deptinfo)
{
	tee3::eim::Client* client = tee3::eim::Client::instance();
	tee3::eim::IDepartment* dept = tee3::eim::IDepartment::obtain(client);
	
	dept->getDepartment(dId, deptinfo);
}

void DeptModule::getChildDeptInfo(DepartmentId dId, DepartmentsType& children)
{
	tee3::eim::Client* client = tee3::eim::Client::instance();
	tee3::eim::IDepartment* dept = tee3::eim::IDepartment::obtain(client);
	
	dept->getDepartmentChilds(dId, children);
}

void DeptModule::getDeptUsersInfo(DepartmentId dId, UsersType& users)
{
	tee3::eim::Client* client = tee3::eim::Client::instance();
	tee3::eim::IDepartment* dept = tee3::eim::IDepartment::obtain(client);
	
	dept->getDepartmentUserInfos(dId, users);
}
