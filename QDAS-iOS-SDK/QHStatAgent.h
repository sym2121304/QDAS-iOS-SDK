//
//  QHStatAgent.h
//  AnalyticsSdkSource
//
//  Created by sunyimin on 15/8/6.
//  Copyright (c) 2015年 北京奇虎科技有限公司. All rights reserved.
//

#import <Foundation/Foundation.h>
 
@interface QHStatAgent : NSObject


///---------------------------------------------------------------------------------------
/// @name  设置
///---------------------------------------------------------------------------------------

/**
 *  设置上报错误信息
 *
 *  @param isEnabled BOOL类型 默认 NO
 */
+ (void)setCrashReportEnabled:(BOOL)isEnabled;


/**
 *  设置是否打印sdk的log信息
 *
 *  @param isEnabled BOOL类型 默认 NO 设置为YES,SDK 会输出log信息,记得release产品时要设置回NO.
 */
+ (void)setLogEnabled:(BOOL)isEnabled;


/**
 *  设置打印数据监控信息
 *
 *  @param debug BOOL类型 默认 NO
 */
+ (void)setDebugMode:(BOOL)debug;



///---------------------------------------------------------------------------------------
/// @name  开启统计
///---------------------------------------------------------------------------------------

/**
 *  开启sdk统计，默认以下次启动方式发送log
 *
 *  @param appKey    在QDAS上注册app的key
 *  @param policy    发送策略
 *  @param channelId 渠道名称,为nil或@""时,默认会被被当作@"App Store"渠道
 */
+ (void)startWithAppkey:(nonnull NSString *)appKey channelId:(nullable NSString *)channelId;


/**
 插件版调用

 @param appKey 在QDAS上注册app的key
 @param policy 发送策略
 @param channedId 渠道名称,为nil或@""时,默认会被被当作@"App Store"渠道
 @param extension 是否是插件端调用
 */
+(void)startWithAppkey:(nonnull NSString *)appKey channelId:(nullable NSString *)channedId isExtension:(BOOL)extension;


/**
 *  获取m2值，只生成一次uuid存入keychain中，下次直接从keychain中获取。
 *
 *  @return  返回keychain中读取的uuid
 */
+ (nullable NSString *)getM2;


/**
 获取SDK当前版本号

 @return  返回SDK当前版本号。
 */
+(nonnull NSString *)getSDKVersion;


///---------------------------------------------------------------------------------------
/// @name  页面计时
///---------------------------------------------------------------------------------------


/**
 *  页面时长统计,记录某个view被打开多长时间,可以自己计时也可以调用onPageBegin,onPageEnd自动计时
 *
 *  @param pageName 需要记录时长的view名称.
 */
+ (void)onPageBegin:(nonnull NSString *)pageName;

+ (void)onPageBegin:(nonnull NSString *)pageName label:(nullable NSString *)label;


+ (void)onPageEnd:(nonnull NSString *)pageName;




///---------------------------------------------------------------------------------------
/// @name  自定义事件统计
///---------------------------------------------------------------------------------------


/**
 *
 *  使用前，请先到QDAS管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID
 *  sdk内部参数使用，$符号开头，自定义字段还请避免使用$开头。
 *  @param eventId 事件ID
 */
+ (void)onEvent:(nonnull NSString *)eventId;

+ (void)onEvent:(nonnull NSString *)eventId attributes:(nullable NSDictionary *)attributes;


/**
 *   立即上传缓存的事件。
 */
+ (void)uploadEvent;


/**
 *  添加一个错误事件。错误事件是事件ID为$custom_error的特殊事件。
 *  @param exception 错误对象
 */
+ (void)onError:(nonnull NSException *)exception;


///---------------------------------------------------------------------------------------
/// @name Utility函数
///---------------------------------------------------------------------------------------


/**
 * 设置预置事件属性 键值对 会覆盖同名的key
 */
+(void) registerPreProperties:(nonnull NSDictionary *)property;


/**
 *
 * 删除指定预置事件属性
 @param key
 */
+(void) unregisterPreProperty:(nonnull NSString *)propertyName;


/**
 * 获取预置事件所有属性；如果不存在，则返回空。
 */
+(nullable NSDictionary *)getPreProperties;


/**
 *清空所有预置事件属性。
 */
+(void)clearPreProperties;


/** 判断设备是否越狱，依据是否存在apt和Cydia.app
 */
+ (BOOL)isJailbroken;

/**active user sign-in.
 *  使用sign-In函数后，如果结束该UID的统计，需要调用sign-Off函数
 *
 *  @param userId : user's ID
 *  @param provider  : 不能以下划线"_"开头，使用大写字母和数字标识; 如果是上市公司，建议使用股票代码。
 */
+ (void)profileSignInWithUID:(nullable NSString *)userId;

+ (void)profileSignInWithUID:(nullable NSString *)userId provider:(nullable NSString *)provider;

/** active user sign-off.
 停止sign-in UID的统计
 @return void.
 */
+ (void)profileSignOff;

@end
