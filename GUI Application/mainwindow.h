#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_allButton_clicked();

    void on_poetryButton_clicked();

    void on_novelButton_clicked();

    void on_scienceButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
