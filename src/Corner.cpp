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
  textFont.load("fonts/HWYGOTH.TTF", scale/10, true, true, true);


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
  vector<string> l;
  l.push_back("LEFT");
  l.push_back("RIGHT");
  l.push_back("TOP");
  setLabels(l);
  
  manipulator.toggleRotation();
}


void Corner::draw(ofCamera cam) {
  
  manipulator.getRotation().getRotate(rotationAngle, rotationVector);
  
  ofPushMatrix();
  
    ofTranslate(manipulator.getTranslation());
    ofRotate(rotationAngle, rotationVector.x, rotationVector.y, rotationVector.z);
  
    if(bWireframe) {
      cornerMesh.drawWireframe();
    } else {
      texture.bind();
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
      
  // draw text
  ofPushMatrix();
    ofTranslate(scale/2, scale/2, 0);
    ofRotateZ(-45);
    textFont.drawStringCentered(cornerLabels[0], 0, 0);
  ofPopMatrix();
  
  ofPushMatrix();
    ofTranslate(0, scale/2, scale/2);
    ofRotateY(90);
    ofRotateZ(45);
    textFont.drawStringCentered(cornerLabels[1], 0, 0);
  ofPopMatrix();
  
  ofPushMatrix();
    ofTranslate(scale/2, 0, scale/2);
      ofRotateX(-90);
      ofRotateZ(-135);
    textFont.drawStringCentered(cornerLabels[2], 0, 0);
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

void Corner::setLabels(vector<string> labels) {
  cornerLabels = labels;
}

vector<ofVec2f> Corner::getCalibrationPoints() {
  return calibration;
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