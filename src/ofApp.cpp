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
    Light::getInstance().initialize(4); //maxUsers
    
    
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
    
    
//    if ((lectura[0])){          // no llegeix espais
//        int sensor=(int)lectura[0]-48; //ASCII comença per 48
//        users[sensor].setHeartBeat(lectura[1]);
//        cout<<lectura<<endl;
//    }
    
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
    
    
    for (int i=0; i<users.size(); i++){
        users[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

}


