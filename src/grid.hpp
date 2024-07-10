#include <fstream>
#include <string>
#include <cmath>
#include <napi.h>
#include "bmp.hpp"

using namespace std;

// add function wrapper
Napi::String drawRoutineWrapped(const Napi::CallbackInfo &info);

// Export API
Napi::Object Init(Napi::Env env, Napi::Object exports);
NODE_API_MODULE(addon, Init)

const int DIMENSION = 2;
const int GRID_SIZE = 600;
const int STEP_BRO = 100;

namespace Colors {

	EasyBMP::RGBColor black(0, 0, 0);
	EasyBMP::RGBColor white(255, 255, 255);
}


class Grid
{
public:
	Grid(/* args */);
	~Grid();
	
	double pos[STEP_BRO][GRID_SIZE][GRID_SIZE];
	void getExtrema(void);

	double maxValue;
	double minValue;
	std::string encodedImage;
};

Grid::Grid(/* args */)
{
	double scale = 2 * M_PI / GRID_SIZE ;
	// creation of example function to plot
	for (int t = 0; t < STEP_BRO; t++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			for (int y = 0; y < GRID_SIZE; y++)
			{
				pos[t][x][y] = sin(scale*scale*(x*x + y*y) - t);
			}
		}
	}
	encodedImage = "null";
}

Grid::~Grid()
{
}


Grid domain = Grid();
EasyBMP::Image img(GRID_SIZE, GRID_SIZE, "test.bmp", Colors::white);

/// @brief calculates maximum and minimum values on grid matrix, and calculates rescale factor for coloring
void Grid::getExtrema() {
	
	// initialization of values
	maxValue = pos[0][0][0];
	minValue = pos[0][0][0];

	for (int t = 0; t < STEP_BRO; t++)
	{
		for (int i = 0; i < GRID_SIZE; i++)
		{
			for (int j = 0; j < GRID_SIZE; j++)
			{
				if (maxValue > pos[t][i][j]) maxValue = pos[t][i][j];
				if (minValue < pos[t][i][j]) minValue = pos[t][i][j];
			}
		}
	}
}

int colorOfValue(const Grid& grid, int step, int x, int y) {

	return std::ceil(255*(domain.pos[step][x][y] - domain.minValue)/(domain.maxValue - domain.minValue));
}

void colorBitmap(EasyBMP::Image &img, int timeStep, Grid& domain)
{	
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			int val = colorOfValue(domain, timeStep, i, j);
			EasyBMP::RGBColor pixelColor(60, 60, val);
			img.SetPixel(i, j, pixelColor, 0);
		}
	}
};