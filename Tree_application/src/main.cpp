#include "../include/bi_tree.h"
int main(void)
{
    Tree binTree = CreateTree();
    Read(binTree);
    TraversalTree(binTree->root);
    return 0;
}