#include <stdlib.h>

#include "huffman_algo.h"
#include "bitarray.h"
#include "entropy.h"
#include "huffman_tree.h" 
int create_huffman_forest(int occurrences[], huffman_tree_p  forest[]) {
  int cpt = 0 ;
  for(int i =0; i < ALPHABET_SIZE; i++ ){
    if(occurrences[i] > 0){
      huffman_tree_p feuille = create_huffman_tree(i, occurrences[i]);
      forest[cpt] = feuille ;
      cpt ++;
    }
  }
  return cpt;
}

int __compare_htrees(const void *ptree1, const void *ptree2) {
  huffman_tree_p tree1 = *((huffman_tree_p *)ptree1);
  huffman_tree_p tree2 = *((huffman_tree_p *)ptree2);
  return compare_huffman_trees(tree1, tree2);
}

void sort_huffman_forest(huffman_tree_p forest[], int size) {
  qsort(forest, size, sizeof(huffman_tree_p ), __compare_htrees);
}

min_nodes get_min_nodes(huffman_tree_p leaves[], int nb_leaves,
                        huffman_tree_p nodes[], int pos_nodes, int nb_nodes) {
  min_nodes min;
  huffman_tree_p least_nodes[2];
  min.nb_leaves = 0;
  min.nb_nodes = 0;
  
  for (int i = 0; i < 2; i++) {
    int cmp;
    if (nb_leaves > 0 && nb_nodes > 0) {
      cmp =compare_huffman_trees(leaves[nb_leaves-1], nodes[pos_nodes]);
    } else if (nb_leaves == 0) {
      cmp = -1;
    } else {
      cmp = 1;
    }
    if (cmp == -1) {
      least_nodes[i] = nodes[pos_nodes];
      pos_nodes++;
      nb_nodes--;
      min.nb_nodes++;
    } else {
      least_nodes[i] = leaves[nb_leaves-1];
      nb_leaves--;
      min.nb_leaves++;
    }
  }
  min.node1 = least_nodes[0];
  min.node2 = least_nodes[1];
  return min;
}

huffman_tree_p build_huffman_tree(huffman_tree_p leaves[], int size) {
  huffman_tree_p nodes[ALPHABET_SIZE] = {NULL}; /* Implements the queue of the nodes
                                                   built during the Huffman algorithm. */
  int nb_nodes = 0;             /* Number of nodes in the queue */
  int start_nodes = 0;          /* Starting position of the queue in `nodes` */
  int nb_leaves = size;

  /* À COMPLÉTER ET MODIFIER */
  while ((nb_nodes + nb_leaves) >= 2) {
    min_nodes min = get_min_nodes(leaves, nb_leaves, nodes, start_nodes, nb_nodes);
    huffman_tree_p h = create_huffman_tree(0, min.node1->nb_occurrences + min.node2->nb_occurrences);
    nodes[start_nodes + nb_nodes] = h;
    nodes[start_nodes + nb_nodes]->left = min.node1;
    nodes[start_nodes + nb_nodes]->right = min.node2;
    nb_nodes++;
    if (is_huffman_leaf(min.node1)) {
      nb_leaves--;
    } else {
      start_nodes++;
      nb_nodes--;
    }
    if (is_huffman_leaf(min.node2)) {
      nb_leaves--;
    } else {
      start_nodes++;
      nb_nodes--;
    }
  }
  return nodes[start_nodes];
}

void _create_huffman_coding(huffman_tree_p tree, bitarray256_t *codes[], bitarray256_t *bits) {
  if (is_huffman_leaf(tree)) {
    copy_bitarray(bits, codes[tree->symbol]);
    return;
  }

  bitarray256_t *left = init_bitarray(), *right = init_bitarray(); 
  copy_bitarray(bits, left);
  copy_bitarray(bits, right);
  
  left_shift_bit(left);
  left_shift_bit(right);

  set_bit(right, 0);
  _create_huffman_coding(tree->left, codes, left);
  _create_huffman_coding(tree->right, codes, right);

  delete_bitarray(left);
  delete_bitarray(right);
}

void create_huffman_coding(huffman_tree_p tree, bitarray256_t *codes[]) {
  bitarray256_t *bits = init_bitarray();
  _create_huffman_coding(tree, codes, bits);
  delete_bitarray(bits);
}

void write_occurrences(int counts[], FILE *output) {
  int i;
  int alphabet_size = 0;
  for (i = 0; i < ALPHABET_SIZE; i++) {
    if (counts[i] > 0)
      alphabet_size++;
  }
  fwrite(&alphabet_size, sizeof(int), 1, output);
  
  for (i = 0; i < ALPHABET_SIZE; i++) {
    unsigned char c = i;
    if (counts[i] > 0) {
      fwrite(&c, 1, 1, output);
      fwrite(&(counts[i]), sizeof(int), 1, output);
    }
  }
}

void read_occurrences(FILE *input, int counts[]) {
  int i;
  int alphabet_size;
  unsigned char c;
  fread(&alphabet_size, sizeof(int), 1, input);
  for (i = 0; i < alphabet_size; i++) {
    fread(&c, 1, 1, input);
    fread(&(counts[c]), sizeof(int), 1, input);
  }
}

void code_file(FILE *input, FILE *output, bitarray256_t *codes[]) { 
  int char_read;
  unsigned char remainder = 0;
  int size_remainder = 0;
  while ((char_read = fgetc(input)) != EOF) {
    int nb_bits_retrieve = codes[char_read]->size;
    int pos = nb_bits_retrieve;
    while (nb_bits_retrieve > 0) {
      int nb_bits = min(8 - size_remainder, nb_bits_retrieve);
      pos -= nb_bits;
      remainder = (remainder << nb_bits) | (get_bits(codes[char_read], pos, nb_bits));
      size_remainder += nb_bits;
      nb_bits_retrieve -= nb_bits;
      if (size_remainder == 8) {
        if (fputc(remainder, output) == EOF) {
          perror("Error writing compressed file");
          exit(3);
        }
        size_remainder = 0;
        remainder = 0;
      }
    }
  }
  if (size_remainder) {
    remainder <<= 8-size_remainder;
    if (fputc(remainder, output) == EOF) {
      perror("Error writing compressed file");
      exit(3);
    }
  }
    
}

void huffman_coding(char *in_filename, char *out_filename, int verbose) {
  int i;
  int counts[ALPHABET_SIZE];
  huffman_tree_p forest[ALPHABET_SIZE];
  bitarray256_t *codes[ALPHABET_SIZE];
  FILE *input = fopen(in_filename, "r");
  FILE *output = fopen(out_filename, "w");
  if (! input || ! output) {
    perror("Cannot open files");
    exit(4);
  }
  for (i = 0; i < ALPHABET_SIZE; i++){ 
    counts[i] = 0;
    forest[i] = NULL;
    codes[i] = init_bitarray(); 
  } 
  count_occurrences(input, counts);
  int nb_leaves = create_huffman_forest(counts, forest);
  sort_huffman_forest(forest, nb_leaves);
  
  huffman_tree_p huffman = build_huffman_tree(forest, nb_leaves);
  
  write_occurrences(counts, output);
  create_huffman_coding(huffman, codes);
  
  fclose(input);
  input = fopen(in_filename, "r");
  code_file(input, output, codes);
  
  /* Initialiser les tableaux counts, forest et codes.
   * Initialiser chaque case du tableau codes avec un 
   * bitarray vide (voir fonction `init_bitarray`) */
  fclose(input);
  fclose(output);
}

void huffman_decode_file(FILE *input, FILE *output, huffman_tree_p tree, int size){
  int c;
  int cpt = 0;
  huffman_tree_p ptr = tree;
  while(cpt < size && (c=fgetc(input)) != EOF)
    for (int b = 7 ; b >= 0; b--){
      int bit = (c>>b)&1;
      if(cpt < size) { 
        if(bit == 0){ 
          ptr = ptr->left;
        } else{ 
          ptr = ptr-> right; 
        }
        if(is_huffman_leaf(ptr)){
	  fwrite(&ptr->symbol, sizeof(unsigned char), 1, output);
	  cpt += 1;
          ptr = tree;
        }
      }
    }
}





void huffman_decoding(char *in_filename, char *out_filename, int verbose) {
  int i;
  int counts[ALPHABET_SIZE];
  huffman_tree_p forest[ALPHABET_SIZE];
  FILE *input = fopen(in_filename, "r");
  FILE *output = fopen(out_filename, "w");
  if (! input || ! output) {
    perror("Cannot open files");
    exit(4);
  }
  for (i = 0; i < ALPHABET_SIZE; i++){
    counts[i] = 0;
  }
  read_occurrences(input, counts);
  int nb_leaves = create_huffman_forest(counts, forest);
  sort_huffman_forest(forest, nb_leaves);
  huffman_tree_p tree = build_huffman_tree(forest, nb_leaves);
  if(verbose){
    print_huffman_tree(tree);
  }
  int tree_size = 0;
  for (i = 0; i < ALPHABET_SIZE; i++){
    tree_size += counts[i];
  }
  huffman_decode_file(input, output, tree, tree_size);
  delete_huffman_tree(tree);

  fclose(input);
  fclose(output);
}

