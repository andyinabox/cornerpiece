#include "ofApp.h"

#define CAL_IMG_SCALE 512
#define CAL_HANDLE_SIZE 7
#define CAL_POINT_GRAB_DIST 10
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
  ofSetFrameRate(30);
	
  // is this actually what I want?
	ofEnableNormalizedTexCoords();

  cameraMovement.addListener(this, &ofApp::toggleCameraMovement);
  drawWireframe.addListener(this, &ofApp::toggleWireframe);

  gui.setup("controls", "setting.xml", ofGetWidth() - 250, 0);
  gui.add(drawWireframe.setup("Draw wireframe", false));
  gui.add(showCalibration.setup("Show calibration", false));
  gui.add(cameraMovement.setup("Enable camera movement", true));

  corner.setup(100);
  
  vid.load("videos/corner-1024.mov");
	vid.setLoopState(OF_LOOP_NORMAL);
  vid.update();
  corner.setTexture(vid.getTexture());
  
  cam.setGlobalPosition(115, 115, 115);
  cam.lookAt(corner);
  cam.roll(180);
  
  cRect.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  cRect.addVertex(ofPoint(0, 0, 0));
  cRect.addVertex(ofPoint(CAL_IMG_SCALE, 0, 0));
  cRect.addVertex(ofPoint(CAL_IMG_SCALE, CAL_IMG_SCALE, 0));
  cRect.addVertex(ofPoint(0, CAL_IMG_SCALE, 0));
  
  cRect.addIndex(0);
  cRect.addIndex(1);
  cRect.addIndex(2);
  cRect.addIndex(3);

  cRect.addTexCoord(ofVec2f(0, 0));
  cRect.addTexCoord(ofVec2f(1, 0));
  cRect.addTexCoord(ofVec2f(1, 1));
  cRect.addTexCoord(ofVec2f(0, 1));
  
}

//--------------------------------------------------------------
void ofApp::update(){

//  if(vid.isFrameNew()) {
    vid.update();
    corner.setTexture(vid.getTexture());
//  }

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofClear(0);

  if(showCalibration) {
    ofDisableDepthTest();
    ofDisableLighting();
    
    ofPushMatrix();
      ofSetColor(255);
      vid.getTexture().bind();
        cRect.draw();
      vid.getTexture().unbind();
    
    vector<ofVec2f> points = corner.getCalibrationPoints();
    
      for(ofVec2f p : points) {
        ofDrawEllipse(
          ofMap(p.x, 0, 1, 0, CAL_IMG_SCALE)
          , ofMap(p.y, 0, 1, 0, CAL_IMG_SCALE)
          , CAL_HANDLE_SIZE
          , CAL_HANDLE_SIZE
        );
      }
    
    ofPopMatrix();
  } else {
    ofEnableDepthTest();
    cam.begin();
      corner.draw(cam);
    cam.end();
    
    ofDisableDepthTest();
  }



  if(showGui) {
    gui.draw();
  }

}

void ofApp::toggleCameraMovement(bool &value) {
  if(value) {
    cam.enableMouseInput();
  } else {
    cam.disableMouseInput();
  }
}

void ofApp::toggleWireframe(bool &value) {
  corner.toggleWireframe(value);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == 'g') {
    showGui = !showGui;
  }
  
  if(key == 'f') {
    ofToggleFullscreen();
  }
  
  if(key == 'w') {
    drawWireframe = !drawWireframe;
  }
  
  
  if(key == '0') {
    cIndex = 0;
  }
  
  if(key == '1') {
    cIndex = 1;
  }

  if(key == '2') {
    cIndex = 2;
  }
  
  if(key == '3') {
    cIndex = 3;
  }
  
  if(key == ' ') {
    if(vid.isPlaying()) {
      vid.stop();
    } else if (vid.isInitialized()) {
      vid.play();
    }
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
  if(showCalibration) {
    corner.setCalibrationPoint(cIndex, ofVec2f(
      ofMap(x, 0, CAL_IMG_SCALE, 0, 1)
      , ofMap(y, 0, CAL_IMG_SCALE, 0, 1)
    ));
  }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
