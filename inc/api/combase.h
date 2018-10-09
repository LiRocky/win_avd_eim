#ifndef RT_COMMON_BASE_H
#define RT_COMMON_BASE_H
#define __BUILD_LIVECAST__

#include "defines.h"
#include <functional>
#include <vector>

#if (defined(RT_LINUX) || defined(RT_IOS) || defined(RT_ANDROID))
typedef uint64_t   AVDHandle;					/**< 句柄类型  */
#else
typedef int		   AVDHandle;					/**< 句柄类型  */
#endif
typedef int				Result;					/**< 返回值类型  */

#define Max_RoomId		64						/**< 房间Id最大字符长度：服务器缺省是40 */
#define Max_UserId		40						/**< 用户Id最大字符长度 */
#define Max_UserData	128						/**< 用户数据最大字符长度 */
#define Max_DeviceId	256						/**< 设备Id最大字符长度 */
#define Max_StreamId    64						/**< 媒体流Id最大字符长度 */
#define Max_UserName	32						/**< 用户名最大字符长度 */
#define Max_DeviceName	64						/**< 设备名最大字符长度 */
#define Max_DeviceDescription	128				/**< 设备描述最大字符长度 */
#define Max_RoomName	256						/**< 房间名最大字符长度 */
#define Max_Password	16						/**< 密码最大字符长度 */
#define Max_Message		256						/**< 消息最大字符长度 */
#define Max_Address		64						/**< 最大地址长度 */
#define Max_StringEnum	32						/**< 最大字符串枚举长度 */
#define Max_UrlLen		256						/**< 最大url的字符长度 */
#define Max_TimeLen		64						/**< 最大时间字符串长度 */

//// Define platform specific window types.
#if defined(RT_LINUX) && !defined(RT_ANDROID)
typedef unsigned long Window;  // Avoid include <X11/Xlib.h>.
#elif defined(RT_WIN32)
// We commonly include win32.h in webrtc/base so just include it here.
#ifndef NOMINMAX 
	#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>  // Include HWND, HMONITOR.
#elif defined(RT_MAC) && !defined(RT_IOS)
typedef unsigned int CGWindowID;
typedef unsigned int CGDirectDisplayID;
#endif

///以下为一组二进制操作函数
/** 判断uint32的某特定位是否已经改变
* @param[in] oldValue 原值。
* @param[in] newValue 新值。
* @param[in] mask 特定位标志。
* @return 返回是否改变。
*/
#define avd_testFlagChange(oldValue,newValue,mask) \
	(0 != ((oldValue^newValue) & mask))

/** 判断uint32的某特定位是否为1
* @param[in] uValue 测试值。
* @param[in] mask 特定位标志。
* @return 返回是否为1。
*/
#define avd_isFlagSet(uValue,mask) \
	(0 != (uValue & mask))
/** 设置uint32的某特定位为1
* @param[in,out] uValue 设置值。
* @param[in] mask 特定位标志。
*/
#define avd_setFlag(uValue,mask) \
	uValue |= mask;
/** 清除uint32的某特定位为0
* @param[in,out] uValue 设置值。
* @param[in] mask 特定位标志。
*/
#define avd_clearFlag(uValue,mask) \
	uValue &= ~mask;

/** 获取uint32的某些特定位
* @param[in,out] uValue 设置值。
* @param[in] mask 特定位标志。
*/
#define avd_getFlag(uValue,mask) \
	uValue &mask;

/** 取反uint32的某特定位
* @param[in,out] uValue 设置值。
* @param[in] mask 特定位标志。
*/
#define avd_xorFlag(uValue,mask) \
	uValue ^= mask;


#define flag_int32_l8		0xFF000000
#define flag_int32_ln8		0x00FF0000
#define flag_int32_r8		0x000000FF
#define flag_int32_rn8		0x0000FF00
#define flag_int32_l16		0xFFFF0000
#define flag_int32_r16		0x0000FFFF

/////////////////////////////////
#if defined(__cplusplus) || defined(WEBRTC_IOS)

#define NAMESPACE_TEE3_BEGIN	\
namespace tee3 {

#define NAMESPACE_TEE3_END		\
}

#define NAMESPACE_TEE3_EIM_BEGIN\
	NAMESPACE_TEE3_BEGIN		\
	namespace eim {

#define NAMESPACE_TEE3_EIM_END	\
	}							\
	NAMESPACE_TEE3_END


#define USE_NAMESPACE_TEE3		\
	using namespace tee3;

#define USE_NAMESPACE_TEE3_EIM	\
	using namespace tee3::eim;

#else
	#define NAMESPACE_TEE3_BEGIN
	#define NAMESPACE_TEE3_END
	#define NAMESPACE_TEE3_IM_BEGIN
	#define NAMESPACE_TEE3_IM_END
	#define USE_NAMESPACE_TEE3
	#define USE_NAMESPACE_TEE3_IM

#endif //__cplusplus

NAMESPACE_TEE3_EIM_BEGIN

typedef uint32 UserId;
typedef uint32 RelationId;
typedef uint32 DepartmentId;
typedef uint32 GroupId;
typedef uint32 MessageId;
typedef uint32 SessionId;
typedef uint32 NotificationId;
typedef std::string String;


/** 网络状态 */
typedef enum {
	cs_ready,								/**< 初始状态  */
	cs_connecting,							/**< 正在连接服务器  */
	cs_connected,							/**< 已经连接上服务器  */
	cs_connectFailed,						/**< 连接服务器失败  */
} ConnectionStatus;

typedef enum {
	ct_windows	= 0x01,
	ct_macos	= 0x02,
	ct_linux	= 0x04,
	ct_web		= 0x08,
	ct_ios		= 0x10,
	ct_android	= 0x20,
} ClientType;

typedef enum {
	gs_offline,
	gs_online,
} OnlineStatus;

typedef enum {
	ws_working,
	ws_dimission,
} WorkingStatus;

typedef enum {
	gt_undefine,
	gt_male,
	gt_feamale,
} GenderType;

typedef enum {
	st_peers,			//Single chat message
	st_group,			//Group chat message
	st_chatroom			//Chatroom chat message
} SessionType;

typedef enum {
	mt_text,			//文本类型消息
	// not supported now
	mt_image,			//图片类型消息
	mt_file,			//文件类型消息
	mt_audio,			//声音类型消息
	mt_video,			//视频类型消息
	mt_location,		//位置类型消息
	mt_notification,	//系统类型通知（包括入群出群通知等）
} MessageType;

typedef enum {
	ms_new,				//New message
	ms_delivering,		//Message is delivering
	ms_delivered,		//Message delivering successed
	ms_read,			//Message has been read in receiver, or been read ack in sender.
	ms_failed,			//Message delivering failed
	ms_recalled,		//Message recalled successed
} MessageStatus;

typedef enum {
	as_new,				//Download is in progress.
	as_uploading,		//Download is in progress.
	as_uploaded,		//Download is in progress.
	as_dwonloading,		//Download is in progress.
	as_dwonloaded,		//Download successed.
	as_failed,			//Download failed.
} AttachmentStatus;
typedef enum {
	gt_normal = 0x01,
	gt_conference = 0x02,
	gt_system = 0x09,
} GroupType;
typedef enum {
	cp_appkey,							/**< 值类型为string, 必填项,用于验证SDK是否授权。
										 * 必须在join调用之前设置才有效。
										 */
	cp_serveraddress,					/**< 值类型为string, 必填项,用于链接服务器。
										 * 必须在join调用之前设置才有效。
										 */
	cp_customdir,						/**< 值类型为string, 默认值为运行目录/custom/, 用于描述进程产生的用户数据存放地址
										 * 必须在join调用之前设置才有效。
										 */
	cp_databasedir,						/**< 值类型为string, 默认值为cp_customdir/userid/, 用于描述数据库存放地址
										 * 必须在join调用之前设置才有效。
										 */
	cp_databasename,					/**< 值类型为string, 默认值为xxx.xx, 用于描述数据库存放文件名
										 * 必须在join调用之前设置才有效。
										 */
	cp_database_encrypt_key,			/**< 值类型为string, 默认值为后台下发密码, 用于描述数据库创建，读写密码
										 * 必须在join调用之前设置才有效，必须具有一致性，及创建和读写密码一致。
										 * 目前只支持最多32个字符的加密密钥！建议使用32个字符
										 */
	cp_reconnect_max_times,				/**< 值类型为uint, 默认值0, 用于描述断线后重连次数
										 * 必须在join调用之前设置才有效。
										 */
} CliParam;
typedef std::vector<std::string> StringsType;

NAMESPACE_TEE3_EIM_END

#endif//RT_COMMON_BASE_H
