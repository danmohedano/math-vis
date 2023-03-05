#include "JuliaGenerator.h"
#include <iostream>
#include "ofGraphics.h"
#include <chrono>

JuliaGenerator::JuliaGenerator(std::complex<double> constant, int img_width, int img_height, double escape_radius, int max_iterations, double zoom)
	:
	constant(constant),
	img_width(img_width),
	img_height(img_height),
	escape_radius(escape_radius),
	max_iterations(max_iterations),
	zoom(zoom)
{
}

std::complex<double> JuliaGenerator::next(std::complex<double> previous)
{
	return (previous * previous) + this->constant;
}

int JuliaGenerator::iterate(std::complex<double> z0)
{
	std::complex<double> zn = z0;
	int iter = 0;
	while (std::norm(zn) < (this->escape_radius * this->escape_radius - this->escape_radius) && iter < this->max_iterations)
	{
		zn = this->next(zn);
		iter++;
	}
	return iter;
}

void JuliaGenerator::update()
{
	if (!(this->updated)) return;

	// Allocate new pixels for the image
	this->img.allocate(this->img_width, this->img_height, OF_IMAGE_COLOR_ALPHA);

	// Compute the scaling factor depending on the smaller of the dimensions of the image
	// This will scale the smallest dimension to [-R, R]
	const int min_dim = std::min(this->img_width, this->img_height);
	const double scale = 2 * this->escape_radius / double(min_dim / 2);
	
	auto pixels = this->img.getPixels();
	auto start = std::chrono::high_resolution_clock::now();

	#pragma omp parallel for
	for (int y = 0; y < this->img_height; ++y)
	{
		for (int x = 0; x < this->img_width; ++x)
		{
			// Transform pixels to coordinates taking into account: offset of the image, resolution scaling and zoom
			const double px = double(x - (this->img_width / 2) + this->offset_x) * scale / this->zoom;
			const double py = double(y - (this->img_height / 2) + this->offset_y) * scale / this->zoom * -1;

			// Compute color based on Bernstein polynomials
			const float iterations = this->iterate(std::complex<double>(px, py));
			const float t = iterations / this->max_iterations;
			const ofColor color(9 * (1 - t) * pow(t, 3) * 255, 15 * pow((1 - t), 2) * pow(t, 2) * 255, 8.5 * pow((1 - t), 3) * t * 255);
			pixels.setColor(x, y, color);
		}
	}

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
	std::cout << "[UPDATE] " << this->img_width * this->img_height << "  " << this->img_width << "x" << this->img_height << "pixels in " << duration.count() << " ms" << std::endl;

	this->img.setFromPixels(pixels);
	this->img.update();
	this->updated = false;
}

void JuliaGenerator::draw()
{
	this->img.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}


void JuliaGenerator::setConstant(glm::vec2& x)
{
	this->updated = true;
	this->constant = std::complex<double>(x.x, x.y);
}


void JuliaGenerator::setRadius(double& x)
{
	this->updated = true;
	this->escape_radius = double(x);
}


void JuliaGenerator::setIterations(int& x)
{
	this->updated = true;
	this->max_iterations = int(x);
}


void JuliaGenerator::setWidth(int& x)
{
	this->updated = true;
	this->img_width = int(x);
}


void JuliaGenerator::setHeight(int& x)
{
	this->updated = true;
	this->img_height = int(x);
}


void JuliaGenerator::setZoom(double& x)
{
	this->updated = true;
	this->zoom = double(x);
}


void JuliaGenerator::updateOffsetX(int x)
{
	this->updated = true;
	this->offset_x += x;
}


void JuliaGenerator::updateOffsetY(int x)
{
	this->updated = true;
	this->offset_y += x;
}


void JuliaGenerator::updateZoom(double x)
{
	this->updated = true;
	this->zoom += x;
}