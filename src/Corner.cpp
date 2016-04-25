//
//  Corner.cpp
//  cornerMapTest1
//
//  Created by Andrew Dayton on 4/25/16.
//
//

#include "Corner.h"

#define CORNER_SCALE 100

void Corner::setup() {

  setGlobalPosition(0, 0, 0);

  // create base triangle
  cornerMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  
  // right tri
  cornerMesh.addVertex(ofPoint(0, 0, 0));
  cornerMesh.addVertex(ofPoint(CORNER_SCALE, 0, 0));
  cornerMesh.addVertex(ofPoint(0, CORNER_SCALE, 0));

  // left tri
  cornerMesh.addVertex(ofPoint(0, 0, 0));
  cornerMesh.addVertex(ofPoint(0, 0, CORNER_SCALE));
  cornerMesh.addVertex(ofPoint(0, CORNER_SCALE, 0));
  
  // top tri
  cornerMesh.addVertex(ofPoint(0, 0, 0));
  cornerMesh.addVertex(ofPoint(0, 0, CORNER_SCALE));
  cornerMesh.addVertex(ofPoint(CORNER_SCALE, 0, 0));

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
  setCalibrationPoints(ofVec2f(0, 0), ofVec2f(1, 0), ofVec2f(0.5, 0.5), ofVec2f(0.5, 1));
  
  manipulator.toggleRotation();
}


void Corner::draw(ofCamera cam) {
  
  manipulator.getRotation().getRotate(rotationAngle, rotationVector);
  
  ofPushMatrix();
  
    ofTranslate(manipulator.getTranslation());
    ofRotate(rotationAngle, rotationVector.x, rotationVector.y, rotationVector.z);
  
  if(calibrationMode) {
    cornerMesh.drawWireframe();
  } else {
    texture.bind();
      cornerMesh.draw();
    texture.unbind();
  }
  
  ofPopMatrix();
  
  manipulator.draw(cam);

}

void Corner::setTexture(ofTexture tex) {
  texture = tex;
}

void Corner::setCalibrationPoints(ofVec2f topLeft, ofVec2f topRight, ofVec2f middle, ofVec2f bottom) {

  calibration.topLeft = topLeft;
  calibration.topRight = topRight;
  calibration.middle = middle;
  calibration.bottom = bottom;

  cornerMesh.clearTexCoords();
  
  // right tri
  cornerMesh.addTexCoord(calibration.middle);
  cornerMesh.addTexCoord(calibration.topRight);
  cornerMesh.addTexCoord(calibration.bottom);
  
  // left tri
  cornerMesh.addTexCoord(calibration.middle);
  cornerMesh.addTexCoord(calibration.topLeft);
  cornerMesh.addTexCoord(calibration.bottom);
  
  // bottom tri
  cornerMesh.addTexCoord(calibration.middle);
  cornerMesh.addTexCoord(calibration.topLeft);
  cornerMesh.addTexCoord(calibration.topRight);

}
