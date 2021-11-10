//
//  ToiletBleTool.h
//  Living
//
//  Created by 李维庆 on 2019/4/24.
//  Copyright © 2019年 Rongguo YU. All rights reserved.
//

#import <Foundation/Foundation.h>

///错误码
typedef NS_ENUM(NSInteger, CCErrorCode){
    ///蓝牙未打开
    CCErrorCodeBluetoothSettingNotOpened,
    ///连接设备超时
    CCErrorCodeConnectingDeviceTimeout,
    ///设备未连接
    CCErrorCodeDeviceNotConnected,
    ///设备响应数据错误
    CCErrorCodeWrongResponseData,
    ///设备未响应
    CCErrorCodeDeviceNoResponse,
    ///设备响应错误参数
    CCErrorCodeResponseWithFailure,
    ///设备响应非法命令
    CCErrorCodeResponseWithIllegalParameters,
};

@interface ToiletBleTool : NSObject
///错误信息
+ (NSString *)errorMessageWithCode:(CCErrorCode)code;
///错误
+ (NSError *)errorWithCode:(CCErrorCode)code;
///从bytes的index开始获取4个字节组成整数
+ (NSUInteger)integerFromBytes:(const Byte *)bytes index:(Byte)index;
///获取integer的第index个字节
+ (Byte)byteFromInteger:(NSUInteger)integer atIndex:(NSUInteger)index;
//获取由两个字节组成的整数
+ (NSInteger)integerFromTwoBytes:(const Byte *)bytes index:(Byte)index;
@end
