//
//  light.cpp
//  Corasonsitu
//
//  Created by Helena Bantulà i Fonts on 17/11/15.
//
//

#include "Light.h"


void Light::initialize(int numUsersIni){
#if TARGET_RASPBERRY_PI
    artnet.setup("192.168.1.110"); //IP de rPi
#else
    artnet.setup("192.168.1.110"); //IP ordinador
#endif    
    //// Temporary Par ///
    ofColor  color(255,0,65);
    //color = (255,0,65); // per tots igual
    
    
    for (int i = 0; i < maxPar; i++){
        Par temPar(color,i);
        leds.push_back(temPar);
    }
    
    numUsers = numUsersIni;
    parXuser = maxPar/numUsers;
    
    vector<vector<int>> tempMatrix(numUsers, vector<int>(parXuser));
    parUserAssign = tempMatrix;
    
    vector<bool> tempCurrentUsers(numUsers);
    currentUsers = tempCurrentUsers;

    vector<unsigned char> tempPackDMX(maxPar*3);
    packDMX = tempPackDMX;
    
    sendInfo();
    
    for (int i = 0; i < numUsers; i++){
        for (int j = 0; j < (parXuser); j++){
            parUserAssign[i][j] = i*(parXuser) +j;
        }
        
    }
}


void Light::assignPars(){
    
    parXuser = maxPar/numCurrentUsers;
    
    vector<vector<int>> tempMatrix(numCurrentUsers, vector<int>(parXuser));
    parUserAssign = tempMatrix;

    
    for (int i = 0; i < numCurrentUsers; i++){
        for (int j = 0; j < (parXuser); j++){
            parUserAssign[i][j] = i*(parXuser) +j;
        }
        
    }


}


void Light::getInfo(){
    
    int j=0;
    for (int i = 0; i < leds.size(); i++){
        leds[i].update();
        
        packDMX[j] = leds[i].getColor().r;
        packDMX[j+1] = leds[i].getColor().g;
        packDMX[j+2] = leds[i].getColor().b;
        j=j+3;
        //cout<<maxPar<<endl;
    }
    
    this->sendInfo();
}


void Light::sendInfo(){
    
    artnet.sendDmx("192.168.1.150",&packDMX[0], packDMX.size());
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
    
    
//    if (numCurrentUsers == 1) {
//        user = 0;
//    }
    
    vector<int> usePars = parUserAssign[user];      //vector de pars de lusuari, si parUserAssign és fixe!
    
    
    for (int i = 0; i < usePars.size(); i++){
        leds[i].topFade = k;
        
        if (fade=='I'){
            leds[usePars[i]].triggerFadeIn(type, step);
        }
        else if (fade == 'O') {
            leds[usePars[i]].triggerFadeOut(step);
        }
    }
    
}


void Light::fadeUnusedPars(float k, char fade, int type, int step, int users){
    
    
    vector<int> noUsers(numUsers - 1);                      // non-user indexs
    vector<int> unusedPars(noUsers.size()*(parXuser));      // non-used pars
    //vector<int> unusedPars;
    int j = 0;
    
    for (int i = 0; i < numUsers; i++){
            if (i != users) {
                noUsers[j] = i;
                j++;
            }
    }
    
    int z = 0;
    for (int i = 0; i < noUsers.size(); i++) {
        for (int j = 0; j < parXuser; j++){
            unusedPars[z] = parUserAssign[noUsers[i]][j];
            z ++;
        }
    }

    
    for (int i = 0; i < unusedPars.size(); i++){
        leds[unusedPars[i]].topFade = k;
        
        if (fade == 'I'){
            leds[unusedPars[i]].triggerFadeIn(type, step);
        }
        else if (fade == 'O') {
            leds[unusedPars[i]].triggerFadeOut(step);
        }
    }


}

void Light::randomPlay(bool state){

    for (int i=0; i<leds.size(); i++){
        leds[i].isRandom = state;
    }
}



void Light::openUser(int userID){
    
    currentUsers[userID] = true;
    //fadeUnusedPars(1, 'O', 1, 2000, userID);        //tots els usuaris que estiguin funcionant
    
    numCurrentUsers = 0;
    for (int i = 0; i < currentUsers.size(); i++){
        if (currentUsers[i])
            numCurrentUsers ++;
    }
    
    //assignPars();
}

void Light::closeUser(int userID){
    
    currentUsers[userID] = false;
    
    for (int i = 0; i < currentUsers.size(); i++){
        if (currentUsers[i])
            numCurrentUsers --;
    }
    
    //assignPars();
    
}


bool Light::isUserOpened(int userID){
    
    if (currentUsers[userID])
        return true;
    else
        return false;
}


void Light::setParState(float k, int user){
    
    vector<int> usePars = parUserAssign[user];      //vector de pars de lusuari, si parUserAssign és fixe!
    
    
    for (int i = 0; i < usePars.size(); i++){
        leds[i].color = k;

    }


}


