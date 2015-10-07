#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(30);
	ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetLogLevel(OF_LOG_VERBOSE);

    mouseIsDown = false;
    
    // load our shader
    lissajousShader.load("shaders/lissajous");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // convert mouseIsDown to float value
    float mouseClick = mouseIsDown ? 1.0 : 0.0;
    
    // set uniforms for lissajous shader
    lissajousShader.begin();
        // mouse position and click state
        lissajousShader.setUniform4f("iMouse", mouseX, mouseY, mouseClick, mouseClick);
        // screen resolution
        lissajousShader.setUniform3f("iResolution", ofGetWidth(), ofGetHeight(), 0.0); // not sure what third item is?
        // elapsed time
        lissajousShader.setUniform1f("iGlobalTime", ofGetElapsedTimef());
    lissajousShader.end();


}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    // draw lissajous shader
    lissajousShader.begin();
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
