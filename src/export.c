#include "module-js.h"

#define DECLARE_NAPI_METHOD(name, func)     \
  {                                         \
    name, 0, func, 0, 0, 0, napi_default, 0 \
  }

napi_ref constructor;

napi_value ExportModule(napi_env env, napi_value exports)
{
  // Define module interface
  DEBUG("ExportModule: Module declaration...");

  napi_status status;
  napi_property_descriptor properties[] = {
      DECLARE_NAPI_METHOD("init", Init),
      DECLARE_NAPI_METHOD("getCount", GetCount),
      DECLARE_NAPI_METHOD("randomBytes", RandomBytes)
  };

  // Define JS class
  napi_value cons;
  status = napi_define_class(env, "Module", NAPI_AUTO_LENGTH, New, NULL, 3, properties, &cons);
  ASSERT(env, status == napi_ok, "Failed to define class");

  // Create reference to JS contructor
  status = napi_create_reference(env, cons, 1, &constructor);
  ASSERT(env, status == napi_ok, "Failed to reference contructor");

  // Export module
  status = napi_set_named_property(env, exports, "Module", cons);
  ASSERT(env, status == napi_ok, "Failed to bind class to native module");

  return exports;
}


NAPI_MODULE(NODE_GYP_MODULE_NAME, ExportModule);
