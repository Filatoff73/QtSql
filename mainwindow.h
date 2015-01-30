#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "table.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    void AddDb();

private:
    Ui::MainWindow *ui;
    QVector <Table*> arr;
    QTableView* result;
    QSqlQueryModel* query;
    QSqlDatabase db;

    QString     hostName, databaseName, userName, password;

private slots:

void SaveChanges();
void AddTable();
void RefreshTable();
void DeleteRow();
void AddRow();
void SetRule();
void MenuBarFunc(QAction *act);

};

#endif // MAINWINDOW_H
