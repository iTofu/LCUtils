//
//  UIView+ColorOfPoint.h
//  
//
//  Created by Leo on 16/2/18.
//  Copyright © 2016年 Leo All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIView (ColorOfPoint)

/**
 *  获取 UIView 上某一点的颜色
 *
 *  @param point 点
 *
 *  @return 颜色
 */
- (UIColor *)colorOfPoint:(CGPoint)point;

@end
