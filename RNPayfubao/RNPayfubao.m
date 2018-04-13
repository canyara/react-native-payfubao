
#import "RNPayfubao.h"

#import <JSProSDK/JSSystem.h>
#import <JSProSDK/JSInfomationModel.h>

@interface RNPayfubao() <JsSDKDelegate>

@end

@implementation RNPayfubao

- (instancetype)init{
    if (self = [super init]) {
        
    }
    [JSSystem sharedInstance].delegate = self;
    return self;
}

- (dispatch_queue_t)methodQueue
{
    return dispatch_get_main_queue();
}
RCT_EXPORT_MODULE()

- (NSArray<NSString *> *)supportedEvents
{
    return @[@"PFBResult", @"AppleResult"];
}

//- (void)calendarEventReminderReceived:(NSNotification *)notification
//{
//    NSString *eventName = notification.userInfo[@"name"];
//    [self sendEventWithName:@"EventReminder" body:@{@"name": eventName}];
//}

RCT_EXPORT_METHOD(sendWithRepeatStatus:(NSString *)paraId appId:(NSString *)appId
                  key:(NSString *)key childParaId:(NSString *)childParaId infoCost:(NSString *)infoCost
                  orderno:(NSString *)orderno
                  notify_url:(NSString *)notify_url
                  appleId:(NSString *)appleId
                  typeArray:(NSArray *)typeArray
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    JSInfomationModel * _model = [[JSInfomationModel alloc] init];
    _model.infoCost = infoCost;                     //支付金额,以分为单位,注意
    _model.appId = appId;                           //贝付宝平台分配的产品id
    _model.paraId = paraId;                         //贝付宝平台分配的商户编号
    _model.childParaId = childParaId;               //子渠道号,只有一个分发渠道则默认为 1 即可
    _model.typeArray = typeArray;                   //0:支付宝   1:微信   2:银联
    _model.orderno = orderno;
    //_model.attach = @"1111111";                       //透传参数,限制最大32位
    _model.notify_url = notify_url;                 //异步通知地址，苹果支付成功后，贝付宝服务器通过此参数通知商户服务器支付结果
    _model.key = key;
    _model.password = @"1";                         //  如果购买的是自动续订商品，请填入【App 专用共享密钥】，否则此类商品在苹果服务器验证时会失败；如果是购买的消耗型商品，那么把password 属性赋字符 1
    
    //获取当前后台切换的支付方式
    [[JSSystem sharedInstance] sendWithRepeatStatus:NO Infomation:_model
                        completionSucessResultBlock:^(NSString *result) {
                            
                            
                            //调起对应的支付方式，result为0 弹出选择框，调第三方支付；106调苹果支付，苹果支付需要开发者自己实现，SDK只提供了调起的接口，即otherBlock里
                            [[JSSystem sharedInstance] startStatus:result Infomation:_model backBlock:^(id su) {
                                // 若商户服务器需要根据客户端上传的标识确定需要下哪种订单，客户端可以将index作为标识上传服务器，来区分是哪种第三方支付方式
                                NSString* index = [NSString stringWithFormat:@"%@",su];
                                
                                //result: 0  第三方支付   106  苹果支付
                                //index: 0: ali 1: wx 2: yl 3: cancel
                                resolve(@{@"result": result, @"index":index});
                                
                            } otherBlock:^{
                                //这里是调起苹果支付的接口
                                resolve(@{@"result": result});
                            }];
                            
                        } failureBlock:^(NSError *error) {
                            //NSLog(@"++++%@",error.localizedDescription);
                            reject(error.localizedDescription, error.localizedDescription, error);
                        } url:nil];
}

RCT_EXPORT_METHOD(beginApplePayWithAppleID:(NSString *)appleId
                  infoCost:(NSString *)infoCost
                  orderno:(NSString *)orderno
                  notify_url:(NSString *)notify_url)
{
    [[JSSystem sharedInstance] beginApplePayWithAppleID:appleId TotalFee:infoCost AppleOrderNO:orderno NotifyUrl:notify_url Attach:@"" ApplePayPassword:@"1"];
}

RCT_EXPORT_METHOD(payWithBody:(NSDictionary *)body)
{
    //下单返回的json  存为dict 调起支付
    [[JSSystem sharedInstance] beginWithJson:body backBlock:nil];
}


#pragma mark - JsSDKDelegate

//-(void)getResultWhenEnterForegroundWithType:(NSInteger)type
//{
//    // 实现此代理方法后，返回APP后会自动调用此方法，可根据type，向商户自己的服务器进行结果查询
//    NSString *eventName = [NSString stringWithFormat:@"%d", type];
//    [self sendEventWithName:@"PFBResult" body:@{@"type": eventName}];
//    [[NSNotificationCenter defaultCenter] removeObserver:[JSSystem sharedInstance]];  //移除通知，不能省略
//}

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
-(void)getResultWhenEnterForegroundWithResult:(NSDictionary *)resultDic
{
    //实现此代理方法后，返回APP后会自动调用此方法，SDK内部自动查询结果
    NSLog(@"付款结果%@",resultDic);
    
    [self sendEventWithName:@"PFBResult" body:@{@"result":resultDic}];
    [[NSNotificationCenter defaultCenter] removeObserver:[JSSystem sharedInstance]];  //移除通知，不能省略
}

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
-(void)getApplePayResult:(NSDictionary *)resultDic
{
    NSLog(@"苹果内购支付结果：%@",resultDic);
    [self sendEventWithName:@"AppleResult" body:@{@"result":resultDic}];
}

@end


