#ifndef WRAP_MODULE_JS_H_
#define WRAP_MODULE_JS_H_

#include <assert.h>
#include <stdlib.h>
#include <node_api.h>
#include "module.h"

#define DECLARE_NAPI_METHOD(name, func)     \
  {                                         \
    name, 0, func, 0, 0, 0, napi_default, 0 \
  }

#define ASSERT(env, test, msg)        \
  if (!(test)) {                      \
    napi_throw_error(env, NULL, msg); \
    return NULL;                      \
  }


void Destructor(napi_env env, void* nativeObject, void* finalize_hint);

napi_value New(napi_env env, napi_callback_info info);
napi_value Init(napi_env env, napi_callback_info info);
napi_value GetCount(napi_env env, napi_callback_info info);
napi_value RandomBytes(napi_env env, napi_callback_info info);

#endif // WRAP_MODULE_JS_H_
