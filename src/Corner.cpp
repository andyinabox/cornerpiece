//
//  Corner.cpp
//  cornerMapTest1
//
//  Created by Andrew Dayton on 4/25/16.
//
//

#include "Corner.h"

void Corner::setup(float s) {

  scale = s;

  setGlobalPosition(0, 0, 0);

  // load font
  textFont.load("fonts/Didot.ttf", scale/15);
//  textFont.load("fonts/Fanwood.otf", scale/12);
//  textFont.load("fonts/Raleway-Thin.otf", scale/15);
//  textFont.load("fonts/Lato-Hairline.ttf", scale/12);


  // create base triangle
  cornerMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  
  // right tri
  cornerMesh.addVertex(ofPoint(0, 0, 0));
  cornerMesh.addVertex(ofPoint(scale, 0, 0));
  cornerMesh.addVertex(ofPoint(0, scale, 0));

  // left tri
  cornerMesh.addVertex(ofPoint(0, 0, 0));
  cornerMesh.addVertex(ofPoint(0, 0, scale));
  cornerMesh.addVertex(ofPoint(0, scale, 0));
  
  // top tri
  cornerMesh.addVertex(ofPoint(0, 0, 0));
  cornerMesh.addVertex(ofPoint(0, 0, scale));
  cornerMesh.addVertex(ofPoint(scale, 0, 0));

  cornerMesh.addIndex(0);
  cornerMesh.addIndex(1);
  cornerMesh.addIndex(2);
  cornerMesh.addIndex(3);
  cornerMesh.addIndex(4);
  cornerMesh.addIndex(5);
  cornerMesh.addIndex(6);
  cornerMesh.addIndex(7);
  cornerMesh.addIndex(8);
  
  // default calibration
  vector<ofVec2f> c;
  c.push_back(ofVec2f(0, 0));
  c.push_back(ofVec2f(1, 0));
  c.push_back(ofVec2f(0.5, 0.5));
  c.push_back(ofVec2f(0.5, 1));
  setCalibrationPoints(c);
  
  // default labels
  cornerLabels.push_back("TOP");
  cornerLabels.push_back("RIGHT");
  cornerLabels.push_back("LEFT");
  
  manipulator.toggleRotation();
}


void Corner::draw(ofCamera cam) {
  
  // set the global transform matrix for this ofNode
  // from the manipulator
  setTransformMatrix(manipulator.getMatrix());
  getOrientationQuat().getRotate(rotationAngle, rotationVector);
  
  
  // seems kind of weird but it works!
  ofPushMatrix();
  
    // apply transform from this node
    ofTranslate(getPosition());
    ofRotate(rotationAngle, rotationVector.x, rotationVector.y, rotationVector.z);
    ofScale(getScale());
  
    if(bWireframe) {
      cornerMesh.drawWireframe();
    } else {
      texture.bind();
        ofSetColor(255);
        cornerMesh.draw();
      texture.unbind();
    }
  
    if(bLabels) {
      drawLabels();
    }
    
  ofPopMatrix();
  
  if(bWireframe) {
    manipulator.draw(cam);
  }

}

void Corner::drawLabels() {
  
  ofPushMatrix();
//    ofSetColor(255, 255, 255, 100);
  // draw text
    ofPushMatrix();
      ofTranslate(scale/2, scale/2, 0);
//      ofTranslate(scale/3, scale/2, 1);
      ofRotateZ(-45);
      textFont.drawStringCentered(ofToUpper(cornerLabels[0]), 0, 0);
    ofPopMatrix();
    
    ofPushMatrix();
      ofTranslate(0, scale/2, scale/2);
//      ofTranslate(1, scale/3, scale/2);
      ofRotateY(90);
      ofRotateZ(45);
      textFont.drawStringCentered(ofToUpper(cornerLabels[1]), 0, 0);
    ofPopMatrix();
    
    ofPushMatrix();
      ofTranslate(scale/2, 0, scale/2);
//      ofTranslate(scale/2, 1, scale/3);
        ofRotateX(-90);
        ofRotateZ(-135);
      textFont.drawStringCentered(ofToUpper(cornerLabels[2]), 0, 0);
    ofPopMatrix();
  ofPopMatrix();
}


void Corner::setTexture(ofTexture tex) {
  texture = tex;
}

void Corner::setCalibrationPoints(vector<ofVec2f> points) {
  calibration = points;
  updateTexCoords();
}

void Corner::setCalibrationPoint(int index, ofVec2f point) {
//  cout << "set calibration point " << index << endl;
  calibration[index] = point;
  updateTexCoords();
}

void Corner::setLabels(string top, string right, string left) {
  cornerLabels[0] = left;
  cornerLabels[1] = right;
  cornerLabels[2] = top;
}

vector<ofVec2f> Corner::getCalibrationPoints() {
  return calibration;
}

ofMatrix4x4 Corner::getMatrix() {
  return manipulator.getMatrix();
}

void Corner::setMatrix(ofMatrix4x4 m) {
  ofVec3f translation;
  ofQuaternion rotation;
  ofVec3f scale;
  ofQuaternion so;
  
  m.decompose(translation, rotation, scale, so);
  
  // apply to manipulator
  manipulator.setTranslation(translation);
  manipulator.setRotation(rotation);
  manipulator.setScale(scale);
  
  // set ofNode matrix
  setTransformMatrix(m);
}

void Corner::toggleWireframe(bool b) {
  bWireframe = b;
}

void Corner::toggleLabels(bool b) {
  bLabels = b;
}



void Corner::updateTexCoords() {

  cornerMesh.clearTexCoords();

  // right tri
  cornerMesh.addTexCoord(calibration[2]);
  cornerMesh.addTexCoord(calibration[1]);
  cornerMesh.addTexCoord(calibration[3]);
  
  // left tri
  cornerMesh.addTexCoord(calibration[2]);
  cornerMesh.addTexCoord(calibration[0]);
  cornerMesh.addTexCoord(calibration[3]);
  
  // bottom tri
  cornerMesh.addTexCoord(calibration[2]);
  cornerMesh.addTexCoord(calibration[0]);
  cornerMesh.addTexCoord(calibration[1]);
}