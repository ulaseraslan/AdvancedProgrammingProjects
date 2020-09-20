#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QVector>
#include <QDebug>


//ulaseraslan 20.12.19 CS204 Sabanci University HW9

struct book {

    QString bookname;               //Book struct for each book (bookname,writer,kind,publisher and stock information).
    QString writer;
    QString kind;
    QString publisher;
    QString stock;
};

static QVector<book>bookList;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)


{


    ui->setupUi(this);

    QFile file("/Users/ulaseraslan/Desktop/ulaseraslan_hw9/booklist.txt");          //Program opens the given txt file (Usage of path is important)
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(nullptr, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {                            //Program reads the file line by line and split each word until ","
        QString line = in.readLine();
        QStringList fields = line.split(", ");

        book booky;

        booky.bookname = fields[0];                     //Each splitted parts assigned to newly created book object.
        booky.writer = fields[1];
        booky.kind = fields[2];
        booky.publisher = fields[3];
        booky.stock = fields[4];

        bookList.push_back(booky);                      //Created book object pushed to the booklist vector.

    }

    file.close();

    ui->tableWidget->setColumnCount(5);                 // Set colum 5 (Book,Writer,Kind,Publisher,Stock)

}

MainWindow::~MainWindow()
{        
    delete ui;
}



void MainWindow::on_allButton_clicked() {               //If "all" radio button is clicked then all books in the vector are displayed.

        int row_count=0;
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);


        for (int i=0; i<bookList.size(); i++) {

            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

            ui->tableWidget->setItem(row_count,0,new QTableWidgetItem(bookList[i].bookname));
            ui->tableWidget->setItem(row_count,1,new QTableWidgetItem(bookList[i].writer));
            ui->tableWidget->setItem(row_count,2,new QTableWidgetItem(bookList[i].kind));
            ui->tableWidget->setItem(row_count,3,new QTableWidgetItem(bookList[i].publisher));
            ui->tableWidget->setItem(row_count,4,new QTableWidgetItem(bookList[i].stock));

             row_count++;
        }

}



void MainWindow::on_poetryButton_clicked(){         //If "Poetry" radio button is clicked then all books in the vector are displayed.

    int row_count=0;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (int i=0; i<bookList.size();i++) {

        if (bookList[i].kind == "Poetry") {

            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

            ui->tableWidget->setItem(row_count,0,new QTableWidgetItem(bookList[i].bookname));
            ui->tableWidget->setItem(row_count,1,new QTableWidgetItem(bookList[i].writer));
            ui->tableWidget->setItem(row_count,2,new QTableWidgetItem(bookList[i].kind));
            ui->tableWidget->setItem(row_count,3,new QTableWidgetItem(bookList[i].publisher));
            ui->tableWidget->setItem(row_count,4,new QTableWidgetItem(bookList[i].stock));

             row_count++;


        }

    }


}

void MainWindow::on_novelButton_clicked() {     //If "Novel" radio button is clicked then all books in the vector are displayed.

    int row_count=0;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (int i=0; i<bookList.size();i++) {

        if (bookList[i].kind == "Novel") {

            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

            ui->tableWidget->setItem(row_count,0,new QTableWidgetItem(bookList[i].bookname));
            ui->tableWidget->setItem(row_count,1,new QTableWidgetItem(bookList[i].writer));
            ui->tableWidget->setItem(row_count,2,new QTableWidgetItem(bookList[i].kind));
            ui->tableWidget->setItem(row_count,3,new QTableWidgetItem(bookList[i].publisher));
            ui->tableWidget->setItem(row_count,4,new QTableWidgetItem(bookList[i].stock));

             row_count++;


        }

    }

}

void MainWindow::on_scienceButton_clicked() {       //If "Science" radio button is clicked then all books in the vector are displayed.

    int row_count=0;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (int i=0; i<bookList.size();i++) {

        if (bookList[i].kind == "Science") {

            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

            ui->tableWidget->setItem(row_count,0,new QTableWidgetItem(bookList[i].bookname));
            ui->tableWidget->setItem(row_count,1,new QTableWidgetItem(bookList[i].writer));
            ui->tableWidget->setItem(row_count,2,new QTableWidgetItem(bookList[i].kind));
            ui->tableWidget->setItem(row_count,3,new QTableWidgetItem(bookList[i].publisher));
            ui->tableWidget->setItem(row_count,4,new QTableWidgetItem(bookList[i].stock));

             row_count++;


        }

    }

}

QVector<book> new_Book (QVector<book> vector, QString word, QString type) {     //This function checks file if the given word is the given list or not.

    QVector<book> returned_vector;
    for (int i=0; i<vector.size(); i++) {

        if (type=="writer") {

            if (vector[i].writer.left(word.length()) == word ) {

                returned_vector.push_back(vector[i]);
            }
        }

        else if (type == "bookname") {
            if (vector[i].bookname.left(word.length()) == word ) {

                returned_vector.push_back(vector[i]);
            }
        }

        else if (type == "publisher") {
            if (vector[i].publisher.left(word.length()) == word ) {

                returned_vector.push_back(vector[i]);
            }

        }

    }

    return returned_vector;
}

void MainWindow::on_searchButton_clicked()          //If "Search" button is clicked then given input by the user is searched in the vector.
{                                                   //If it is found the it is displayed on the screen.

   QVector <book> returned_vector;

   QString searchWriter = ui->writer_input->text();             //First take input from the user.
   QString searchBookname = ui->bookname_input->text();
   QString searchPublisher = ui->publisher_input->text();

   bool writer=false;       //These are control booleans to check wheter writer input or bookname input is given by the user.
   bool bookname=false;

      if (ui->allButton->isChecked()) {         //If "ALL" button is checked then program act accordingly.

          if (searchWriter != "") {

              writer = true;

             returned_vector = new_Book(bookList,searchWriter,"writer");

          }

          if (searchBookname != "") {

              bookname = true;

              if (writer == false) {
                  returned_vector = new_Book(bookList,searchBookname,"bookname");
              }

              else {

                  returned_vector = new_Book(returned_vector,searchBookname,"bookname");

              }

          }

          if (searchPublisher != "") {

              if (writer == false && bookname==false) {
                  returned_vector = new_Book(bookList,searchPublisher,"publisher");
              }

              else {

                  returned_vector = new_Book(returned_vector,searchPublisher,"publisher");
              }
          }

          int row_count=0;                          //After all check operations program displays the book in the vector.
          ui->tableWidget->clearContents();
          ui->tableWidget->setRowCount(0);

          for (int i=0; i<returned_vector.size();i++) {

                  ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

                  ui->tableWidget->setItem(row_count,0,new QTableWidgetItem(returned_vector[i].bookname));
                  ui->tableWidget->setItem(row_count,1,new QTableWidgetItem(returned_vector[i].writer));
                  ui->tableWidget->setItem(row_count,2,new QTableWidgetItem(returned_vector[i].kind));
                  ui->tableWidget->setItem(row_count,3,new QTableWidgetItem(returned_vector[i].publisher));
                  ui->tableWidget->setItem(row_count,4,new QTableWidgetItem(returned_vector[i].stock));

                   row_count++;


              }

          }


       else if (ui->poetryButton->isChecked()) {                //Same as the previous button.

          if (searchWriter != "") {

              writer = true;

             returned_vector = new_Book(bookList,searchWriter,"writer");

          }

          if (searchBookname != "") {

              bookname = true;

              if (writer == false) {
                  returned_vector = new_Book(bookList,searchBookname,"bookname");
              }

              else {

                  returned_vector = new_Book(returned_vector,searchBookname,"bookname");

              }

          }

          if (searchPublisher != "") {

              if (writer == false && bookname==false) {
                  returned_vector = new_Book(bookList,searchPublisher,"publisher");
              }

              else {

                  returned_vector = new_Book(returned_vector,searchPublisher,"publisher");
              }
          }

          int row_count=0;
          ui->tableWidget->clearContents();
          ui->tableWidget->setRowCount(0);

          for (int i=0; i<returned_vector.size();i++) {

              if (returned_vector[i].kind == "Poetry") {

                  ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

                  ui->tableWidget->setItem(row_count,0,new QTableWidgetItem(returned_vector[i].bookname));
                  ui->tableWidget->setItem(row_count,1,new QTableWidgetItem(returned_vector[i].writer));
                  ui->tableWidget->setItem(row_count,2,new QTableWidgetItem(returned_vector[i].kind));
                  ui->tableWidget->setItem(row_count,3,new QTableWidgetItem(returned_vector[i].publisher));
                  ui->tableWidget->setItem(row_count,4,new QTableWidgetItem(returned_vector[i].stock));

                   row_count++;
                  }


              }



       }

       else if (ui->novelButton->isChecked()) { //Same as the previous button.

          if (searchWriter != "") {

              writer = true;

             returned_vector = new_Book(bookList,searchWriter,"writer");

          }

          if (searchBookname != "") {

              bookname = true;

              if (writer == false) {
                  returned_vector = new_Book(bookList,searchBookname,"bookname");
              }

              else {

                  returned_vector = new_Book(returned_vector,searchBookname,"bookname");

              }

          }

          if (searchPublisher != "") {

              if (writer == false && bookname==false) {
                  returned_vector = new_Book(bookList,searchPublisher,"publisher");
              }

              else {

                  returned_vector = new_Book(returned_vector,searchPublisher,"publisher");
              }
          }

          int row_count=0;
          ui->tableWidget->clearContents();
          ui->tableWidget->setRowCount(0);

          for (int i=0; i<returned_vector.size();i++) {

              if (returned_vector[i].kind == "Novel") {

                  ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

                  ui->tableWidget->setItem(row_count,0,new QTableWidgetItem(returned_vector[i].bookname));
                  ui->tableWidget->setItem(row_count,1,new QTableWidgetItem(returned_vector[i].writer));
                  ui->tableWidget->setItem(row_count,2,new QTableWidgetItem(returned_vector[i].kind));
                  ui->tableWidget->setItem(row_count,3,new QTableWidgetItem(returned_vector[i].publisher));
                  ui->tableWidget->setItem(row_count,4,new QTableWidgetItem(returned_vector[i].stock));

                   row_count++;
                  }

              }

       }

       else if (ui->scienceButton->isChecked()) {       //Same as the previous button.

          if (searchWriter != "") {

              writer = true;

             returned_vector = new_Book(bookList,searchWriter,"writer");

          }

          if (searchBookname != "") {

              bookname = true;

              if (writer == false) {
                  returned_vector = new_Book(bookList,searchBookname,"bookname");
              }

              else {

                  returned_vector = new_Book(returned_vector,searchBookname,"bookname");

              }

          }

          if (searchPublisher != "") {

              if (writer == false && bookname==false) {
                  returned_vector = new_Book(bookList,searchPublisher,"publisher");
              }

              else {

                  returned_vector = new_Book(returned_vector,searchPublisher,"publisher");
              }
          }

          int row_count=0;
          ui->tableWidget->clearContents();
          ui->tableWidget->setRowCount(0);

          for (int i=0; i<returned_vector.size();i++) {

              if (returned_vector[i].kind == "Science") {

                  ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

                  ui->tableWidget->setItem(row_count,0,new QTableWidgetItem(returned_vector[i].bookname));
                  ui->tableWidget->setItem(row_count,1,new QTableWidgetItem(returned_vector[i].writer));
                  ui->tableWidget->setItem(row_count,2,new QTableWidgetItem(returned_vector[i].kind));
                  ui->tableWidget->setItem(row_count,3,new QTableWidgetItem(returned_vector[i].publisher));
                  ui->tableWidget->setItem(row_count,4,new QTableWidgetItem(returned_vector[i].stock));

                   row_count++;
                  }


              }

       }
}
