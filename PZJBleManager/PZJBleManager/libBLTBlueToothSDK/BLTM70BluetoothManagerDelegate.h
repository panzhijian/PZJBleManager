//
//  BLTM70BluetoothManagerDelegate.h
//  BLTBlueToothSDK
//
//  Created by luteng on 17/3/21.
//  Copyright © 2017年 luteng. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol BLTM70BluetoothManagerDelegate <NSObject>
@optional


/**
 蓝牙设备状态改变接口（Bluetooth device status changes interface）

 @param state state description
 */
- (void)BLTM70MmanagerStateDidChanged:(CBCentralManagerState)state;



/**
 蓝牙链接回调（Bluetooth connection callback）

 @param aManager aManager description
 */
- (void)BLTM70ManagerDidConnected:(BLTBluetoothManager *)aManager withDeviceInfo:(BLTBTInfo*)info;




/**
 蓝牙断开连接回（Bluetooth disconnects back）

 @param aManager aManager description
 */
- (void)BLTM70ManagerDidDisconnect:(BLTBluetoothManager *)aManager;

//血氧参数数据协议  prValue：PR值  bloodValue：血注强度数组     pIValue：PI参数值   respValue：resp参数值（Blood Oxygen Parameter Data Protocol prValue: PR Value bloodValue: Blood Intensity Array pIValue: PI Parameter Value respValue: resp Parameter Value）
/**

 @param aManager aManager description
 @param spo2Value
 @param prValue PR
 @param bloodValue
 @param piValue
 @param respValue
 */
- (void)BLTM70Manager:(BLTBluetoothManager *)aManager didUpdateValues:(int)spo2Value withPrValue:(int)prValue withBloodValues:(NSArray*)bloodValue withPIValue:(int)piValue withRespValue:(int)respValue;



/**
 血氧波形协议函数（Oxygen Waveform Protocol Function）
 @param aManager
 @param waves 波形数组 float类型数据（Waveform array float type data）
 */
- (void)BLTM70Manager:(BLTBluetoothManager *)aManager didUpdateSpo2Waves:(NSArray*)waves;




/**
 蓝牙设备电量状态回调（Bluetooth device power state callback）

 @param aManager aManager description
 @param status 电池电量枚举定义（Battery power enumeration definition）
 */
- (void)BLTM70Manager:(BLTBluetoothManager *)aManager electricityStatus:(NSInteger)status;



/**
 扫描到所有设备的数组（Scan to an array of all devices）

 @param aManager aManager description
 @param btInfos 数组每个成员为一个（BLTBTInfo*）类型的对象（Each member of the array is an object of type (BLTBTInfo *)）
 */
- (void)BLTM70Manager:(BLTBluetoothManager *)aManager discoverBTInfo:(NSArray *)btInfos;



/**
 设备固件版本号回调（Device firmware version number callback）

 @param aManager aManager description
 @param version 固件版本号（Firmware version number）
 */
- (void)BLTM70Manager:(BLTBluetoothManager *)aManager firmwareVersion:(NSString *)version timeIntel:(NSInteger)time;
@end
