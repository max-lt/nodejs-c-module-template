#ifndef WRAP_MODULE_H_
#define WRAP_MODULE_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#define ENABLE_DEBUG 0

#if ENABLE_DEBUG
#define DEBUG(str, ...) \
  fprintf(stdout,"%s(%u): " str "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
  #define DEBUG( ... )
#endif

typedef struct {
  #if ENABLE_DEBUG
    int id;
  #endif
  unsigned char initialized;
  unsigned char counter;
  char *seed;
} my_module_instance_t;

/**
 * Buffer type
 */
typedef struct {
  size_t len;
  uint8_t *data;
} buf_t;

void new(my_module_instance_t *this);
void init(my_module_instance_t *this);
buf_t* randomBytes(my_module_instance_t *this, size_t n);

#endif // WRAP_MODULE_H_
