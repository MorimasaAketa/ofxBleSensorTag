//
//  BlePeripherals.h
//  BleSensorTag
//
//  Created by Morimasa Aketa on 2015/12/12.
//
//

#ifndef BlePeripherals_h
#define BlePeripherals_h
#endif /* BlePeripherals_h */

#import <Foundation/Foundation.h>


#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#   import <CoreBluetooth/CoreBluetooth.h>
#elif TARGET_OS_MAC
#   import <IOBluetooth/IOBluetooth.h>
#endif


enum BPSensorType {
    BPUnknown,
    BPMioHeartRate,
    BPSensorTagLux,
};

@interface BleCharacteristic: NSObject{
    NSString *name;
    NSString *uuidString;
    int type;
}
@property  (nonatomic,retain) NSString *name;
@property  (atomic) int type;
@property  (nonatomic,retain) NSString *uuidString;
-(bool) setupWithPeripheral:(CBPeripheral *) peripheral
                    Service:(CBService *) service;
@end

@interface MioAlphaPulse: BleCharacteristic

-(double) calcData: (NSData *)data;

@end

@interface SensorTagLux: BleCharacteristic
@end


@interface BlePeripherals: NSObject{
    NSMutableArray *peripherals;
    NSMutableArray *targetAdvertisementNames;
    NSMutableDictionary *characteristicsDict;

}
@property (nonatomic,retain) NSMutableArray *peripherals;
@property (nonatomic,retain) NSMutableArray *targetAdvertisementNames;
@property (nonatomic,retain) NSMutableDictionary *characteristicsDict;
-(id) init;
-(BleCharacteristic *) findCharacteristicForUUID:(NSString *)sUUID;
@end

@interface BlePeripheral: NSObject{
    NSMutableArray *characteristics;
}
@property (nonatomic, retain) NSMutableArray *characteristics;
@end
