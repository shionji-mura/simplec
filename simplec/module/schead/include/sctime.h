﻿#ifndef _H_SIMPLEC_SCTIMEUTIL
#define _H_SIMPLEC_SCTIMEUTIL

#include <time.h>
#include <stdbool.h>

// struct tm 中 tm_year, tm_mon 用的偏移量
#define _INT_YEAROFFSET		(1900)
#define _INT_MONOFFSET		(1)
// 定义每天是开始为 0时0分0秒
#define _INT_MINSECOND		(60)
#define _INT_HOURSECOND		(3600)
#define _INT_DAYSECOND		(24UL * _INT_HOURSECOND)
#define _INT_DAYSTART		( 8UL * _INT_HOURSECOND)
// 定义每天新的开始时间
#define _INT_DAYNEWSTART	( 0UL * _INT_HOURSECOND + 0 * _INT_MINSECOND + 0)

// 秒到毫秒|毫秒到微秒, 毫秒到纳秒|秒到微秒 
#define _INT_STOMS			(1000)
#define _INT_MSTONS			(1000000)

#ifdef __GNUC__
#include <sys/time.h>
#endif

// 为Visual Studio导入一些和linux上优质思路
#ifdef _MSC_VER

#include <WinSock2.h>

/*
 * 返回当前得到的时间结构体, 高仿linux上调用
 * pt	: const time_t * , 输入的时间戳指针
 * ptm	: struct tm * , 输出的时间结构体
 *		: 返回 ptm 值
 */
#define localtime_r(pt, ptm) localtime_s(ptm, pt), ptm

//
// gettimeofday - Linux sys/time.h 中得到微秒的一种实现
// tv		:	返回结果包含秒数和微秒数
// tz		:	包含的时区,在window上这个变量没有用不返回
// return	:   默认返回0
//
extern inline int gettimeofday(struct timeval * tv, void * tz);

#endif

// 定义时间串类型
#define _INT_STULEN			(64)
typedef char stime_t[_INT_STULEN];

/*
 * 将 [2016-7-10 21:22:34] 格式字符串转成时间戳
 * tstr	: 时间串分隔符只能是单字节的.
 * pt	: 返回得到的时间戳
 * otm	: 返回得到的时间结构体
 *		: 返回这个字符串转成的时间戳, -1表示构造失败
 */
extern bool stu_gettime(stime_t tstr, time_t * pt, struct tm * otm);

/*
 * 判断当前时间戳是否是同一天的.
 * lt : 判断时间一
 * rt : 判断时间二
 *    : 返回true表示是同一天, 返回false表示不是
 */
extern bool stu_tisday(time_t lt, time_t rt);

/*
 * 判断当前时间戳是否是同一周的.
 * lt : 判断时间一
 * rt : 判断时间二
 *    : 返回true表示是同一周, 返回false表示不是
 */
extern bool stu_tisweek(time_t lt, time_t rt);

//
// stu_sisday - 判断当前时间串是否是同一天的.
// ls : 判断时间一
// rs : 判断时间二
//    : 返回true表示是同一天, 返回false表示不是
//
extern bool stu_sisday(stime_t ls, stime_t rs);

//
// 判断当前时间串是否是同一周的.
// ls : 判断时间一
// rs : 判断时间二
//    : 返回true表示是同一周, 返回false表示不是
//
extern bool stu_sisweek(stime_t ls, stime_t rs);

/*
 * 将时间戳转成时间串 [2016-7-10 22:38:34]
 * nt	: 当前待转的时间戳
 * tstr	: 保存的转后时间戳位置
 *		: 返回传入tstr的首地址
 */
#define _STR_TIME			"%04d-%02d-%02d %02d:%02d:%02d"
extern char * stu_gettstr(time_t nt, stime_t tstr);

/*
 * 得到当前时间戳 [2016-7-10 22:38:34]
 * tstr	: 保存的转后时间戳位置
 *		: 返回传入tstr的首地址
 */
extern char * stu_getntstr(stime_t tstr);

//
// stu_getmstr - 得到加毫秒的串 [2016-7-10 22:38:34 500]
// tstr		: 保存最终结果的串
// return	: 返回当前串长度
//
#define _STR_MTIME			"%04d-%02d-%02d %02d:%02d:%02d %03ld"
extern size_t stu_getmstr(stime_t tstr);

//
// stu_getmstrn - 得到毫秒的串, 每个中间分隔符都是fmt[idx]
// buf		: 保存最终结果的串
// len		: 当前buf串长度
// fmt		: 输出格式串例如 -> "simplec-%04d%02d%02d-%02d%02d%02d-%03ld.log"
// return	: 返回当前串长度
//
extern size_t stu_getmstrn(char buf[], size_t len, const char * const fmt);

#endif // !_H_SIMPLEC_SCTIMEUTIL