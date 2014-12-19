#ifndef GUI_H
#define GUI_H

#include <QFileDialog>
#include <QMainWindow>
#include "Huffman.h"

namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();


private slots:
    void on_Btn_from_clicked();

    void on_Btn_to_clicked();

    void on_Btn_huff_clicked();

    void on_Btn_clear_clicked();

    void on_Btn_unhuff_clicked();

private:
    Ui::Gui *ui;
};

#endif // GUI_H
