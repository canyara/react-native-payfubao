//
//  JSSystem.h
//  JSProSDK
//
//  Created by 杰莘宏业 on 2017/7/21.
//  Copyright © 2017年 LX. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JSInfomationModel.h"

@protocol JsSDKDelegate <NSObject>
@optional



/***
* 获取点击选项的title
* title 的值： Cancel，z，w，y；
*  z，w，y，分别代表三种选项title的拼音首字母
*/
-(void)getIndex:(NSString *)title;


/***
* 实现此代理方法后，返回APP后会自动调用此方法，SDK内部自动查询结果  注：此结果是向贝付宝服务器查询的结果
* resultDic : 结果
 
* status 1   该订单支付成功
             同时会返回以下参数：total_fee      订单金额，以分为单位
                             ali_trade_no   第三方流水号
                             order_time     支付成功的时间
* status 2   该订单支付失败
* status 3   签名失败
* status 4   订单为空
* status 5   无此支付类型
* status 6   客户端获取结果时网络错误
* status 7   客户端获取结果时返回json错误
*/
-(void)getResultWhenEnterForegroundWithResult:(NSDictionary *)resultDic;





/**
* 获取苹果内购支付的结果
* status：1000    苹果内购支付成功 且服务器验证成功
* status：1001    支付成功后上传服务器进行验证的参数不全
* status：1002    无此商户，请检查验证时上传的商户id是否正确
* status：1003    支付成功后，向苹果服务器验证支付结果失败，code：苹果服务器返回的错误状态码
* status：10001   没有开通内购功能
* status：10002   找不到该商品
* status：10003   连接苹果内购服务器失败
* status：10004   支付完成后，连接服务器验证时出现网络错误
* status：10005   改商品已经购买
* status：10006   交易取消或失败
* status：10007   连接服务器验证时返回的数据格式错误
*/
-(void)getApplePayResult:(NSDictionary *)resultDic;


@end




@interface JSSystem : NSObject
    
+ (JSSystem *)sharedInstance;
    
@property(nonatomic,weak)id<JsSDKDelegate> delegate;
    

    
/***
* 获取切换的类型:
* repeatStatus : YES,第一次请求支付类型以后会记录下来,下次使用第一次的数据,不再重复请求;，可用-(void)deleteRepeatSetting方法来清除本地存储的类型数据
*              : NO ,每次都请求后台设置的类型
* infoModel      上传的参数
* resultBlock    返回结果
* failure        失败结果
* url            默认nil
*/
- (void)sendWithRepeatStatus:(BOOL)repeatStatus Infomation:(JSInfomationModel *)infoModel completionSucessResultBlock:(void(^)(NSString * result))resultBlock failureBlock:(void(^)(NSError * error))failure url:(NSString *)url;


/***
* 清除第一次请求类型时记录的类型方式:
*/
-(void)deleteRepeatSetting;
    




/***
* status           选择的方式
* backCompletion   返回点击的第三方的下标值
* otherInfomaiton  自定义方式
*/
- (void)startStatus:(NSString *)status Infomation:(JSInfomationModel *)infoModel backBlock:(void(^)(id su))backCompletion otherBlock:(void(^)())otherInfomaiton;





/***
* 如果使用贝付宝的切换方式，则使用该方法调起支付
* backJson   商家服务器向贝付宝服务器下单后返回的订单信息,解析为NSDictionary格式
*/
-(void)beginWithJson:(NSDictionary * )backJson backBlock:(void(^)(id su))backCompletion;





/*
 * 调起苹果内购支付
 * applePayID   苹果后台配置的商品内购id；
 * totalFee     商品价格，单位是分；
 * appleOrderNo 商户的苹果订单号，不超过32位；
 * notifyUrl    苹果支付完成后的异步通知地址，贝付宝服务器通过此地址通知商户服务器；
 * attach       透传参数 ，不超过32的字母或者数字，不能为中文；
 * password     调起苹果内购支付时，如果购买的内购商品属于自动续订订阅商品（区别于消耗型商品），那么在支付成功后进行验证时需要添加秘钥才能验证，否则会返回21004
 如何查看密钥：在添加内购商品页面，点击右边 【App 专用共享密钥】 即可查看该密钥；
 如果是购买的自动续订商品，那么把该密钥赋给 password 属性就可；
 如果是购买的消耗型商品，那么把password 属性赋字符 1 ；
 */
-(void)beginApplePayWithAppleID:(NSString *)applePayID
                       TotalFee:(NSString *)totalFee
                   AppleOrderNO:(NSString *)appleOrderNo
                      NotifyUrl:(NSString *)notifyUrl
                         Attach:(NSString *)attach
               ApplePayPassword:(NSString *)password;

@end

