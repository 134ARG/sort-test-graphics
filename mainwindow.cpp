#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sorts.h"
#include "maximum_subarray.h"

#include <thread>

#include <iostream>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display_selection(QString str)
{
    ui->pushButton_selection->setText(str);
}


void MainWindow::display_shell(QString str)
{
    ui->pushButton_shell->setText(str);
}

void MainWindow::display_rate(QString str)
{
    ui->pushButton_rate->setText(str);
}

void MainWindow::display_insertion(QString str)
{
    ui->pushButton_insertion->setText(str);
}



void MainWindow::on_pushButton_2_clicked()
{
    //int array[10]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    //selection_sort(array, &array[9]);




    size_t size = size_t(ui->doubleSpinBox_size->value());
    ui->pushButton_shell->setText("");
    ui->pushButton_insertion->setText("");
    ui->pushButton_selection->setText("");
    ui->pushButton_rate->setText("");
    //compare_sorts(this, size);



    std::thread th1(compare_sorts, this, size);
    th1.detach();
    //td::cout << "father end" << std::endl;

}


void MainWindow::on_pushButton_clicked()
{
    std::vector<int> test_vec{-1, 2, 3, -4, -5};
    std::vector<int> result, result2;

    result = find_max_subvec(test_vec, 0, test_vec.size());



    std::cout << result[0] << " " << result[1] << std::endl;
}
