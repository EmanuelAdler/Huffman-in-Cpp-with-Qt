#ifndef TREE_H
#define TREE_H

#include <QString>
#include <QByteArray>
#include <QBitArray>
#include <QVector>
#include <QDebug>

#include "Node.h"

class tree
{
    Node *m_root;
public:
    tree();
    void append(Node *node); // cria a árvore
    QByteArray treeRepresentation(Node *node, QVector<QByteArray> &cod); // retorna a representação da árvore
    QByteArray treeRepresentation(QVector<QByteArray> &cod); // retorna a representação da árvore
    void buildDecTree(Node *node, QByteArray x); // monta a árvore para a descompressão
    Node *getTree(); // retorna a raíz da árvore
};

#endif // TREE_H
