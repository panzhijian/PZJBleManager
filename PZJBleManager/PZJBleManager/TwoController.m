//
//  TwoController.m
//  PZJBleManager
//
//  Created by 潘志健 on 2021/11/8.
//

#import "TwoController.h"
#import "PZJBleManager.h"
#import "PZJBleDevice.h"
#import "ToiletBleTool.h"
#define KIsNullString(str) ([str isKindOfClass:[NSNull class]] || str == nil || [str length] < 1 ? YES : NO )

@interface TwoController ()<UITableViewDelegate,UITableViewDataSource>
@property(nonatomic,strong)NSMutableArray *deviceArr;
@property(nonatomic,strong)PZJBleManager *bleManager;
@property(nonatomic,strong)PZJBleDevice *targetDevice;
@property (weak, nonatomic) IBOutlet UITableView *tableV;

@end

@implementation TwoController

-(void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:YES];
}

-(NSMutableArray *)deviceArr
{
    if(!_deviceArr){
        _deviceArr=[[NSMutableArray alloc] init];
    }
    return _deviceArr;
}
- (void)viewDidLoad {
    [super viewDidLoad];

//1: 连接和断开连接 的枚举码
//2: 和硬件交互的  服务和特征有多少个
//3:  怎么将接收到的数据传给各个控制器  (完成)
//   1>>写个方法 用一个属性保存blcok  然后block回调数据
//   2>>通过通知 NSNotifition 传值
//4: 断开连接的处理
//5: 退出app 怎么连接到上一个设备
//6: 蓝牙后台问题 (目前没发现问题)
//7: 不能自己扫描 要点击按钮扫描问题
    
    self.navigationItem.title=@"TestDemo";
    self.tableV.dataSource=self;
    self.tableV.delegate=self;
    self.tableV.rowHeight=60;
    
    
    
    [[PZJBleManager sharedInstance] startBleScanWithInterval:2 filterName:@"B" scanSuccessBlock:^(NSMutableArray *deviceArr) {
        self.deviceArr=deviceArr;
        [self.tableV reloadData];
        
    } scanFailBlock:^(ScanDeviceFail code) {
                
    }];

}



- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.deviceArr.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CMainCell = @"CMainCell";
    PZJBleDevice *device=self.deviceArr[indexPath.row];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CMainCell];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault  reuseIdentifier:CMainCell] ;
    }
    cell.textLabel.text = device.cbPeripheral.name;
    return cell;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    PZJBleDevice *device=self.deviceArr[indexPath.row];
    if(self.deviceArr.count<=0){
        NSLog(@"设备总数为0");
        return;
    }
    
    [[PZJBleManager sharedInstance] connectDevice:device connectSuccessBlock:^(PZJBleDevice *device) {
        
        self.targetDevice=device;
        // 监听接收到的数据
        [self.targetDevice   bleDataCallBack:^(CBCharacteristic *character, NSData *data) {
            
            NSLog(@"监听到的数据====%@",data);
        }];
        
    } connectFailBlock:^(NSError *error) {
        
    }];
    
}

- (IBAction)scanBut:(id)sender {
    
  
    

}

// 写数据
- (IBAction)clickWriteData:(id)sender {
    if([PZJBleManager sharedInstance].isConnected&& self.targetDevice){
    
        [self.targetDevice   remoteControlType:@"0" success:^{
            NSLog(@"写入数据成功  !!!");
        } orFailure:^(NSError * _Nonnull error) {
            NSLog(@"写入数据失败  !!!");
        }];
        
    }
}


// 读数据
- (IBAction)clickRadData:(id)sender {
    [self.targetDevice.cbPeripheral readValueForCharacteristic:self.targetDevice.notifyChar];
    
}


- (IBAction)disConnectBut:(id)sender {
    [self.bleManager.centralManager  cancelPeripheralConnection:self.targetDevice.cbPeripheral];
}


/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
