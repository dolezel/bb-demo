#include <nan.h>
#include "mycallback.h"

void RunCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;

  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[1]->IsFunction()) {
    Nan::ThrowTypeError("Second argument must be function");
    return;
  }

  v8::Local<v8::Value> arg = info[0];
  v8::Local<v8::Function> cb = info[1].As<v8::Function>();

  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { arg };
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
}
