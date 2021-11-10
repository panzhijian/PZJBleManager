//
//  ToiletBleTool.m
//  Living
//
//  Created by 李维庆 on 2019/4/24.
//  Copyright © 2019年 Rongguo YU. All rights reserved.
//

#import "ToiletBleTool.h"
#import <CoreBluetooth/CBUUID.h>

@implementation ToiletBleTool

+ (NSString *)errorMessageWithCode:(CCErrorCode)code{
    NSString *errorMessage = @"";
    switch (code) {
        case CCErrorCodeBluetoothSettingNotOpened:
            errorMessage = @"Bluetooth setting not opened";
            break;
            
        case CCErrorCodeConnectingDeviceTimeout:
            errorMessage = @"Connecting device time out";
            break;
            
        case CCErrorCodeDeviceNotConnected:
            errorMessage = @"Device not connected";
            break;
            
        case CCErrorCodeWrongResponseData:
            errorMessage = @"Wrong response data";
            break;
            
        case CCErrorCodeDeviceNoResponse:
            errorMessage = @"Device no response";
            
        case CCErrorCodeResponseWithFailure:
            errorMessage = @"Response with failure";
            
        case CCErrorCodeResponseWithIllegalParameters:
            errorMessage = @"Response with illegal parameters";
            
        default:
            break;
    }
    return errorMessage;
}

+ (NSError *)errorWithCode:(CCErrorCode)code{
    return [NSError errorWithDomain:@"com.CCBluetoothAPI.error"
                               code:code
                           userInfo:@{@"message":[ToiletBleTool errorMessageWithCode:code]}];
}




+ (NSString *)uuidStringWithCBUUID:(CBUUID *)cbuuid
{
    NSData *data = [cbuuid data];
    
    NSUInteger bytesToConvert = [data length];
    const unsigned char *uuidBytes = [data bytes];
    NSMutableString *outputString = [NSMutableString stringWithCapacity:16];
    
    for (NSUInteger currentByteIndex = 0; currentByteIndex < bytesToConvert; currentByteIndex++) {
        switch (currentByteIndex) {
            case 3:
            case 5:
            case 7:
            case 9:[outputString appendFormat:@"%02x-", uuidBytes[currentByteIndex]]; break;
            default:[outputString appendFormat:@"%02x", uuidBytes[currentByteIndex]];
        }
    }
    return outputString;
}


/**
 *  从字节数组中的4个字节组成一个整数
 *
 *  @param bytes 字节地址
 *  @param index 开始位置
 *
 *  @return 整形
 */
+ (NSUInteger)integerFromBytes:(const Byte *)bytes index:(Byte)index{
    NSUInteger steps = bytes[index] +
    bytes[index+1] * 0x100 +
    bytes[index+2] * 0x10000 +
    bytes[index+3] * 0x1000000;
    return steps;
}

+ (NSInteger)integerFromTwoBytes:(const Byte *)bytes index:(Byte)index{
    NSUInteger steps = bytes[index] + bytes[index+1] * 0x100 ;
    return steps;
}

+ (Byte)byteFromInteger:(NSUInteger)integer atIndex:(NSUInteger)index{
    NSData *yearData = [NSData dataWithBytes:&integer length:sizeof(integer)];
    const Byte * yearBytes = yearData.bytes;
    if (index >= sizeof(integer)) {
        return 0;
    } else {
        return yearBytes[index];
    }
}

@end
