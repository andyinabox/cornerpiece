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
  gui.add(drawWireframe.setup("Draw wireframe", false));
  gui.add(useVideo.setup("Use video", true));

  gui.add(showCalibration.setup("Show calibration", false));

  // create default calibration points
  cPoints.push_back(ofVec2f(0, 0));
  cPoints.push_back(ofVec2f(1, 0));
  cPoints.push_back(ofVec2f(0.5, 0.5));
  cPoints.push_back(ofVec2f(0.5, 1));

  image.load("corner-1024.jpg");
  
  vid.load("videos/corner-1024.mov");
	vid.setLoopState(OF_LOOP_NORMAL);

  cam.setGlobalPosition(100, 100, 100);
  cam.lookAt(ofVec3f(0, 0, 0));
  cam.roll(180);

  manipulator.toggleTranslation();
  
  tri1.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  tri1.addVertex(ofPoint(0, 0, 0));
  tri1.addVertex(ofPoint(cornerScale, 0, 0));
  tri1.addVertex(ofPoint(0, cornerScale, 0));

  tri1.addIndex(0);
  tri1.addIndex(1);
  tri1.addIndex(2);

  tri2.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  tri2.addVertex(ofPoint(0, 0, 0));
  tri2.addVertex(ofPoint(0, 0, cornerScale));
  tri2.addVertex(ofPoint(0, cornerScale, 0));

  tri2.addIndex(0);
  tri2.addIndex(1);
  tri2.addIndex(2);
  
  tri3.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  tri3.addVertex(ofPoint(0, 0, 0));
  tri3.addVertex(ofPoint(0, 0, cornerScale));
  tri3.addVertex(ofPoint(cornerScale, 0, 0));

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
  tri1.addTexCoord(cPoints[2]);
  tri1.addTexCoord(cPoints[1]);
  tri1.addTexCoord(cPoints[3]);
  
  tri2.clearTexCoords();
  tri2.addTexCoord(cPoints[2]);
  tri2.addTexCoord(cPoints[0]);
  tri2.addTexCoord(cPoints[3]);
  
  tri3.clearTexCoords();
  tri3.addTexCoord(cPoints[2]);
  tri3.addTexCoord(cPoints[0]);
  tri3.addTexCoord(cPoints[1]);
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
    
      manipulator.draw(cam);

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
