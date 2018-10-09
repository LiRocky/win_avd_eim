#ifndef __tee3_eim_Object__
#define __tee3_eim_Object__

#include "combase.h"
#ifdef XXX_COMPILER
#include "usingxxx.h"
#endif
NAMESPACE_TEE3_EIM_BEGIN

///
class UserInfo {
public:
	UserInfo() : id(0), gender(gt_undefine), userStatus(gs_offline), departId(0), shield(false), updated(0), status(0) {}
public:
	bool isValid() const { return 0 != id; }
	//
	void setId(const UserId &value) { id = value; }
	UserId getId() const { return id; }
	void setGender(const GenderType &value) { gender = value; }
	const GenderType& getGender() const { return gender; }
	void setName(const String &value) { name = value; }
	const String& getName() const { return name; }
	void setPinyname(const String &value) { pinyname = value; }
	const String& getPinyname() const { return pinyname; }
	void setNickname(const String &value) { nickname = value; }
	const String& getNickname() const { return nickname; }
	void setPassword(const String &value) { password = value; }
	const String& getPassword() const { return password; }
	void setPhone(const String &value) { phone = value; }
	const String& getPhone() const { return phone; }
	void setEmail(const String &value) { email = value; }
	const String& getEmail() const { return email; }
	void setDescription(const String &value) { description = value; }
	const String& getDescription() const { return description; }
	void setAvatar(const String &value) { avatar = value; }
	const String& getAvatar() const { return avatar; }
	void setUserStatus(const OnlineStatus &value) { userStatus = value; }
	const OnlineStatus& getUserStatus() const { return userStatus; }
	void setDepartId(const uint32 &value) { departId = value; }
	const uint32& getDepartId() const { return departId; }
	void setShield(const bool &value) { shield = value; }
	const bool& getShield() const { return shield; }
	//
	void setStatus(uint8 value) { status = value; }
	uint8 getStatus() const { return status; }
	void setAppjson(const String &value) { appjson = value; }
	const String& getAppjson() const { return appjson; }
	void setUpdated(const uint32 &value) { updated = value; }
	const uint32& getUpdated() const { return updated; }
protected:
	UserId id;
	GenderType gender;
	String name;
	String pinyname;
	String nickname;
	String password;
	String phone;
	String email;
	String description;
	String avatar;
	OnlineStatus userStatus;
	uint32 departId;
	bool   shield;
	String appjson;
	uint32 updated;
	uint8 status;
	XXX_COMPILER_CLASS;
};
extern RT_API_EXPORT const UserInfo	g_emptyUser;
typedef std::vector<UserInfo> UsersType;
typedef std::vector<UserId>	  UserIdsType;

///
class Department {
public:
	Department() : id(0), priority(0), level(0), parentId(0), updated(0), status(0) {}
public:
	bool isValid() const { return 0 != id; }
	//
	void setId(const DepartmentId &value) { id = value; }
	const DepartmentId& getId() const { return id; }
	void setPriority(const uint32 &value) { priority = value; }
	const uint32& getPriority() const { return priority; }
	void setLevel(const uint32 &value) { level = value; }
	const uint32& getLevel() const { return level; }
	void setName(const String &value) { name = value; }
	const String& getName() const { return name; }
	void setParentId(const uint32 &value) { parentId = value; }
	const uint32& getParentId() const { return parentId; }
	void setMembers(const UserIdsType &value) { members = value; }
	const UserIdsType& getMembers() const { return members; }
	UserIdsType& getMembers() { return members; }
	//
	void setStatus(uint8 value) { status = value; }
	uint8 getStatus() const { return status; }
	void setAppjson(const String &value) { appjson = value; }
	const String& getAppjson() const { return appjson; }
	void setUpdated(const uint32 &value) { updated = value; }
	const uint32& getUpdated() const { return updated; }
protected:
	DepartmentId id;		//部门ID
	String name;			//部门名称
	uint32 priority;		//排序优先级
	uint32 level;
	uint32 parentId;		//上级部门名称
	UserIdsType	members;	//成员列表
	String appjson;
	uint32 updated;
	uint8 status;
	XXX_COMPILER_CLASS;
};
extern RT_API_EXPORT const Department g_emptyDepartment;
typedef std::vector<Department> DepartmentsType;

///
class GroupInfo {
public:
	GroupInfo() : id(0), type(gt_normal), ownerId(0), maxuser(0), blocked(false), updated(0), status(0)  {}
public:
	bool isValid() const { return 0 != id; }
	//
	void setId(const GroupId &value) { id = value; }
	const GroupId& getId() const { return id; }
	void setName(const String &value) { name = value; }
	const String& getName() const { return name; }
	void setType(const GroupType &value) { type = value; }
	const GroupType& getType() const { return type; }
	void setOwnerId(const UserId &value) { ownerId = value; }
	const UserId& getOwnerId() const { return ownerId; }
	void setDescription(const String &value) { description = value; }
	const String& getDescription() const { return description; }
	void setAvatar(const String &value) { avatar = value; }
	const String& getAvatar() const { return avatar; }
	void setMaxuser(uint16 value) { maxuser = value; }
	const uint16& getMaxuser() const { return maxuser; }
	void setUpdated(uint16 value) { updated = value; }
	const uint16& getUpdated() const { return updated; }
	const UserIdsType& getMembers() const { return members; }
	UserIdsType& getMembers() { return members; }
	bool isBlocked() const { return blocked; }
	void setBlocked(bool value) { blocked = value; }
	//
	void setStatus(uint8 value) { status = value; }
	uint8 getStatus() const { return status; }
	void setAppjson(const String &value) { appjson = value; }
	const String& getAppjson() const { return appjson; }
protected:
	GroupId	id;
	String name;
	GroupType type;
	UserId ownerId;
	String description;
	String avatar;
	uint16 maxuser;
	UserIdsType members;
	bool blocked;
	String appjson;
	uint16 updated;
	uint8 status;
	XXX_COMPILER_CLASS;
};
extern RT_API_EXPORT const GroupInfo g_emptyGroupInfo;
typedef std::vector<GroupInfo> GroupsType;

///
//class RelationInfo {
//public:
//	RelationInfo() : status(0) {}
//public:
//	RelationId getId() const { return id; }
//	void setId(RelationId value) { id; }
//	UserId getSmallId() const { return smlId; }
//	void setSmallId(UserId value) { smlId = value; }
//	UserId getBigId() const { return bigId; }
//	void setBigId(UserId value) { bigId = value; }
//	//
//	void setStatus(uint8 value) { status = value; }
//	uint8 getStatus() const { return status; }
//	void setUpdated(const uint32 &value) { updated = value; }
//	const uint32& getUpdated() const { return updated; }
//protected:
//	RelationId id;
//	UserId smlId;
//	UserId bigId;
//	uint32 updated;
//	uint8  status;
//	XXX_COMPILER_CLASS;
//};
//typedef std::vector<RelationInfo> RelationsType;

///
struct SessionKey {
	SessionId   sesId; // 会话的ID 群消息：groupId, 个人消息：接收方userId
	SessionType sesType;
	SessionKey() : sesId(0), sesType(st_peers) {}
	SessionKey(SessionId a, SessionType b) : sesId(a), sesType(b) {}
};
class SessionInfo {
public:
	SessionInfo() : unread(0), lastMsgId(0), lastMsgType(mt_text), lastFromId(0), updated(0), status(0) {}
public:
	bool isValid() const { return 0 != key.sesId; }
	//
	const SessionKey& getId() const { return key; }
	void setId(const SessionKey& value) { key = value; }
	SessionId getSessionId() const { return key.sesId; }
	void setSessionId(SessionId value) { key.sesId = value; }
	SessionType getType() const { return key.sesType; }
	void setType(SessionType value) { key.sesType = value; }
	//
	uint32 getUnread() const { return unread; }
	void setUnread(uint32 value) { unread = value; }
	void setLastMsgId(const MessageId &value) { lastMsgId = value; }
	MessageId getLastMsgId() const { return lastMsgId; }
	void setLastMsgType(MessageType value) { lastMsgType = value; }
	MessageType getLastMsgType() const { return lastMsgType; }
	void setLastContent(const String &value) { lastContent = value; }
	const String& getLastContent() const { return lastContent; }
	void setLastFromId(UserId value) { lastFromId = value; }
	UserId getLastFromId() const { return lastFromId; }
	//
	void setStatus(uint8 value) { status = value; }
	uint8 getStatus() const { return status; }
	void setAppjson(const String &value) { appjson = value; }
	const String& getAppjson() const { return appjson; }
	void setUpdated(const uint32 &value) { updated = value; }
	const uint32& getUpdated() const { return updated; }
protected:
	SessionKey key;
	uint32 unread;
	MessageId lastMsgId;
	String lastContent;
	MessageType	lastMsgType;
	UserId lastFromId;
	String appjson;
	uint32 updated;
	uint8  status;
	XXX_COMPILER_CLASS;
};
extern RT_API_EXPORT const SessionKey g_emptySessionKey;
extern RT_API_EXPORT const SessionInfo g_emptySessionInfo;
typedef std::vector<SessionInfo> SessionsType;

///
struct MessageKey{
	MessageId   objId;
	SessionId   sesId;
	SessionType sesType;
	MessageKey() :objId(0), sesId(0), sesType(st_peers) {}
	MessageKey(MessageId mid, const SessionKey& sid) : objId(mid), sesId(sid.sesId), sesType(sid.sesType) {}
	MessageKey(MessageId mid, SessionId sid, SessionType type) : objId(mid), sesId(sid), sesType(type) {}
};
class Message {
public:
	Message() : fromId(0), msgType(mt_text), status(ms_new), msgTime(0) {}
public:
	//virtual void release() = 0;
	void setKey(const MessageKey& value) { key = value; }
	const MessageKey& getKey() const { return key; }
	void setMsgId(const MessageId& value) { key.objId = value; }
	const MessageId& getMsgId() const { return key.objId; }
	void setSessionId(SessionId value) { key.sesId = value; }
	const SessionId& getSessionId() const { return key.sesId; }
	void setSessionType(SessionType value) { key.sesType = value; }
	const SessionType& getSessionType() const { return key.sesType; }
	//
	void setFromId(UserId value) { fromId = value; }
	const UserId& getFromId() const { return fromId; }
	void setMsgType(MessageType value) { msgType = value; }
	const MessageType& getMsgType() const { return msgType; }
	void setMsgStatus(MessageStatus value) { status = value; }
	const MessageStatus& getMessageStatus() const { return status; }
	void setMessageTime(uint32 value) { msgTime = value; }
	const uint32& getMessageTime() const { return msgTime; }
	void setContent(const String& value) { content = value; }
	const String& getContent() const { return content; }
public:
	//
	static MessageId createTextMessage(UserId to, MessageType type, const char* content);
	//static MessageId createImageMessage(UserId to, MessageType type, const IMImage &image, const char* file_path);
	//static MessageId createFileMessage(UserId to, MessageType type, const IMFile &file, const char* file_path);
	//static MessageId createAudioMessage(UserId to, MessageType type, const IMAudio &audio, const char* file_path);
	//
	static bool parseMessage(const std::string &json_msg, Message &msg);
	//static bool parseImageMessage(const IMessage &msg, IMImage &image);
	//static bool parseFileMessage(const IMessage &msg, IMFile &file);
	//static bool parseAudioMessage(const IMessage &msg, IMAudio &audio);

protected:
	MessageKey key;
	UserId fromId;					//消息的发送者
	MessageType	msgType;			//消息类型
	MessageStatus  status;
	String content;					//消息内容
	uint32 msgTime;					//消息产生时间
	XXX_COMPILER_CLASS;
	// key:  1. senderId, sessionId, status;  2. messageId, sessionId
};
extern RT_API_EXPORT const MessageKey g_emptyMessageKey;
extern RT_API_EXPORT const Message g_emptyMessage;
typedef std::vector<Message> MessagesType;

///
class SyncTime {
public:
	SyncTime() : lastUpdated(0) {}
	SyncTime(const std::string& k, uint32 v) : id(k), lastUpdated(v) {}
	void setId(const std::string& value) { id = value; }
	const std::string& getId() const { return id; }
public:
	static const std::string key_user;
	static const std::string key_depart;
	static const std::string key_session;
	static const std::string key_group;
public:
	static uint32 getItem(const std::string& key);
	static bool setItem(const std::string& key, uint32 v);
public:
	std::string id;
	uint32 lastUpdated;
	XXX_COMPILER_CLASS;
};

#ifdef XXX_COMPILER
#include "usingxxxend.h"
#endif

NAMESPACE_TEE3_EIM_END

#endif /* defined(__tee3_eim_Object__) */
