#ifndef HUFF_H
#define HUFF_H

#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <algorithm>
#include <QVector>
#include <QBitArray>

#include "HTree.h"
#include "Node.h"

QString getNameOut(QString nameOut);
QString getNameIn(QString nameIn);
bool lessthan(Node *a, Node *b);

class Huffman
{
public:
    Huffman(){}
    void comprimir(QString string, QString string2); // Método para compressão do arquivo
    QByteArray fileCodif(QByteArray data, QVector<QByteArray> codes); //Método que gera um byte array com a codificação do arquivo
    void generateFileCod(QByteArray &codification, QByteArray &fileData, QByteArray &treeSize); //Método que gera a codificação do arquivo já com o lixo inserido
    void setBitArray(QBitArray &tamanho, QByteArray &codif);// Seta o bit array do cabeçalho para descompressão
    void getSizes(QBitArray &bit, int &trash, int &treeSize, int &nameSize);// Pega os tamanhos do lixo, da árvore e do nome do arquivo a partir do cabeçalho
    void bitArrayDec(QBitArray &bit, QByteArray &codif, int &count ,int &k);// Método que constrói o bit array para descompressão do arquivo
    void descomprimir(QString string); // Método para descompressão do arquivo
    void createNewFile(QString &nome, tree &arvore, Node *node, QBitArray &bit, QByteArray &finalCode, int &trash);// Método que cria o novo arquivo após a descompressão
};

#endif // HUFF_H
