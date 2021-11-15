//
//  BLTConstantDefine.h
//  BLTBlueToothSDK
//
//  Created by luteng on 17/3/21.
//  Copyright © 2017年 luteng. All rights reserved.
//

#ifndef BLTConstantDefine_h
#define BLTConstantDefine_h

//BLT设备定义（BLT device index definition）
typedef enum {
    BLT_BLUE_DEVICE_WT1= 0,         //WT1
    BLT_BLUE_DEVICE_WT2,            //WT2
    BLT_BLUE_DEVICE_WBP,            //WBP
    BLT_BLUE_DEVICE_WF,             //WF
    BLT_BLUE_DEVICE_M70,            //M70
    BLT_BLUE_DEVICE_MAX
} BLTDEVICE;

//设备电池电量定义（Device battery power index definition）
typedef enum {
    BLTDeviceElectricityStatusEmpty = 0,    //空电量(Empty)
    BLTDeviceElectricityStatusLow,          //电量低(Low power consumption)
    BLTDeviceElectricityStatusHalf, 		//一半电量(Half of the electricity)
    BLTDeviceElectricityStatusFull, 		//满格电量(Full grid power)
    BLTDeviceElectricityStatusMax
} BLTDeviceElectricityStatus;

//血压计客户类型枚举
typedef enum {
    BLTUserTypeA=1, 		//userA
    BLTUserTypeB, 		//userB
    BLTUserTypeGuest  	//Guest
} BLTUserType;

#define SDK_VER @"1.0.1"
#endif /* BLTConstantDefine_h */
