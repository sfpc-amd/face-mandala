#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetLogLevel(OF_LOG_VERBOSE);

    mouseIsDown = false;
    lissajousShader.load("shaders/lissajous");
}

//--------------------------------------------------------------
void ofApp::update(){
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    float mouseClick = mouseIsDown ? 1.0 : 0.0;
    
    lissajousShader.begin();
        lissajousShader.setUniform4f("iMouse", mouseX, mouseY, mouseClick, mouseClick);
        lissajousShader.setUniform3f("iResolution", ofGetWidth(), ofGetHeight(), 0.0); // not sure what third item is?
        lissajousShader.setUniform1f("iGlobalTime", ofGetElapsedTimef());
    
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    lissajousShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouseIsDown = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mouseIsDown = false;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
