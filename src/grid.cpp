#include "grid.hpp"

std::string drawGrid(EasyBMP::Image& img, Grid& domain, int t)
{
	std::string encodedImage = "";

	domain.getExtrema();

	// bitmap file creation
	//for (int t = 0; t < STEP_NUMBER; t++)
	//{
		colorBitmap(img, t, domain);
		std::string fileName = "test" + std::to_string(t) + ".bmp";
		std::string fileName2 = "test.bmp";
		img.AsBase64(encodedImage);
		//std::remove("test.bmp");
	//}

	// size_t totalSize = sizeof(domain);
	// int bmpBufferElements = totalSize / sizeof(char);
	// char bmpBuffer[bmpBufferElements];
	// std::memcpy(bmpBuffer, &domain, totalSize);

	return encodedImage;
};

std::string drawRoutine(int step) {

	std::string encoded = drawGrid(img, domain, step);
	return encoded;
};

int main()
{
	drawRoutine(1);

	return 0;
}

Napi::String drawRoutineWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Number step = info[0].As<Napi::Number>();

	Napi::String returnValue = Napi::String::New(env, drawRoutine(step.Int32Value()));

	return returnValue;
};

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	// export Napi function
	exports.Set("drawRoutine", Napi::Function::New(env, drawRoutineWrapped));
	return exports;
};