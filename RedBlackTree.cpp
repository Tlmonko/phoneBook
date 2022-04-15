#include <iostream>
#include "RedBlackTree.h"

template<typename T, typename P>
void RedBlackTree<T, P>::add(T value) {
    if (!root) {
        root = new Node<T, P>(false, value);
        root->leftChild = new Node<T, P>(root);
        root->rightChild = new Node<T, P>(root);
        return;
    }
    Node<T, P> *node = root;
    Node<T, P> *newNode = new Node<T, P>(true, value);
    newNode->leftChild = new Node<T, P>(newNode);
    newNode->rightChild = new Node<T, P>(newNode);
    while (node->leftChild != nullptr && node->rightChild != nullptr) {
        if (node->value > value)
            node = node->leftChild;
        else
            node = node->rightChild;
    }
    newNode->parent = node->parent;
    if (node == node->parent->rightChild)
        node->parent->rightChild = newNode;
    else
        node->parent->leftChild = newNode;
    balanceInsertion(newNode);
}

template<typename T, typename P>
void RedBlackTree<T, P>::balanceInsertion(Node<T, P> *node) {
    if (node == this->root) {
        node->isRed = false;
        return;
    }

    while (node->parent && node->parent->isRed) {
        Node<T, P> *uncle = getUncle(node);
        Node<T, P> *grandFather = getGrandFather(node);
        if (isFatherLeftChild(node)) {
            if (uncle->isRed) {
                node->parent->isRed = false;
                uncle->isRed = false;
                grandFather->isRed = true;
                node = grandFather;
            } else {
                if (node == node->parent->rightChild) {
                    node = node->parent;
                    leftRotate(node->parent);
                }
                node->parent->isRed = false;
                grandFather->isRed = true;
                rightRotate(grandFather);
            }
        } else {
            if (uncle->isRed == true) {
                node->parent->isRed = false;
                uncle->isRed = false;
                grandFather->isRed = true;
                node = grandFather;
            } else {
                if (node == node->parent->leftChild) {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->isRed = false;
                grandFather->isRed = true;
                leftRotate(grandFather);
            }
        }
    }
    root->isRed = false;
}

template<typename T, typename P>
Node<T, P> *RedBlackTree<T, P>::getUncle(Node<T, P> *node) {
    if (isFatherLeftChild(node))
        return node->parent->parent->rightChild;
    return node->parent->parent->leftChild;
}

template<typename T, typename P>
bool RedBlackTree<T, P>::isFatherLeftChild(Node<T, P> *node) {
    return node->parent == node->parent->parent->leftChild;
}

template<typename T, typename P>
Node<T, P> *RedBlackTree<T, P>::getGrandFather(Node<T, P> *node) {
    return node->parent->parent;
}

template<typename T, typename P>
void RedBlackTree<T, P>::leftRotate(Node<T, P> *node) {
    Node<T, P> *pivot = node->rightChild;

    pivot->parent = node->parent;

    if (node->parent) {
        if (node == node->parent->leftChild)
            node->parent->leftChild = pivot;
        else
            node->parent->rightChild = pivot;
    } else {
        root = pivot;
    }

    if (pivot->leftChild)
        pivot->leftChild->parent = node;

    node->parent = pivot;
    node->rightChild = pivot->leftChild;
    pivot->leftChild = node;
}

template<typename T, typename P>
void RedBlackTree<T, P>::rightRotate(Node<T, P> *node) {
    Node<T, P> *pivot = node->leftChild;

    pivot->parent = node->parent;

    if (node->parent) {
        if (node == node->parent->leftChild)
            node->parent->leftChild = pivot;
        else
            node->parent->rightChild = pivot;
    } else {
        root = pivot;
    }

    if (pivot->rightChild)
        pivot->rightChild->parent = node;

    node->parent = pivot;
    node->leftChild = pivot->rightChild;
    pivot->rightChild = node;
}

template<typename T, typename P>
void RedBlackTree<T, P>::remove(T value) {
    Node<T, P> *node = root;
    Node<T, P> *balanceNode;
    while (node->value != value) {
        if (node->value < value)
            node = node->rightChild;
        else
            node = node->leftChild;
    }

    bool nodeOriginalIsRed = node->isRed;

    if (!node->rightChild->rightChild && !node->leftChild->leftChild) {
        if (node == root) {
            root = nullptr;
            return;
        } else {
            if (node == node->parent->leftChild)
                node->parent->leftChild = new Node<T, P>(node->parent);
            else
                node->parent->rightChild = new Node<T, P>(node->parent);
            return;
        }
    }

    if (node->rightChild->rightChild && !node->leftChild->leftChild) {
        balanceNode = node->rightChild;
        replaceNode(node, node->rightChild);
    } else if (!node->rightChild->rightChild && node->leftChild->leftChild) {
        balanceNode = node->leftChild;
        replaceNode(node, node->leftChild);
    } else {
        Node<T, P> *nextNode = node->rightChild;
        while (nextNode->leftChild->leftChild)
            nextNode = nextNode->leftChild;
        balanceNode = nextNode->rightChild;
        nodeOriginalIsRed = nextNode->isRed;
        if (nextNode->parent == node) {
            balanceNode->parent = nextNode;
        } else {
            replaceNode(nextNode, nextNode->rightChild);
            nextNode->rightChild = node->rightChild;
            nextNode->rightChild->parent = nextNode;
        }
        replaceNode(node, nextNode);
        nextNode->leftChild = node->leftChild;
        nextNode->leftChild->parent = nextNode;
        nextNode->isRed = node->isRed;
    }
    if (!nodeOriginalIsRed) {
        balanceRemoving(balanceNode);
    }
}

template<typename T, typename P>
void RedBlackTree<T, P>::balanceRemoving(Node<T, P> *node) {
    while (node->isRed == false && node != root) {
        if (node == node->parent->leftChild) {
            Node<T, P> *brother = node->parent->rightChild;
            if (brother->isRed) {
                brother->isRed = false;
                node->parent->isRed = true;
                leftRotate(node->parent);
                brother = node->parent->rightChild;
            }
            if (brother->leftChild->isRed == false && brother->rightChild->isRed == false) {
                brother->isRed = true;
                node = node->parent;
            } else {
                if (brother->rightChild->isRed == false) {
                    brother->leftChild->isRed = false;
                    brother->isRed = true;
                    rightRotate(brother);
                    brother = node->parent->rightChild;
                }
                brother->isRed = node->parent->isRed;
                node->parent->isRed = false;
                brother->rightChild->isRed = false;
                leftRotate(node->parent);
                node = root;
            }
        } else {
            Node<T, P> *brother = node->parent->leftChild;
            if (brother->isRed) {
                brother->isRed = false;
                node->parent->isRed = true;
                rightRotate(node->parent);
                brother = node->parent->leftChild;
            }
            if (brother->leftChild->isRed == false && brother->rightChild->isRed == false) {
                brother->isRed = true;
                node = node->parent;
            } else {
                if (brother->leftChild->isRed == false) {
                    brother->rightChild->isRed = false;
                    brother->isRed = true;
                    leftRotate(brother);
                    brother = node->parent->leftChild;
                }
                brother->isRed = node->parent->isRed;
                node->parent->isRed = false;
                brother->leftChild->isRed = false;
                rightRotate(node->parent);
                node = root;
            }
        }
    }
    root->isRed = false;
}

template<typename T, typename P>
void RedBlackTree<T, P>::replaceNode(Node<T, P> *firstNode, Node<T, P> *secondNode) {
    if (firstNode->parent == nullptr) {
        root = secondNode;
    } else if (firstNode == firstNode->parent->leftChild) {
        firstNode->parent->leftChild = secondNode;
    } else {
        firstNode->parent->rightChild = secondNode;
    }
    secondNode->parent = firstNode->parent;
}

template<typename T, typename P>
void RedBlackTree<T, P>::print(Node<T, P> *node, int blackHeight) {
    if (!node->leftChild && !node->rightChild)
        return;
    int blackHeightAddition = 0;
    if (node->isRed == false)
        blackHeightAddition = 1;
    print(node->leftChild, blackHeight + blackHeightAddition);
    std::cout << node->value << " (" << blackHeight + blackHeightAddition << ')' << std::endl;
    print(node->rightChild, blackHeight + blackHeightAddition);
}
