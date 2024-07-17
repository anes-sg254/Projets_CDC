#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#define PRINT_TREE_DEPTH 100
#define PRINT_TREE_WIDTH 500

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

typedef struct huffman_tree_s *huffman_tree_p;

/**
 * Representation of a Huffman tree
 */
struct huffman_tree_s {
  /** `left` and `right` are respectively the left and right subtrees of the tree. */
  huffman_tree_p left, right;
  /** The number of occurrences of the symbol (in a leaf) or the cumulative number
   * of occurrences of the symbols in the subtree */
  int nb_occurrences;
  /** The symbol (only in a leaf) */
  unsigned char symbol;
};


/**
 * Creates an empty Huffman Tree, with 0 occurrence.
 * 
 * @post isHuffmanLeaf() on the returned tree will correspond to True.
 */
huffman_tree_p create_empty_huffman_tree();

/**
 * Creates an Huffman Tree (actually a leaf) for the specified character
 * with the specified count (the number of occurrences of this character).
 * 
 * @post isHuffmanLeaf() on the returned tree will correspond to True
 * and the attributes `symbol` and `nb_occurrences` are respectively set
 * to `c` and `count`.
 */
huffman_tree_p create_huffman_tree(char c, int count);

/**
 * Deletes the Huffman Tree given in parameter and all its subtrees
 *
 * A Huffman tree created with `create_empty_huffman_tree` or with 
 * `create_huffman_tree` must be deleted with this function when the
 * tree is not used anymore.
 */
void delete_huffman_tree(huffman_tree_p);

/**
 * Predicate that tells if the Huffman tree in parameter is empty.
 * 
 * @return a value evaluated to true if the tree in parameter is empty
 */
int is_empty_huffman_tree(huffman_tree_p);

/**
 * Predicate that tells if the Huffman tree in parameter is a leaf.
 * 
 * @return a value evaluated to true if the tree in parameter is restricted to
 * a leaf (ie. `left_huffman_tree(tree)` and `right_huffman_tree(tree)` are empty).
 */
int is_huffman_leaf(huffman_tree_p tree);

/**
 * @return the left subtree of the tree in parameter
 * @pre ! is_empty_huffman_tree (tree)
 */
huffman_tree_p left_huffman_tree(huffman_tree_p tree);

/**
 * @return the left subtree of the tree in parameter
 * @pre ! is_empty_huffman_tree (tree)
 */
huffman_tree_p right_huffman_tree(huffman_tree_p);

/**
 * @return the count of the node in parameter
 * @pre ! is_empty_huffman_tree (tree)
 */
int get_count(huffman_tree_p tree);

/**
 * @return the symbol of the node in parameter
 * @pre ! is_empty_huffman_tree (tree)
 */
unsigned char get_symbol(huffman_tree_p tree);

/**
 * Sets the count of the node in parameter
 * @pre ! is_empty_huffman_tree (tree)
 */
void set_count(huffman_tree_p tree, int count);

/**
 * Sets the left subtree of `tree`
 */
void set_left_huffman_subtree(huffman_tree_p tree, huffman_tree_p left);

/**
 * Sets the right subtree of `tree`
 */
void set_right_huffman_subtree(huffman_tree_p tree, huffman_tree_p right);

/**
 * Sets the symbol of the node in parameter
 * @pre ! is_empty_huffman_tree (tree)
 */
void set_symbol(huffman_tree_p tree, unsigned char symbol);

/**
 * Compare two Huffman trees by the number of occurrences they represent.
 *
 * @return -1 if tree1 has more occurrences than tree2, 1, in the opposite case
 * and 0 if occurrences from both trees are equal
 */
int compare_huffman_trees(huffman_tree_p tree1, huffman_tree_p tree2);

/**
 * Prints a Huffman tree
 */
void print_huffman_tree(huffman_tree_p tree);



#endif
