/*
 * This function prints an empty rectangle of the specific width and height.
 */
void PrintRectangle(int width, int height) {
  const char kSymbol = '-';
  const char kSpace = ' ';
  for (int i = 0; i < width; i++) {
    printf("%c", kSymbol);
  }
  printf("\n");

  for (int i = 0; i < height - 2; i++) {
    printf("%c", kSymbol);
    for (int j = 0; j < width - 2; j++) {
      printf("%c", kSpace);
    }
    printf("%c", kSymbol);
    printf("\n");
  }

  for (int i = 0; i < width; i++) {
    printf("%c", kSymbol);
  }
  printf("\n");
}

/*
 * This function prints a fancy rectangle.
 */
void PrintFancyRectangle(int width, int height, char symbol, int fill) {
  const char kSpace = ' ';
  char fill_symbol;
  if (fill == 1) {
    fill_symbol = symbol;
  }
  else {
    fill_symbol = kSpace;
  }

  for (int i = 0; i < width; i++) {
    printf("%c" ,symbol);
  }
  printf("\n");

  for (int i = 0; i < height - 2; i++) {
    printf("%c", symbol);
    for (int j = 0; j < width - 2; j++) {
      printf("%c", fill_symbol);
    }
    printf("%c", symbol);
    printf("\n");
  }
  
  for (int i = 0; i < width; i++) {
    printf("%c", symbol);
  }
  printf("\n");
