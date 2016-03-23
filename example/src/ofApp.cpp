#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ble.setup();
    
    // Replace your Mio UUID.
    // UUID is printed to log window when we found Mio device.
    // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    
    //    uuids.push_back("EB9E30A5-7FE2-4FED-97A8-8EB2DCEF0AB3"); // ake mio alpha
//    uuids.push_back("A1CAD737-2144-4A8B-8A4B-05E4BF93E871"); // CC2650 SensorTag v2.0
//    uuids.push_back("C80EC239-EDDE-4DC8-95DC-02AD0B221B81"); // CC2650 SensorTag v2.0
    uuids.push_back("2FA9F3D7-39C6-446B-88FB-C6CDC4612EB5"); // SensorTag v1.0
    uuids.push_back("0F1D1580-2439-405A-BDF5-AB6B98B79851"); // SensorTag v1.0
    uuids.push_back("98140828-BB86-482B-81A3-5AE0A6A9F41F"); // SensorTag v1.0
    uuids.push_back("2D4245FC-7572-4E80-813B-728B6B47DD57"); // SensorTag v1.0

    
    for(int i = 0; i < uuids.size(); i++) {
        ble.addDeviceUUID(uuids[i]);
    }
    
    bStartScan = ble.startScan();
    nTag = uuids.size();
    
    for( vector<string>::iterator ite = uuids.begin(); ite != uuids.end(); ++ite){
        dataHistory dh;
        history.insert(map<string, dataHistory>::value_type(*ite, dh));
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

    uint64_t before = 0;
    for(int i=0; i< nTag; i++ ){
        if(ble.isConnectedToDevice(uuids[i])) {
            timeLastScanned = ofGetElapsedTimef();
            vector<double> values = ble.getLatestValuesFromDevice(uuids[i]);

            if(values.size()) {
                //                ofLogNotice() << "from " << uuids[i];
                for(auto value : values) {
                    uint64_t last = 0;
                    if( history[uuids[i]].started){
                        last = history[uuids[i]].currentTimeMicros;
                    }
                    //                    ofLogNotice() << "IR temperture " << value;
                    history[uuids[i]].setCurrent(value);
                    
                    uint64_t interval
                        =history[uuids[i]].value_history.front().elapsedTime - last;
                    
                    ofLogNotice() <<
                    interval << " :  " <<
                    history[uuids[i]].value_history.front().value;

                    before = history[uuids[i]].value_history.front().elapsedTime;
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
//
    int nTag = uuids.size();
    int i = 0;
    for (vector<string>::iterator ite = uuids.begin(); ite != uuids.end(); ++ite) {
        int history_size =  history[*ite].value_history.size();

        for(int j = 0; j < ofGetHeight(); j++){
            if( j >= history_size ){
                break;
            }
            ofSetColor( ofMap(history[*ite].value_history[j].value,
                              history[*ite].min, history[*ite].max + 0.1, 0, 255) );
            ofRect((ofGetWidth()/nTag)*i, j, ofGetWidth()/nTag, 1);

            
            /*
             int start_index = history[i].value_history.size() - ofGetHeight();
            if(start_index < 0 ){
                start_index = 0;
            }
            int line_index = start_index + j;
            if(line_index >= history[i].value_history.size() ){
                break;
            }
*/
            //            ofSetColor( ofMap(history[i].value_history[line_index],
//                              history[i].min, history[i].max+0.1, 0, 255) );


        }
        i++;
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
