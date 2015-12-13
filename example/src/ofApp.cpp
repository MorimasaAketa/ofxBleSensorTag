#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ble.setup();
    
    // Replace your Mio UUID.
    // UUID is printed to log window when we found Mio device.
    // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    
    //    uuids.push_back("EB9E30A5-7FE2-4FED-97A8-8EB2DCEF0AB3"); // ake mio alpha
    //    uuids.push_back("A1CAD737-2144-4A8B-8A4B-05E4BF93E871"); // CC2650 SensorTag v2.0
    uuids.push_back("C80EC239-EDDE-4DC8-95DC-02AD0B221B81"); // CC2650 SensorTag v2.0

    for(int i = 0; i < uuids.size(); i++) {
        ble.addDeviceUUID(uuids[i]);
    }
    
    bStartScan = ble.startScan();
    nTag = uuids.size();
    for (int i=0; i < nTag; i++) {
        max_lux[i] = 1.0;
        lux[i] = 0.0;
    }
    timeLastBeated = 0.0;
    timeLastScanned = 0.0;

    //
}

//--------------------------------------------------------------
void ofApp::update(){
    // If ble succeeds in start to scan device, startScan will return true.
    if(!bStartScan) {
        bStartScan = ble.startScan();
    }
    
    for(int i=0; i< uuids.size(); i++ ){
        if(ble.isConnectedToDevice(uuids[i])) {
            timeLastScanned = ofGetElapsedTimef();
            vector<int> hbs = ble.getLatestHeartBeatsFromDevice(uuids[i]);
            if(hbs.size()) {
                ofLogNotice() << "from " << uuids[i];
                for(auto hb : hbs) {
                    ofLogNotice() << "lux " << hb;
                    lux[i]=(double)hb;
                    if(max_lux[i] < lux[i]){
                        max_lux[i] = lux[i];
                    }
                }
            }else{
                //            lux = 0.0;
                //            timeLastBeated = 0.0;
        }
    }
    }
 }

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    // Paints screen sensed max brightness as white.
    for (int i=0; i<nTag; i++) {
        ofSetColor( ofMap(lux[i], 0,max_lux[i]+0.1, 0, 255) );
        ofRect((ofGetHeight()/nTag)*i, 0, ofGetWidth()/nTag, ofGetHeight());
    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}
