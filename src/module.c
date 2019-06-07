#include <assert.h>
#include <malloc.h>
#include <stdlib.h>

#include "module.h"

void new(my_module_instance_t *this) {
  this->initialized = false;

  #if ENABLE_DEBUG
    static int nInstances = 0;
    this->id = ++nInstances;
  #endif
}


void init(my_module_instance_t *this) {
  this->initialized = true;

  // Get seed from environment
  this->seed = getenv("SEED");
  DEBUG("init::Init seed=\"%s\"", this->seed);
}


buf_t* randomBytes(my_module_instance_t *this, size_t n) {
  buf_t * buf = calloc(1, sizeof(buf_t));
  buf->len = n;
  buf->data = calloc(n, sizeof(*buf->data));

  // Increment counter
  this->counter++;

  return buf;
}
