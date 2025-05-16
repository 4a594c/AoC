#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
  return (*(int*)a - *(int *)b);
}

int main(void) {
  FILE *fptr = fopen("input.txt", "r");
  if (fptr == NULL) {
    perror("Error opening file");
    return 1;
  }

  char buff[64];
  int size = 32;
  int *f = malloc(size * sizeof(int));
  int *s = malloc(size * sizeof(int));
  if (!f || !s) {
    perror("Memory allocation failed");
    free(f);
    free(s);
    fclose(fptr);
    return 1;
  }

  int index = 0;

  while (fgets(buff, sizeof(buff), fptr) != NULL) {
    char *ptr = strchr(buff, ' ');
    if (ptr == NULL) continue;
    *ptr = '\0';
    ptr++;

    f[index] = atoi(buff);
    s[index] = atoi(ptr);
    index++;

    if (index == size) {
      size *= 2;
      int *new_f = realloc(f, size * sizeof(int));
      int *new_s = realloc(s, size * sizeof(int));
      if (new_f == NULL || new_s == NULL) {
        free(f);
        free(s);
        fclose(fptr);
        return 1;
      }
      f = new_f;
      s = new_s;
    }
  }

  fclose(fptr);

  qsort(f, index, sizeof(int), compare);
  qsort(s, index, sizeof(int), compare);

  int sum = 0;

  for (int i = 0; i < index; i++) {
    if (f[i] > s[i]) sum += f[i] - s[i];
    else sum += s[i] - f[i];
  }

  printf("%d\n", sum);

  free(f);
  free(s);
  return 0;
}

