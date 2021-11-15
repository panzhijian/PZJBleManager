//
//  BLTDeviceInfo.h
//  BLTBlueToothSDK
//
//  Created by luteng on 17/3/21.
//  Copyright © 2017年 luteng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BLTDeviceInfo : NSObject
@property (nonatomic, assign) NSInteger deviceModel;        //设备型号(device mode)
@property (nonatomic, assign) NSInteger protocolVersion;    //蓝牙协议版本(Bluetooth protocol version)
@property (nonatomic, readonly) NSString *deviceModelName;  //型号名(Model name)
@property (nonatomic, strong) NSString *serialNumber;       //设备序列号(devise serial number)
@property (nonatomic, strong) NSString *nickName;           //备注(Remarks)
@property (nonatomic, strong) NSString *firmwareVersion;    // 固件版本号(Firmware version number)

+ (BLTDeviceInfo *)DeviceInfoWithHex:(NSString *)hexStr;    //获取设备信息结构对象(Get the device information structure object)
@end
