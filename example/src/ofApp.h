#pragma once


#include "ofMain.h"
#include "ofxBleSensorTag.h"

#define HISTORY_MAX 10000

struct timedDouble{
    uint64_t    elapsedTime;
    double value;
};

class dataHistory{

public:
    double current, max, min;
    bool started;
    uint64_t currentTimeMicros;
//    deque<double> value_history;
//    deque<uint64_t> time_history;
    deque<timedDouble> value_history;
    dataHistory(){
        value_history.resize(0);
        current = max = min = 0.0;
        started = false;
    }

    void setCurrent(double value){
        started = true;
        current = value;
        if(max < value){
            max = value;
        }
        if(min > value){
            min = value;
        }
        timedDouble tb;
        
        tb.elapsedTime = ofGetElapsedTimeMicros();
        currentTimeMicros = tb.elapsedTime;
        
        tb.value = value;
        value_history.push_front(tb);

        while( value_history.size() > HISTORY_MAX ){
            value_history.pop_back();
        }
    }
};



class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit() {
        ble.disconnect();
    }
    
private:
    ofxBleSensorTag ble;
    bool bStartScan;

    vector<string> uuids;
    map<string,dataHistory> history;
    
    int nTag;
    double lux[16];
    double max_lux[16];
    float timeLastBeated;
    float timeLastScanned;
};
