#include "mainwindow.h"
#include "ui_mainwindow.h"


QString text_number;
uint number;
int number_of_zeros;
QString zeros;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("HexBinConverter");

    QValidator *validator = new QIntValidator(0, 2147483646, this);
    ui->dec_line->setValidator(validator);
    QRegularExpression mask("(?:(?:[0-9A-Fa-fxX]{1,2}[0-9A-Fa-f]{1,8}))");
    validator = new QRegularExpressionValidator(mask,this);
    ui->hex_line->setValidator(validator);
    mask.setPattern("(?:(?:[0-1bB]{1,2}[0-1]{1,32}))");
    validator = new QRegularExpressionValidator(mask,this);
    ui->bin_line->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bin_line_textEdited(const QString &arg1)
{
    switch (ui->bin_line->text().indexOf("b",0,Qt::CaseInsensitive))
    {
    case 0:
        ui->bin_line->setText(ui->bin_line->text().prepend("0"));
        // WITHOUT break;
    case 1:
        number= ui->bin_line->text().remove(0,2).toUInt(&bStatus,2);
        number_of_zeros=(ui->bin_line->text().indexOf('1')-2)/4;
        if(ui->bin_line->text().contains("1b",Qt::CaseInsensitive))
        {
            ui->bin_line->setText(ui->bin_line->text().replace(0,1,"0"));
        }
        break;
    case -1://b not found
        number= ui->bin_line->text().toUInt(&bStatus,2);
        number_of_zeros=ui->bin_line->text().indexOf('1')/4;
        break;
    }
    zeros="";
    for(int k=0;k<number_of_zeros;k++)
    {
        zeros=zeros+"0";
    }
    text_number="0x"+zeros+QString::number(number,16).toUpper();
    ui->hex_line->setText(text_number);
    text_number=QString::number(number,10);
    ui->dec_line->setText(text_number);
}

void MainWindow::on_dec_line_textEdited(const QString &arg1)
{
    number= ui->dec_line->text().toUInt();
    text_number=QString::number(number,2);
    switch ((text_number.length())%4) {
    case 1:
        zeros="000";
        break;
    case 2:
        zeros="00";
        break;
    case 3:
        zeros="0";
        break;
    default:
        zeros="";
        break;
    }
    text_number="0b"+zeros+text_number;
    ui->bin_line->setText(text_number);
    text_number="0x"+QString::number(number,16).toUpper();
    ui->hex_line->setText(text_number);
}

void MainWindow::on_hex_line_textEdited(const QString &arg1)
{
    switch (ui->hex_line->text().indexOf("x",0,Qt::CaseInsensitive))
    {
    case 0:
        ui->hex_line->setText(ui->hex_line->text().prepend("0"));
        // WITHOUT break;
    case 1:
        number= ui->hex_line->text().remove(0,2).toUInt(&bStatus,16);
        number_of_zeros=ui->hex_line->text().indexOf(QRegExp("0[1-9a-fA-F]"))-2;
        break;
    case -1://x not found
        number= ui->hex_line->text().toUInt(&bStatus,16);
        number_of_zeros=ui->hex_line->text().indexOf(QRegExp("0[1-9a-fA-F]"));
        break;
    }
    zeros="";
    for(int k=0;k<=number_of_zeros;k++)
    {
        zeros=zeros+"0000";
    }
    text_number=QString::number(number,2);
    switch (text_number.length()%4) {
    case 1:
        zeros=zeros+"000";
        break;
    case 2:
        zeros=zeros+"00";
        break;
    case 3:
        zeros=zeros+"0";
        break;
    default:
        break;
    }
    text_number="0b"+zeros+text_number;
    ui->bin_line->setText(text_number);
    text_number=QString::number(number,10);
    ui->dec_line->setText(text_number);
}
