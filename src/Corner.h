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

#define FONT_SIZE 20

class Corner : public ofNode {
  public:
    void setup(float scale);
    void draw(ofCamera cam);
  
    void setTexture(ofTexture tex);
    void setCalibrationPoints(vector<ofVec2f> points);
    void setCalibrationPoint(int index, ofVec2f point);
  
    vector<ofVec2f> getCalibrationPoints();
  
    void toggleWireframe(bool b);
  
    bool bWireframe = false;

    float scale = 100;
  
    ofxManipulator manipulator;
    ofTexture texture;
    ofMesh cornerMesh;
    ofTrueTypeFont textFont;
  
  protected:
  
  private:
    void updateTexCoords();

    float rotationAngle;
    ofVec3f rotationVector;
    vector<ofVec2f> calibration;


};