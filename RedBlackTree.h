#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H

template<typename T, typename P>
class Node {
public:
    Node<T, P> *parent = nullptr;
    Node<T, P> *leftChild = nullptr;
    Node<T, P> *rightChild = nullptr;
    bool isRed = false;
    T value;
    P payload;

    Node(bool isRed, T value, P payload) : isRed(isRed), value(value), payload(payload) {};

    Node(Node<T, P> *parent) : parent(parent) {};

    Node() = default;
};

template<typename T, typename P>
class RedBlackTree {
public:
    Node<T, P> *root = nullptr;

    RedBlackTree() = default;;

    void add(T value, P payload);

    void remove(T value);

private:
    void balanceInsertion(Node<T, P> *node);

    void balanceRemoving(Node<T, P> *node);

    Node<T, P> *getUncle(Node<T, P> *node);

    Node<T, P> *getGrandFather(Node<T, P> *node);

    bool isFatherLeftChild(Node<T, P> *node);

    void leftRotate(Node<T, P> *node);

    void rightRotate(Node<T, P> *node);

    void replaceNode(Node<T, P> *firstNode, Node<T, P> *secondNode);
};


#endif