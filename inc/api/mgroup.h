#ifndef __tee3_eim_IGroupManager__
#define __tee3_eim_IGroupManager__

#include "mfriend.h"

NAMESPACE_TEE3_EIM_BEGIN




class RT_API_EXPORT IGroup {
public:
	typedef std::function<void(const GroupInfo &group, Result result)> Cb_CreateGroupResult;
	typedef std::function<void(Result result, const String &cursor, GroupsType& groups)> Cb_GetPublicGroupsResult;
	//
	typedef std::function<void(const GroupId& gId, const NotificationId& nId, const String& event_json)> Cb_NotifyGroupEvent;

	// group event Notification
	const NotificationId NId_group_event_base = 100;
	const NotificationId NId_group_event_join_group = NId_group_event_base + 1;					    /* �û�����Ⱥ�������Լ�������뱻ͨ����ͬ�����룻
																									 * {"uId":a1,"user_name":"xxx"}
																									 */
	const NotificationId NId_group_event_leave_group = NId_group_event_base + 2;					/* �û��˳�Ⱥ�������Լ������˳�Ⱥ��
																									 * {"uId":a1,"user_name":"xxx"}
																									 */
	const NotificationId NId_group_event_update_group = NId_group_event_base + 3;					/* ����Ⱥ��Ϣ��
																									* {"uId":a1,"user_name":"xxx"}
																									*/
	const NotificationId NId_group_event_invite_from_group = NId_group_event_base + 4;				/* �������Ⱥ
																									 * {"inviter":a1,"invite_message":"xxx"}
																									 */
	const NotificationId NId_group_event_reject_invite_from_group = NId_group_event_base + 5;		/* �ܾ��������Ⱥ;  ��������������Ⱥ���� NId_group_event_join_group
																									 * {"uId":a1,"reason":"xxx"}
																									 */
	const NotificationId NId_group_event_kick_from_group = NId_group_event_base + 6;				/* Ⱥ���߳�ĳ�ˣ������������յ� NId_group_event_leave_group
																									 * {"kicker":a1,"reason":"xxx"}
																									 */
	const NotificationId NId_group_event_apply_join_group = NId_group_event_base + 7;				/* �������Ⱥ
																									 * {"uId":a1,apply_message":"xxx"}
																									 */
	const NotificationId NId_group_event_reject_apply_join_group = NId_group_event_base + 8;		/* �ܾ��������Ⱥ;  ��������������Ⱥ���� NId_group_event_join_group
																									 * {"uId":a1,"reason":"xxx"}
																									 */
	const NotificationId NId_group_event_dismiss_group = NId_group_event_base + 9;					/* Ⱥ��ɢ
																									 * {"reason":"xxx"}
																									 */
	const NotificationId NId_group_event_update_nickname = NId_group_event_base + 10;				/* ����Ⱥ��Ա��Ƭ
																									* {"uId":a1,"nick_name":"xxx""}
																									*/
public:
	/** @brief Ⱥ���¼�֪ͨ */
	struct GroupEvent {
		NotificationId nId_;					/**< ֪ͨ����ID */
		GroupId gId_;							/**< Ⱥ��ID */
		// from json
		UserId userId_;							/** uId, inviter, kicker */
		String strInfo_;						/** user_name, invite_message, reason, apply_message */
	};
	/**
	  * @brief ����Ⱥ���¼�֪ͨ
	  * @param[in] gId Ⱥ��ID
	  * @param[in] nId ֪ͨ����ID
	  * @param[in] event_json ֪ͨ���ݣ�Json Value���ݣ�
	  * @param[out] event Ⱥ���¼�֪ͨ
	  * @return Result
	  */
	static Result parseGroupEvent(const GroupId& gId, const NotificationId nId, const String& event_json, GroupEvent& event);

protected:
	virtual ~IGroup() {};
public:
	static IGroup* obtain(Client* client);

	virtual Result getAllMyGroups(GroupsType &set) = 0;

	virtual Result getPublicGroupsWithCursor(const String &cursor, int pageSize, Cb_GetPublicGroupsResult cb) = 0;
	//
	virtual Result createGroup(GroupInfo &group, const Cb_CreateGroupResult& cb) = 0;

	/*  others(NId_group_event_dismiss_group)
	 */
	virtual Result dismissGroup(const GroupId& gId) = 0;
	//
	virtual Result updateGroupInfo(const GroupInfo& group) = 0;
	/*  inviteGroupMembers --> someone (NId_group_event_invite_from_group -->  acceptInvitation/declineInvitation) -->
	 *  -->  NId_group_event_join_group/NId_group_event_reject_invite_from_group
	 *  others(NId_group_event_join_group)
	 */
	virtual Result inviteGroupMembers(const GroupId& gId, const UserIdsType &members, const String &welcomeMessage) = 0;
	/*  kickGroupMembers -->  server --> NId_group_event_kick_from_group
	 *  others(NId_group_event_leave_group)
	 */
	virtual Result kickGroupMembers(const GroupId& gId, const UserIdsType &members, const String &reason) = 0;

	virtual Result acceptInvitation(const GroupId& gId) = 0;

	virtual Result declineInvitation(const GroupId& gId, const String &reason) = 0;
	/*  applyJoinGroup --> group owner (NId_group_event_apply_join_group -->  acceptJoinGroupApplication/declineJoinGroupApplication)
	 *  -->  NId_group_event_join_group/NId_group_event_reject_apply_join_group
	 *  others(NId_group_event_join_group)
	 */
	virtual Result applyJoinGroup(const GroupId& gId, const String &message) = 0;

	virtual Result passApplyJoinGroup(const GroupId& gId, const UserId& uId) = 0;

	virtual Result rejectApplyJoinGroup(const GroupId& gId, const UserId& uId, const String &reason) = 0;
	/*  leaveGroup -->  server
	 *  others(NId_group_event_join_group)
	 */
	virtual Result leaveGroup(const GroupId& gId) = 0;

	virtual Result blockGroupMessage(const GroupId& gId) = 0;

	virtual Result unblockGroupMessage(const GroupId& gId) = 0;
	//
	virtual void setNotify(Cb_NotifyGroupEvent cb) = 0;

	//
	virtual Result updateMyNickName(const GroupId& gId, const String& name) = 0;

	virtual void clearCallbacks() = 0;
};

NAMESPACE_TEE3_EIM_END

#endif /* defined(__tee3_eim_IGroupManager__) */
