#include "grid.hpp"

void drawGrid(EasyBMP::Image& img, Grid& domain, int t)
{
	domain.getExtrema();

	// bitmap file creation
	//for (int t = 0; t < STEP_NUMBER; t++)
	//{
		colorBitmap(img, t, domain);
		std::string fileName = "test" + std::to_string(t) + ".bmp";
		std::string fileName2 = "test.bmp";
		img.Write(fileName2);
		//std::remove("test.bmp");
	//}

	// size_t totalSize = sizeof(domain);
	// int bmpBufferElements = totalSize / sizeof(char);
	// char bmpBuffer[bmpBufferElements];
	// std::memcpy(bmpBuffer, &domain, totalSize);
	// domain.encodedImage = base64_encode(bmpBuffer, totalSize);

	// return encodedImage;
	//return "drawGrid() finito senza errori!\n";
};

const bool drawRoutine(int step) {

	drawGrid(img, domain, step%STEP_NUMBER);
	if (step == STEP_NUMBER-1) return true;
	return false;
};

Napi::Boolean drawRoutineWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Number step = info[0].As<Napi::Number>();

	Napi::Boolean returnValue = Napi::Boolean::New(env, drawRoutine(step.Int32Value()));

	return returnValue;
};

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	// export Napi function
	exports.Set("drawRoutine", Napi::Function::New(env, drawRoutineWrapped));
	return exports;
};