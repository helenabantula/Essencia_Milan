//
//  Light.h
//  Corasonsitu
//
//  Created by Helena Bantulà i Fonts on 17/11/15.
//
//

#ifndef __Corasonsitu__light__
#define __Corasonsitu__light__

#include <iostream>
#include "ofxArtnet.h"
#include "Par.h"



class Light{
    
public:
    
    
    static Light &getInstance()
    {
        static Light instance;
        return instance;
    
    }
    
    ofxArtnet artnet;
    vector<Par> leds;
    vector<unsigned char> packDMX;
    //unsigned char packDMX[48];
    //unsigned char old_packDMX[15];
    
    uint8_t dmx[3];
    int maxPar = 16;
    int numUsers;
    int parXuser;
    
    vector<vector<int>> parUserAssign;
  
    
    void initialize(int numUsers);
    void getInfo();
    void sendInfo();
    void equalFade(float k, char fade, int type, int step); //tots els pars
    void fadeUserPars(float k, char fade, int type, int step, int user);    // fade of the current user pars (only 1 user allowed)
    void fadeUnusedPars(float k, char fade, int type, int step, int users); // fade of the non-used pars only by knowing the current users
    void randomPlay(bool state);
    

    

    


};

#endif /* defined(__Corasonsitu__light__) */