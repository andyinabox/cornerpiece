#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	ofEnableDepthTest();
	
	// ofBox uses texture coordinates from 0-1, so you can load whatever
	// sized images you want and still use them to texture your box
	// but we have to explicitly normalize our tex coords here
	ofEnableNormalizedTexCoords();

  ofEnableArbTex();

  gui.setup();
  gui.add(showGrid.setup("Show grid", true));
  gui.add(drawWireframe.setup("Draw wireframe", false));
//  gui.add(cornerScale.setup("Corner scale", 100, 0, 1000));

  image.load("corner-1024.jpg");
//  imageTexture.allocate(image.getPixels(), true);
//  ofLoadImage(imageTexture, "corner-1024.jpg");
  
  corner.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  
  corner.addVertex(ofPoint(0, 0, 0));
  corner.addVertex(ofPoint(cornerScale, 0, 0));
  corner.addVertex(ofPoint(cornerScale, -cornerScale, 0));
  corner.addVertex(ofPoint(0, -cornerScale, 0));
  
  corner.addVertex(ofPoint(0, 0, 0));
  corner.addVertex(ofPoint(0, 0, cornerScale));
  corner.addVertex(ofPoint(0, -cornerScale, cornerScale));
  corner.addVertex(ofPoint(0, -cornerScale, 0));

  corner.addVertex(ofPoint(0, 0, 0));
  corner.addVertex(ofPoint(cornerScale, 0, 0));
  corner.addVertex(ofPoint(cornerScale, 0, cornerScale));
  corner.addVertex(ofPoint(0, 0, cornerScale));

  corner.addVertex(ofPoint(0, 0, 0));


  corner.addIndex(5);
  corner.addIndex(1);
  corner.addIndex(3);
  corner.addIndex(6);
//  corner.addIndex(0);

  corner.addTexCoord(ofVec2f(0,0));
  corner.addTexCoord(ofVec2f(0, 1));
  corner.addTexCoord(ofVec2f(1, 1));
  corner.addTexCoord(ofVec2f(1, 0));
//  corner.addTexCoord(ofVec2f(0.5, 0.5));
  
//  rect.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
//  rect.addVertex(ofPoint(0, 0, 0));
//  rect.addVertex(ofPoint(cornerScale, 0, 0));
//  rect.addVertex(ofPoint(cornerScale, -cornerScale, 0));
//  rect.addVertex(ofPoint(0, -cornerScale, 0));
//  rect.addVertex(ofPoint(0, 0, 0));
//  
//  
//  rect.addIndex(0);
//  rect.addIndex(1);
//  rect.addIndex(2);
//  rect.addIndex(3);
//
//  rect.addTexCoord(ofVec2f(0, 1));
//  rect.addTexCoord(ofVec2f(1, 1));
//  rect.addTexCoord(ofVec2f(1, 0));
//  rect.addTexCoord(ofVec2f(0, 0));
//  
//  points[0].x = 100;
//  points[0].y = 100;
//  points[1].x = 600;
//  points[1].y = 100;
//  points[2].x = 600;
//  points[2].y = 600;
//  points[3].x = 100;
//  points[3].y = 600;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
//  ofClear(0);

//  imageTexture.draw(points[0], points[1], points[2], points[3]);

  cam.begin();
  

    if(showGrid) {
      ofDrawGrid(10);
    }
    image.getTexture().bind();
  
      if(drawWireframe) {
        corner.drawWireframe();
//        rect.drawWireframe();
      } else {
        corner.draw();
//        rect.draw();
      }
    image.getTexture().unbind();
  cam.end();
  
  ofDisableDepthTest();
  
//  ofDisableLighting();
  gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//  if(key == '1') {
//    cornerIndex = 0;
//  }
//  if(key == '2') {
//    cornerIndex = 1;
//  }
//  if(key == '3') {
//    cornerIndex = 2;
//  }
//  if(key == '4') {
//    cornerIndex = 3;
//  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
//  points[cornerIndex].x = x;
//  points[cornerIndex].y = y;
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
