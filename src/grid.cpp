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
	const int itemp = GRID_SIZE / 2;
	un->mesh[itemp][itemp] = 2;
	un->mesh[itemp+1][itemp] = 1;
	un->mesh[itemp+1][itemp+1] = 0.5;
	un->mesh[itemp+1][itemp-1] = 0.5;
	un->mesh[itemp-1][itemp] = 1;
	un->mesh[itemp-1][itemp+1] = 0.5;
	un->mesh[itemp-1][itemp-1] = 0.5;
	un->mesh[itemp][itemp+1] = 1;
	un->mesh[itemp][itemp-1] = 1;

	minValue = 0;
	maxValue = 1;

	encodedImage = "null";
}

Grid::~Grid()
{
}

void Grid::granularStep(int ix, int iy)
{
	bool isBorder = (ix == 0 || iy == 0 || ix == GRID_SIZE-1 || iy == GRID_SIZE-1) ? true : false;

	if (isBorder) {
		unp->mesh[ix][iy] = 0; // Dirichlet conditions
	}
	else {
		double xDoubleDer = (un->mesh[ix + 1][iy] - 2 * un->mesh[ix][iy] + un->mesh[ix - 1][iy]) / (DX * DX);
		double yDoubleDer = (un->mesh[ix][iy + 1] - 2 * un->mesh[ix][iy] + un->mesh[ix][iy - 1]) / (DX * DX);
		unp->mesh[ix][iy] = 2 * un->mesh[ix][iy] - unm->mesh[ix][iy] + WAVE_SPEED * WAVE_SPEED * DT * DT * (xDoubleDer + yDoubleDer);
		// hacky fix to stabilise to b.c.	
		unp->mesh[ix][iy] *= 0.995;
	}
};

void Grid::numericalStep()
{
	for (int ix = 0; ix != GRID_SIZE-1; ix++)
	{
		for (int iy = 0; iy != GRID_SIZE-1; iy++)
		{
			granularStep(ix, iy);
		}
	}

	auto temp = unm;
	unm = un;
	un = unp;
	unp = temp;
};

EasyBMP::RGBColor Grid::colorOfValue(int x, int y)
{
	// for debug purposes only (checking numerical stability)
	// if (un->mesh[x][y] > 0.1)
	// 	printPixelValue(x,y);

	int valBlue = std::floor(255 * un->mesh[x][y]);
	int valGreen = std::floor(valBlue / 4);
	int valRed = std::floor(valBlue / 16);

	EasyBMP::RGBColor retColor(valRed % 255, valGreen % 255, valBlue % 255);
	return retColor;
}

void Grid::colorBitmap()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			EasyBMP::RGBColor pixelColor = colorOfValue(i, j);
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

	std::cout << "\033[1;32mSimulation configuration: \033[0m\n";
	std::cout << "DIMENSION = " << DIMENSION << std::endl;
	std::cout << "GRID_SIZE = " << GRID_SIZE << std::endl;
	std::cout << "LX = " << LX << std::endl;
	std::cout << "DX = " << DX << std::endl;
	std::cout << "WAVE_SPEED = " << WAVE_SPEED << std::endl;
	std::cout << "CFL_MAX = " << CFL_MAX << std::endl << std::endl;
};

void Grid::printPixelValue(int x, int y) {
	std::cout << "u(" << x << "," << y << ") = " << un->mesh[x][y] << std::endl;
}