#include "../include/bi_tree.h"
int main(void)
{
    
    Tree binTree = CreateTree();
    Read(binTree);
    TraversalTree(binTree->root);
    cout << "Done." << endl;
    return 0;
}