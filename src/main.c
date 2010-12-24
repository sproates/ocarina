#include <stdio.h>

void print_usage(void);
int run_script(const char * filename);

int main(int argc, const char ** argv) {
  printf("Ocarina\n");
  if(argc < 2) {
    print_usage();
    return 1;
  } else {
    return run_script(argv[1]);
  }
}

void print_usage(void) {
  printf("Usage: ocarina.exe <filename>\n");
}

int run_script(const char * filename) {
  FILE * script_file;
  int closure;

  script_file = fopen(filename, "r");
  if(NULL == script_file) {
    printf("Could not open %s for reading.\n", filename);
    return 1;
  }
  printf("Running on %s...\n", filename);
  closure = fclose(script_file);
  if(EOF == closure) {
    printf("Oddness. Failed to close file handle on %s.\n", filename);
    return 1;
  }
  return 0;
}