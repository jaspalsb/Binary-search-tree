

#ifndef __HEADER_H
#define __HEADER_H

# ifndef TYPE
# define TYPE      void*
# endif

int compare(TYPE left, TYPE right);

void print_type(TYPE curval);


struct BSTree;

void initBSTree(struct BSTree *tree);

struct BSTree *newBSTree();

void clearBSTree(struct BSTree *tree);

void deleteBSTree(struct BSTree *tree);

int  isEmptyBSTree(struct BSTree *tree);
int     sizeBSTree(struct BSTree *tree);

void     addBSTree(struct BSTree *tree, TYPE val);
int containsBSTree(struct BSTree *tree, TYPE val);
void  removeBSTree(struct BSTree *tree, TYPE val);
void printTree(struct BSTree *tree);
# endif
