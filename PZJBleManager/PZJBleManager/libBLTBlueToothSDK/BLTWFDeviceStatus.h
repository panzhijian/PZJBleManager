//
//  BLTWFDeviceStatus.h
//  BLTBlueToothSDK
//
//  Created by luteng on 17/3/21.
//  Copyright © 2017年 luteng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BLTWFDeviceStatus : NSObject
@property(nonatomic,assign) NSInteger electricityValue;          //电池电量(battery power)
@property(nonatomic,assign) NSInteger voiceValue;                //音量级别(Volume level)
@property(nonatomic,assign) NSInteger workMode;                  //工作模式  0(胎心测量)，1(收音机)，2(音乐播放器)，3(蓝牙音箱)球型胎心仪支持4种模式，其他只支持0 模式()(Work mode 0 (fetal heart rate measurement), 1 (radio), 2 (music player), 3 (Bluetooth speaker) ball type fetal support four modes, the other only supports 0)
@property(nonatomic,strong) NSString* firmwareVersion;           //固件版本号(Firmware version number)
@property(nonatomic,strong) NSString* subVersion;               //从固件版本号(From firmware version number)
@property(nonatomic,assign) NSTimeInterval time;                //设备时间 2000.1.1号至今秒数(Equipment time 2000.1.1 number of seconds so far)
@end
