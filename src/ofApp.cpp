#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetLogLevel(OF_LOG_VERBOSE);

    lissajousShader.load("shaders/lissajous");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    lissajousShader.begin();
        lissajousShader.setUniform2f("iMouse", mouseX, mouseY);
        lissajousShader.setUniform2f("iResolution", ofGetWidth(), ofGetHeight());
        lissajousShader.setUniform1f("iGlobalTime", ofGetElapsedTimef());
    lissajousShader.end();

}

//--------------------------------------------------------------
void ofApp::draw(){
//    lissajousShader.draw();
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
