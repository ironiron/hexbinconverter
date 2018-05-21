#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

QString text_number;
int number;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QValidator *validator = new QIntValidator(1, 2147483646, this);
    ui->dec_line->setValidator(validator);
    QRegularExpression mask("(?:(?:[0-9A-Fa-fxX]{1,2}[0-9A-Fa-f]{1,20}))");
    validator = new QRegularExpressionValidator(mask,this);
    ui->hex_line->setValidator(validator);
    mask.setPattern("^(?:(?:[0-1][b0-1][0-1]{1,32})*)$");
    validator = new QRegularExpressionValidator(mask,this);
    ui->bin_line->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bin_line_textEdited(const QString &arg1)
{
    if (ui->bin_line->text().contains("b"))
    {
        number= ui->bin_line->text().remove(0,2).toUInt(&bStatus,2);
    }
    else
    {
        number= ui->bin_line->text().toUInt(&bStatus,2);
    }
    text_number="0x"+QString::number(number,16);
    ui->hex_line->setText(text_number);
    text_number=QString::number(number,10);
    ui->dec_line->setText(text_number);
}

void MainWindow::on_dec_line_textEdited(const QString &arg1)
{
    number= ui->dec_line->text().toUInt();
    text_number="0x"+QString::number(number,16);
    ui->hex_line->setText(text_number);
    text_number="0b"+QString::number(number,2);
    ui->bin_line->setText(text_number);
}

void MainWindow::on_hex_line_textEdited(const QString &arg1)
{
    if (ui->hex_line->text().contains("x",Qt::CaseInsensitive))
    {
        number= ui->hex_line->text().remove(0,2).toUInt(&bStatus,16);
    }
    else
    {
        number= ui->hex_line->text().toUInt(&bStatus,16);
    }
    text_number="0b"+QString::number(number,2);
    ui->bin_line->setText(text_number);
    text_number=QString::number(number,10);
    ui->dec_line->setText(text_number);
}
