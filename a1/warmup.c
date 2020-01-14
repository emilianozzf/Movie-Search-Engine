/*
 * This function prints victory message three times.
 */
void PrintVictory1(){
  const int kTimes = 3;
  const char kMessage[] = "VICTORY!\n";
  for (int i = 0; i < kTimes; i++) {
    printf(kMessage);
  }
}

void PrintVictory2(){
  const char kMessage[] = "VICTORY!\nVICTORY!\nVICTORY!\n";
  printf(kMessage);
}
