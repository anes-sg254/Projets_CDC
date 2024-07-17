#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree.h"

huffman_tree_p create_empty_huffman_tree() {
  return calloc(1, sizeof(struct huffman_tree_s));
}

huffman_tree_p create_huffman_tree(char c, int count) {
  huffman_tree_p tree = create_empty_huffman_tree();
  set_symbol(tree, c);
  set_count(tree, count);
  return tree;
}

void delete_huffman_tree(huffman_tree_p tree) {
  if (! is_huffman_leaf(tree)) {
    delete_huffman_tree(left_huffman_tree(tree));
    delete_huffman_tree(right_huffman_tree(tree));
  }
  free(tree);
}

int is_empty_huffman_tree(huffman_tree_p tree) {
  return tree == NULL;
}

int is_huffman_leaf(huffman_tree_p tree) {
  return ! is_empty_huffman_tree(tree) && is_empty_huffman_tree(left_huffman_tree(tree)) &&
    is_empty_huffman_tree(right_huffman_tree(tree));
}

huffman_tree_p left_huffman_tree(huffman_tree_p tree) {
  return tree->left;
}

huffman_tree_p right_huffman_tree(huffman_tree_p tree) {
  return tree->right;
}

int get_count(huffman_tree_p tree) {
  return tree->nb_occurrences;
}

unsigned char get_symbol(huffman_tree_p tree) {
  return tree->symbol;
}

void set_count(huffman_tree_p tree, int count) {
  tree->nb_occurrences = count;
}

void set_left_huffman_subtree(huffman_tree_p tree, huffman_tree_p left) {
  tree->left = left;
}

void set_right_huffman_subtree(huffman_tree_p tree, huffman_tree_p right) {
  tree->right = right;
}

void set_symbol(huffman_tree_p tree, unsigned char symbol) {
  tree->symbol = symbol;
}


int compare_huffman_trees(huffman_tree_p tree1, huffman_tree_p tree2) {
  if (get_count(tree1) < get_count(tree2)) {
    return 1;
  } else if (get_count(tree1) > get_count(tree2)) {
    return -1;
  }
  return 0;
}

int _print_ht(huffman_tree_p tree, int depth) {
  if (is_empty_huffman_tree(tree)) return 0;

  _print_ht(right_huffman_tree(tree), depth + 1);
  
  for (int i = 0; i < depth; i++)
    printf("\t");
  if (is_huffman_leaf(tree))
    printf("[%d, %d]\n", get_count(tree), (int)get_symbol(tree));
  else
    printf("(%d)\n", get_count(tree));
    
  _print_ht(left_huffman_tree(tree), depth + 1);

  return 1;
}

void print_huffman_tree(huffman_tree_p tree) {
  if (! tree)
    printf("NULL\n");
  _print_ht(tree, 0);
}
