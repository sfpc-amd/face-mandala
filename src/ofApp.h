#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

	public:
    
        // flags
        bool mouseIsDown;
        bool showGui;
        bool showHelp;
    
        // shaders
        ofxAutoReloadedShader lissajousShader;
    
        // gui
        ofxPanel gui;
    
        // face features
        ofxLabel faceLabel;
    
        ofxToggle faceFound;
    
        ofxIntSlider faceEyeLeft;
        ofxIntSlider faceEyeRight;
        ofxIntSlider faceEyebrowLeft;
        ofxIntSlider faceEyebrowRight;
        ofxIntSlider faceJaw;
        ofxIntSlider faceMouthHeight;
        ofxIntSlider faceMouthWidth;
        ofxIntSlider faceNostrils;
    
        ofxIntSlider faceOrientationX;
        ofxIntSlider faceOrientationY;
        ofxIntSlider faceOrientationZ;

        ofxIntSlider facePositionX;
        ofxIntSlider facePositionY;
    
        ofxIntSlider faceScale;

    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
