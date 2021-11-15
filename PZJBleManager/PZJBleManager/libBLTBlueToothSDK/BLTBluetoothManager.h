//
//  BLTBluetoothManager.h
//  BLTBlueToothSDK
//
//  Created by luteng on 17/3/21.
//  Copyright © 2017年 luteng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "BLTConstantDefine.h"
#import "BLTBTInfo.h"
#import "BLTWT1BluetoothManagerDelegate.h"
#import "BLTWT2BluetoothManagerDelegate.h"
#import "BLTWFBluetoothManagerDelegate.h"
#import "BLTWBPBluetoothManagerDelegate.h"
#import "BLTM70BluetoothManagerDelegate.h"


@interface BLTBluetoothManager : NSObject
@property(nonatomic, weak) id <BLTWT1BluetoothManagerDelegate> WT1delegate;
@property(nonatomic, weak) id <BLTWT2BluetoothManagerDelegate> WT2delegate;
@property(nonatomic, weak) id <BLTWBPBluetoothManagerDelegate> WBPdelegate;
@property(nonatomic, weak) id <BLTWFBluetoothManagerDelegate> WFdelegate;
@property(nonatomic, weak) id <BLTM70BluetoothManagerDelegate> M70delegate;

/**
 获取蓝牙对象的单例接口(Gets a singleton interface for a Bluetooth object)

 @return 返回一个BLTBluetoothManager实例对象(Returns a BLTBluetoothManager instance object)
 */
+ (id)sharedInstance;


-(void)releaseManager;



/**
 设置软件是否 打印调试信息(Set whether the software prints debugging information)

 @param debug true  DEBUG false:
 */
-(void)setBLTDebugMode:(BOOL)debug;

/**
 SDK version
 @return version
 */
-(NSString*)getSDKVersion;

/**
 设置设备型号接口(Set the device model interface)

 @param device device description
 */
-(void)setDevice:(BLTDEVICE)device;


/**
 开始蓝牙扫描接口(Start the Bluetooth scan interface)
 */
- (void)scan;


/**
 停止蓝牙扫描信号(Stop the Bluetooth scan signal)
 */
- (void)stopScan;


/**
 取消链接蓝牙设备（Cancel the connection to the Bluetooth device）
 */
- (void)cancelPeripheralConnection;


/**
 链接蓝牙设备信号（Connect the Bluetooth device）

 @param info info description
 */
- (void)connectPeripheralWithInfo:(BLTBTInfo*)info;


/**
 重新扫描蓝牙接口（Rescan the Bluetooth interface）
 */
- (void)reDiscovere;


/**
 启动测量接口(只对血压计设备有效)（Start the measurement interface (only for the WBP device)）
 */
-(void)startMonitor;



/**
 停止测量接口(只对血压计设备有效)（Stop measurement interface (only for WBP device)）
 */
-(void)stopMonitor;



/**
 发送用户信息给设备 只适用于血压计（Send user information to the device only for the WBP）

 @param type UserType
 */
- (void)requestSyncUserInfoWithUserType:(BLTUserType)type;


/**
 设置胎心音量 (只支持WF设备)（Set the volume of fetal heart (only support WF equipment)）

 @param value value：0（quiet） 1， 2，3，4，5
 */
-(void)setWFDeviceVoiceValue:(int)value;


/**
 同步数据接口  暂时只适应于WT1 WT3 WBP（The synchronous data interface is only available for WT1 WT3 WBP）
 */
-(void)startSyncData;
@end
