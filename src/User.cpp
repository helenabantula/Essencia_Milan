//
//  User.cpp
//  Essencia_Milan
//
//  Created by Helena Bantulà i Fonts on 08/03/16.
//
//

#include "User.h"


User:: User(string soundfile1, string soundfile2, int position){
    
    soundUp.load(soundfile1,true);
    soundDown.load(soundfile2,true);
    
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

    
}


void User::warming(){
    
    // si han passat dos segons i dins d'aquests reps una H, canvia estat
    if (((ofGetElapsedTimeMillis() - timeSinceUser) > warmingTime) && (ofGetElapsedTimeMillis() - timeSinceH < warmingTime)){
        userState = STATE_PLAY;
        timeSincePlay = ofGetElapsedTimeMillis();
    }

}


void User::play(){
    
    
    if ((ofGetElapsedTimeMillis() - timeSincePlay) >= periodMean) {
        
        // play light and sound
        soundUp.play();
        Light::getInstance().fadeUserPars(1, 'I', 2, 200, sensorID);       //fadeIn
        
        // start again
        timeSincePlay = ofGetElapsedTimeMillis();
        playPhase = true;
    }
    
    if (((ofGetElapsedTimeMillis() - timeSincePlay) >= phaseMean) && playPhase){
        soundDown.play();
        Light::getInstance().fadeUserPars(1, 'O', 1, 200, sensorID);       //fadeOut
        playPhase = false;
    }
    
    if (((ofGetElapsedTimeMillis()-timeSinceUser) > playTime) || (ofGetElapsedTimeMillis() - timeSinceH > maxErrorTime)) {
        Light::getInstance().fadeUserPars(1, 'O', 1, warmingTime, sensorID); //dos segons de fadeOut
        timeSinceLeft = ofGetElapsedTimeMillis();
        userState = STATE_STOP;
        cout<<"HE PARAT!!!!"<<endl;
    }
    
}


void User::stop(){
    if ((ofGetElapsedTimeMillis()-timeSinceLeft) > stopTime)
        periodMean = periodMeanInit;
        period.clear();
        userState = STATE_INITIAL;
}


void User::wait(){
        cout<<"FUNCIONO_OFF"<<endl;
}


void User::setHeartBeat(char value){

    
    if(((userState == STATE_INITIAL) && (value == 'H') && (ofGetElapsedTimeMillis() - timeSinceH) < maxPeriod)){    // asseguro H no falses
        timeSinceUser = ofGetElapsedTimeMillis();
        Light::getInstance().fadeUserPars(1, 'O', 1, warmingTime, sensorID);
        userState = STATE_WARMING;
        cout<<"HE ENTRAT"<<endl;

    }
    
    
//    if (userState == STATE_PLAY && value == 'H'){
//        cout<<"HIGH"<<endl;
//        sound.play();
//        Light::getInstance().fadeUserPars(1, 'I', 1, 500, sensorID);       //fadeIn + fadeOut
//    }
    
//    else if (userState == STATE_PLAY && value == 'L'){
//        cout<<"LOW"<<endl;
//        //sound.play();
//        //Light::getInstance().fadeUserPars(1, 'I', 1, 500, sensorID);       //fadeIn + fadeOut
//    
//    }
    
//    if (userState == STATE_STOP){
//        //Light::getInstance().fadeUserPars(1, 'O', 1, warmingTime, sensorID); //dos segons de fadeOut
//        //timeSinceLeft = ofGetElapsedTimeMillis();
//        cout<<"HE PARAT!!!!"<<endl;
//    }
    
        
    
    //frequency computation (always?)
    if (value == 'H'){
        
        // period
        tempPeriod = ofGetElapsedTimeMillis() - timeSinceH;
        
        if (tempPeriod > minPeriod && tempPeriod < maxPeriod){
            period.push_back(tempPeriod);
        }
        else {
            period.push_back(periodMeanInit);
        
        }
        
        // period mean
        periodMean = 0;
        for( int i = 0; i < period.size(); i++) {
            periodMean += period[i];
        }
        periodMean /= period.size();
        
        
        
        // tornem a començar
        timeSinceH = ofGetElapsedTimeMillis();
    
        // phase computation (always?)
        phaseMean = 0.25*periodMean;
    }
}



