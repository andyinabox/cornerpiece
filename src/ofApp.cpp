#include "ofApp.h"

#define CAL_IMG_SCALE 512
#define CAL_HANDLE_SIZE 7
#define CAL_POINT_GRAB_DIST 10
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
//	ofEnableDepthTest();
	
	// ofBox uses texture coordinates from 0-1, so you can load whatever
	// sized images you want and still use them to texture your box
	// but we have to explicitly normalize our tex coords here
	ofEnableNormalizedTexCoords();

  gui.setup("controls", "setting.xml", ofGetWidth() - 250, 0);
  gui.add(showGrid.setup("Show grid", false));
  gui.add(drawWireframe.setup("Draw wireframe", false));
  gui.add(useVideo.setup("Use video", true));

  
  gui.add(tri1Tx0s.setup("tri1Tx0s", 0.5, 0, 1));
  gui.add(tri1Tx0t.setup("tri1Tx0t", 0.5, 0, 1));
  gui.add(tri1Tx1s.setup("tri1Tx1s", 1, 0, 1));
  gui.add(tri1Tx1t.setup("tri1Tx1t", 0.2, 0, 1));
  gui.add(tri1Tx2s.setup("tri1Tx2s", 0, 0, 1));
  gui.add(tri1Tx2t.setup("tri1Tx2t", 0.2, 0, 1));
  
  gui.add(tri2Tx0s.setup("tri2Tx0s", 0.5, 0, 1));
  gui.add(tri2Tx0t.setup("tri2Tx0t", 0.5, 0, 1));
  gui.add(tri2Tx1s.setup("tri2Tx1s", 0, 0, 1));
  gui.add(tri2Tx1t.setup("tri2Tx1t", 1, 0, 1));
  gui.add(tri2Tx2s.setup("tri2Tx2s", 0, 0, 1));
  gui.add(tri2Tx2t.setup("tri2Tx2t", 0.2, 0, 1));
  
  gui.add(tri3Tx0s.setup("tri3Tx0s", 0.5, 0, 1));
  gui.add(tri3Tx0t.setup("tri3Tx0t", 0.5, 0, 1));
  gui.add(tri3Tx1s.setup("tri3Tx1s", 0.5, 0, 1));
  gui.add(tri3Tx1t.setup("tri3Tx1t", 1, 0, 1));
  gui.add(tri3Tx2s.setup("tri3Tx2s", 1, 0, 1));
  gui.add(tri3Tx2t.setup("tri3Tx2t", 0.2, 0, 1));

  gui.add(showCalibration.setup("Show calibration", false));

  // create default calibration points
  cPoints.push_back(ofVec2f(0, 0));
  cPoints.push_back(ofVec2f(1, 0));
  cPoints.push_back(ofVec2f(0.5, 0.5));
  cPoints.push_back(ofVec2f(0.5, 1));


  image.load("corner-1024.jpg");
  
  vid.load("videos/corner-1024.mov");
	vid.setLoopState(OF_LOOP_NORMAL);

  
  tri1.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  tri1.addVertex(ofPoint(0, 0, 0));
  tri1.addVertex(ofPoint(cornerScale, 0, 0));
  tri1.addVertex(ofPoint(0, -cornerScale, 0));

  tri1.addIndex(0);
  tri1.addIndex(1);
  tri1.addIndex(2);

  tri2.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  tri2.addVertex(ofPoint(0, 0, 0));
  tri2.addVertex(ofPoint(0, 0, cornerScale));
  tri2.addVertex(ofPoint(0, -cornerScale, 0));

  tri2.addIndex(0);
  tri2.addIndex(1);
  tri2.addIndex(2);
  
  tri3.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  tri3.addVertex(ofPoint(0, 0, 0));
  tri3.addVertex(ofPoint(cornerScale, 0, 0));
  tri3.addVertex(ofPoint(0, 0, cornerScale));

  tri3.addIndex(0);
  tri3.addIndex(1);
  tri3.addIndex(2);
  
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

  if(useVideo) {
    vid.update();
    tex = vid.getTexture();
  } else {
    tex = image.getTexture();
  }

  tri1.clearTexCoords();
  tri1.addTexCoord(ofVec2f(tri1Tx0s, tri1Tx0t));
  tri1.addTexCoord(ofVec2f(tri1Tx1s, tri1Tx1t));
  tri1.addTexCoord(ofVec2f(tri1Tx2s, tri1Tx2t));
  
  tri2.clearTexCoords();
  tri2.addTexCoord(ofVec2f(tri2Tx0s, tri2Tx0t));
  tri2.addTexCoord(ofVec2f(tri2Tx1s, tri2Tx1t));
  tri2.addTexCoord(ofVec2f(tri2Tx2s, tri2Tx2t));
  
  tri3.clearTexCoords();
  tri3.addTexCoord(ofVec2f(tri3Tx0s, tri3Tx0t));
  tri3.addTexCoord(ofVec2f(tri3Tx1s, tri3Tx1t));
  tri3.addTexCoord(ofVec2f(tri3Tx2s, tri3Tx2t));
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofClear(0);

  if(showCalibration) {
    ofDisableDepthTest();
    ofDisableLighting();
    
    ofPushMatrix();
      ofSetColor(255);
      tex.bind();
        cRect.draw();
      tex.unbind();
    
      for(ofVec2f p : cPoints) {
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
      if(showGrid) {
        ofDrawGrid(10);
      }
    
      if(drawWireframe) {
        tri1.drawWireframe();
        tri2.drawWireframe();
        tri3.drawWireframe();
      } else {
        tex.bind();
        tri1.draw();
        tri2.draw();
        tri3.draw();
        tex.unbind();
      }
    cam.end();
    ofDisableDepthTest();
  }


  if(showGui) {
    gui.draw();
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
    cPoints[cIndex].x = ofMap(x, 0, CAL_IMG_SCALE, 0, 1);
    cPoints[cIndex].y = ofMap(y, 0, CAL_IMG_SCALE, 0, 1);
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
