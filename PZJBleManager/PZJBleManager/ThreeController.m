//
//  ThreeController.m
//  PZJBleManager
//
//  Created by 潘志健 on 2021/11/11.
//

#import "ThreeController.h"

@interface ThreeController ()

@end

@implementation ThreeController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.navigationItem.title=@"进制转化";
    
    
    [self test];
    
    
    
    //发送数据
//   NSData *data1= [self hexToBytes:@"1B9901"];
//
//
//    //发送数据
//    NSData *data = [self getCheckSum:@"1B9901"];//data=<1b99014b>
   
    
    
    
    
    

//    // 大端模式 转为本地模式   蓝牙数据的传输都是小端模式
//    NSLog(@"%0x",CFSwapInt16BigToHost(10));
//    1>>大端的00 00 00 0a 转换为0a 00 00 00
//    2>>计算器,拿到的nsdata 要先转为大端自己,然后放到计算器中去
//    3>> nsadata转int 其实就是小端转为大端让我们看出来是10
    
 
//    Byte value[3]={0};
//    value[0]=0;
//    value[1]=2;
//    value[2]=1;
//    value[3]=10;
//    value[4]=13;
//    value[5]=14;
//    value[6]=15;
//    NSData * data = [NSData dataWithBytes:&value length:sizeof(value)];
//    [self integerFromBytes:<#(const Byte *)#> index:1];
    
}

- (NSUInteger)integerFromBytes:(const Byte *)bytes index:(Byte)index{
    NSUInteger steps = bytes[index] +
    bytes[index+1] * 0x100 +
    bytes[index+2] * 0x10000 +
    bytes[index+3] * 0x1000000;
    return steps;
}

 #pragma mark nadata 的第几个元素
-(void)test3{
    Byte value[3]={0};
    value[0]=10;
    value[1]=2;
    value[2]=0x1a;
    NSData * data = [NSData dataWithBytes:&value length:sizeof(value)];
    
    const u_int8_t *bytes = [data bytes];
    NSInteger powerValue = bytes[2];
    NSLog(@"%ld",powerValue);
}



// 大端的nadata 转小端int
-(signed int)signedDataTointWithData:(NSData *)data Location:(NSInteger)location Offset:(NSInteger)offset {
    signed int value=0;
    NSData *intdata= [data subdataWithRange:NSMakeRange(location, offset)];
    if (offset==2) {
        value=CFSwapInt16BigToHost(*(int*)([intdata bytes]));
    }
    else if (offset==4) {
        value = CFSwapInt32BigToHost(*(int*)([intdata bytes]));
    }
    else if (offset==1) {
        signed char *bs = (signed char *)[[data subdataWithRange:NSMakeRange(location, 1) ] bytes];
        value = *bs;
    }
    return value;
}



//int转data
-(NSData *)intToData:(int)i{
    NSData *data = [NSData dataWithBytes: &i length: sizeof(i)];
    return data;
}

////data转int
-(int)dataToInt:(NSData *)data
{
    int i;
    [data getBytes:&i length:sizeof(i)];
    return i;
}






#pragma mark Byte转NSData
//优点：这种方法比较简单，没有进行转换，直接一个字节一个字节的拼装好发送出去。
//缺点：当发送数据比较长时会很麻烦，而且不易更改。
-(void)test
{
    Byte value[3]={0};
    value[0]=10;
    value[1]=2;
    value[2]=3;
    NSData * data = [NSData dataWithBytes:&value length:sizeof(value)];
    

    Byte bytes[20];
       bytes[0] = (Byte)(1);//帧头
       bytes[1] = (Byte)(2);//读取电量的功能码
       for (NSInteger i = 2; i < 19; i++) {
           bytes[i] = (Byte)(0);
       }
//       bytes[19] = (Byte)(/*校验和*/);
       NSData *data2 = [NSData dataWithBytes:bytes length:sizeof(bytes)];
    NSLog(@"data =%@  data2%@",data,data2);
    
//    2021-11-11 13:14:25.034156+0800 PZJBleManager[507:44725] data =<1b9901>  data2<01020000 00000000 00000000 00000000 00000000>
}

#pragma mark NSString转NSData
//优点：比较直观，可以一次转换一长条数据，对于一些功能简单的蓝牙程序，这种转换能处理大部分情况。
//缺点：只能发送一些固定的指令，不能参与计算。
- (NSData *)hexToBytes:(NSString *)str{
    NSMutableData* data = [NSMutableData data];
    int idx;
    for (idx = 0; idx+2 <= str.length; idx+=2) {
        NSRange range = NSMakeRange(idx, 2);
        NSString* hexStr = [str substringWithRange:range];
        NSScanner* scanner = [NSScanner scannerWithString:hexStr];
        unsigned int intValue;
        [scanner scanHexInt:&intValue];
        [data appendBytes:&intValue length:1];
    }
    return data;
}
#pragma mark 求校验和
//接下来探讨下发送的数据需要计算的情况。
//最常用的发送数据需要计算的场景是求__校验和（CHECKSUM）__。这个根据硬件厂商来定，常见的求校验和的规则有：
//
//如果发送数据长度为n字节，则CHECKSUM为前n-1字节之和的低字节
//CHECKSUM=0x100-CHECKSUM（上一步的校验和）
//
//如果我要发送带上校验和的0x1B9901，方法就是：


- (NSData *)getCheckSum:(NSString *)byteStr{
    int length = (int)byteStr.length/2;
    NSData *data = [self hexToBytes:byteStr];
    Byte *bytes = (unsigned char *)[data bytes];
    Byte sum = 0;
    for (int i = 0; i<length; i++) {
        sum += bytes[i];
    }
    int sumT = sum;
    int at = 256 - sumT;

    printf("校验和：%d\n",at);
    if (at == 256) {
        at = 0;
    }
    NSString *str = [NSString stringWithFormat:@"%@%@",byteStr,[self ToHex:at]];
    return [self hexToBytes:str];
}
//将十进制转化为十六进制
- (NSString *)ToHex:(int)tmpid{
    NSString *nLetterValue;
    NSString *str =@"";
    int ttmpig;
    for (int i = 0; i<9; i++) {
        ttmpig=tmpid%16;
        tmpid=tmpid/16;
        switch (ttmpig){
            case 10:
                nLetterValue =@"A";break;
            case 11:
                nLetterValue =@"B";break;
            case 12:
                nLetterValue =@"C";break;
            case 13:
                nLetterValue =@"D";break;
            case 14:
                nLetterValue =@"E";break;
            case 15:
                nLetterValue =@"F";break;
            default:
                nLetterValue = [NSString stringWithFormat:@"%u",ttmpig];
        }
        str = [nLetterValue stringByAppendingString:str];
        if (tmpid == 0) {
            break;
        }
    }
    //不够一个字节凑0
    if(str.length == 1){
        return [NSString stringWithFormat:@"0%@",str];
    }else{
        return str;
    }
}



@end
