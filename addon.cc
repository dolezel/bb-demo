#include <nan.h>
#include "myobject.h"
#include "propobject.h"
#include "mycallback.h"

void InitAll(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  exports->Set(
    Nan::New("MyObject").ToLocalChecked(),
    MyObject::Init()
  );
  exports->Set(
    Nan::New("PropObject").ToLocalChecked(),
    PropObject::Init()
  );
  exports->Set(
    Nan::New("RunCallback").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(RunCallback)->GetFunction()
  );
}

NODE_MODULE(addon, InitAll)
