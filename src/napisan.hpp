#ifndef NAPISAN_LOADED
#define NAPISAN_LOADED

#include <napi.h>
#include "grid.hpp"

// define class wrapper
class wrappedGrid : public Napi::ObjectWrap<wrappedGrid> {
    public:
        wrappedGrid(const Napi::CallbackInfo& info);
        Napi::Value drawNext(const Napi::CallbackInfo&);
    
        static Napi::Function GetClass(Napi::Env); // TODO is this needed for wrapper

    private:
        Grid sol;
};

// Export API 
Napi::Object Init(Napi::Env env, Napi::Object exports); // TODO

// define stuff

wrappedGrid::wrappedGrid(const Napi::CallbackInfo& info)
    : sol(), ObjectWrap(info) {
        
};

Napi::Value wrappedGrid::drawNext(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();

	Napi::String returnValue = Napi::String::New(env, sol.StepAndDraw());

	return returnValue;
};

Napi::Function wrappedGrid::GetClass(Napi::Env env) {
    return DefineClass(
        env,
        "Grid",
        {
            wrappedGrid::InstanceMethod("drawNext", &wrappedGrid::drawNext),
        });
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::String name = Napi::String::New(env, "Grid");
    exports.Set(name, wrappedGrid::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)

#endif