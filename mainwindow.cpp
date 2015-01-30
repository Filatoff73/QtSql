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

#include "dialogmy.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

         hostName = "localhost";
         databaseName = "postgres";
         userName = "postgres";
         password = "381467";

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

         connect(ui->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(MenuBarFunc(QAction*)) );


}

void MainWindow::AddDb()
{
    DialogMy dialog;
    QTextEdit* text1 = dialog.SetTextQuestion("Введите имя хоста", hostName);
    QTextEdit* text2 = dialog.SetTextQuestion("Введите имя БД", databaseName);
    QTextEdit* text3 = dialog.SetTextQuestion("Введите имя пользователя", userName);
    QTextEdit* text4 = dialog.SetTextQuestion("Введите пароль", password);

    dialog.show();
    dialog.exec();

    if(dialog.result() == QDialog::Accepted)
    {
        if(db.isOpen())
          db.close();

        db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName(text1->toPlainText());
        db.setDatabaseName(text2->toPlainText());
        db.setUserName(text3->toPlainText());
        db.setPassword(text4->toPlainText());
        bool ok = db.open();
        qDebug() << ok << endl;

    }
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
        DialogMy dialog;
        QTextEdit* text1 = dialog.SetTextQuestion("Введите запрос", "select table0.id id1, table1.id id2, table0.ch from table0 join table1 on  table0.ch = table1.ch");

        dialog.setMinimumHeight(200);
        dialog.setMinimumWidth(300);

        dialog.show();
        dialog.exec();


        if(dialog.result() == QDialog::Accepted)
        {
             query->setQuery(text1->toPlainText());
             result->setModel(query);

        }
     }

}

void MainWindow::MenuBarFunc(QAction *act)
{
    if (act)
    {
        QString txt = act->text();

        if(!txt.compare("Добавить БД"))
        {      
            AddDb();
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
