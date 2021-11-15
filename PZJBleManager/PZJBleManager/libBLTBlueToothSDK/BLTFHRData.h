//
//  BLTFHRData.h
//  BLTBlueToothSDK
//
//  Created by luteng on 17/3/21.
//  Copyright © 2017年 luteng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BLTFHRData : NSObject
@property(nonatomic,assign) BOOL isTwins;               //是否双胎(Whether twins)
@property(nonatomic,assign) BOOL isFHR1Lose;            //胎心1是否脱落(FHR1 is off?)
@property(nonatomic,assign) BOOL isFHR2Lose;            //胎心2是否脱落(FHR2 is off)
@property(nonatomic,assign) BOOL isTocoLose;            //宫缩是否脱落(Whether the contractions fall off)
@property(nonatomic,assign) BOOL isCoincide;            //胎心是否重合(Whether the fetal heart coincides)
@property(nonatomic,assign) BOOL isFetalMovement;       //是否有胎动(Whether there is fetal movement)
@property(nonatomic,assign) NSInteger signalValue;      //信号强度(Signal )
@property(nonatomic,assign) NSInteger fhr1WaveValue;        //胎心1 波形值(FHR1 value)
@property(nonatomic,assign) NSInteger fhr2WaveValue;        //胎心2 波形值(FHR2 value)
@property(nonatomic,assign) NSInteger FMValue;           //FM
@property(nonatomic,assign) NSInteger UCValue;           //UC
@end
