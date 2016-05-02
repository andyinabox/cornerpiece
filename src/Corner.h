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
#include "ofxCenteredTrueTypeFont.h"

class Corner : public ofNode {
  public:
    void setup(float s);
    void draw(ofCamera cam);
    void drawLabels();
  
    void setTexture(ofTexture tex);
    void setCalibrationPoints(vector<ofVec2f> points);
    void setCalibrationPoint(int index, ofVec2f point);
    void setLabels(string left, string right, string top);

    vector<ofVec2f> getCalibrationPoints();
  
    ofMatrix4x4 getMatrix();
    void setMatrix(ofMatrix4x4 m);
  
    void toggleWireframe(bool b);
    void toggleLabels(bool b);
  
    bool bWireframe = false;
    bool bLabels = true;

    float scale = 100;
  
    ofxManipulator manipulator;
    ofTexture texture;
    ofMesh cornerMesh;
    ofxCenteredTrueTypeFont textFont;
  
    vector<string> cornerLabels;
  
  protected:
  
  private:
    void updateTexCoords();

    float rotationAngle;
    ofVec3f rotationVector;
    vector<ofVec2f> calibration;


};