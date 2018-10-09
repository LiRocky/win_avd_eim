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
	const NotificationId NId_group_event_join_group = NId_group_event_base + 1;					    /* 用户加入群；包括自己申请加入被通过和同意邀请；
																									 * {"uId":a1,"user_name":"xxx"}
																									 */
	const NotificationId NId_group_event_leave_group = NId_group_event_base + 2;					/* 用户退出群；包括自己主动退出群；
																									 * {"uId":a1,"user_name":"xxx"}
																									 */
	const NotificationId NId_group_event_update_group = NId_group_event_base + 3;					/* 更新群信息；
																									* {"uId":a1,"user_name":"xxx"}
																									*/
	const NotificationId NId_group_event_invite_from_group = NId_group_event_base + 4;				/* 邀请加入群
																									 * {"inviter":a1,"invite_message":"xxx"}
																									 */
	const NotificationId NId_group_event_reject_invite_from_group = NId_group_event_base + 5;		/* 拒绝邀请加入群;  如果接受邀请加入群，则 NId_group_event_join_group
																									 * {"uId":a1,"reason":"xxx"}
																									 */
	const NotificationId NId_group_event_kick_from_group = NId_group_event_base + 6;				/* 群中踢出某人；所有其他人收到 NId_group_event_leave_group
																									 * {"kicker":a1,"reason":"xxx"}
																									 */
	const NotificationId NId_group_event_apply_join_group = NId_group_event_base + 7;				/* 申请加入群
																									 * {"uId":a1,apply_message":"xxx"}
																									 */
	const NotificationId NId_group_event_reject_apply_join_group = NId_group_event_base + 8;		/* 拒绝申请加入群;  如果接受申请加入群，则 NId_group_event_join_group
																									 * {"uId":a1,"reason":"xxx"}
																									 */
	const NotificationId NId_group_event_dismiss_group = NId_group_event_base + 9;					/* 群解散
																									 * {"reason":"xxx"}
																									 */
	const NotificationId NId_group_event_update_nickname = NId_group_event_base + 10;				/* 更新群成员名片
																									* {"uId":a1,"nick_name":"xxx""}
																									*/
public:
	/** @brief 群组事件通知 */
	struct GroupEvent {
		NotificationId nId_;					/**< 通知类型ID */
		GroupId gId_;							/**< 群组ID */
		// from json
		UserId userId_;							/** uId, inviter, kicker */
		String strInfo_;						/** user_name, invite_message, reason, apply_message */
	};
	/**
	  * @brief 解析群组事件通知
	  * @param[in] gId 群组ID
	  * @param[in] nId 通知类型ID
	  * @param[in] event_json 通知内容（Json Value数据）
	  * @param[out] event 群组事件通知
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
