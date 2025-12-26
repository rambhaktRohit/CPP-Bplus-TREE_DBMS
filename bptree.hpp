// =============================================================
// FILE: bptree.hpp
// PURPOSE: Defines the blueprint (structure) of the B+ Tree
// =============================================================

#ifndef BPTREE_HPP
#define BPTREE_HPP

#include <vector>
#include <iostream>
using namespace std;

// NODE STRUCTURE
// Represents a single block in our B+ Tree.
struct Node
{
    bool isLeaf;             // true if this node holds actual data links
    vector<int> keys;        // The IDs stored in this node
    vector<Node *> children; // Pointers to child nodes (if not a leaf)

    Node(bool leaf); // Constructor
};

// TREE CLASS
// The main engine that organizes IDs for fast searching.
class BTree
{
    Node *root; // Pointer to the top of the tree
    int t;      // Minimum degree (how "fat" the nodes are)

public:
    BTree(int _t);      // Constructor
    void insert(int k); // Add a new ID to the index
    bool search(int k); // Check if an ID exists
    void display();     // Visualizes the tree levels

private:
    // Internal helper functions (users don't need to see these)
    void insertNonFull(Node *x, int k);
    void splitChild(Node *x, int i, Node *y);
    void display(Node *cursor, int level);
};

#endif