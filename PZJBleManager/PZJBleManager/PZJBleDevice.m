//
//  PZJBleDeviceTwo.m
//  PZJBleManager
//
//  Created by 潘志健 on 2021/11/8.
//

#import "PZJBleDevice.h"

NSString * const kCCCustomServiceUUID = @"2E8C0001-2D91-5533-3117-59380A40AF8F";
NSString *  const kCCCustomWritingCharacteristicUUID = @"6e400002-ffff-ffff-6943-6172626f6e58";
NSString *  const kCCCustomNotifyCharacteristicUUID = @"6e400003-ffff-ffff-6943-6172626f6e58";

@interface PZJBleDevice () <CBPeripheralDelegate>



@end

@implementation PZJBleDevice

- (instancetype)initWithPeripheral:(CBPeripheral *)aPeripheral {
    if (self = [super init]) {
        self.cbPeripheral= aPeripheral;
    }
    return self;
}

- (void)didDiscoverServices
{
    self.cbPeripheral.delegate=self;
    [self.cbPeripheral discoverServices:nil];
}



#pragma mark - CBPeripheralDelegate
#pragma mark 发现服务

- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(nullable NSError *)error{
    NSLog(@"发现服务====%@",peripheral.services);
    for (CBService *service in peripheral.services) {
        
        [self.cbPeripheral discoverCharacteristics:nil forService:service];
    }
    
}


#pragma mark 发现特征
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error {

    for (CBCharacteristic *s in service.characteristics) {
        NSLog(@"发现特征====%@",s);
        if ([s.UUID isEqual:[CBUUID UUIDWithString:@"2E8C0002-2D91-5533-3117-59380A40AF8F"]]) {
            self.notifyChar = s;
            [self.cbPeripheral setNotifyValue:YES forCharacteristic:self.notifyChar];
        }
    }
}

//=====发现服务====(
//    "<CBService: 0x282401300, isPrimary = YES, UUID = FE59>",
//    "<CBService: 0x282401700, isPrimary = YES, UUID = Heart Rate>",
//    "<CBService: 0x282401740, isPrimary = YES, UUID = Battery>",
//    "<CBService: 0x282401780, isPrimary = YES, UUID = 2E8C0001-2D91-5533-3117-59380A40AF8F>"
//)
//2021-11-09 15:44:44.009354+0800 PZJBleManager[947:212440] =====发现特征====<CBCharacteristic: 0x2815a0600, UUID = 8EC90003-F315-4F60-9FB8-838830DAEA50, properties = 0x28, value = (null), notifying = NO>
//2021-11-09 15:44:44.011473+0800 PZJBleManager[947:212440] =====发现特征====<CBCharacteristic: 0x2815a4180, UUID = 2A37, properties = 0x10, value = (null), notifying = NO>
//2021-11-09 15:44:44.011799+0800 PZJBleManager[947:212440] =====发现特征====<CBCharacteristic: 0x2815a84e0, UUID = 2A38, properties = 0x2, value = (null), notifying = NO>
//2021-11-09 15:44:44.012457+0800 PZJBleManager[947:212440] =====发现特征====<CBCharacteristic: 0x2815a8480, UUID = Battery Level, properties = 0x12, value = (null), notifying = NO>
//2021-11-09 15:44:44.013799+0800 PZJBleManager[947:212440] =====发现特征====<CBCharacteristic: 0x2815a8420, UUID = 2E8C0003-2D91-5533-3117-59380A40AF8F, properties = 0xC, value = (null), notifying = NO>
//2021-11-09 15:44:44.014050+0800 PZJBleManager[947:212440] =====发现特征====<CBCharacteristic: 0x2815a8540, UUID = 2E8C0002-2D91-5533-3117-59380A40AF8F, properties = 0x10, value = (null), notifying = NO>
//2021-11-09 15:44:44.117918+0800 PZJBleManager[947:212440] 订阅失败 !!!

#pragma mark 订阅代理
- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error
{
    if(error){
        NSLog(@"订阅失败 !!!");
    }else{
        NSLog(@"订阅成功 !!!");
    }
}


-(void)bleDataCallBack:(BleDataCallback)bleDataCallBack
{
    self.bleDataCallBack = bleDataCallBack;
}

#pragma mark 接收数据
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error {
    
    if(error)
    {
        NSLog(@"接收数据didUpdateValueForCharacteristic===%@",error);
        return;
    }
    
    NSData *value = [characteristic.value copy];
    NSLog(@"接收到的数据===%@",value);
    if([characteristic isEqual:self.notifyChar]){
        if (self.bleDataCallBack) {
            self.bleDataCallBack(characteristic,value);
        }
    }
    
}


#pragma mark 数据写入的回调
- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
    //必须有  writeChar
    if(error){
        self.readDataError(error);
        NSLog(@"写入数据失败didWriteValueForCharacteristic !!!");
        return;
    }
    
    self.readDataSucceed();
}






/************-------------------指令--------------------************/
#pragma mark 指令
- (void)remoteControlType:(NSString *)type success:(void (^)(void))success
                orFailure:(void (^)(NSError *error))failure
{
    Byte cmd[] = {0x4F, 0x53, 0x4C, 0x75};
    NSData *data = [NSData dataWithBytes:cmd length:sizeof(cmd)];
    [self.cbPeripheral writeValue:data
                forCharacteristic:self.writingChar
                             type:CBCharacteristicWriteWithResponse];
    self.readDataError = failure;
    self.readDataSucceed  = success;
}

- (void)writeCharacteristic
{
    
}

@end
