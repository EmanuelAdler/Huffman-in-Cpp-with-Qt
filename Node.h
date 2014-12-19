#ifndef NODE_H
#define NODE_H

#include <QByteArray>

class Node // A classe dos nós que são fundamentais em todo o processo
{
public:
    Node *left;
    Node *right;
    unsigned char content;
    int frequency;
    QByteArray code;
    Node()
    {
        this->content = 0;
        this->left = 0;
        this->right = 0;
        this->frequency = 0;
    }
    Node(unsigned char content, Node* left, Node* right, int frequency){
        this->content = content;
        this->left = left;
        this->right = right;
        this->frequency = frequency;
    }
};

#endif // NODE_H
