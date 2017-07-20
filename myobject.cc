#include "myobject.h"

Nan::Persistent<v8::Function> MyObject::constructor;

MyObject::MyObject(double value) : value_(value) {
}

MyObject::~MyObject() {
}

v8::Local<v8::Function> MyObject::Init() {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "value", GetValue);
  Nan::SetPrototypeMethod(tpl, "plusOne", PlusOne);
  Nan::SetPrototypeMethod(tpl, "multiply", Multiply);

  constructor.Reset(tpl->GetFunction());
  return tpl->GetFunction();
}

v8::Local<v8::Object> MyObject::NewInstance(const v8::Local<v8::Value> value) {
  Nan::EscapableHandleScope scope;

  const int argc = 1;
  v8::Local<v8::Value> argv[argc] = { value };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();

  return scope.Escape(instance);
}

void MyObject::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    double value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
    MyObject* obj = new MyObject(value);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    info.GetReturnValue().Set(MyObject::NewInstance(info[0]));
  }
}

void MyObject::GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->value_));
}

void MyObject::PlusOne(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  obj->value_ += 1;
  info.GetReturnValue().Set(Nan::New(obj->value_));
}

void MyObject::Multiply(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  double multiple = info[0]->IsUndefined() ? 1 : info[0]->NumberValue();

  info.GetReturnValue().Set(MyObject::NewInstance(Nan::New(obj->value_ * multiple)));
}
