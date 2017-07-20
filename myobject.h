#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <nan.h>

class MyObject : public Nan::ObjectWrap {
 public:
  static v8::Local<v8::Function> Init();

 private:
  explicit MyObject(double value = 0);
  ~MyObject();

  static v8::Local<v8::Object> NewInstance(const v8::Local<v8::Value> value);

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void PlusOne(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Multiply(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static Nan::Persistent<v8::Function> constructor;
  double value_;
};

#endif
