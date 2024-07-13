#include <fstream>
#include <string>
#include <cmath>
#include "bmp.hpp"

using namespace std;


const int DIMENSION = 2;
const int GRID_SIZE = 600;
const int STEP_BRO = 100;
const double DT = 1/STEP_BRO;
const double SOUND_SPEED = 1;


namespace Colors {

	EasyBMP::RGBColor black(0, 0, 0);
	EasyBMP::RGBColor white(255, 255, 255);
}

typedef struct InstantGrid {
	double mesh[GRID_SIZE][GRID_SIZE];
};

typedef struct culationMatrix {
	InstantGrid instant[3];
};

class Grid
{
public:
	Grid(/* args */);
	~Grid();

	std::string StepAndDraw();

private:
	void granularStep(int ix, int iy);
	void numericalStep();
	int colorOfValue(int x, int y);
	void colorBitmap();
	void step();

	// numerical stuff
	culationMatrix solInMem;
	InstantGrid *un, *unp, *unm;

	// roba per i pastelli
	void getExtrema(void);
	double maxValue;
	double minValue;

	EasyBMP::Image img;
	std::string encodedImage;
};

Grid::Grid(/* args */): img(GRID_SIZE, GRID_SIZE, "test.bmp", Colors::white)
{

	solInMem = {};

	un = &solInMem.instant[1];
	unp = &solInMem.instant[2];
	unm = &solInMem.instant[0];

	// some initial condition
	un->mesh[GRID_SIZE/2][GRID_SIZE/2] = 1;

	double scale = 2 * M_PI / GRID_SIZE ;
	encodedImage = "null";
}

Grid::~Grid()
{
}



void Grid::granularStep(int ix, int iy) {
	unp->mesh[ix][iy] = 2*un->mesh[ix][iy] - unm->mesh[ix][iy] - SOUND_SPEED*SOUND_SPEED*DT*DT*(un->mesh[ix][iy+1] - 2*un->mesh[ix][iy] + un->mesh[ix][iy-1] + un->mesh[ix+1][iy] - 2*un->mesh[ix][iy] + un->mesh[ix-1][iy]);
};

void Grid::numericalStep() {
	for (int ix = 1; ix != (GRID_SIZE-2); ix++){
		for (int iy = 1; iy != (GRID_SIZE-2); iy++){
			granularStep(ix,iy);
		}
	}
	auto temp = unm;
	unm = un;
	un = unp;
	unp = temp;
};

void Grid::step() {
	numericalStep();
	getExtrema();
};

void Grid::getExtrema() {
	
	// initialization of values
	maxValue = un->mesh[0][0];
	minValue = un->mesh[0][0];

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (maxValue > un->mesh[i][j]) maxValue = un->mesh[i][j];
			if (minValue < un->mesh[i][j]) minValue = un->mesh[i][j];
		}
	}
}

int Grid::colorOfValue(int x, int y) {
	return std::ceil(255*(un->mesh[x][y] - minValue)/(maxValue - minValue));
}

void Grid::colorBitmap()
{	
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			int val = colorOfValue(i, j);
			EasyBMP::RGBColor pixelColor(60, 60, val);
			img.SetPixel(i, j, pixelColor, 0);
		}
	}
};

std::string Grid::StepAndDraw()
{
//	std::string encodedImage = "";

	step();
	colorBitmap();
	img.AsBase64(encodedImage);

	return encodedImage;
};