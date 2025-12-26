// =============================================================
// FILE: bptree.cpp
// PURPOSE: Implements the complex logic for the B+ Tree
// =============================================================

#include "bptree.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

// Constructor for Node
Node::Node(bool leaf)
{
    isLeaf = leaf;
}

// Constructor for Tree
BTree::BTree(int _t)
{
    root = NULL;
    t = _t;
}

// SEARCH FUNCTION
// Traverses from Top (Root) to Bottom (Leaf) to find an ID.
bool BTree::search(int k)
{
    if (root == NULL)
        return false;

    Node *current = root;

    // 1. Travel down the internal nodes
    while (current->isLeaf == false)
    {
        int i = 0;
        // Find which child path to take
        while (i < current->keys.size() && k >= current->keys[i])
        {
            i++;
        }
        current = current->children[i];
    }

    // 2. We reached a leaf (bottom). Check if ID is here.
    for (int i = 0; i < current->keys.size(); i++)
    {
        if (current->keys[i] == k)
        {
            return true; // Found it!
        }
    }
    return false; // Not found
}

// INSERT FUNCTION
// Adds an ID and handles "Splitting" if a node gets too full.
void BTree::insert(int k)
{
    if (root == NULL)
    {
        // Case 1: Tree is empty. Create the first node.
        root = new Node(true);
        root->keys.push_back(k);
    }
    else
    {
        // Case 2: Root is full. Needs to grow height.
        if (root->keys.size() == 2 * t - 1)
        {
            Node *s = new Node(false);
            s->children.push_back(root);
            splitChild(s, 0, root);

            // Decide which of the two new children gets the key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            insertNonFull(s->children[i], k);

            root = s;
        }
        else
        {
            // Case 3: Root has space. Just insert.
            insertNonFull(root, k);
        }
    }
}

// HELPER: Insert into a node that isn't full yet
void BTree::insertNonFull(Node *x, int k)
{
    int i = x->keys.size() - 1;

    if (x->isLeaf)
    {
        // Leaf Node: Find correct spot and slide others over
        x->keys.push_back(0);
        while (i >= 0 && x->keys[i] > k)
        {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
    }
    else
    {
        // Internal Node: Find which child to go deeper into
        while (i >= 0 && x->keys[i] > k)
            i--;

        // If that child is full, split it first
        if (x->children[i + 1]->keys.size() == 2 * t - 1)
        {
            splitChild(x, i + 1, x->children[i + 1]);
            if (x->keys[i + 1] < k)
                i++;
        }
        insertNonFull(x->children[i + 1], k);
    }
}

// HELPER: Splits a full node into two
void BTree::splitChild(Node *x, int i, Node *y)
{
    Node *z = new Node(y->isLeaf);

    // Move half the keys to the new node 'z'
    for (int j = 0; j < t - 1; j++)
        z->keys.push_back(y->keys[j + t]);

    // If it has children, move half of them too
    if (!y->isLeaf)
    {
        for (int j = 0; j < t; j++)
            z->children.push_back(y->children[j + t]);
    }

    // Resize the old node 'y'
    y->keys.resize(t - 1);
    if (!y->isLeaf)
        y->children.resize(t);

    // Link 'z' to the parent
    x->children.insert(x->children.begin() + i + 1, z);
    x->keys.insert(x->keys.begin() + i, y->keys[t - 1]);
}

// DISPLAY FUNCTION
// Prints the tree visually so we can verify the structure
void BTree::display()
{
    if (root != NULL)
        display(root, 0);
}

void BTree::display(Node *cursor, int level)
{
    cout << "Level " << level << ": [ ";
    for (int x : cursor->keys)
    {
        cout << x << " ";
    }
    cout << "]" << endl;

    if (!cursor->isLeaf)
    {
        for (Node *child : cursor->children)
        {
            display(child, level + 1);
        }
    }
}