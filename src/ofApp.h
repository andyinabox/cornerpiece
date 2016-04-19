#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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
  
    ofImage image;
    ofTexture imageTexture;
//    ofPoint points[4];
//    int cornerIndex = 0;
		
    ofLight light;
    ofEasyCam cam;
    ofMesh corner;
    ofMesh rect;
  
  
    ofxToggle showGrid;
    ofxToggle drawWireframe;
//    ofxFloatSlider cornerScale;
    float cornerScale = 100;
    ofxPanel gui;
  
};
