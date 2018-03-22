//
//  JSInfomationModel.h
//  JSProSDK
//
//  Created by 杰莘宏业 on 2017/7/21.
//  Copyright © 2017年 LX. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JSInfomationModel : NSObject

/*
 *  由平台分配的商户号,用于标记商户
 */
@property (nonatomic ,strong)NSString *paraId;
/*
 *  由平台分配的产品号,用于标记商户的产品,如果一个商户有多个产品,那么
 *  在接入SDK的时候,商户号不变,针对每个产品需要平台分配不同的产品号.
 */
@property (nonatomic ,strong)NSString *appId;


/*
 *贝付宝平台分配的key
 */
@property (nonatomic ,strong)NSString * key;




/*
 *  由平台分配的子渠道号,当商户在不同渠道推广商品时就要配置不同的子渠道号,平
 *  台以此来统计每个渠道的收入情况,如果只有一条推广渠道,则默认写1即可
 */
@property (nonatomic ,strong)NSString *childParaId;

/*
 *  以分为单位
 */
@property (nonatomic ,strong)NSString *infoCost;

/*
 * 弹出的内容顺序  0-- z ; 1-- w ; 2-- y
 */
@property (nonatomic ,strong)NSArray *typeArray;

/*
 * 商户订单号  不超过32位
 */
@property(nonatomic,copy)NSString * orderno;

/*
 * 透传参数
 */
@property(nonatomic,copy)NSString * attach;


/*
 * 苹果内购支付后，异步通知地址，用于贝付宝服务器通知商户服务器支付结果
 */
@property(nonatomic,copy)NSString * notify_url;


/*
 *  调起苹果内购支付时，如果购买的内购商品属于自动续订订阅商品（区别于消耗型商品），那么在支付成功后进行验证时需要添加秘钥才能验证，否则会返回21004
 *  如何查看密钥：在添加内购商品页面，点击右边 【App 专用共享密钥】 即可查看该密钥；
 * 
 *  如果是购买的自动续订商品，那么把该密钥赋给 password 属性就可；
 *  如果是购买的消耗型商品，那么把password 属性赋字符 1 ；
 */
@property(nonatomic,copy)NSString * password;


@end
