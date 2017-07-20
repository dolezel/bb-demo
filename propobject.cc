#include "propobject.h"

Nan::Persistent<v8::Function> PropObject::constructor;

PropObject::PropObject(double value) : value_(value) {
}

PropObject::~PropObject() {
}

v8::Local<v8::Function> PropObject::Init() {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("PropObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(tpl->GetFunction());
  return tpl->GetFunction();
}

v8::Local<v8::Object> PropObject::NewInstance(const v8::Local<v8::Value> value) {
  Nan::EscapableHandleScope scope;

  const int argc = 1;
  v8::Local<v8::Value> argv[argc] = { value };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();

  return scope.Escape(instance);
}

void PropObject::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new PropObject(...)`
    double value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
    PropObject* obj = new PropObject(value);
    obj->Wrap(info.This());

    Nan::SetAccessor(
      obj->handle(),
      Nan::New("value").ToLocalChecked(),
      ValueGetter,
      ValueSetter
    );

    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `PropObject(...)`, turn into construct call.
    info.GetReturnValue().Set(PropObject::NewInstance(info[0]));
  }
}

void PropObject::ValueGetter(
    v8::Local<v8::String> property,
    const Nan::PropertyCallbackInfo<v8::Value>& info
  ) {
  PropObject* obj = ObjectWrap::Unwrap<PropObject>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->value_));
}

void PropObject::ValueSetter(
    v8::Local<v8::String> property,
    v8::Local<v8::Value> value,
    const Nan::PropertyCallbackInfo<void>& info
  ) {
  PropObject* obj = ObjectWrap::Unwrap<PropObject>(info.Holder());
  double val = value->NumberValue();
  obj->value_ = val;
  info.GetReturnValue().Set(Nan::Undefined());
}
