//
//  BLTWT1BluetoothManagerDelegate.h
//  BLTBlueToothSDK
//
//  Created by luteng on 17/3/21.
//  Copyright © 2017年 luteng. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BLTBluetoothManager;
@protocol BLTWT1BluetoothManagerDelegate <NSObject>
@optional
/*
 蓝牙设备状态改变接口（Bluetooth device status changes interface）
 @param state
 */
- (void)BLTWT1ManagerStateDidChanged:(CBCentralManagerState)state;


/*
 //蓝牙连接协议接口（Bluetooth connectivity protocol interface）
 @param aManager
 */
- (void)BLTWT1managerDidConnected:(BLTBluetoothManager *)aManager withDeviceInfo:(BLTBTInfo*)info;


/*
 蓝牙断开连接协议接口（Bluetooth disconnect protocol interface）
 @param aManager
 */
- (void)BLTWT1managerDidDisconnect:(BLTBluetoothManager *)aManager;

/*
 连接蓝牙后设备发送的体温数据（The temperature data sent by the device after connecting Bluetooth）
 @param aManager
 @param value
 */
- (void)BLTWT1manager:(BLTBluetoothManager *)aManager didUpdateValues:(float)value;

/*
 蓝牙设备电量状态回调  status :电池电量枚举定义  isOff:  是否脱落（Bluetooth device power status callback status: battery charge enumeration definition isOff: whether to fall off）
 @param aManager
 @param status 电池电量状态（Battery status）
 @param isOff 是否脱落（Whether to fall off）
 */
- (void)BLTWT1manager:(BLTBluetoothManager *)aManager electricityStatus:(BLTDeviceElectricityStatus)status fallOff:(BOOL)isOff;


/*
 扫描到所有设备的数组（Scan to an array of all devices）
 @param aManager aManager description
 @param btInfos 数组每个成员为一个（BLTBTInfo*）类型的对象（Each member of the array is an object of type (BLTBTInfo *)）
 */
- (void)BLTWT1manager:(BLTBluetoothManager *)aManager discoverBTInfo:(NSArray *)btInfos;


/*
 设备固件版本号回调（Device firmware version number callback）

 @param aManager aManager description
 @param version Firmware version number
 */
- (void)BLTWT1manager:(BLTBluetoothManager *)aManager firmwareVersion:(NSString *)version timeIntel:(NSInteger)time;


/**
 更新历史同步数据（Update history sync data）

 @param amanger amanger description
 @param SyncData 同步数据字典（Synchronize data results）
 */
-(void)BLTWT1manager:(BLTBluetoothManager*)amanger DidFinishSyncData:(NSMutableDictionary*)SyncData;


/**
 同步数据失败（Synchronization data failed）
 @param amanger amangerSyncDataFail description
 */
-(void)BLTWT1managerSyncDataFail:(BLTBluetoothManager *)amanger;


/**
 同步数据块大小（Synchronize the data block size）
 @param amanger amanger description
 @param dataCount 数据块大小（Data block size）
 */
-(void)BLTWT1manager:(BLTBluetoothManager *)amanger SyncDataCount:(NSInteger)dataCount;
@end
