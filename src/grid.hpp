#pragma once

#include <fstream>
#include <string>
#include <cmath>

#include "bmp.hpp"
#include "structures.hpp"

namespace Colors
{

	EasyBMP::RGBColor black(0, 0, 0);
	EasyBMP::RGBColor white(255, 255, 255);
}



class Grid
{
public:
	Grid(/* args */);
	~Grid();

	std::string StepAndDraw();
	void StepAndWrite(std::string filename);

private:
	void granularStep(int ix, int iy);
	void numericalStep();
	int colorOfValue(int x, int y);
	void colorBitmap();
	void printSimInfo();

	// numerical stuff
	CalculationMatrix solInMem;
	InstantGrid *un, *unp, *unm;

	// roba per i pastelli
	double maxValue;
	double minValue;

	EasyBMP::Image img;
	std::string encodedImage;
};