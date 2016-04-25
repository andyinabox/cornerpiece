#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Corner.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    bool showGui = true;
  
//    ofImage image;
    ofVideoPlayer vid;
//    ofTexture tex;
//    vector<ofVec2f> cPoints;
//    int cIndex = 0;
//    ofPoint points[4];
//    int cornerIndex = 0;
		
    ofLight light;
    ofCamera cam;
    Corner corner;
  
  
//    ofMesh tri1;
//    ofMesh tri2;
//    ofMesh tri3;
    ofMesh cRect;
  
  
    ofxToggle drawWireframe;
//    ofxToggle useVideo;
    ofxToggle showCalibration;
  
  
//    ofxFloatSlider cornerScale;
//    float cornerScale = 100;
    ofxPanel gui;
  
};
