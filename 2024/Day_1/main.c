#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compare function for qsort
int compare(const void *a, const void *b) {
  return (*(int*)a - *(int *)b);
}

int main(void) {
  // Open the file
  FILE *fptr = fopen("input.txt", "r");
  if (fptr == NULL) {
    perror("Error opening file");
    return 1;
  }

  char buff[64]; // Buffer to store the input
  int size = 32; // Initial size of the pair
  int *f = malloc(size * sizeof(int));
  int *s = malloc(size * sizeof(int));
  if (!f || !s) {
    free(f);
    free(s);
    fclose(fptr);
    return 1;
  }

  int index = 0;

  while (fgets(buff, sizeof(buff), fptr)) {
    char *ptr = strchr(buff, ' ');
    if (ptr == NULL) continue;
    *ptr = '\0';
    ptr++;

    // Save to the pair
    f[index] = atoi(buff);
    s[index] = atoi(ptr);
    index++;

    // Check for resizing
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

  qsort(f, index, sizeof(int), compare);
  qsort(s, index, sizeof(int), compare);

  int sum = 0;

  // Calculate the puzzle
  for (int i = 0; i < index; i++) {
    if (f[i] > s[i]) sum += f[i] - s[i];
    else sum += s[i] - f[i];
  }

  // Output
  printf("%d\n", sum);

  // Cleanup
  fclose(fptr);
  free(f);
  free(s);
  return 0;
}

