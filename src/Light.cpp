//
//  light.cpp
//  Corasonsitu
//
//  Created by Helena Bantulà i Fonts on 17/11/15.
//
//

#include "Light.h"


void Light::initialize(int numUsers){
#if TARGET_RASPBERRY_PI
    artnet.setup("192.168.1.103"); //IP de l'ordinador
#else
    artnet.setup("192.168.1.110");
#endif    
    //// Temporary Par ///
    ofColor  color;
    color = (255,0,65); // per tots igual
    
    
    for (int i = 0; i<maxPar; i++){
        Par temPar(color,0);
        leds.push_back(temPar);
    }

    
    vector<vector<int>> tempMatrix(numUsers, vector<int>(maxPar/numUsers));
    parUserAssign = tempMatrix;

//    for(int i=0 ; i<4 ; i++){
//        vector<int> tempMiniVec;
//        for(int j=0; j<2 ; j++){
//            tempMiniVec.push_back(0);
//        }
//        parUserAssign.push_back(tempMiniVec);
//    }
    
    for (int i = 0; i < numUsers; i++){
        for (int j = 0; j < maxPar/numUsers; j++){
            parUserAssign[i][j] = i*(maxPar/numUsers) +j;
        }
        
    }
    
    
    
    
    sendInfo();
}


void Light::getInfo(){
    
    int j=0;
    for (int i=0; i<leds.size(); i++){
        leds[i].update();
        
        packDMX[j] = leds[i].color[0];
        packDMX[j+1] = leds[i].color[1];
        packDMX[j+2] = leds[i].color[2];
        j=j+3;
    }
    
    sendInfo();
}


void Light::sendInfo(){
    
    artnet.sendDmx("192.168.1.150",packDMX, sizeof(packDMX));
}


void Light::equalFade(float k, char fade, int type, int step){
    

    for (int i=0; i<leds.size(); i++){
        leds[i].topFade = k;
        
        if (fade=='I'){
            leds[i].triggerFadeIn(type, step);
        }
        else if (fade == 'O') {
            leds[i].triggerFadeOut(step);
        }
    }
}

void Light::fadeUserPars(float k, char fade, int type, int step, int user){
    
    vector<int> usePars = parUserAssign[user];      //vector de pars de lusuari
    
    for (int i = usePars[0]; i<usePars.size(); i++){
        leds[i].topFade = k;
        
        if (fade=='I'){
            leds[i].triggerFadeIn(type, step);
        }
        else if (fade == 'O') {
            leds[i].triggerFadeOut(step);
        }
    }

}


void Light::randomPlay(bool state){

    for (int i=0; i<leds.size(); i++){
        leds[i].isRandom = state;
    }
}


