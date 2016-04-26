//
//  Corner.cpp
//  cornerMapTest1
//
//  Created by Andrew Dayton on 4/25/16.
//
//

#include "Corner.h"

void Corner::setup(float scale) {

  scale = scale;

  setGlobalPosition(0, 0, 0);

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
    
  ofPopMatrix();
  
  if(bWireframe) {
    manipulator.draw(cam);
  }

}

void Corner::setTexture(ofTexture tex) {
  texture = tex;
}

void Corner::setCalibrationPoints(vector<ofVec2f> points) {
  calibration = points;
  updateTexCoords();
}

void Corner::setCalibrationPoint(int index, ofVec2f point) {
  calibration[index] = point;
}

vector<ofVec2f> Corner::getCalibrationPoints() {
  return calibration;
}

void Corner::toggleWireframe(bool b) {
  bWireframe = b;
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