#include<stdio.h>
#include<stdlib.h>

#include "lib/entropy.h"

int main(int argc, char **argv) {

  if (argc <= 1) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(1);
  }
  FILE *file = fopen(argv[1], "r");
  int counts[256];
  
  for (int i = 0; i < 256; i++) {
    counts[i] = 0;
  }

  count_occurrences(file, counts);
  struct file_stat stat = entropy(counts);
  printf("Le fichier fait %d octets et a une entropie de %f bits par octet\n", stat.size, stat.entropy);

  int optimal = 100 - (stat.size*stat.entropy / 8 / stat.size * 100);
  printf("Au mieux un codage optimal améliorerait le stockage de ce fichier de %d%%\n", optimal);
  fclose(file);
  exit(0);
}
