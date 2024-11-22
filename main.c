#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  char *md_file_name = argv[1];
  char *html_file_name = argv[2];
  printf("%c", *md_file_name);
  return EXIT_SUCCESS;
}
