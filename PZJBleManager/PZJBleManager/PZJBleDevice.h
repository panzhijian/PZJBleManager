//
//  PZJBleDeviceTwo.h
//  PZJBleManager
//
//  Created by 潘志健 on 2021/11/8.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

typedef void (^WriteDataSucceed) ();
typedef void (^WriteDataError) (NSError *error);
typedef void (^BleDataCallback) (CBCharacteristic *character, NSData *data);

NS_ASSUME_NONNULL_BEGIN

@interface PZJBleDevice : NSObject
//设备的mac地址(设备的唯一标识)
@property (nonatomic,strong)NSString *macAddress;
//设备的名称
@property (nonatomic,strong)NSString *name;

//设备显示型号
@property (nonatomic,strong)NSString *model;
///信号强度
@property (assign, nonatomic) NSInteger rssi;


@property (strong, nonatomic) CBPeripheral *cbPeripheral;

@property (strong, nonatomic) CBCharacteristic *writingChar;
@property (strong, nonatomic) CBCharacteristic *writingCharTwo;

@property (strong, nonatomic) CBCharacteristic *notifyChar;
@property (strong, nonatomic) CBCharacteristic *notifyCharTwo;

@property (strong, nonatomic) CBCharacteristic *readChar;
@property (strong, nonatomic) CBCharacteristic *readCharTwo;

@property (copy, nonatomic) WriteDataSucceed readDataSucceed;
@property (copy, nonatomic) WriteDataError readDataError;

- (instancetype)initWithPeripheral:(CBPeripheral *)aPeripheral ;
- (void)didDiscoverServices;



@property (copy, nonatomic) BleDataCallback  bleDataCallBack;
//监听蓝牙返回的数据
-(void)bleDataCallBack:(BleDataCallback)bleDataCallBack;





/************-------------------指令--------------------************/

// 向马桶发送指令  0暂停    1冲水  2归位
- (void)remoteControlType:(NSString *)type success:(void (^)(void))success
                orFailure:(void (^)(NSError *error))failure;





@end

NS_ASSUME_NONNULL_END
