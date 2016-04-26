#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Corner.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    void toggleCameraMovement(bool &value);
    void toggleWireframe(bool &value);

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
  
    ofVideoPlayer vid;
    ofLight light;
    ofEasyCam cam;
    Corner corner;
  
    int cIndex = 0;
    ofMesh cRect;
  
    ofxPanel gui;
    ofxToggle drawWireframe;
    ofxToggle showCalibration;
    ofxToggle cameraMovement;
  
  
};
