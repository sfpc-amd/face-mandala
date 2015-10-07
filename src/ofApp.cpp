#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(30);
	ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetLogLevel(OF_LOG_VERBOSE);

    mouseIsDown = false;
    showHelp = true;
    showGui = true;
    
    // load our shader
    lissajousShader.load("shaders/lissajous");
    
    // setup gui
    
    gui.setup();
    gui.add(faceLabel.setup("Face Features", ""));
    gui.add(faceFound.setup("Face Found", false));
    gui.add(faceEyeLeft.setup("Left Eye", 0, 127, 0));
    gui.add(faceEyeRight.setup("Right Eye", 0, 127, 0));
    gui.add(faceEyebrowLeft.setup("Left Eyebrow", 0, 127, 0));
    gui.add(faceEyebrowRight.setup("Right Eyebrow", 0, 127, 0));
    gui.add(faceJaw.setup("Jaw", 0, 127, 0));
    gui.add(faceMouthHeight.setup("Mouth Height", 0, 127, 0));
    gui.add(faceMouthWidth.setup("Mouth Width", 0, 127, 0));
    gui.add(faceNostrils.setup("Nostrils", 0, 127, 0));
    gui.add(faceOrientationX.setup("Face Orientation X", 0, 127, 0));
    gui.add(faceOrientationY.setup("Face Orientation Y", 0, 127, 0));
    gui.add(faceOrientationZ.setup("Face Orientation Z", 0, 127, 0));
    gui.add(facePositionX.setup("Face Position X", 0, 127, 0));
    gui.add(facePositionY.setup("Face Position Y", 0, 127, 0));
    gui.add(faceScale.setup("Face Scale", 0, 127, 0));

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
    
    // GUI
    
    if(showGui) {
        gui.setPosition(0, 0);
        gui.draw();
    }
    
    if(showHelp) {
        ofDrawBitmapStringHighlight("h - toggle help / g - toggle GUI", 10, ofGetHeight() - 10);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 'h':
            showHelp = !showHelp;
            break;
        case 'g':
            showGui = !showGui;
            break;
    }
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
