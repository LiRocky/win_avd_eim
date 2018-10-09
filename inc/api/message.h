#ifndef __tee3_eim_message__
#define __tee3_eim_message__

#include "combase.h"

NAMESPACE_TEE3_EIM_BEGIN
//
//class Message
//{
//public:
//	//virtual void release() = 0;
//
//	MessageId messageId() const { return messageId; }
//	void setMsgId(const MessageId& value) { messageId = value; }
//
//	UserId from() const { return from_; }
//	void setFrom(UserId value) { from_ = value; }
//	UserId to() const { return to_; }
//	void setTo(UserId value) { to_ = value; }
//	uint32 timestamp() const { return messgeTime; }
//	void setTimestamp(uint32 value) { messgeTime = value; }
//
//	SessionType sessionType() const { return sessionType; }
//	void setSessionType(SessionType value) { sessionType = value; }
//	MessageType messageType() const { return messageType; }
//	void setMessageType(MessageType value) { messageType = value; }
//
//	SessionId sessionId() const { return sessionId; }
//	void setSessionId(SessionId value) { sessionId = value; }
//
//	MessageStatus messageStatus() const { return messageStatus; }
//	void setMessageStatus(MessageStatus value) { messageStatus = value; }
//public:
//	//
//	static MessageId createTextMessage(UserId to, MessageType type, const char* content);
//	//static MessageId createImageMessage(UserId to, MessageType type, const IMImage &image, const char* file_path);
//	//static MessageId createFileMessage(UserId to, MessageType type, const IMFile &file, const char* file_path);
//	//static MessageId createAudioMessage(UserId to, MessageType type, const IMAudio &audio, const char* file_path);
//	//
//	static bool parseMessage(const std::string &json_msg, Message &msg);
//	//static bool parseImageMessage(const IMessage &msg, IMImage &image);
//	//static bool parseFileMessage(const IMessage &msg, IMFile &file);
//	//static bool parseAudioMessage(const IMessage &msg, IMAudio &audio);
//
//public:
//	Message() {
//	}
//protected:
//	MessageId		messageId;		//msg ID
//	UserId			senderId;		//消息的发送者
//	SessionId		sessionId;		//会话的ID 群消息：groupId, 个人消息：接收方userId
//	SessionType		sessionType;	//消息来源
//	MessageType		messageType;	//消息类型
//	MessageStatus	messageStatus;	//消息的状态
//	String			content;		//消息内容
//	uint32			messgeTime;		//消息产生时间
//};
//typedef std::vector<Message> MessagesType;

NAMESPACE_TEE3_EIM_END

#endif /* defined(__tee3_eim_message__) */
