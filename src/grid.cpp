#include "grid.hpp"

std::string drawGrid(EasyBMP::Image& img, Grid& domain)
{
	domain.getExtrema();

	// bitmap file creation
	for (int t = 0; t < STEP_NUMBER; t++)
	{
		colorBitmap(img, t, domain);
		std::string fileName = "test" + std::to_string(t) + ".bmp";
		std::string fileName2 = "test.bmp";
		img.Write(fileName2);
		//std::remove("test.bmp");
	}

	// size_t totalSize = sizeof(domain);
	// int bmpBufferElements = totalSize / sizeof(char);
	// char bmpBuffer[bmpBufferElements];
	// std::memcpy(bmpBuffer, &domain, totalSize);
	// std::string encodedImage = base64_encode(bmpBuffer, totalSize);

	// return encodedImage;
	return "drawGrid() finito senza errori!\n";
};

int drawRoutine(void) {

	std::string test = drawGrid(img, domain);
	return 0;
};

int main()
{
	drawRoutine();

	return 0;
}

Napi::Number drawRoutineWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();

	Napi::Number returnValue = Napi::Number::New(env, drawRoutine());

	return returnValue;
};

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	// export Napi function
	exports.Set("drawRoutine", Napi::Function::New(env, drawRoutineWrapped));
	return exports;
};