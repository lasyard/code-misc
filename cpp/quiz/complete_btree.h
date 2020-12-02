#ifndef _COMPLETE_BTREE_H_
#define _COMPLETE_BTREE_H_

struct Node {
    int data;
    Node *left, *right;
};

enum BtreeType { NONE, COMPLETE, FULL };

__declspec(dllexport) BtreeType testBtree(Node *root, int &depth);

inline bool isFullBtree(Node *root, int &depth)
{
    return testBtree(root, depth) == FULL;
}

inline bool isCompleteBtree(Node *root, int &depth)
{
    BtreeType type = testBtree(root, depth);
    return type == COMPLETE || type == FULL;
}

__declspec(dllexport) Node *makeBtree(int list[], int size, int current);
__declspec(dllexport) void destroyBtree(Node *root);

#endif
