#include "ofApp.h"
#include <omp.h>
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
	// Default values
	std::complex<double> constant(-0.835, -0.2321);
	double escape_radius = 2;
	int max_iterations = 150;
	double aspect_ratio = double(ofGetWindowWidth()) / double(ofGetWindowHeight());
	int img_width = 500;
	int img_height = int(double(img_width) / aspect_ratio);
	double zoom = 4;
	int THREADS = 4;
	this->filename = "julia-";

	// Setup of GUI
	this->gui_constant.addListener(this, &ofApp::listenerConstant);
	this->gui_escape_radius.addListener(this, &ofApp::listenerRadius);
	this->gui_max_iterations.addListener(this, &ofApp::listenerIterations);
	this->gui_img_width.addListener(this, &ofApp::listenerWidth);
	this->gui_zoom.addListener(this, &ofApp::listenerZoom);

	this->gui_constant.set("constant", glm::vec2(constant.real(), constant.imag()), glm::vec2(-1, -1), glm::vec2(1, 1));
	this->gui_escape_radius.set("escape_radius", escape_radius, 1, 5);
	this->gui_max_iterations.set("max_iterations", max_iterations, 1, 500);
	this->gui_img_width.set("img_width", img_width, 10, 1920);
	this->gui_zoom.set("zoom", zoom, 0, 100);

	this->gui.setup("panel");
	gui.add(this->gui_constant);
	gui.add(this->gui_escape_radius);
	gui.add(this->gui_max_iterations);
	gui.add(this->gui_img_width);
	gui.add(this->gui_zoom);

	// Configuration of OpenMP for multi-thread processing
	omp_set_num_threads(THREADS);

	this->julia = JuliaGenerator(constant, img_width, img_height, escape_radius, max_iterations, zoom);
}

//--------------------------------------------------------------
void ofApp::update(){
	this->julia.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	this->julia.draw();
	this->gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_LEFT)
	{
		this->julia.updateOffsetX(-10);
	}
	else if (key == OF_KEY_RIGHT)
	{
		this->julia.updateOffsetX(10);
	}
	else if (key == OF_KEY_DOWN)
	{
		this->julia.updateOffsetY(10);
	}
	else if (key == OF_KEY_UP)
	{
		this->julia.updateOffsetY(-10);
	}
	else if (key == 's')
	{
		ofSaveImage(this->julia.img.getPixels(), this->filename + ofToString(ofGetFrameNum()) + ".png", OF_IMAGE_QUALITY_BEST);
		std::cout << "[CONTROLS] Image saved" << std::endl;
	}
	else if (key == 'z')
	{
		this->julia.updateZoom(0.1);
		this->gui_zoom.set(this->gui_zoom.get() + 0.1);
	}
	else if (key == 'x')
	{
		this->julia.updateZoom(-0.1);
		this->gui_zoom.set(this->gui_zoom.get() - 0.1);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	this->julia.update();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::listenerConstant(glm::vec2& x)
{
	this->julia.setConstant(x);
}


void ofApp::listenerRadius(double& x)
{
	this->julia.setRadius(x);
}


void ofApp::listenerIterations(int& x)
{
	this->julia.setIterations(x);
}


void ofApp::listenerWidth(int& x)
{
	const double aspect_ratio = double(ofGetWindowWidth()) / double(ofGetWindowHeight());
	int width = x;
	int height = int(double(x) / aspect_ratio);
	this->julia.setWidth(width);
	this->julia.setHeight(height);
}


void ofApp::listenerZoom(double& x)
{
	this->julia.setZoom(x);
}
