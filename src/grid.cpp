// #include "example.hpp"
#include <fstream>
#include <string>
#include "bmp.hpp"

using namespace std;

const int DIMENSION = 2;
const int GRID_SIZE = 1001;

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

struct Grid
{
  double pos[GRID_SIZE][GRID_SIZE];
};

std::string base64_encode(char const* buf, unsigned int bufLen) {
  std::string ret;
  int i = 0;
  int j = 0;
  char char_array_3[3];
  char char_array_4[4];

  while (bufLen--) {
    char_array_3[i++] = *(buf++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';
  }

  return ret;
};

std::string drawGrid()
{
  Grid domain = Grid();
  double x_min = 0;
  double x_max = 1;
  double y_min = 0;
  double y_max = 1;

  double step = (x_max - x_min) / (GRID_SIZE - 1);

  EasyBMP::RGBColor black(0, 0, 0);
  EasyBMP::RGBColor white(255,255,255); 
  EasyBMP::Image img(GRID_SIZE, GRID_SIZE, "test.bmp", white);

  for (int i = 0; i < GRID_SIZE; i++)
    for (int j = 0; j < GRID_SIZE; j++)
    {
      domain.pos[i][j] = x_min + i * j * step;
      EasyBMP::RGBColor blue(0, 0, std::ceil(domain.pos[i][j]));  
      img.SetPixel(i, j, blue, 0);
    }

  img.Write("test.bmp");

  size_t totalSize = sizeof(domain);
  int bmpBufferElements = totalSize / sizeof(char);
  char bmpBuffer[bmpBufferElements];

  std::cout << "totalsize = " << totalSize << std::endl;
  std::cout << "sizeof(char) = " << sizeof(char) << std::endl;

  std::memcpy(bmpBuffer, &domain, totalSize);
  std::string encodedImage = base64_encode(bmpBuffer, totalSize);

  return encodedImage;
};


int main() {

  std::cout << drawGrid();

  return 0;
}