#pragma once
#include <complex>
#include "ofImage.h"
#include "ofxGui.h"

class JuliaGenerator
{
public:
	ofImage img = ofImage();

	JuliaGenerator() {};
	JuliaGenerator(std::complex<double> constant, int img_width, int img_height, double escape_radius, int max_iterations, double zoom);
	std::complex<double> next(std::complex<double> previous);
	int iterate(std::complex<double> z0);
	void update();
	void draw();
	void setConstant(glm::vec2& x);
	void setRadius(double& x);
	void setIterations(int& x);
	void setWidth(int& x);
	void setHeight(int& x);
	void setZoom(double& x);
	void updateOffsetX(int x);
	void updateOffsetY(int x);
	void updateZoom(double x);


private:
	// Computation elements
	std::complex<double> constant = std::complex<double>(0, 0);
	double escape_radius = 2.0;
	int max_iterations = 50;
	int img_width = 192;
	int img_height = 108;
	double zoom = 1.0;
	int offset_x = 0;
	int offset_y = 0;

	// GUI Elements
	bool updated = true;
};

