//
//  BLTWFBluetoothManagerDelegate.h
//  BLTBlueToothSDK
//
//  Created by luteng on 17/3/21.
//  Copyright © 2017年 luteng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BLTWFDeviceStatus.h"
#import "BLTFHRData.h"
@protocol BLTWFBluetoothManagerDelegate <NSObject>
@optional


/**
 蓝牙设备状态改变接口(Bluetooth device status changes interface)

 @param state
 */
- (void)BLTWFManagerStateDidChanged:(CBCentralManagerState)state;



/**
 蓝牙链接回调(Bluetooth connection callback)

 @param aManager aManager description
 */
- (void)BLTWFManagerDidConnected:(BLTBluetoothManager *)aManager withDeviceInfo:(BLTBTInfo*)info;



/**
 蓝牙断开连接回(Bluetooth disconnects back)

 @param aManager aManager description
 */
- (void)BLTWFManagerDidDisconnect:(BLTBluetoothManager *)aManager;




/**
 胎心参数数据协议(Fetal Heart Parameter Data Protocol)

 @param aManager aManager description
 @param data 胎心参数(Fetal heart rate parameters)
 */
- (void)BLTWFManager:(BLTBluetoothManager *)aManager didUpdateValueData:(BLTFHRData*)data;




/**
 扫描到所有设备的数组(Scan to an array of all devices)

 @param aManager aManager description
 @param btInfos 数组每个成员为一个（BLTBTInfo*）类型的对象(Each member of the array is an object of type (BLTBTInfo *))
 */
- (void)BLTWFManager:(BLTBluetoothManager *)aManager discoverBTInfo:(NSArray *)btInfos;



/**
 设备状态协议接口(Device Status Protocol Interface)

 @param aManager aManager description
 @param status WF蓝牙状态信息(WF Bluetooth status information)
 */
- (void)BLTWFManager:(BLTBluetoothManager *)aManager WFDeviceStatus:(BLTWFDeviceStatus*)status;

@end
