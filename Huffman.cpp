#include "Huffman.h"

QString getNameOut(QString nameOut)
{
    QString nameFileOut;
    int i;
    for(i = nameOut.size()-1 ; i > 0 && nameOut.at(i)!= '/'; i--);
    if(i > 0 && nameOut.at(i) == '/') {
        i++;
    }
    for( ; i < nameOut.size() && nameOut.at(i) != '.'; i++) {
         nameFileOut.append(nameOut.at(i));
    }
    nameFileOut += ".huff";
    return nameFileOut;
}

QString getNameIn(QString nameIn)
{
    QString nameFileIn;
    int i;
    for(i = nameIn.size()-1 ; i > 0 && nameIn.at(i)!= '/'; i--);
    if(i > 0 && nameIn.at(i) == '/'){
        i++;
    }
    for(; i < nameIn.size(); i++){
        nameFileIn.append(nameIn.at(i));
    }
    return nameFileIn;
}

bool lessthan(Node *a, Node *b)
{
    if(a->frequency == b->frequency)
        return a->content < b->content;
    return a->frequency < b->frequency;
}

QByteArray Huffman::fileCodif(QByteArray data, QVector<QByteArray> codes){
    QByteArray codification;
    for(int i = 0; i < data.size(); ++i)
        codification.append(codes[(unsigned char)data.at(i)]);
    return codification;
}

void Huffman::generateFileCod(QByteArray &codification, QByteArray &fileData, QByteArray &treeSize){
	int lixo=0; // tamanho do lixo da codificação
	if(codification.size()%8 != 0)
		lixo = 8 - codification.size()%8; 
	for(int i = 0, k = 2, j = 0, g = 0; i < 16; ++i, --k)
    {
        if(i <= 2)
        {
            if(g + (1 << k) <= lixo)
            {
                j += (1 << (k + 5));
                g += (1 << k);
            }
            if(i == 2)
            {
                g = 0;
                k = 13;
            }
        }
        else
        {
            if(g + (1 << k) <= treeSize.size())
            {
                if(i <= 7)
                    j += (1 << (k - 8));
                else
                    j += (1 << k);
                g += (1 << k);
            }
            if(i == 7)
            {
                fileData.append(j);
                j = 0;
            }
            if(g == treeSize.size())
            {
                fileData.append(j);
                break;
            }
        }
    }

}

void Huffman::comprimir(QString string, QString string2)
{
        int count[256] = {0};
        QFile file(string);
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Ocorreu um erro ao tentar abrir o arquivo original.";
            exit(1);
        }
        QByteArray line, linha; // Variáveis com o conteúdo do arquivo original
        while (!file.atEnd())
        {
            line = file.readLine(1024);
            linha.append(line);
            for(int i = 0; i < line.size(); ++i)
                ++count[(unsigned char) line.at(i)];
        }
        int i, j;
        QList<Node*> lista; // vetor de nós.
        Node *node;
        for(j = 0; j < 256; ++j){ // monta o nosso vetor
            if(count[j])
            {
                node = new Node((unsigned char)j, 0, 0, count[j]);
                lista.append(node);
            }
        }
        tree arvore;
        while(lista.size() != 1) // monta a árvore
        {
            qSort(lista.begin(), lista.end(), lessthan);
            node = new Node(0, lista[0], lista[1], lista[0]->frequency + lista[1]->frequency);
            lista.removeAt(0);
            lista.removeAt(0);
            lista.append(node);
        }
        arvore.append(lista.at(0)); // aqui o nó principal vira a raiz da árvore
        QVector<QByteArray> cod(256);
        QByteArray xcv = arvore.treeRepresentation(cod);
        QByteArray codif; // será o bytearray com a codificação do arquivo
        QByteArray aux;
        int k;
        codif= fileCodif(linha, cod);
        for(i = 0, k = 7, j = 0; i < codif.size(); ++i, --k)
        {
            if(codif[i] == 49)
                j = j + (1 << k);
            if(k == 0 || i == codif.size() - 1)
            {
                aux.append(j);
                j = 0;
                k = 8;
            }
        }
        linha.clear();
        generateFileCod(codif, linha, xcv);
        linha.append(string.size()).append(string).append(xcv).append(aux);
        file.close(); // Fecha o arquivo original
        QFile newfile(string2); // Criação do arquivo comprimido
        if(!newfile.open(QIODevice::WriteOnly))
            {
                qDebug() << "Ocorreu um erro ao abrir o arquivo da compressão.";
                exit(1);
            }
        newfile.write(linha); // nesta linha ocorre a compressão.
        newfile.close(); // compressão concluída.
        qDebug() << "Arquivo comprimido com êxito.";
}

void Huffman::setBitArray(QBitArray &tamanho, QByteArray &codif)
{
    int i=0, j, k, l=0;
    unsigned char aux = codif[0];
    for(k = 0, j = 7; k < 24; ++k, --j)
    {
        if(i + (1 << j) <= aux)
        {
            i+= (1 << j);
            tamanho[k] = true;
            if(i == aux)
            {
                j = 8;
                i = 0;
                k = l*8 + 7;
                ++l;
                aux = codif[l];
            }
        }
    }
}

void Huffman::getSizes(QBitArray &bit, int &trash, int &treeSize, int &nameSize)
{
    for(int k = 0, i = 2; k < 24; ++k, --i)
    {
        if(k >= 0 && k < 3)
        {
            if(bit[k] == true)
                trash+= (1 << i);
            if(k == 2)
                i = 13;
        }
        else if(k >= 3 && k < 16)
        {
            if(bit[k] == true)
                treeSize+= (1 << i);
            if(k == 15)
                i = 8;
        }
        else
        {
            if(bit[k] == true)
                nameSize+= (1 << i);
        }
    }
}

void Huffman::bitArrayDec(QBitArray &bit, QByteArray &codif, int &count, int &k)
{
    int i, j=0;
    unsigned char aux;
    for(count = 0, i = 7, aux = codif[k]; count < bit.size(); --i, ++count)
    {
        if(j + (1 << i) <= aux)
        {
            j+= (1 << i);
            bit[count] = true;
        }
        if((count + 1)%8 == 0 && count != 0)
        {
            j = 0;
            i = 8;
            ++k;
            aux = codif[k];
        }
    }
}

void Huffman::createNewFile(QString &nome, tree &arvore, Node *node, QBitArray &bit, QByteArray &finalCode, int &trash)
{
    int i;
    QFile huff(nome); // Criação do novo arquivo descomprimido
    if(!huff.open(QIODevice::WriteOnly))
    {
        qDebug() << "O novo arquivo da descompressão não pôde ser aberto.";
        exit(1);
    };

    for(node = arvore.getTree(), i = 0; i < bit.size() - trash; ++i) // aqui eu escrevo o código do arquivo para a descompressão
    {
        if(node->left && node->right)
        {
            if(bit[i] == true)
                node = node->right;
            else
                node = node->left;
        }
        if(!node->left && !node->right)
        {
            finalCode.append(node->content);
            node = arvore.getTree();
        }
    }
    huff.write(finalCode); // Escreve no novo arquivo os dados
    huff.close(); // Fecha o arquivo
}
void Huffman::descomprimir(QString string)
{
    QFile fil(string);
    if(!fil.open(QIODevice::ReadOnly)){
        qDebug() << "O arquivo comprimido não pôde ser aberto.";
        exit(1);
    }
    QByteArray compCod, treeCod, finalCode;
    compCod = fil.readAll(); // Pegar os dados originais do arquivo comprimido
    QBitArray tam(24);//bit array com o tamanho do cabeçalho
    int trash=0, treeSize=0, nameSize=0, i, k;
    setBitArray(tam, compCod);
    getSizes(tam, trash, treeSize, nameSize);

    for(i = 3 + nameSize; i < 3 + nameSize + treeSize; ++i) // Recuperação da codificação da árvore
        treeCod.append(compCod[i]);

    tree decTree;//Árvore da descompressão
    Node *node = new Node; // Raíz da árvore da descompressão
    decTree.append(node);
    decTree.buildDecTree(node, treeCod); // Montagem da árvore da descompressão
    int count = compCod.size() - 3 - treeSize - nameSize; // Quantidade de bytes da codificação
    k = 3 + treeSize + nameSize;//Índice do primeiro bit da codificação do arquivo

    QBitArray dec(count*8); // Bit array com a decodificação do arquivo
    bitArrayDec(dec, compCod, count, k);//Monta o bit array com a decodificação do arquivo

    QString string2;//nome do novo arquivo
    compCod.remove(0, 3);
    compCod.remove(nameSize, compCod.size() - nameSize);
    string2=compCod;
    createNewFile(string2, decTree, node, dec, finalCode, trash); //Decodifica e cria o arquivo descompactado
    fil.close(); // Fim da descompressão
    qDebug() << "Arquivo descomprimido com êxito.";

}

