#include "module-js.h"


void Destructor(napi_env env, void *nativeObject, void * finalize_hint)
{
  my_module_instance_t *this = nativeObject;
  DEBUG("Instance %d beeing garbage collected", this->id);
}


napi_value New(napi_env env, napi_callback_info info)
{
  napi_status status;
  DEBUG("MyModule::New...");

  // Get JS this
  napi_value jsthis;
  status = napi_get_cb_info(env, info, NULL, NULL, &jsthis, NULL);
  ASSERT(env, status == napi_ok, "Failed to get arguments");

  // Check if called with "new" keyword
  napi_value target;
  status = napi_get_new_target(env, info, &target);
  ASSERT(env, status == napi_ok, "Failed to get \"new\" target");
  ASSERT(env, target != NULL, "Class constructor Module cannot be invoked without 'new'");

  my_module_instance_t *this = calloc(1, sizeof(my_module_instance_t));
  DEBUG("MyModule::New this=%p", this);

  new(this);

  // Wrap native object
  status = napi_wrap(env, jsthis, this, Destructor, NULL, NULL);
  ASSERT(env, status == napi_ok, "Failed to retreive native structure");
  DEBUG("MyModule::New id=%d   this=%p", this->id, jsthis);

  return jsthis;
}


napi_value Init(napi_env env, napi_callback_info info)
{
  napi_status status;

  // Get JS this
  napi_value jsthis;
  status = napi_get_cb_info(env, info, NULL, NULL, &jsthis, NULL);
  ASSERT(env, status == napi_ok, "Invalid type");

  // Get native this
  my_module_instance_t *this;
  status = napi_unwrap(env, jsthis, (void**) &this);
  ASSERT(env, status == napi_ok, "Failed to get this");
  DEBUG("Init this=%p", this);

  // Calling C function 
  init(this);
  // ASSERT(env, this->seed != NULL, "Missing environment variable \"SEED\"");

  return NULL;
}


napi_value GetCount(napi_env env, napi_callback_info info)
{
  napi_status status;

  // Get JS this
  napi_value jsthis;
  status = napi_get_cb_info(env, info, NULL, NULL, &jsthis, NULL);
  ASSERT(env, status == napi_ok, "Invalid type");

  // Get native this
  my_module_instance_t *this;
  status = napi_unwrap(env, jsthis, (void**) &this);
  ASSERT(env, status == napi_ok, "Failed to get this");

  // Return jsnum from counter
  napi_value num;
  status = napi_create_double(env, this->counter, &num);
  ASSERT(env, status == napi_ok, "Failed to create number");
  return num;
}


napi_value RandomBytes(napi_env env, napi_callback_info info)
{
  napi_status status;

  // Get JS this and arguments
  size_t argc = 1;
  napi_value jsthis;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL);
  ASSERT(env, status == napi_ok, "Invalid type");

  // Get native this
  my_module_instance_t *this;
  status = napi_unwrap(env, jsthis, (void**) &this);
  ASSERT(env, status == napi_ok, "Failed to get this");

  // Get first argument
  uint32_t n;
  status = napi_get_value_uint32(env, argv[0], &n);
  ASSERT(env, status == napi_ok, "Failed to get n");

  // Calling C function 
  DEBUG("MyModule::GET %u RANDOM BYTES", n);
  buf_t* buf = randomBytes(this, n);

  // Return jsbuffer
  napi_value buffer;
  status = napi_create_buffer_copy(env, buf->len, buf->data, NULL, &buffer);

  ASSERT(env, status == napi_ok, "Failed to create buffer");
  return buffer;
}
