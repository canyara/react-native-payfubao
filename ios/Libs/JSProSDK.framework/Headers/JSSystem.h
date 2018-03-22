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
* 获取点击选项下标值:
* index : 得到的下标值
*/
-(void)getIndex:(NSString *)index;



/***
* 当切换回应用后.在此方法内根据type获取结果，
* 实现此代理方法后，返回APP后会自动调用此方法，可根据type，向商户自己的服务器进行结果查询
*/
-(void)getResultWhenEnterForegroundWithType:(NSInteger)type;




/***
* 当切换回应用后.在此方法内根据type获取结果，
* 实现此代理方法后，返回APP后会自动调用此方法，SDK内部自动查询结果  注：此结果是向贝付宝服务器查询的结果
* type  : 0   z
*        : 1   w
*        : 2   y
 
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
-(void)getResultWhenEnterForegroundWithType:(NSInteger)type Result:(NSDictionary *)resultDic;





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
 * applePayID   苹果后台配置的商品内购id
 */
-(void)beginApplePayWithAppleID:(NSString *)applePayID;





/***
* 如果使用商家自己的切换方法，则请使用该方法调起支付，调起不同的类型需要通过type进行区分
* backJson   商家服务器返回的订单信息,解析为NSDictionary格式;
* type       选择的方式: 0  z   ;
*                      1  w   ;
*                      2  y   ;
*/
-(void)beginWithJson:(NSDictionary * )backJson withType:(NSInteger)type;







@end

