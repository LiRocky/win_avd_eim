#ifndef __tee3_eim_IDepartment__
#define __tee3_eim_IDepartment__

#include "client.h"
#include "object.h"
NAMESPACE_TEE3_EIM_BEGIN

class RT_API_EXPORT IDepartment {
protected:
	virtual ~IDepartment() {};
public:
	static IDepartment* obtain(Client* client);
	
	virtual Result getDepartment(DepartmentId id, Department& item) = 0; // id: 0 is root

	virtual Result getDepartmentChilds(DepartmentId id, DepartmentsType& subs) = 0;
	
	virtual Result getDepartmentUserInfos(DepartmentId id, UsersType& buddies) = 0;
};

NAMESPACE_TEE3_EIM_END

#endif /* defined(__tee3_eim_IDepartment__) */
