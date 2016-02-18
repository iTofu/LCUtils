//
//  UIView+ColorOfPoint.m
//  
//
//  Created by Leo on 16/2/18.
//  Copyright © 2016年 Leo All rights reserved.
//

#import "UIView+ColorOfPoint.h"

@implementation UIView (ColorOfPoint)

- (UIColor *)colorOfPoint:(CGPoint)point {
    
    unsigned char pixel[4] = {0};
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(pixel, 1, 1, 8, 4, colorSpace, (CGBitmapInfo)kCGImageAlphaPremultipliedLast);
    
    CGContextTranslateCTM(context, -point.x, -point.y);
    
    [self.layer renderInContext:context];
    
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
    
    UIColor *color = [UIColor colorWithRed:pixel[0]/255.0f
                                     green:pixel[1]/255.0f
                                      blue:pixel[2]/255.0f
                                     alpha:pixel[3]/255.0f];
    
    return color;
}

@end
