#ifndef __tee3_eim_client__
#define __tee3_eim_client__

#include "combase.h"
#include "object.h"

NAMESPACE_TEE3_EIM_BEGIN

struct ClientInfo {
	ClientType client_type_;
	String  mac_address_;
	String 	deviceId_;
	uint32	login_time_;

	ClientInfo() : client_type_(ct_windows), login_time_(0) {}
};
typedef std::vector<ClientInfo> OtherSpotsType;

class RT_API_EXPORT Client {
public:
	typedef std::function<void(Result result, const OtherSpotsType& others)> Cb_LoginResult;
	//
	typedef std::function<void(ConnectionStatus status)>					 Cb_NotifyConnectionStatus;
	typedef std::function<void(Result reason)>								 Cb_NotifyKickout;
	typedef std::function<void(const ClientInfo& spot, OnlineStatus status)> Cb_NotifyOtherSpotStatus;
	typedef std::function<void(UserId, OnlineStatus status)>				 Cb_NotifyStatusChange;

protected:
	virtual ~Client() {}
public:
	static Client* instance();
	static void destroy();
	//login/out
	virtual Result start() = 0;
	virtual Result login(const String& account, const String& password, const String& appjson, const Cb_LoginResult& cb) = 0;
	virtual Result login(const String& usertoken, const String& appjson, const Cb_LoginResult& cb) = 0;
	virtual Result relogin(const Cb_LoginResult& cb) = 0;
	virtual Result logout(Result reason) = 0;
	virtual bool   isLogining() const = 0;
	//user 
	virtual ClientType getClientType() const = 0;
	virtual const UserInfo& getSelf() const = 0;
	virtual Result updateNickName(const UserId& uId, const String& name) = 0;
	virtual const tee3::eim::UserInfo getUser(const UserId& id) = 0;
	//query user from server
	virtual Result queryUsers(const String& condition) = 0;
	//params
	virtual void setParam(CliParam type, uint32 value) = 0;
	virtual void setParam(CliParam type, const String& value) = 0;
	//notify
	virtual void setNotify(Cb_NotifyConnectionStatus cb) = 0;
	virtual void setNotify(Cb_NotifyStatusChange cb) = 0;
	virtual void setNotify(Cb_NotifyKickout cb) = 0;
	virtual void setNotify(Cb_NotifyOtherSpotStatus cb) = 0;
	virtual void clearCallbacks() = 0;
};

NAMESPACE_TEE3_EIM_END

#endif /* defined(__tee3_eim_client__) */
