//
//  ofxUnique2_1.h
//
//  Created by 服部 弘平 on 2015/12/27.
//
//


#ifndef ofxUnique2_1_h
#define ofxUnique2_1_h

#include "ofMain.h"
#include "ofxDmx.h"

#define PER_CHANNEL 2


class ofxUnique2_1 : public ofBaseApp
{
    
public:
    ofxUnique2_1();
    ~ofxUnique2_1();
    
    bool isConnected();
    void setup(string path, int total);
    void set_startChannel(int target, int startChannel);
    
    void communicateStart();
    void communicateStop();
    
    void change_pump(int target, int val);
    void change_fan(int target, int val);
        
    
    void update();
    
    static ofEvent<string> ERROR;
    
    
private:
    void setChannelManager(int target, int ch, int val);
    
    bool checker(int target, int ch, int val);
    bool checker_target(int target);
    bool checker_channel(int ch);
    bool checker_val(int val);
    
    ofxDmx *_dmx;
    
    bool UPDATE_ENABLED;
    int TOTAL;
    
    string ERROR_TEXT;
    
    vector<int>          _startChannels;
    vector<vector<int> > _ch_values;
};




#endif /* ofxUnique2_1_h */