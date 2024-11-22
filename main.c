#include <stdio.h>
#include <stdlib.h>


// Function to set html boilerplate
void set_html_boillerplate(FILE *html_file) {
  fprintf(html_file, "<!DOCTYPE html>\n");
  fprintf(html_file, "<html lang=\"en\">\n");
  fprintf(html_file, "<head>\n");
  fprintf(html_file, "\t<meta charset=\"UTF-8\">\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
  fprintf(html_file, "\t<meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">\n");
  fprintf(html_file, "\t<title>HTML 5 Boilerplate</title>\n");
  fprintf(html_file, "<head>\n");
  fprintf(html_file, "<body>\n");
}


int main(int argc, char *argv[]) {
  // Error handling for incorrect input
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <md_file_name> <html_file_name>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Assign pointers to file names from cmd line arguments
  char *md_file_name = argv[1];
  char *html_file_name = argv[2];

  // Read file
  FILE *file = fopen(md_file_name, "r");
  if (file == NULL) {
    perror("Unable to open markdown file");
    return EXIT_FAILURE;
  }

  // Create HTML file and append boilerplate
  FILE *html_file = fopen(html_file_name, "a");
  if (html_file == NULL) {
    perror("Unable to create HTML file");
    return EXIT_FAILURE;
  }

  // add boilerplate initially
  set_html_boillerplate(html_file);

  // add closing tags
  fprintf(html_file, "</body>\n");
  fprintf(html_file, "</html>\n");

  // Close files
  fclose(file);
  fclose(html_file);
  return EXIT_SUCCESS;
}
