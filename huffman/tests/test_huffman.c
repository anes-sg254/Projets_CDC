#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "tests.h"
#include "../lib/entropy.h"
#include "../lib/huffman_algo.h"

MU_TESTS_INIT

static int test_huffman_occurrences_storage() {
  FILE *input = fopen("test1", "r");
  char tempname[] = "tmp.XXXXXX";
  int fd_temp = mkstemp(tempname);
  FILE *output = fdopen(fd_temp, "w");
  int counts[ALPHABET_SIZE];
  int counts2[ALPHABET_SIZE];
  int i;
  for (i = 0; i < ALPHABET_SIZE; i++) {
    counts[i] = 0;
    counts2[i] = 0;
  }

  count_occurrences(input, counts);
  fclose(input);
  write_occurrences(counts, output);
  fclose(output);

  FILE *input2 = fopen(tempname, "r");
  read_occurrences(input2, counts2);
  char message[200];
  for (i = 0; i < ALPHABET_SIZE; i++) {
    sprintf(message, "Check counts equality (i=%d)", i);
    mu_assert_eq(message, counts2[i], counts[i]);
  }

  fclose(input2);
  unlink(tempname);
  return 0;
}

static int test_huffman_coding_test1() {
  FILE *input = fopen("test1", "r");
  int counts[ALPHABET_SIZE];
  huffman_tree_p forest[ALPHABET_SIZE];
  bitarray256_t *codes[ALPHABET_SIZE];
  int i;
  for (i = 0; i < ALPHABET_SIZE; i++) {
    counts[i] = 0;
    forest[i] = NULL;
    codes[i] = init_bitarray();
  }

  count_occurrences(input, counts);
  fclose(input);

  int nb_leaves = create_huffman_forest(counts, forest);
  mu_assert_eq("Number of leaves in Huffman forest", nb_leaves, 3);
  for (i = 0; i < nb_leaves; i++)
    mu_assert("Leaf defined in Huffman forest", forest[i]!=NULL);
  for (i = nb_leaves; i < ALPHABET_SIZE; i++)
    mu_assert("Cell should be empty after create_huffman_forest", forest[i] == NULL);
    
  sort_huffman_forest(forest, nb_leaves);
  
  huffman_tree_p huffman = build_huffman_tree(forest, nb_leaves);
  mu_assert("Huffman tree should not be NULL", huffman != NULL);
  mu_assert_eq("Nine symbols in test1", get_count(huffman), 9);
  mu_assert("a must either be at the root of the left or of the right subtree",
            get_symbol(left_huffman_tree(huffman)) == 'a' ||
            get_symbol(right_huffman_tree(huffman)) == 'a');

  create_huffman_coding(huffman, codes);

  mu_assert_eq("Code length for a", codes[(int)'a']->size, 1);
  mu_assert_eq("Code length for b", codes[(int)'b']->size, 2);
  mu_assert_eq("Code length for c", codes[(int)'c']->size, 2);
  mu_assert_eq("Code length for d", codes[(int)'d']->size, 0);

  for(i = 0; i < ALPHABET_SIZE; i++)
    delete_bitarray(codes[i]);
  delete_huffman_tree(huffman);

  return 0;
}


static int test_huffman_coding_decoding(char * file) {
  char tempout[] = "tmp.XXXXXX";
  char tempin[] = "tmp.XXXXXX";
  FILE *uncompressed, *input;

  mkstemp(tempout);
  mkstemp(tempin);

  huffman_coding(file, tempout, 0);

  huffman_decoding(tempout, tempin, 0);

  input = fopen(file, "r");
  uncompressed = fopen(tempin, "r");

  char c1, c2;
  int count = 0;
  char message[200];
  while (((c1 = fgetc(input)) != EOF) && ((c2 = fgetc(uncompressed)) != EOF)) {
    count++;
    sprintf(message, "Byte %d differ in file %s\n", count, file);
    mu_assert_eq(message, c1, c2);
  }
  sprintf(message, "c1 should be at EOF when testing file %s\n", file);
  mu_assert_eq(message, c1, EOF);
  sprintf(message, "c2 should not be at EOF yet when testing file %s\n", file);
  mu_assert(message, c2 != EOF);
  c2 = fgetc(uncompressed);
  sprintf(message, "c2 should now be at EOF when testing file %s\n", file);
  mu_assert_eq(message, c2, EOF);

  fclose(input);
  fclose(uncompressed);

  unlink(tempout);
  unlink(tempin);
  return 0;
}

static int test_huffman_coding_decoding_file1() {
  return test_huffman_coding_decoding("test1");
}
static int test_huffman_coding_decoding_file2() {
  return test_huffman_coding_decoding("test2");
}
static int test_huffman_coding_decoding_huffman() {
  return test_huffman_coding_decoding("test_huffman.c");
}


static int all_tests() {
   mu_run_test(test_huffman_occurrences_storage);
   mu_run_test(test_huffman_coding_test1);
   
   mu_run_test(test_huffman_coding_decoding_file1);
   mu_run_test(test_huffman_coding_decoding_file2);
   mu_run_test(test_huffman_coding_decoding_huffman);
   
   return mu_tests_success;
}
 
int main(int argc, char **argv) {
  int result = all_tests();
  if (result != 0) {
    fprintf(stderr, "TESTS FAILED!\n");
  }
  else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d (including %d assertions)\n", mu_tests_run, mu_assert_run);
  
  return result != 0;
}
