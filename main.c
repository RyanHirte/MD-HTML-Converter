#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


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

// Function to remove newline character
void remove_newline(char *buffer) {
  for (int i = 0; buffer[i] != '\0'; i++) {
    if (buffer[i] == '\n') {
      buffer[i] = '\0';
      break;
    }
  }
}

// Function to mimic strip() 
void strip_white_space(char *str) {
  char *end;

  // Trim leading space
  while (isspace((unsigned char)*str)) {
    str++;
  }

  // Return if the line is completely empty
  if (*str == 0) {
    return;
  }

  // Trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end)) {
    end--;
  }

  // Write new null terminator
  *(end + 1) = 0;
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
  FILE *md_file = fopen(md_file_name, "r");
  if (md_file == NULL) {
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

  // Read the md line by line and determine syntax for html
  char buffer[1024];
  while (fgets(buffer, sizeof(buffer), md_file)) {

    // Remove newline character
    remove_newline(buffer);

    // Strip leading whitespace
    strip_white_space(buffer);

    // Skip empty lines
    if (strlen(buffer) == 0) {
      continue;
    }
    // Check for h3, '###' in markdown
    if (buffer[0] == '#' && buffer[1] == '#' && buffer[2] == '#') {
      fprintf(html_file, "\t<h3>%s<h3>\n", buffer + 4);
    }
    // Check for h2, '##' in markdown
    else if (buffer[0] == '#' && buffer[1] == '#') {
      fprintf(html_file, "\t<h2>%s<h2>\n", buffer + 3);
    }
    // Check for h1, '#' in markdown
    else if (buffer[0] == '#') {
      fprintf(html_file, "\t<h1>%s<h1>\n", buffer + 2);
    }
    // else, its a <p>
    else {
      fprintf(html_file, "\t<p>%s<p>\n", buffer);
    }
    
  }

  // add closing tags
  fprintf(html_file, "</body>\n");
  fprintf(html_file, "</html>\n");

  // Close files
  fclose(md_file);
  fclose(html_file);
  return EXIT_SUCCESS;
}
