#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H

template<typename T>
class Node {
public:
    Node<T> *parent = nullptr;
    Node<T> *leftChild = nullptr;
    Node<T> *rightChild = nullptr;
    bool isRed = false;
    T value;

    Node(bool isRed, T value) : isRed(isRed), value(value) {};
    Node(Node<T> *parent) : parent(parent) {};
    Node() = default;
};

template<typename T>
class RedBlackTree {
public:
    Node<T> *root = nullptr;

    RedBlackTree() = default;;

    void add(T value);

    void remove(T value);

    void print(Node<T> *node, int blackHeight);

private:
    void balanceInsertion(Node<T> *node);

    void balanceRemoving(Node<T> *node);

    Node<T> *getUncle(Node<T> *node);

    Node<T> *getGrandFather(Node<T> *node);

    bool isFatherLeftChild(Node<T> *node);

    void leftRotate(Node<T> *node);

    void rightRotate(Node<T> *node);

    void replaceNode(Node<T> *firstNode, Node<T> *secondNode);
};


#endif