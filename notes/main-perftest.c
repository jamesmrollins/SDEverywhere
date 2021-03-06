#include <time.h>
#include "sde.h"

int main(int argc, char** argv) {
  // TODO make the input buffer size dynamic
  char inputs[1000];
  // Try to read input from a file named in the argument.
  if (argc > 1) {
    FILE* instream = fopen(argv[1], "r");
    if (instream && fgets(inputs, sizeof inputs, instream) != NULL) {
      fclose(instream);
      size_t len = strlen(inputs);
      if (inputs[len-1] == '\n') {
        inputs[len-1] = '\0';
      }
    }
  }
  else {
    *inputs = '\0';
  }

struct timespec startTime, finishTime;
clock_gettime(CLOCK_MONOTONIC, &startTime);

  // Run the model and get output for all time steps.
  char* outputs = run_model(inputs);

clock_gettime(CLOCK_MONOTONIC, &finishTime);
double runtime = 1000.0 * finishTime.tv_sec + 1e-6 * finishTime.tv_nsec -
  (1000.0 * startTime.tv_sec + 1e-6 * startTime.tv_nsec);
fprintf(stderr, "%g ms\n", runtime);

  // Write a header for output data.
  printf("%s\n", getHeader());
  // Write tab-delimited output data, one line per output time step.
  if (outputs != NULL) {
    char* p = outputs;
    while (*p) {
      char* line = p;
      for (size_t i = 0; i < numOutputs; i++) {
        if (i > 0) {
          p++;
        }
        while (*p && *p != '\t') {
          p++;
        }
      }
      *p++ = '\0';
      printf("%s\n", line);
    }
  }
  finish();
}
