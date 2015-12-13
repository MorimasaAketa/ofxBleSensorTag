//
//  BlePeripherals.mm
//  BleSensorTag
//
//  Created by Morimasa Aketa on 2015/12/12.
//
//

#import "BlePeripherals.h"

@implementation BlePeripherals
@synthesize targetAdvertisementNames, peripherals, characteristicsDict;

- (id) init{
    self = [super init];

    self.peripherals = [NSMutableArray new];
    self.targetAdvertisementNames = [NSMutableArray new];

    [self.targetAdvertisementNames addObjectsFromArray:@[@"MIO GLOBAL",
                                                         @"MIO GLOBAL LINK",
                                                         @"CC2650 SensorTag"]];


    BlePeripheral *mio = [BlePeripheral new];
    [mio.characteristics addObject:[MioAlphaPulse new]];
    [self.peripherals addObject:mio];

    BlePeripheral *sensorTag = [BlePeripheral new];
    [sensorTag.characteristics addObject:[SensorTagLux new]];
    [self.peripherals addObject:sensorTag];

    
    self.characteristicsDict = [NSMutableDictionary new];
    for ( BlePeripheral *p in self.peripherals){
        for ( BleCharacteristic *c in p.characteristics){
            [self.characteristicsDict setObject:c forKey:c.uuidString];
        }
    }
    return self;
}

-(BleCharacteristic *) findCharacteristicForUUID:(NSString *)sUUID {
    return [self.characteristicsDict objectForKey:sUUID];
}

@end

@implementation BlePeripheral
@synthesize characteristics;
-(id) init{
    self = [super init];
    self.characteristics = [[NSMutableArray alloc]init];
    return self;

    
}
@end;

@implementation BleCharacteristic
@synthesize name, uuidString, type;
- (id) init{
    self = [super init];
    self.name = @"";
    self.uuidString = @"";
    type = 0;
    return self;
}

- (bool) setupWithPeripheral:(CBPeripheral *)peripheral
                     Service:(CBService *)service{
    return true;
}

@end

#pragma device specific characteristics
@implementation MioAlphaPulse

-(id) init{
    self = [super init];
    self.name = @"mio alpha pluse";
    self.uuidString = @"2A37";
    type = 1;
}

-(double) calcData: (NSData *) data{
    const uint8_t *reportData = (const uint8_t *)[data bytes]; // bytes returns pointer
    uint16_t bpm = 0.0;

    if ((reportData[0] & 0x01) == 0) {
        /* uint8 bpm */ /* mio alpha sends uint8 */
        bpm = reportData[1];
    } else {
        /* uint16 bpm */
        bpm = CFSwapInt16LittleToHost(*(uint16_t *)(&reportData[1]));
    }

    return (double)bpm;
    
}
@end;


@implementation SensorTagLux
- (id) init{
    self = [super init];
    self.name = @"sensor tag lux";
    self.uuidString = @"F000AA71-0451-4000-B000-000000000000";
    type = 2;
}

- (bool) setupWithPeripheral:(CBPeripheral *)peripheral
                     Service:(CBService *)service{
    NSString *toWriteUUID = @"F000AA72-0451-4000-B000-000000000000";
    for(CBCharacteristic *characteristic in service.characteristics) {
        CBUUID *uuid = [characteristic UUID];
        if([uuid isEqual:[CBUUID UUIDWithString: toWriteUUID]]){
            uint8_t data = 0x01;
            [peripheral writeValue:[NSData dataWithBytes:&data length:1]
                 forCharacteristic:characteristic
                              type:CBCharacteristicWriteWithResponse];
            break;
        }
    }
    return true;
}

- (double) calcData: (NSData *)data{
    const uint8_t *reportData = (const uint8_t *)[data bytes];
    uint16_t lux = 0 ;
    double output;
    double magnitude;
    int mantissa;
    int exponent;

    lux = (uint16_t)reportData[1] << 8;
    lux += (uint16_t)reportData[0];

    mantissa = (int)lux & 0x0fff;
    exponent = (int)(lux >> 12) & 0xff;
    magnitude = pow(2.0, (double)exponent);
    output =  (double)mantissa * magnitude;
//    NSLog(@"lux: %f", output/100.0);
    return output / 100.0;
}

@end
