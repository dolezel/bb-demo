#ifndef PROPOBJECT_H
#define PROPOBJECT_H

#include <nan.h>

class PropObject : public Nan::ObjectWrap {
 public:
  static v8::Local<v8::Function> Init();

 private:
  explicit PropObject(double value = 0);
  ~PropObject();

  static v8::Local<v8::Object> NewInstance(const v8::Local<v8::Value> value);

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static void ValueGetter(
    v8::Local<v8::String> property,
    const Nan::PropertyCallbackInfo<v8::Value>& info
    );
  static void ValueSetter(
    v8::Local<v8::String> property,
    v8::Local<v8::Value> value,
    const Nan::PropertyCallbackInfo<void>& info
  );

  static Nan::Persistent<v8::Function> constructor;
  double value_;
};

#endif
