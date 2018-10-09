#ifndef __tee3_eim_IFriend__
#define __tee3_eim_IFriend__

#include "client.h"
#include "object.h"
NAMESPACE_TEE3_EIM_BEGIN

class RT_API_EXPORT IFriend {
public:
	typedef std::function<void(const UsersType& set, Result result)>				 Cb_GetFriendInfosResult;
	//
	typedef std::function<void(const NotificationId& nId, const String& event_json)> Cb_NotifyFriendEvent;
	// friend event Notification
	const NotificationId NId_friend_event_base = 200;
	//const NotificationId NId_friend_event_add = NId_friend_event_base + 1;						/* 用户添加好友；
	//																								 * {"uId":a1,"user_name":"xxx"}
	//																								 */
	const NotificationId NId_friend_event_delete = NId_friend_event_base + 2;						/* 用户删除好友；
																									 * {"uId":a1,"user_name":"xxx"}
																									 */
	const NotificationId NId_friend_event_update = NId_friend_event_base + 3;						/* 更新好友信息；
																									* {"uId":a1,"user_name":"xxx"}
																									*/
	const NotificationId NId_friend_event_invite = NId_friend_event_base + 4;						/* 邀请成为好友
																									 * {"inviter":a1,"invite_message":"xxx"}
																									 */
	const NotificationId NId_friend_event_accept_invite = NId_friend_event_base + 5;				/* 接受成为好友 NId_friend_event_accept_invite
																									 * {"uId":a1,"user_name":"xxx"}
																									 */
	const NotificationId NId_friend_event_reject_invite = NId_friend_event_base + 5;				/* 拒绝成为好友;  如果接受成为好友，则 NId_friend_event_add
																									* {"uId":a1,"reason":"xxx"}
																									*/
public:
	/** @brief 好友事件通知 */
	struct FriendEvent {
		NotificationId nId_;					/**< 通知类型ID */
		UserId userId_;							/**< 好友ID */
		// from json
		String strInfo_;						/** user_name, invite_message, reason */
	};
	/**
	* @brief 解析好友事件通知
	* @param[in] nId 通知类型ID
	* @param[in] event_json 通知内容（Json Value数据）
	* @param[out] event 好友事件通知
	* @return Result
	*/
	static Result parseFriendEvent(const NotificationId nId, const String& event_json, FriendEvent& event);
protected:
	virtual ~IFriend() {};
public:

	static IFriend* obtain(Client* client);
	
	/*  inviteFriend -->  others(Cb_NotifyAcceptInvitation -->  acceptInvitation/declineInvitation)  --> Cb_InviteFriendResult
	 */
	virtual Result inviteFriend(const UserId& toId, const String& message) = 0;

	virtual Result acceptInvitation(const UserId& fromId) = 0;

	virtual Result declineInvitation(const UserId& fromId, const String &sreason) = 0;

	//
	virtual Result deleteFriend(const UserId& uId) = 0;
	/*  updateFriend -->  others(Cb_NotifyUpdateFriend)  --> Cb_UpdateFriendResult
	 */

	virtual Result getFriendIds(UserIdsType& buddyIds ) = 0;
	virtual Result getFriendInfos(UsersType& buddies) = 0;

	//
	virtual void setNotify(Cb_NotifyFriendEvent cb) = 0;
	//virtual void clearCallbacks() = 0;
};

NAMESPACE_TEE3_EIM_END

#endif /* defined(__tee3_eim_IFriend__) */
