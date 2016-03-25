#pragma once

#include "ofMain.h"
#include "Light.h"
#include "User.h"

class ofApp : public ofBaseApp{

public:
    
    
    
        ofSerial serial;
        Light llum;
        vector<User> users;
        int maxPars; //maxim nombre de pars per usuari, hauria de ser accessible per tothom!
        ofSoundPlayer background;
    
    
		void setup();
		void update();
		void draw();

		//void keyPressed(int key);
		//void keyReleased(int key);
		//void mouseMoved(int x, int y );
		//void mouseDragged(int x, int y, int button);
		//void mousePressed(int x, int y, int button);
		//void mouseReleased(int x, int y, int button);
		//void mouseEntered(int x, int y);
		//void mouseExited(int x, int y);
		//void windowResized(int w, int h);
		//void dragEvent(ofDragInfo dragInfo);
		//void gotMessage(ofMessage msg);
    
    

		
};
