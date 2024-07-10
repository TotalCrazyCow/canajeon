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
const int GRID_SIZE = 501;
const int STEP_NUMBER = 100;

namespace Colors {

	EasyBMP::RGBColor black(0, 0, 0);
	EasyBMP::RGBColor white(255, 255, 255);
}

static const std::string base64_chars =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";


class Grid
{
public:
	Grid(/* args */);
	~Grid();
	
	double pos[STEP_NUMBER][GRID_SIZE][GRID_SIZE];
	void getExtrema(void);

	double maxValue;
	double minValue;
	std::string encodedImage;
};

Grid::Grid(/* args */)
{
	double scale = 2 * M_PI / GRID_SIZE ;
	// creation of example function to plot
	for (int t = 0; t < STEP_NUMBER; t++)
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

	for (int t = 0; t < STEP_NUMBER; t++)
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

std::string base64_encode(char const *buf, unsigned int bufLen) {

	std::string ret;
	int i = 0;
	int j = 0;
	char char_array_3[3];
	char char_array_4[4];

	while (bufLen--)
	{
		char_array_3[i++] = *(buf++);
		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';
	}

	return ret;
};

int colorOfValue(const Grid& grid, int step, int x, int y) {

	return std::ceil(255*(domain.pos[step][x][y] - domain.minValue)/(domain.maxValue - domain.minValue));
}

void colorBitmap(EasyBMP::Image &img, int timeStep, Grid& domain)
{	
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			EasyBMP::RGBColor blueVal(0, 0, colorOfValue(domain, timeStep, i, j));
			img.SetPixel(i, j, blueVal, 0);
		}
	}
};