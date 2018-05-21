#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bin_line_textEdited(const QString &arg1);

    void on_dec_line_textEdited(const QString &arg1);

    void on_hex_line_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
        bool bStatus = false;
};

#endif // MAINWINDOW_H
