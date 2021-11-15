//
//  BLTWBPBluetoothManagerDelegate.h
//  BLTBlueToothSDK
//
//  Created by luteng on 17/3/21.
//  Copyright © 2017年 luteng. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol BLTWBPBluetoothManagerDelegate <NSObject>
@optional


/**
 APP发送 启动/停止  命令  BLE 应答 确定命令发送成功（APP Send Start / Stop Command BLE Reply OK The command was sent successfully）

 @param aManager aManger
 */
-(void)BLTWBPManagerBLERespondedMeasuringCommand:(BLTBluetoothManager*)aManager;


/**
 APP 发送更改用户类型 时  设备应答  如果3s 内 收不到应答包  可以再发送一次   并且APP不能进入测量模式（APP sends a change to the user type when the device responds if the reply packet can not be sent again within 3s and the APP can not enter the measurement mode）

 @param aManager aManager description
 */
-(void)BLTWBPManagerBLERespondedUserTypeCommand:(BLTBluetoothManager *)aManager;

/**
 血压计忙闲状态 协议接口（Blood Pressure Meter Busy Status Protocol Interface）
 @param aManager aManager description
 @param isBusy true busy :  false idle
 */
- (void)BLTWBPManagerWorkingStatus:(BLTBluetoothManager *)aManager IsBusy:(BOOL)isBusy workMode:(NSInteger)workmode;



/**
 蓝牙设备状态改变接口（Bluetooth device status changes interface）
 @param state
 */
- (void)BLTWBPManagerStateDidChanged:(CBCentralManagerState)state;



/**
 蓝牙链接回调（Bluetooth connection callback）

 @param aManager aManager description
 */
- (void)BLTWBPManagerDidConnected:(BLTBluetoothManager *)aManager withDeviceInfo:(BLTBTInfo*)info;



/**
 蓝牙断开连接协议（Bluetooth disconnect protocol）

 @param aManager aManager description
 */
- (void)BLTWBPManagerDidDisconnect:(BLTBluetoothManager *)aManager;


/**
 测量结果协议（Measurement result protocol）

 @param aManager aManager description
 @param sys
 @param dia
 @param map
 @param pr
 @param date
 */
- (void)BLTWBPManager:(BLTBluetoothManager *)aManager didUpdateValuesSYS:(int)sys DIA:(int)dia MAP:(int)map PR:(int)pr date:(NSInteger)date withErrorFlag:(BOOL)bError withErrorCode:(NSInteger)errorCode;



/**
 电池电量（power）

 @param aManager aManager description
 @param status status description
 */
- (void)BLTWBPManager:(BLTBluetoothManager *)aManager electricityStatus:(NSInteger)status;



/**
 扫描到所有设备的数组（Scan to an array of all devices）
 @param aManager aManager description
 @param btInfos 数组每个成员为一个（BLTBTInfo*）类型的对象（Each member of the array is an object of type (BLTBTInfo *)）
 */
- (void)BLTWBPManager:(BLTBluetoothManager *)aManager discoverBTInfo:(NSArray *)btInfos;



/**
 固件版本号（Firmware version number）
 @param aManager aManager description
 @param version version description
 */
- (void)BLTWBPManager:(BLTBluetoothManager *)aManager firmwareVersion:(NSString *)version timeIntel:(NSInteger)time;


/**
 实时测量压力值（Real-time measurement of pressure values）
 @param aManager aManager description
 @param values 压力值（Pressure value）
 */
- (void)BLTWBPManager:(BLTBluetoothManager *)aManager pressureValue:(int)values pulseValue:(int)pValue CuffIsError:(BOOL)bError;


/**
 蓝牙设备用户类型（Bluetooth device user type）

 @param aManager aManager description
 @param status 用户类型（user type）
 */
- (void)BLTWBPManager:(BLTBluetoothManager *)aManager userTypeStatus:(NSInteger)status;



/**
 同步历史数据总数(Total number of synchronized historical data)
 @param aManger aManger description
 @param dataCount 数据块(data block)
 */
-(void)BLTWBPManager:(BLTBluetoothManager*)aManger syncDataCount:(NSInteger)dataCount;


/**
 同步数据结束(Synchronization data ends)
 @param aManger aManger description
 @param syncData 数据结果( results Data)
 @param berror berror description
 */
-(void)BLTWBPManager:(BLTBluetoothManager*)aManger syncDataFinish:(NSArray*)syncData isError:(BOOL)berror;

@end
