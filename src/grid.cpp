#include "grid.hpp"

std::string drawGrid(EasyBMP::Image& img, Grid& domain, int t)
{
	std::string encodedImage = "";

	domain.getExtrema();

	colorBitmap(img, t, domain);
	img.AsBase64(encodedImage);

	return encodedImage;
};

std::string drawRoutine(int step) {

	std::string encoded = drawGrid(img, domain, step % STEP_BRO);
	return encoded;
};

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