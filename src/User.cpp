//
//  User.cpp
//  Essencia_Milan
//
//  Created by Helena Bantulà i Fonts on 08/03/16.
//
//

#include "User.h"


User:: User(string soundfile, int position){
    
    sound.load(soundfile,true);
    
    sensorID=position;
    
    userState = STATE_INITIAL;

}


// Decidir quin estat s'executa
void User:: update(){
    
    switch(userState){
        case STATE_INITIAL:
            initial();
            break;
        case STATE_WARMING:
            warming();
            break;
        case STATE_PLAY:
            play();
            break;
        case STATE_STOP:
            stop();
            break;
        case STATE_WAIT:
            wait();
            break;
    }



}

void User::initial(){
    //  baixar la musica?
    // fer un fadeOut dels llums
    
}


void User::warming(){
    //  calculant la frequencia
    
    // si han passat dos segons, canvies estat
    if ((ofGetElapsedTimeMillis()-timeSinceUser)>warmingTime){
        userState = STATE_PLAY;
    }

}


void User::play(){
    
    if ((ofGetElapsedTimeMillis()-timeSinceUser)>playTime)
        userState = STATE_STOP;
}


void User::stop(){
    if ((ofGetElapsedTimeMillis()-timeSinceLeft)>stopTime)
        userState = STATE_INITIAL;
    
    
}


void User::wait(){
        cout<<"FUNCIONO_OFF"<<endl;
}


void User::setHeartBeat(char value){
    //heartBeat = value;
    
    if(userState == STATE_INITIAL){
        timeSinceUser = ofGetElapsedTimeMillis();
        Light::getInstance().fadeUserPars(1, 'O', 1, warmingTime, sensorID); //dos segons de fadeOut
        userState = STATE_WARMING;
    }
    
    
    if (userState == STATE_PLAY && value == 'H'){
        cout<<"HIGH"<<endl;
        sound.play();
        Light::getInstance().fadeUserPars(1, 'I', 1, 500, sensorID);       //fadeIn + fadeOut
    }
    
    else if (userState == STATE_PLAY && value == 'L'){
        cout<<"LOW"<<endl;
        sound.play();
        Light::getInstance().fadeUserPars(1, 'I', 1, 500, sensorID);       //fadeIn + fadeOut
    
    }
    
    if (userState == STATE_STOP){
        Light::getInstance().fadeUserPars(1, 'O', 1, warmingTime, sensorID); //dos segons de fadeOut
        timeSinceLeft = ofGetElapsedTimeMillis();
    }
}



