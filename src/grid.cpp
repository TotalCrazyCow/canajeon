#include "grid.hpp"

std::string drawGrid()
{
//	std::string encodedImage = "";

	sol.step();

	colorBitmap(img, sol);
	img.AsBase64(sol.encodedImage);

	return sol.encodedImage;
};

std::string drawRoutine(int step) {

	std::string encoded = drawGrid();
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