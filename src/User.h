//
//  User.hpp
//  Essencia_Milan
//
//  Created by Helena Bantulà i Fonts on 08/03/16.
//
//

#ifndef User_h
#define User_h

#include <stdio.h>
#include "ofMain.h"
#include "Light.h"


#endif /* User_hpp */

enum userStateType{
    
    STATE_INITIAL,
    STATE_WARMING,
    STATE_PLAY,
    STATE_STOP,
    STATE_WAIT
};

class User{
    
public:
    
    int sensorID;
    //int pars[2];
    bool active;
    ofSoundPlayer sound;
    char heartBeat;
    
    //TIME MANAGEMENT
    int timeSinceUser;
    int timeSinceLeft;
    int playTime = 40000;
    int warmingTime = 2000;
    int stopTime = 3000;
    
    
    //CONTROL STATE
    void update();
    userStateType userState;
    
    
    
    //INHERENT
    User(string soundfile, int position);
    
    
    //STATES
    void initial();
    void warming();
    void play();
    void stop();
    void wait();
    void setHeartBeat(char value);


};