//
//  ofxUnique2_1.cpp
//
//  Created by 服部 弘平 on 2015/12/27.
//
//

#include "ofxUnique2_1.h"


ofxUnique2_1::ofxUnique2_1()
{
}


ofxUnique2_1::~ofxUnique2_1()
{
}

ofEvent<string> ofxUnique2_1::ERROR = ofEvent<string>();


//--------------------------------------------------------------
bool ofxUnique2_1::isConnected()
{
    return _dmx->isConnected();
}


//--------------------------------------------------------------
void ofxUnique2_1::setup(string path, int total)
{
    cout << "[ofxUnique2_1::setup] get total : " << total << endl;
    
    if(path != "" && total > 0)
    {
        TOTAL = total;
        _dmx = new ofxDmx();
        _dmx->connect(path, 512);
        
        cout << "[ofxUnique2_1::setup] path : " << path << endl;
        cout << "[ofxUnique2_1::setup] total(set to ofxDmx) : " << PER_CHANNEL * TOTAL << endl;
        
        for(int i = 0; i < TOTAL; i++)
        {
            vector<int> list;
            
            for(int j = 0; j < PER_CHANNEL; j++)
            {
                list.push_back(0);
            }
            _startChannels.push_back(1+(PER_CHANNEL*i));
            _ch_values.push_back(list);
            
            cout << "[ofxUnique2_1::setup] _startChannels[" << i << "]:" << _startChannels[i] << endl;
        }
    }
}


//--------------------------------------------------------------
void ofxUnique2_1::set_startChannel(int target, int startChannel)
{
    cout << "[ofxUnique2_1::set_startChannel] target : " << target << ", startChannel : " << startChannel << endl;
    _startChannels[target] = startChannel;
}


//--------------------------------------------------------------
void ofxUnique2_1::communicateStart()
{
    UPDATE_ENABLED = true;
}

void ofxUnique2_1::communicateStop()
{
    UPDATE_ENABLED = false;
}


//--------------------------------------------------------------
void ofxUnique2_1::change_pump(int target, int val)
{
    setChannelManager(target, 1, val);
}


void ofxUnique2_1::change_fan(int target, int val)
{
    setChannelManager(target, 2, val);
}


//--------------------------------------------------------------
void ofxUnique2_1::update()
{
    if(_dmx->isConnected())// connect
    {
        if(UPDATE_ENABLED)
        {
            for(int i = 0; i < TOTAL; i++)
            {
                for(int j = 1; j <= PER_CHANNEL; j++)
                {
                    _dmx->setLevel((_startChannels[i]-1)+j, _ch_values[i][j-1]);
                }
            }
            _dmx->update();
        }
    }
}


//--------------------------------------------------------------
// PRIVATE
//--------------------------------------------------------------
void ofxUnique2_1::setChannelManager(int target, int ch, int val)
{
    if(checker(target, ch, val))
    {
        _ch_values[target-1][ch-1] = val;
    }
}


bool ofxUnique2_1::checker(int target, int ch, int val)
{
    bool f1 = checker_target(target);
    bool f2 = checker_channel(ch);
    bool f3 = checker_val(val);
    
    if(f1 && f2 && f3)// success
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool ofxUnique2_1::checker_channel(int ch)
{
    if(ch >= 1 && ch <= PER_CHANNEL)
    {
        return true;
    }
    else
    {
        ERROR_TEXT = "[ofxUnique2_1::ERROR] channel is bad.";
        ofNotifyEvent(ERROR, ERROR_TEXT);
        return false;
    }
}


bool ofxUnique2_1::checker_target(int target)
{
    if(target >= 1 && target <= TOTAL)
    {
        return true;
    }
    else
    {
        ERROR_TEXT = "[ofxUnique2_1::ERROR] target is bad.";
        ofNotifyEvent(ERROR, ERROR_TEXT);
        return false;
    }
}

bool ofxUnique2_1::checker_val(int val)
{
    if(val >= 0 && val <= 255)
    {
        return true;
    }
    else
    {
        ERROR_TEXT = "[ofxUnique2_1::ERROR] set level is bad.";
        ofNotifyEvent(ERROR, ERROR_TEXT);
        return false;
    }
}