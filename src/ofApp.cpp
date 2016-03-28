#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    ////////////////////////// SERIAL ////////////////////////
    ofSetVerticalSync(true);
    int baud = 115200;

    serial.listDevices();
    
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
#if TARGET_RASPBERRY_PI
    serial.setup(0, baud);
#else
    serial.setup("/dev/cu.usbmodem1421",baud);
#endif

    ////////////////////////// USERS ////////////////////////
    
    User temUser("GreuEssencia.wav","PercuEssencia.wav",0);
    users.push_back(temUser);
    
    User temUser1("PercuEssencia.wav","PercuEssencia.wav",1);
    users.push_back(temUser1);
    
    ////////////////////////// LIGHT ////////////////////////
    Light::getInstance().initialize(numUsers); //maxUsers
    
    
    ////////////////////////// SOUND ////////////////////////
    background.load("humans_OK.mp3",true);
    background.setVolume(0.85);
    background.setLoop(true);
    background.play();
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    unsigned  char lectura[3];
    serial.readBytes(lectura, 2);  //int readBytes(unsigned char * buffer, int length);
    
    int sensor=(int)lectura[0]-48; //ASCII comença per 48
    switch (sensor) {
        case 0:
            users[sensor].setHeartBeat(lectura[1]);
            cout<<lectura<<endl;
            break;
        case 1:
            users[sensor].setHeartBeat(lectura[1]);
            cout<<lectura<<endl;

            break;
        case 2:
            users[sensor].setHeartBeat(lectura[1]);
            cout<<lectura<<endl;

            break;
        default:
            break;
    }
    
    
    int counter_state_initial = 0;
    for (int i = 0; i < users.size(); i++){
        users[i].update();
        if (users[i].userState == STATE_INITIAL) {
            counter_state_initial ++;
        }
    }
    
    if (counter_state_initial == users.size())
        Light::getInstance().randomPlay(true);
    else
        Light::getInstance().randomPlay(false);
        
    
    
    Light::getInstance().getInfo();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofSetColor(0);
    

    ofDrawBitmapString((int)Light::getInstance().packDMX[0], 50, 50);
    ofDrawBitmapString((int)Light::getInstance().packDMX[1], 50, 70);
    ofDrawBitmapString((int)Light::getInstance().packDMX[2], 50, 90);
    
    ofDrawBitmapString((int)Light::getInstance().packDMX[3], 200, 50);
    ofDrawBitmapString((int)Light::getInstance().packDMX[4],200, 70);
    ofDrawBitmapString((int)Light::getInstance().packDMX[5], 200, 90);
    
    ofDrawBitmapString((int)Light::getInstance().packDMX[6], 350, 50);
    ofDrawBitmapString((int)Light::getInstance().packDMX[7], 350, 70);
    ofDrawBitmapString((int)Light::getInstance().packDMX[8], 350, 90);
    
    ofDrawBitmapString((int)Light::getInstance().packDMX[9], 500, 50);
    ofDrawBitmapString((int)Light::getInstance().packDMX[10], 500, 70);
    ofDrawBitmapString((int)Light::getInstance().packDMX[11], 500, 90);

}


