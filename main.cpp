#include <QCoreApplication>
#include <QApplication>
#include "Huffman.h"
#include "gui.h"

void help()
{
    qDebug() << "";
    qDebug() << "                      AJUDA                                              ";
    qDebug() << "Para comprimir um arquivo, é necessário digitar 1º- '-c', 2º- 'nome do arquivo original'.";
    qDebug() << "Para comprimir um arquivo, ele não pode possuir o formato '.huff'.";
    qDebug() << "O arquivo de saída na compressão terá formato 'nome do arquivo original.huff' automaticamente.";
    qDebug() << "";
    qDebug() << "Para descomprimir um arquivo, ele deve possuir obrigatoriamente o formato '.huff',";
    qDebug() << "Para acessar a interface gráfica, basta digitar '--gui'.";
    qDebug() << "";
    qDebug() << "Se desejar ver essa mensagem novamente, digite '-h'.";
    qDebug() << "";
}

int main(int argc, char *argv[])
{
    Huffman huff;
    QCoreApplication a(argc, argv);
    if(argc == 3)
    {
        QString com(argv[1]), file(argv[2]), filef;
        filef = file.remove(0, file.size() - 4);
        if(!com.compare("-c"))
        {
            if(filef.compare("huff"))
            {
                file = argv[2];
                filef = file.remove(file.size() - 4, 4);
                file = argv[2];
                filef.append(".huff");
                huff.comprimir(file, filef);
            }
            else
            {
                qDebug() << "O arquivo de entrada não deve ser do formato '.huff'.";
                help();
                exit(1);
            }
        }
        else
        {
            if(com.compare("-gui")){
                QCoreApplication a(argc, argv);
                Gui w;
                w.show();
                return a.exec();
            }
            else{
                qDebug() << "O argumento inserido não é reconhecido pelo programa.";
                help();
                exit(1);
            }
        }
    }
    else if(argc == 2)
    {
        QString file(argv[1]), filef;
        filef = file.remove(0, file.length() - 4);
        file = argv[1];
        if(!file.compare("-h"))
            help();
        else if(!filef.compare("huff"))
            huff.descomprimir(file);
        else
        {
            qDebug() << "O arquivo não possui o formato '.huff'!.";
            help();
            exit(1);
        }
    }
    else
    {
        qDebug() << "Argumentos inválidos.";
        help();
        exit(1);
    }
    return 0;
}
