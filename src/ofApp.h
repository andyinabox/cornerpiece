#pragma once

#include "ofMain.h"

#include "ofxGui.h"
#include "ofxCsv.h"
#include "ofxCameraSaveLoad.h"

#include "Corner.h"
#include "ShaderScreen.h"

#define CAM_DISTANCE 400
#define CORNER_SCALE 350
#define CAL_IMG_SCALE 512
#define CAL_HANDLE_SIZE 7
#define CAL_POINT_GRAB_DIST 10

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    void toggleCameraMovement(bool &value);
    void toggleWireframe(bool &value);
    void toggleLabels(bool &value);
    void nextLabels();
  
    void resetCamera();
    void resetCorner();
  
    void saveSettings();
    void loadSettings();

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
  
    const string labelsPath = "threes.csv";
    const string guiSettingsPath = "settings/gui.xml";
    const string camSettingsPath = "settings/camera";
    const string xmlSettingsPath = "settings/settings.xml";
  
    ofVideoPlayer vid;
    ofLight light;
    ofEasyCam cam;
    Corner corner;
  
    int cIndex = 0;
    ShaderScreen screen;
  
    ofxPanel gui;
    ofxToggle drawWireframe;
    ofxToggle showCalibration;
    ofxToggle cameraMovement;
    ofxToggle showLabels;
  
    ofxCsv labels;
    int labelsIndex = -1;
  
//    ofTrueTypeFont font;
};
