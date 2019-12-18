#include <string.h>

int strcmp(const char *a, const char *b) {
  while (*a != '\0' && *b != '\0') {
    if (*a < *b) {
      return -1;
    } else if (*b < *a) {
      return 1;
    }
    a++;
    b++;
  }

  if (*a != *b) {
    return *a == '\0' ? -1 : 1;
  }

  return 0;
}
