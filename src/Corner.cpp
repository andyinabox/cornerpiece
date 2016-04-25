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
  triRight.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  triRight.addVertex(ofPoint(0, 0, 0));
  triRight.addVertex(ofPoint(CORNER_SCALE, 0, 0));
  triRight.addVertex(ofPoint(0, CORNER_SCALE, 0));

  triRight.addIndex(0);
  triRight.addIndex(1);
  triRight.addIndex(2);

  triLeft.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  triLeft.addVertex(ofPoint(0, 0, 0));
  triLeft.addVertex(ofPoint(0, 0, CORNER_SCALE));
  triLeft.addVertex(ofPoint(0, CORNER_SCALE, 0));

  triLeft.addIndex(0);
  triLeft.addIndex(1);
  triLeft.addIndex(2);
  
  triTop.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  triTop.addVertex(ofPoint(0, 0, 0));
  triTop.addVertex(ofPoint(0, 0, CORNER_SCALE));
  triTop.addVertex(ofPoint(CORNER_SCALE, 0, 0));

  triTop.addIndex(0);
  triTop.addIndex(1);
  triTop.addIndex(2);
  
  // default calibration
  setCalibrationPoints(ofVec2f(0, 0), ofVec2f(1, 0), ofVec2f(0.5, 0.5), ofVec2f(0.5, 1));
}


void Corner::draw(ofCamera cam) {
  
  if(calibrationMode) {
    triRight.drawWireframe();
    triLeft.drawWireframe();
    triTop.drawWireframe();
    manipulator.draw(cam);
  } else {
    texture.bind();
      triRight.draw();
      triLeft.draw();
      triTop.draw();
    texture.unbind();
  }
}

void Corner::setTexture(ofTexture tex) {
  texture = tex;
}

void Corner::setCalibrationPoints(ofVec2f topLeft, ofVec2f topRight, ofVec2f middle, ofVec2f bottom) {

  calibration.topLeft = topLeft;
  calibration.topRight = topRight;
  calibration.middle = middle;
  calibration.bottom = bottom;

  triRight.clearTexCoords();
  triRight.addTexCoord(calibration.middle);
  triRight.addTexCoord(calibration.topRight);
  triRight.addTexCoord(calibration.bottom);
  
  triLeft.clearTexCoords();
  triLeft.addTexCoord(calibration.middle);
  triLeft.addTexCoord(calibration.topLeft);
  triLeft.addTexCoord(calibration.bottom);
  
  triTop.clearTexCoords();
  triTop.addTexCoord(calibration.middle);
  triTop.addTexCoord(calibration.topLeft);
  triTop.addTexCoord(calibration.topRight);

}
