//
//  BLTBTInfo.h
//  BLTBlueToothSDK
//
//  Created by luteng on 17/3/21.
//  Copyright © 2017年 luteng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@interface BLTBTInfo : NSObject
@property (nonatomic, strong) CBPeripheral *peripheral;     //蓝牙设备管理对象(Bluetooth device management object)
@property (nonatomic, strong) NSString *manufacturerData;   //扫描蓝牙广播原始数据(Scan the Bluetooth broadcast raw data)
@property (nonatomic,assign)  NSInteger signal;                   //蓝牙信号强度(Bluetooth signal)
@end
