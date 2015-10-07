#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"


#define PORT 8338
#define FACE_CAM_WIDTH 600
#define FACE_CAM_HEIGHT 400

class ofApp : public ofBaseApp{

	public:
    
        // flags
        bool mouseIsDown;
        bool showGui;
        bool showHelp;
    
		vector < ofPoint > points;
        ofMatrix4x4 orientationMatrix;
    
        // face tracker
        ofVideoGrabber cam;
        ofxFaceTracker tracker;
    
        // shaders
        ofxAutoReloadedShader lissajousShader;
        ofxAutoReloadedShader baseShader;
    
        // osc
        ofxOscReceiver receiver;
    
        // gui
        ofxPanel gui;
    
        // manual mode
        ofxToggle manualControl;
    
        // face features
        ofxLabel faceLabel;
    
        ofxToggle faceFound;
    
        ofxFloatSlider faceEyeLeft;
        ofxFloatSlider faceEyeRight;
        ofxFloatSlider faceEyebrowLeft;
        ofxFloatSlider faceEyebrowRight;
        ofxFloatSlider faceJaw;
        ofxFloatSlider faceMouthHeight;
        ofxFloatSlider faceMouthWidth;
        ofxFloatSlider faceNostrils;
    
        ofxFloatSlider faceOrientationX;
        ofxFloatSlider faceOrientationY;
        ofxFloatSlider faceOrientationZ;

        ofxFloatSlider facePositionX;
        ofxFloatSlider facePositionY;
    
        ofxFloatSlider faceScale;

    
		void setup();
		void update();
		void draw();
    
        void receiveOsc();
        void updateFromTracker();
        void setupGui();

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
