#pragma once

#include "ofMain.h"
#include "generator/JuliaGenerator.h"
#include "ofxGui.h"
#include <string>

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

		void listenerConstant(glm::vec2& x);
		void listenerRadius(double& x);
		void listenerIterations(int& x);
		void listenerWidth(int& x);
		void listenerZoom(double& x);

	private:
		// Julia visualizer with math logic
		JuliaGenerator julia;

		// GUI elements
		ofxPanel gui;
		ofParameter<glm::vec2> gui_constant;
		ofParameter<double> gui_escape_radius;
		ofParameter<int> gui_max_iterations;
		ofParameter<int> gui_img_width;
		ofParameter<double> gui_zoom;

		// Saving image file name
		std::string filename;
};
