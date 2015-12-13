# ofxBleSensorTag

An openFrameworks Addon to connect to Texus Instruments SensorTag.

## System Requirements

### Mac
  Tested on OS X 10.10.5 / XCode 7.2 / openFrameworks 0.8.4
### iOS
 May work, not tested.

## How to use

1. Generate Project with oF Project Generator, adding including this Addon.
2. Add CoreBluetooth.framework to the XCode Project.
3. Define your SensorTag's identifire(UUID) in ofApp.cpp

## API

### ofxBleSensorTag
(in progress)

## BLE device configure

Objective-C classes in BlePeripherals.mm has functions which contain device-specific information and procedure; BLE peripheral name, chracteristics UUID, algorithm to calculate raw sensor data to metrics.


## Update history

### ver 0.01 [beta] release

Can read only lux value from CC2650 SensorTag.
Also can read Mio Alpha's heartrate bpm value.

## License

MIT License.

## Author

* Morimasa Aketa @ake_____

## Special Thanks

* Ishii 2bit [[bufferRenaiss co., ltd.](http://buffer-renaiss.com)]

This program was made through extending 2bit's [ofxMioAlpha](https://github.com/2bbb/ofxMioAlpha) code.



