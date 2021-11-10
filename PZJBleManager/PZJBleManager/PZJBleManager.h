//
//  PZJBleManager.h
//  PZJBleManager
//
//  Created by 潘志健 on 2021/11/8.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

#import"PZJBleDevice.h"
#import"PZJBleManager.h"

typedef NS_ENUM(NSInteger,ScanDeviceFail) {
    QingNiuScanDeviceFailUnsupported = 0,//不支持蓝牙4.0
    QingNiuScanDeviceFailPoweredOff = 1,//蓝牙关闭
};

// 扫描blcok
typedef void (^ScanSuccessBlock) (NSMutableArray *deviceArr);
typedef void (^ScanFailBlock) (ScanDeviceFail code);

// 连接block
typedef void (^ConnectSuccessBlock) (PZJBleDevice *device);
typedef void (^ConnectFailBlock) (NSError *error);


NS_ASSUME_NONNULL_BEGIN

@interface PZJBleManager : NSObject<CBCentralManagerDelegate,CBPeripheralDelegate>
+ (instancetype)sharedInstance;

@property (strong, nonatomic) CBCentralManager *centralManager;
@property (assign, nonatomic) BOOL bleOpened;
@property (strong, nonatomic) NSMutableArray *scannedPeripherals;
///连接状态
@property (assign, nonatomic ) BOOL isConnected;
@property (copy, nonatomic) NSString *filterName;
@property (copy, nonatomic) NSString *deviceIdentifier;

@property (copy, nonatomic) ScanSuccessBlock scanSuccessBlock;
@property (copy, nonatomic) ScanFailBlock scanFailBlock;

@property (copy, nonatomic) ConnectSuccessBlock connectSuccessBlock;
@property (copy, nonatomic) ConnectFailBlock connectFailBlock;

// 当前连接上的设备,
@property (strong, nonatomic) PZJBleDevice *saveDevice;

- (void)startBleScanWithInterval:(NSTimeInterval)interval filterName:(NSString *)filterName scanSuccessBlock:(ScanSuccessBlock)scanSuccessBlock scanFailBlock:(ScanFailBlock)scanFailBlock;

-(void)connectDevice:(PZJBleDevice *)device connectSuccessBlock:(ConnectSuccessBlock)connectSuccessBlock connectFailBlock:(ConnectFailBlock)connectFailBlock;


@end

NS_ASSUME_NONNULL_END
