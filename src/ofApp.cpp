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
//    lissajousShader.load("shaders/lissajous");
    
    // setup osc
    cout << "listening for messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    // setup gui
    gui.setup();
    gui.add(manualControl.setup("Manual Control", false));
    gui.add(faceLabel.setup("Face Features", ""));
    gui.add(faceFound.setup("Face Found", false));
    gui.add(faceEyeLeft.setup("Left Eye", 0.0, 0.0, 10.0));
    gui.add(faceEyeRight.setup("Right Eye", 0.0, 0.0, 10.0));
    gui.add(faceEyebrowLeft.setup("Left Eyebrow", 0.0, 0.0, 15.0));
    gui.add(faceEyebrowRight.setup("Right Eyebrow", 0.0, 0.0, 15.0));
    gui.add(faceJaw.setup("Jaw", 0.0, 0.0, 50.0));
    gui.add(faceMouthHeight.setup("Mouth Height", 0.0, 0.0, 10.0));
    gui.add(faceMouthWidth.setup("Mouth Width", 0.0, 0.0, 20.0));
    gui.add(faceNostrils.setup("Nostrils", 0.0, 0.0, 10.0));
    gui.add(faceOrientationX.setup("Face Orientation X", 0.0, -1.0, 1.0));
    gui.add(faceOrientationY.setup("Face Orientation Y", 0.0, -1.0, 1.0));
    gui.add(faceOrientationZ.setup("Face Orientation Z", 0.0, -1.0, 1.0));
    gui.add(facePositionX.setup("Face Position X", 0.0, ofGetWidth(), 0.0));
    gui.add(facePositionY.setup("Face Position Y", 0.0, ofGetHeight(), 0.0));
    gui.add(faceScale.setup("Face Scale", 0.0, 0.0, 15.0));

}

//--------------------------------------------------------------
void ofApp::update(){
    
    // convert mouseIsDown to float value
//    float mouseClick = mouseIsDown ? 1.0 : 0.0;
    
    // set uniforms for lissajous shader
//    lissajousShader.begin();
//        // mouse position and click state
//        lissajousShader.setUniform4f("iMouse", mouseX, mouseY, mouseClick, mouseClick);
//        // screen resolution
//        lissajousShader.setUniform3f("iResolution", ofGetWidth(), ofGetHeight(), 0.0); // not sure what third item is?
//        // elapsed time
//        lissajousShader.setUniform1f("iGlobalTime", ofGetElapsedTimef());
//    lissajousShader.end();

    if(!manualControl) {
        ofApp::receiveOsc();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    // draw lissajous shader
//    lissajousShader.begin();
//        ofRect(0, 0, ofGetWidth(), ofGetHeight());
//    lissajousShader.end();
    
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
void ofApp::receiveOsc() {
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        string a = m.getAddress();
        
//        if(m.getArgTypeName(0) == "float" ) {
//            cout << m.getAddress() << ": " << m.getArgAsFloat(0) << "\n";
//        }

        if(a == "/found") {
            faceFound = (m.getArgAsInt32(0) > 0) ? true : false;
        } else if(a == "/gesture/nostrils") {
            faceNostrils = m.getArgAsFloat(0);
        } else if(a == "/gesture/jaw") {
            faceJaw = m.getArgAsFloat(0);
        } else if(a == "/gesture/eye/right") {
            faceEyeRight = m.getArgAsFloat(0);
        } else if(a == "/gesture/eye/left") {
            faceEyeLeft = m.getArgAsFloat(0);
        } else if(a == "/gesture/eyebrow/right") {
            faceEyebrowRight = m.getArgAsFloat(0);
        } else if(a == "/gesture/eyebrow/left") {
            faceEyebrowLeft = m.getArgAsFloat(0);
        } else if(a == "/gesture/mouth/height") {
            faceMouthHeight = m.getArgAsFloat(0);
        } else if(a == "/gesture/mouth/width") {
            faceMouthWidth = m.getArgAsFloat(0);
        } else if(a == "/pose/orientation") {
            faceOrientationX = m.getArgAsFloat(0);
            faceOrientationY = m.getArgAsFloat(1);
            faceOrientationZ = m.getArgAsFloat(2);
        } else if(a == "/pose/position") {
            facePositionX = m.getArgAsFloat(0);
            facePositionY = m.getArgAsFloat(1);
        } else if(a == "/pose/scale") {
            faceScale = m.getArgAsFloat(0);
        }
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
