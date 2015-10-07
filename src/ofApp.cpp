#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetLogLevel(OF_LOG_VERBOSE);

    mouseIsDown = false;
    showHelp = true;
    showGui = true;
    
//     load our shader
    baseShader.load("shaders/base");
    
	cam.initGrabber(640, 480);
	tracker.setup();
    
    ofApp::setupGui();
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    
	if(cam.isFrameNew()) {
		tracker.update(ofxCv::toCv(cam));
        if(!manualControl) {
            ofApp::updateFromTracker();
        }
	}
    
    baseShader.begin();
        baseShader.setUniform4f(
            "iMouse"
            , ofMap(facePositionX, 0, FACE_CAM_WIDTH, 0, ofGetWidth())
            , ofMap(facePositionY, 0, FACE_CAM_HEIGHT, 0, ofGetHeight())
            , (mouseIsDown ? 1.0 : 0.0)
            , 0.0
        );
        baseShader.setUniform3f(
            "iResolution"
            , ofGetWidth()
            , ofGetHeight()
            , 0.0
        );        // elapsed time
        baseShader.setUniform1f(
            "iGlobalTime"
            , ofGetElapsedTimef()
        );
        baseShader.setUniform1f(
            "faceEyeLeft"
            , ofMap(faceEyeLeft, 2.0, 3.0, 0.0, 1.0, true)
        );
        baseShader.setUniform1f(
            "faceEyeRight"
            , ofMap(faceEyeRight, 2.0, 3.0, 0.0, 1.0, true)
        );
        baseShader.setUniform1f(
            "faceEyebrowLeft"
            , ofMap(faceEyebrowLeft, 7.0, 9.0, 0.0, 1.0, true)
        );
        baseShader.setUniform1f(
            "faceEyebrowRight"
            , ofMap(faceEyebrowRight, 7.0, 9.0, 0.0, 1.0, true)
        );
    baseShader.end();

    ofVec3f euler = ofVec3f(
        faceOrientationX
        , faceOrientationY
        , faceOrientationZ
    );
    orientationMatrix.makeRotationMatrix(
        ofRadToDeg(euler.x)
        , ofVec3f(1,0,0)
        , ofRadToDeg(euler.y)
        , ofVec3f(0,1,0)
        , ofRadToDeg(euler.z)
        , ofVec3f(0,0,1)
    );
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);

    float xorig = 0;
    float yorig = 0;
    float angle = ofGetElapsedTimef();
	float radius = ofGetHeight()/2;
    float x = xorig + radius * cos(angle * 3.4);
	float y = yorig + radius * -sin(angle * 4.7);
    
	ofPoint temp;
	temp.x = x;
	temp.y = y;
	points.push_back(temp);
	if (points.size() > 400){
		points.erase(points.begin());
	}
    
    baseShader.begin();
    ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofxCv::applyMatrix(orientationMatrix);
        ofScale(0.15*faceScale, 0.15*faceScale);

        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(255,0,127);
        ofFill();
        ofCircle(x,y,10);
        
        ofSetColor(255,255,255);
    
        ofNoFill();
        ofBeginShape();
        for (int i = 0; i < points.size(); i++){
            ofCurveVertex(points[i].x, points[i].y);
        }
        ofEndShape();
    ofPopMatrix();
    baseShader.end();
    
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
void ofApp::updateFromTracker() {

	ofVec2f position;
	ofVec3f orientation;
	ofMatrix4x4 rotationMatrix;

    faceFound = tracker.getFound();
    faceNostrils = tracker.getGesture(ofxFaceTracker::NOSTRIL_FLARE);
    faceJaw = tracker.getGesture(ofxFaceTracker::JAW_OPENNESS);
    faceEyeRight = tracker.getGesture(ofxFaceTracker::RIGHT_EYE_OPENNESS);
    faceEyeLeft = tracker.getGesture(ofxFaceTracker::LEFT_EYE_OPENNESS);
    faceEyebrowRight = tracker.getGesture(ofxFaceTracker::RIGHT_EYEBROW_HEIGHT);
    faceEyebrowLeft = tracker.getGesture(ofxFaceTracker::LEFT_EYEBROW_HEIGHT);
    faceMouthHeight = tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT);
    faceMouthWidth = tracker.getGesture(ofxFaceTracker::MOUTH_WIDTH);
    
    orientation = tracker.getOrientation();
    position = tracker.getPosition();

    faceOrientationX = orientation.x;
    faceOrientationY = orientation.y;
    faceOrientationZ = orientation.z;
    
    facePositionX = position.x;
    facePositionY = position.y;
    
    faceScale = tracker.getScale();
}


void ofApp::setupGui() {
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
    gui.add(facePositionX.setup("Face Position X", 0.0, 0.0,FACE_CAM_WIDTH));
    gui.add(facePositionY.setup("Face Position Y", 0.0, 0.0, FACE_CAM_HEIGHT));
    gui.add(faceScale.setup("Face Scale", 3.0, 0.0, 15.0));
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
