#include "stash.h"
#include "resource.h"

void int_to_str(unsigned int nb, char *buffer)
{
  if (nb == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    return;
  }
  if (nb == UINT_MAX) {
    char *p = "inf";
    while (*p) {
      *buffer++ = *p++;
    }
    *buffer = '\0';
    return;
  }

  int i = 0;
  while (nb != 0) {
    buffer[i++] = (nb%10) + '0';
    nb /= 10;
  }
  buffer[i] = '\0';

  int start = 0;
  int end = i-1;
  while (start<end) {
    char tmp = buffer[start];
    buffer[start] = buffer[end];
    buffer[end] = tmp;
    start++; 
    end--;
  }
}

void stash_to_string(const struct stash_t* stash, char* buffer)
{
  int j = 0;
  for (int i = 0; i < NUM_RESOURCES+1; i++) {
    const char *resource_name = resource_to_short_string((enum resource_t)i);
    while (*resource_name) {
      if (j == MAX_STASH_STRING_LENGTH-1) break;
      buffer[j++] = *resource_name++;
    }
    if (j == MAX_STASH_STRING_LENGTH-1) break;
    buffer[j++] = ':';

    char str_nb_resource[10]; 
    int_to_str(stash->r[i], str_nb_resource);
    char *p = str_nb_resource;
    while (*p) {
      if (j == MAX_STASH_STRING_LENGTH-1) break;
      buffer[j++] = *p++;
    }
    if (j == MAX_STASH_STRING_LENGTH-1) break;
    buffer[j++] = ' ';
  }
  buffer[j] = '\0';
}

struct stash_t stash_add(const struct stash_t* a, const struct stash_t* b)
{
  struct stash_t c;
  for (int i = 0; i < NUM_RESOURCES+1; i++) {
    c.r[i] = a->r[i] + b->r[i];
  }
  return c;
}

struct stash_t stash_sub(const struct stash_t* a, const struct stash_t* b)
{
  struct stash_t c;
  for (int i = 0; i < NUM_RESOURCES+1; i++) {
    c.r[i] = (a->r[i] >= b->r[i]) ? (a->r[i] - b->r[i]) : 0;
  }
  return c;
}

int stash_contains(const struct stash_t* a, const struct stash_t* b)
{
  for (int i = 0; i < NUM_RESOURCES+1; i++) {
    if (a->r[i] < b->r[i]) return 0;
  }
  return 1;
}
