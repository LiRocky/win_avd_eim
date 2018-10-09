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
	//const NotificationId NId_friend_event_add = NId_friend_event_base + 1;						/* �û���Ӻ��ѣ�
	//																								 * {"uId":a1,"user_name":"xxx"}
	//																								 */
	const NotificationId NId_friend_event_delete = NId_friend_event_base + 2;						/* �û�ɾ�����ѣ�
																									 * {"uId":a1,"user_name":"xxx"}
																									 */
	const NotificationId NId_friend_event_update = NId_friend_event_base + 3;						/* ���º�����Ϣ��
																									* {"uId":a1,"user_name":"xxx"}
																									*/
	const NotificationId NId_friend_event_invite = NId_friend_event_base + 4;						/* �����Ϊ����
																									 * {"inviter":a1,"invite_message":"xxx"}
																									 */
	const NotificationId NId_friend_event_accept_invite = NId_friend_event_base + 5;				/* ���ܳ�Ϊ���� NId_friend_event_accept_invite
																									 * {"uId":a1,"user_name":"xxx"}
																									 */
	const NotificationId NId_friend_event_reject_invite = NId_friend_event_base + 5;				/* �ܾ���Ϊ����;  ������ܳ�Ϊ���ѣ��� NId_friend_event_add
																									* {"uId":a1,"reason":"xxx"}
																									*/
public:
	/** @brief �����¼�֪ͨ */
	struct FriendEvent {
		NotificationId nId_;					/**< ֪ͨ����ID */
		UserId userId_;							/**< ����ID */
		// from json
		String strInfo_;						/** user_name, invite_message, reason */
	};
	/**
	* @brief ���������¼�֪ͨ
	* @param[in] nId ֪ͨ����ID
	* @param[in] event_json ֪ͨ���ݣ�Json Value���ݣ�
	* @param[out] event �����¼�֪ͨ
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
