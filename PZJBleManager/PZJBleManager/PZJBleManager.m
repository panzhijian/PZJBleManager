//
//  PZJBleManager.m
//  PZJBleManager
//
//  Created by 潘志健 on 2021/11/8.
//

#import "PZJBleManager.h"
#import"SVProgressHUD.h"
extern NSString * const kCCCustomServiceUUID;
#define KIsNullString(str) ([str isKindOfClass:[NSNull class]] || str == nil || [str length] < 1 ? YES : NO )

@implementation PZJBleManager

+ (instancetype)sharedInstance
{
    static PZJBleManager *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [PZJBleManager new];
    });
    return sharedInstance;
}
- (instancetype)init
{
    self = [super init];
    if (self) {

        self.centralManager = [[CBCentralManager alloc] initWithDelegate:self queue:dispatch_get_main_queue()];
        _scannedPeripherals = [NSMutableArray new];

    }
    return self;
}
- (void)centralManagerDidUpdateState:(CBCentralManager *)central
{
    if (central.state == CBCentralManagerStatePoweredOn) {
        self.bleOpened=YES;
        NSLog(@"蓝牙状态正常!!!");
    }else{
        NSLog(@"蓝牙状态异常!!!");
        self.bleOpened=NO;
    }
    
}


- (void)startBleScanWithInterval:(NSTimeInterval)interval filterName:(NSString *)filterName scanSuccessBlock:(ScanSuccessBlock)scanSuccessBlock scanFailBlock:(ScanFailBlock)scanFailBlock;
{
    [self.scannedPeripherals removeAllObjects];

    if(!self.bleOpened)
    {
        scanFailBlock(QingNiuScanDeviceFailPoweredOff);
        return;
    }
    
//    self.scanSuccessBlock = scanSuccessBlock;
    self.filterName=filterName;
    //     1:重连已知的 peripeheral 列表中的peripeheral (以前发现的,或者以前连接过的)
//    NSUUID *uuid= [[NSUUID alloc] initWithUUIDString:@"774FE1FC-9BB6-D4E0-E0E0-2A3AB75B34E1"];
//    NSUUID *uuid2= [[NSUUID alloc] initWithUUIDString:@"411EC50D-6231-A8BA-B061-F3ADFF6DE149"];
//    NSArray *connectedPeripherals1 =[self.centralManager  retrievePeripheralsWithIdentifiers:@[uuid2]];
//    NSLog(@"以前发现的,或者以前连接过的%@",connectedPeripherals1);
//   CBPeripheral *per=connectedPeripherals1[0];
//    PZJBleDevice *deviece= [self deviceWrapperByPeripheral:per];



//    //2:重新连接当前系统  已经连接的设备
    CBUUID *uuid= [CBUUID UUIDWithString:kCCCustomServiceUUID];
    NSArray *connectedPeripherals = [self.centralManager retrieveConnectedPeripheralsWithServices:@[uuid]];
    for (CBPeripheral *p in connectedPeripherals) {
       [self deviceWrapperByPeripheral:p];
    }
    NSLog(@"获取系统连接到的设备%@",connectedPeripherals);

    
    
//    3:连接搜索到的peripheral
//    scanForPeripheralsWithServices
    
    
    //扫描未连接的设备
//    NSArray * services = [NSArray arrayWithObjects:[CBUUID UUIDWithString:@"1"],nil];
    [self.centralManager scanForPeripheralsWithServices:nil options:nil];

//    //到时间之后停止扫描设备
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(interval * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self.centralManager stopScan];
        if (scanSuccessBlock) {
            scanSuccessBlock([self sortedDevices]);
        }
    });
    
}

- (void)centralManager:(CBCentralManager *)central
 didDiscoverPeripheral:(CBPeripheral *)peripheral
     advertisementData:(NSDictionary *)advertisementData
                  RSSI:(NSNumber *)RSSI
{
        NSLog(@"发现的设备====%@",peripheral);

        PZJBleDevice *device = [self deviceWrapperByPeripheral:peripheral];
        device.rssi = RSSI.integerValue;
        if (device.rssi > 0) {
            device.rssi = -device.rssi;
        }
}

/**
 * 封装CBPeripheral成CCBluetoothDevice
 *  1: 获取已经连接的设备,直接都放在self.scannedPeripherals
 *  2: 扫描到的所有设备,排重,然后添加到self.scannedPeripherals,只要发现扫描到相同设备 就退出for循环(每台设备都是唯一一个)
 *  3:  结果里面有马桶 有手表 ,有体重秤
 */
- (PZJBleDevice *)deviceWrapperByPeripheral:(CBPeripheral *)aPeripheral
{
    PZJBleDevice *wrapper = nil;
    for (PZJBleDevice *scanned in self.scannedPeripherals) {
        if ([scanned.cbPeripheral isEqual: aPeripheral]) {
            wrapper = scanned;
            break;
        }
    }
    if (!wrapper) {
        // 过滤下没有名字的设备
        if(!KIsNullString(aPeripheral.name))
        {
            wrapper = [[PZJBleDevice alloc] initWithPeripheral:aPeripheral ];
            [self.scannedPeripherals addObject:wrapper];
        }
    }
    return wrapper;
}

/**
 * 返回过滤、排序后的设备
 * 从马桶 手表 体重秤 中过滤出来自己要的设备      通过名称,然后信号强度强的放前面
 */
- (NSMutableArray *)sortedDevices{
    NSMutableArray *array = [NSMutableArray new];
    if (self.filterName) {
        for (PZJBleDevice *device in self.scannedPeripherals) {
            if ([device.cbPeripheral.name containsString:self.filterName]) {//[device.name rangeOfString:self.filterName].length != 0
                [array addObject:device];
            }
        }
    }else{
        array = self.scannedPeripherals;
    }
    
    [array sortUsingComparator:^NSComparisonResult(PZJBleDevice *a, PZJBleDevice *b){
        return a.rssi < b.rssi;
    }];
    return [array mutableCopy];
}


-(void)connectDevice:(PZJBleDevice *)device connectSuccessBlock:(ConnectSuccessBlock)connectSuccessBlock connectFailBlock:(ConnectFailBlock)connectFailBlock
{
    self.connectSuccessBlock = connectSuccessBlock;
    self.connectFailBlock  = connectFailBlock;
    [self.centralManager connectPeripheral:device.cbPeripheral options:nil];

}
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral {

    NSLog(@"didConnectPeripheral 连接成功!!!!");
    self.saveDevice= [self deviceWrapperByPeripheral:peripheral];
    self.deviceIdentifier=peripheral.identifier.UUIDString;
    
     [[NSUserDefaults standardUserDefaults] setObject:self.deviceIdentifier forKey:peripheral.name];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
// 需要全局变量
   [self.saveDevice didDiscoverServices];
    if (self.connectSuccessBlock){
        self.connectSuccessBlock(self.saveDevice);
    }
    self.isConnected=YES;

}




- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral  error:(nullable NSError *)error{
    NSLog(@"didFailToConnectPeripheral  连接失败!!!! %@",error);
    if (self.connectFailBlock) self.connectFailBlock(error);
    self.isConnected=NO;
}

// 后台扫描设备跟前台扫描周围设备有一点不同：
//       也许是考虑到功耗的原因，在后台只能搜索特定的设备，所以必须要传Service UUID。不传的 话一台设备都搜不到。而这时就需要外设在广播包中有Service UUID，需要广播包中含有。
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(nullable NSError *)error{
    NSLog(@"didDisconnectPeripheral  断开连接!!!!  %@",error);
    self.saveDevice=nil;
    self.saveDevice.cbPeripheral=nil;
    // 更改下状态
    self.isConnected=NO;
    
    
    //如果是异常断开才需要自动重连 主动断开error为空
    if (error) {
        [self performSelector:@selector(retryConnectToDevice) withObject:self afterDelay:0.5];
    }
    

}

/** 重试连接设备 */
-(void)retryConnectToDevice
{
     
    NSUUID *uuid = [[NSUUID alloc] initWithUUIDString:self.deviceIdentifier];
    NSArray *arr = [NSArray arrayWithObject:uuid];
    NSArray *perArr = [self.centralManager retrievePeripheralsWithIdentifiers:arr];
    
    if(perArr && perArr.count) {
        CBPeripheral *peripheral = [perArr objectAtIndex:0];
        PZJBleDevice *device= [self deviceWrapperByPeripheral:peripheral];
        [self.centralManager connectPeripheral:device.cbPeripheral options:nil];
   
    }
}
@end
