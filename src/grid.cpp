#include "napisan.hpp"
#include "grid.hpp"

Grid::Grid(/* args */) : img(GRID_SIZE, GRID_SIZE, "test.bmp", Colors::white)
{
	// for numerical stability
	DT = DX * CFL_MAX / WAVE_SPEED;
	printSimInfo();

	solInMem = {};

	un = &solInMem.instant[1];
	unp = &solInMem.instant[2];
	unm = &solInMem.instant[0];

	// some initial condition
	for (int i = (GRID_SIZE / 2) - 60; i < (GRID_SIZE / 2) - 50; i++)
		for (int j = (GRID_SIZE / 2) - 180; j < (GRID_SIZE / 2) - 120; j++)
			un->mesh[i][j] = (double) rand() / (RAND_MAX);

	minValue = 0;
	maxValue = 1;

	encodedImage = "null";
}

Grid::~Grid()
{
}

void Grid::granularStep(int ix, int iy)
{
	double xDoubleDer = (un->mesh[ix + 1][iy] - 2 * un->mesh[ix][iy] + un->mesh[ix - 1][iy]) / DX / DX;
	double yDoubleDer = (un->mesh[ix][iy + 1] - 2 * un->mesh[ix][iy] + un->mesh[ix][iy - 1]) / DX / DX;
	unp->mesh[ix][iy] = 2 * un->mesh[ix][iy] - unm->mesh[ix][iy] + WAVE_SPEED * WAVE_SPEED * DT * DT * (xDoubleDer + yDoubleDer);
};

void Grid::numericalStep()
{
	for (int ix = 1; ix != (GRID_SIZE - 2); ix++)
	{
		for (int iy = 1; iy != (GRID_SIZE - 2); iy++)
		{
			granularStep(ix, iy);
		}
	}

	auto temp = unm;
	unm = un;
	un = unp;
	unp = temp;
};

int Grid::colorOfValue(int x, int y)
{
	// for debug purposes only (checking numerical stability)
	// if (un->mesh[x][y] > 0.05)
	// 	std::cout << "u(" << x << "," << y << ") = " << un->mesh[x][y] << std::endl;

	return std::floor(255 * un->mesh[x][y]);
}

void Grid::colorBitmap()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			int val = colorOfValue(i, j);
			EasyBMP::RGBColor pixelColor(0, 0, val);
			img.SetPixel(i, j, pixelColor, 0);
		}
	}
};

std::string Grid::StepAndDraw()
{
	numericalStep();
	colorBitmap();
	img.AsBase64(encodedImage);

	return encodedImage;
};

void Grid::StepAndWrite(std::string filename)
{
	numericalStep();
	colorBitmap();
	img.Write(filename);
};

void Grid::printSimInfo() {

	std::cout << "Simulation configuration: \n";
	std::cout << "DIMENSION = " << DIMENSION << std::endl;
	std::cout << "GRID_SIZE = " << GRID_SIZE << std::endl;
	std::cout << "LX = " << LX << std::endl;
	std::cout << "DX = " << DX << std::endl;
	std::cout << "WAVE_SPEED = " << WAVE_SPEED << std::endl;
	std::cout << "CFL_MAX = " << CFL_MAX << std::endl << std::endl;
};