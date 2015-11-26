//
//  MD5.h
//  TTlol
//
//  Created by Leo on 15/11/25.
//  Copyright © 2015年 LanMeng Tec. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface MD5 : NSObject

/**
 *  MD5 加密
 *
 *  @param inPutText 需要加密的字符串
 *
 *  @return MD5 值
 */
+ (NSString *)md5:(NSString *)inPutText;

/**
 *  获取文件的 MD5
 *
 *  @param path 文件路径
 *
 *  @return MD5 值
 */
+ (NSString *)fileMD5:(NSString *)path;

@end
