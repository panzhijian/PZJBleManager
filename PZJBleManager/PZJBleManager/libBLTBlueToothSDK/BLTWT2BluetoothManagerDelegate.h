//
//  BLTWT2BluetoothManagerDelegate.h
//  BLTBlueToothSDK
//
//  Created by luteng on 17/3/21.
//  Copyright © 2017年 luteng. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol BLTWT2BluetoothManagerDelegate <NSObject>
@optional

/**
 Bluetooth device status changes interface

 @param state state description
 */
- (void)BLTWT2ManagerStateDidChanged:(CBCentralManagerState)state;


/**
 蓝牙链接回调（Bluetooth connection callback）
 @param aManager aManager description
 */
- (void)BLTWT2ManagerDidConnected:(BLTBluetoothManager *)aManager withDeviceInfo:(BLTBTInfo*)info;



/**
 蓝牙断开连接回调（Bluetooth disconnect callback）

 @param aManager aManager description
 */
- (void)BLTWT2ManagerDidDisconnect:(BLTBluetoothManager *)aManager;


/**
 测量体温数据 未平衡时函数（Measure the function of the body temperature data unbalanced）

 @param aManager aManager description
 @param value value description
 @param stable 是否平衡（Whether it is balanced）
 @param tempStatus 温度状态（Temperature state）
 */
- (void)BLTWT2ManagerDidUpdateTemp:(BLTBluetoothManager *)aManager didUpdateValues:(float)value Stable:(BOOL)stable tempStatus:(NSInteger)tempStatus;


/**
 蓝牙设备电量状态回调（Bluetooth device power state callback）

 @param aManager aManager description
 @param status 电池电量枚举定义（Battery power enumeration definition）
 @param isOff 是否脱落（Whether to fall off）
 */
- (void)BLTWT2Manager:(BLTBluetoothManager *)aManager electricityStatus:(NSInteger)status fallOff:(BOOL)isOff;



/**
 扫描到所有设备的数组（Scan to an array of all devices）

 @param aManager aManager description
 @param btInfos 数组每个成员为一个（BLTBTInfo*）类型的对象（Each member of the array is an object of type (BLTBTInfo *)）
 */
- (void)BLTWT2Manager:(BLTBluetoothManager *)aManager discoverBTInfo:(NSArray *)btInfos;


//

/**
 设备固件版本号回调（Device firmware version number callback）
 @param aManager aManager description
 @param version
 */
- (void)BLTWT2Manager:(BLTBluetoothManager *)aManager firmwareVersion:(NSString *)version timeIntel:(NSInteger)time;

@end
