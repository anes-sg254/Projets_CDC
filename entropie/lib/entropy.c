#include "entropy.h"
#include <math.h>
/**
 * Counts the occurrences of all the characters in the file given as the first
 * parameter (the FILE pointer was obtained with the fopen function) and puts
 * all the counts in the counts array.  
 *
 * @param file: A file opened in read mode
 * @param counts: The counts array must be of size 256,
 * and all cells must initially be at 0.
 * @post the `counts` array will contain the number of occurrences of each symbol
 *       (ie. counts[i] contains the number of occurrences of symbol i).
 */
void count_occurrences(FILE *file, int counts[]) {
    int c;
    while ((c=fgetc(file))!=EOF)
    {
        counts[c]+=1;
    }
    
}
/**
 * Computes the entropy according to the symbol occurrences.
 *
 * @param counts: an array of 256 cells that contains the number of occurrences of each of the
 *        256 bytes.
 * @return a data structure containing the entropy information of the file.
 */
struct file_stat entropy(int counts[]){
  struct file_stat res;
  int i;
  int taille = 0;
  float somme = 0;
  for(i=0; i < 256; i++){
    if(counts[i] > 0){
      taille += counts[i];
      somme += counts[i] * log2f(counts[i]);
    }
  }
  res.size = taille;
  res.entropy = log2f(taille) - somme/(float)taille;

  return res;
}
