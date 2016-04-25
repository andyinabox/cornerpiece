//
//  Corner.h
//  cornerMapTest1
//
//  Created by Andrew Dayton on 4/25/16.
//
//

#ifndef __cornerMapTest1__Corner__
#define __cornerMapTest1__Corner__

#include <stdio.h>

#endif /* defined(__cornerMapTest1__Corner__) */

#include "ofxManipulator.h"

typedef struct {
  ofVec2f topLeft;
  ofVec2f topRight;
  ofVec2f middle;
  ofVec2f bottom;
} CornerCalibration;

class Corner : public ofNode {
  public:
    void setup();
    void draw(ofCamera cam);
  
    void setTexture(ofTexture tex);
    void setCalibrationPoints(ofVec2f topLeft, ofVec2f topRight, ofVec2f middle, ofVec2f bottom);
  
    bool calibrationMode = false;
  
    ofxManipulator manipulator;
    ofTexture texture;
    ofMesh triLeft, triRight, triTop;
  
  protected:
    CornerCalibration calibration;
  
  private:

};