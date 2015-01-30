#ifndef TABLE_H
#define TABLE_H

#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlDatabase>
#include <QMouseEvent>

class Table : public QTableView
{
    Q_OBJECT
public:
    explicit Table(QString nameTable, QSqlDatabase& db, QObject* a, QTableView *parent = 0);

    ~Table();

    QSqlTableModel *getModel() const;

private:

    QSqlTableModel *model;

};

#endif // TABLE_H
