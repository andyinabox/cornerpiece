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

#define FONT_SIZE 10

class Corner : public ofNode {
  public:
    void setup(float s);
    void draw(ofCamera cam);
    void drawLabels();
  
    void setTexture(ofTexture tex);
    void setCalibrationPoints(vector<ofVec2f> points);
    void setCalibrationPoint(int index, ofVec2f point);
  
    void setLabels(vector<string> labels);
  
    vector<ofVec2f> getCalibrationPoints();
  
    void toggleWireframe(bool b);
  
    bool bWireframe = false;
    bool bLabels = true;

    float scale = 100;
  
    ofxManipulator manipulator;
    ofTexture texture;
    ofMesh cornerMesh;
    ofTrueTypeFont textFont;
  
    vector<string> cornerLabels;
  
  protected:
  
  private:
    void updateTexCoords();

    float rotationAngle;
    ofVec3f rotationVector;
    vector<ofVec2f> calibration;


};