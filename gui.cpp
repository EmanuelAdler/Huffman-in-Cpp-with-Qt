#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
}

Gui::~Gui()
{
    delete ui;
}

void Gui::on_Btn_from_clicked()
{
    ui->Lne_from->setText(
                QFileDialog::getOpenFileName(
                    this,tr("Choose File"), "/home"));
}

void Gui::on_Btn_to_clicked()
{
    ui->Lne_to->setText(QFileDialog::getExistingDirectory(this,tr("Save File"), "/home"));
}

void Gui::on_Btn_huff_clicked()
{
    QString fileNameIn = ui->Lne_from->text();
    QString fileNameOut = getNameOut(fileNameIn);
    QString localOut = ui->Lne_to->text();

    if(fileNameIn.size() && localOut.size()){
        if(localOut.at(localOut.size()-1) != '/') localOut += '/';
        localOut += fileNameOut;
        comprimir(fileNameIn, localOut);
    }
    on_Btn_clear_clicked();
}

void Gui::on_Btn_clear_clicked()
{
    ui->Lne_from->setText("");
    ui->Lne_to->setText("");
}

void Gui::on_Btn_unhuff_clicked()
{
    QString fileNameIn = ui->Lne_from->text();
    QString localOut = ui->Lne_to->text();

    if(fileNameIn.size() && localOut.size()){
        if(localOut.at(localOut.size()-1) != '/') localOut += '/';
        descomprimir(getNameIn(fileNameIn), localOut);
    }
    on_Btn_clear_clicked();
}


