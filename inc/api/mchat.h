#ifndef __tee3_eim_IChat__
#define __tee3_eim_IChat__

#include "client.h"
#include "object.h"

NAMESPACE_TEE3_EIM_BEGIN

class RT_API_EXPORT IChat {
public:
	typedef std::function<void(const Message& msg)>														Cb_NotifyReceiveMessage;
	typedef std::function<void(MessageStatus status, const SessionKey& sesId, const MessageId& msgId)>	Cb_NotifyMessageStatusChanged;

protected:
	virtual ~IChat() { };
public:
	static IChat* obtain(Client* client);
	///
	virtual Result sendMessage(Message& msg) = 0;

	virtual Result recallMessage(const MessageId &msgId) = 0;

	//
	virtual Result getSession(const SessionKey& sId, SessionInfo& info) = 0;

	virtual Result getLastSessions(uint16 max, SessionsType& set) = 0;
	
	virtual Result deleteSession(const SessionKey &sId, bool isRemoveMessages = true) = 0;

	virtual Result deleteAllSessions(bool isRemoveMessages = true) = 0;

	virtual Result resetSessionUnread(const SessionKey &sId) = 0;

	virtual Result setSessionTop(const SessionKey &sId, bool isTop) = 0;
	//
	virtual void setNotify(Cb_NotifyReceiveMessage cb) = 0;
	virtual void setNotify(Cb_NotifyMessageStatusChanged cb) = 0;
	virtual void clearCallbacks() = 0;
};

NAMESPACE_TEE3_EIM_END

#endif /* defined(__tee3_eim_IChat__) */
