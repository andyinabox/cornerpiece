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
  
  labels.load(labelsPath);
  
//  font.load("fonts/Helvetica.ttf", 30, true, true, true);

  cameraMovement.addListener(this, &ofApp::toggleCameraMovement);
  drawWireframe.addListener(this, &ofApp::toggleWireframe);
  showLabels.addListener(this, &ofApp::toggleLabels);


  gui.setup("controls", guiSettingsPath, ofGetWidth() - 250, 0);
  gui.add(drawWireframe.setup("Draw wireframe", false));
  gui.add(showCalibration.setup("Show calibration", false));
  gui.add(cameraMovement.setup("Enable camera movement", false));
  gui.add(showLabels.setup("Show labels", true));


  corner.setup(350);
  nextLabels();
  
  vid.load("videos/CornerAnimation1.mov");
	vid.setLoopState(OF_LOOP_NORMAL);
  vid.update();
  corner.setTexture(vid.getTexture());
  
  
  ofxLoadCamera(cam, camSettingsPath);
  
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
  
  loadSettings();
  
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
    
      for(int i = 0; i < points.size(); i++) {
      
        ofPushStyle();
          if(i == cIndex) {
            ofSetColor(0, 0, 255);
          }
        
          ofDrawEllipse(
            ofMap(points[i].x, 0, 1, 0, CAL_IMG_SCALE)
            , ofMap(points[i].y, 0, 1, 0, CAL_IMG_SCALE)
            , CAL_HANDLE_SIZE
            , CAL_HANDLE_SIZE
          );
        ofPopStyle();
      }
      string text = "Currently selected point no. " + ofToString(cIndex) + ". Use 0-3 on your keyboard to modify selected.";
      ofDrawBitmapStringHighlight(text, 0, CAL_IMG_SCALE+30);
    ofPopMatrix();
  } else {
    ofEnableDepthTest();
    cam.begin();
      corner.draw(cam);
    
//      font.drawStringAsShapes("Test", 10, 10);
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

void ofApp::toggleLabels(bool &value) {
  corner.toggleLabels(value);
}


void ofApp::nextLabels() {
  labelsIndex++;
  if(labelsIndex > labels.getNumRows()-1) {
    labelsIndex = 0;
  }
  
  ofxCsvRow row = labels.getRow(labelsIndex);
  corner.setLabels(row[0], row[1], row[2]);
}

void ofApp::resetCamera() {
  cam.setGlobalPosition(CAM_DISTANCE, CAM_DISTANCE, CAM_DISTANCE);
  cam.lookAt(corner);
  cam.roll(180);
}

void ofApp::resetCorner() {
  corner.reset();
}


void ofApp::saveSettings() {
  ofXml rootXml;
  
  rootXml.addChild("settings");
  rootXml.setTo("//settings");
  
  // save calibration
  ofXml calibrationXml;
  calibrationXml.addChild("calibration");
  calibrationXml.setTo("//calibration");
  vector<ofVec2f> calibrationPoints = corner.getCalibrationPoints();
  
  for(int i = 0; i < calibrationPoints.size(); i++) {
    ofXml point;
    point.addChild("point");
    point.setTo("//point");
    
    point.setAttribute("index", ofToString(i));
    point.setAttribute("x", ofToString(calibrationPoints[i].x));
    point.setAttribute("y", ofToString(calibrationPoints[i].y));

    calibrationXml.addXml(point);
  }
  
  rootXml.addXml(calibrationXml);
  
  // save corner orientation
  ofXml cornerXml;
  cornerXml.addChild("corner");
  cornerXml.setTo("//corner");
  cornerXml.addValue("transform", ofToString(corner.getGlobalTransformMatrix()));
  
  rootXml.addXml(cornerXml);
  
  // save camera orientation
  ofxSaveCamera(cam, camSettingsPath);

  rootXml.save(xmlSettingsPath);

}


void ofApp::loadSettings() {
  ofXml xml;
  
  if(xml.load(xmlSettingsPath)) {
  
    // load texture coordinate calibration
    if (xml.exists("//calibration")) {
      xml.setTo("//calibration");
      for(int i = 0; i < xml.getNumChildren(); i++) {
        xml.setToChild(i);
        map<string, string> attr = xml.getAttributes();
        corner.setCalibrationPoint(i, ofVec2f(ofToFloat(attr["x"]), ofToFloat(attr["y"])));
        xml.setToParent();
      }
    }
    
    xml.setTo("//settings");
    if(xml.exists("//corner/transform")) {
      string matStr = xml.getValue("//corner/transform");
      ofMatrix4x4 m;
      istringstream iss;
      iss.str(matStr);
      iss >> m;
      corner.setMatrix(m);
    
    }
    
  
  }

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
  
  if(key == 's') {
    ofLogNotice("'s' key") << "Savings settings";
    saveSettings();
  }
  
  
  if(key == 'o') {
    ofLogNotice("'o' key") << "Opening settings";
    loadSettings();
  }
  
  if(key == 'r') {
    ofLogNotice("'r' key") << "Reset settings";
    resetCamera();
    resetCorner();
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
      vid.setPaused(!vid.isPaused());
    } else {
      vid.play();
    }
  }
  
  if(key == 'l') {
    nextLabels();
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
//    saveSettings();
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
