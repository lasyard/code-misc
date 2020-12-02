#include <iostream>

#include "complete_btree.h"

using namespace std;

BtreeType testBtree(Node *root, int &depth)
{
    depth = 0;
    if (root == NULL)
        return FULL;
    BtreeType type, lType, rType;
    int lDepth, rDepth;
    type = NONE;
    lType = testBtree(root->left, lDepth);
    rType = testBtree(root->right, rDepth);
    if (lType == FULL) {
        if (rType == FULL) {
            if (lDepth == rDepth) {
                type = FULL;
            } else if (lDepth == rDepth + 1) {
                type = COMPLETE;
            }
        } else if (rType == COMPLETE && lDepth == rDepth) {
            type = COMPLETE;
        }
    } else if (lType == COMPLETE && rType == FULL && lDepth == rDepth + 1) {
        type = COMPLETE;
    }
    depth = (lDepth >= rDepth ? lDepth : rDepth) + 1;
    return type;
}

Node *makeBtree(int list[], int size, int current)
{
    if (current >= size || list[current] == 0)
        return NULL;
    Node *node = new Node;
    node->data = list[current];
    int left = current + current + 1;
    int right = current + current + 2;
    node->left = makeBtree(list, size, left);
    node->right = makeBtree(list, size, right);
    return node;
}

void destroyBtree(Node *root)
{
    if (root == NULL)
        return;
    destroyBtree(root->left);
    destroyBtree(root->right);
    delete root;
}
