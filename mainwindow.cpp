#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QLayout>
#include <QTableView>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


         db = QSqlDatabase::addDatabase("QPSQL");
         db.setHostName("localhost");
         db.setDatabaseName("postgres");
         db.setUserName("postgres");
         db.setPassword("381467");
         bool ok = db.open();
         qDebug() << ok<< endl;

          query = new QSqlQueryModel;
         result = new QTableView;
         result->setModel(query);
         ui->horizontalLayout_2->addWidget(result);
         //ui->horizontalLayout_2->setDirection(QBoxLayout::RightToLeft);



         connect(ui->addTable, SIGNAL(clicked()), this, SLOT(AddTable()));
         connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(SaveChanges()));
         connect(ui->refreshTable, SIGNAL(clicked()), this, SLOT(RefreshTable()));
         connect(ui->deleteRow, SIGNAL(clicked()), this, SLOT(DeleteRow()));
         connect(ui->addRow, SIGNAL(clicked()), this, SLOT(AddRow()));
         connect(ui->rule, SIGNAL(clicked()), this, SLOT(SetRule()));


}



void MainWindow::SaveChanges()
{
    if(db.isOpen())
    {
    for(int i=0;i<arr.size();i++)
        arr[i]->getModel()->submitAll();
    }
}

void MainWindow::AddTable()
{
    if(db.isOpen())
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr(""),
                                          tr("Введите имя таблицы"), QLineEdit::Normal,
                                          "table0", &ok);
        if (ok && !text.isEmpty() )
        {

           if(db.tables(QSql::Tables).contains(text))
           {
            arr.append(new Table(text,db,this));
            arr.last()->show();
            ui->horizontalLayout_2->addWidget(arr.last());
           }
           else
            QMessageBox::information(NULL,QObject::tr("Информация"),tr("Таблицы с таким именем не существует"));

        }
    }
}

void MainWindow::RefreshTable()
{
    if(db.isOpen())
    {
    for(int i=0;i<arr.size();i++)
        arr[i]->getModel()->select();
    }
}

void MainWindow::DeleteRow()
{
    if(db.isOpen())
    {
        for(int i=0;i<arr.size();i++)
        {
            int count = arr[i]->selectionModel()->selectedRows().count();
            for(int i1=0;i1<count;i1++)
                arr[i]->getModel()->removeRow( arr[i]->selectionModel()->selectedRows().at(i1).row(), QModelIndex());
        }

    }
}

void MainWindow::AddRow()
{
    if(db.isOpen())
    {
        for(int i=0;i<arr.size();i++)
        {
            int count = arr[i]->selectionModel()->selectedRows().count();
            for(int i1=0;i1<count;i1++)
                arr[i]->getModel()->insertRow(arr[i]->selectionModel()->selectedRows().at(i1).row()+1, QModelIndex());
        }

    }
}

void MainWindow::SetRule()
{

    if(db.isOpen())
    {
        QDialog question;
        QPushButton okButton,cancelButton;

        okButton.setText(tr("OK"));
        cancelButton.setText(tr("Cancel"));

        QVBoxLayout layout;

             QHBoxLayout layoutText1;
             QLabel text1;
             text1.setText("введите запрос");
             QTextEdit parametrText;
             parametrText.setText("select table0.id id1, table1.id id2, table0.ch from table0 join table1 on  table0.ch = table1.ch");
             parametrText.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
             layoutText1.addWidget(&text1);
             layoutText1.addWidget(&parametrText);

         layout.addLayout(&layoutText1);
         layout.addWidget(&okButton);
         layout.addWidget(&cancelButton);

         question.setLayout(&layout);

         QObject::connect(&okButton, SIGNAL(clicked()), &question, SLOT(accept()));
         QObject::connect(&cancelButton, SIGNAL(clicked()), &question, SLOT(reject()));
         question.setVisible(true);
         question.show();
         question.exec();

         if(question.result() == QDialog::Accepted)
         {
             query->setQuery(parametrText.toPlainText());
             result->setModel(query);

         }
       }

}

MainWindow::~MainWindow()
{

    for(int i=0;i<arr.size();i++)
        delete arr[i];

    delete result;
    delete query;

    delete ui;


}
