#include "table.h"
#include <QDebug>


Table::Table(QString nameTable, QSqlDatabase& db, QObject* a, QTableView *parent) : QTableView(parent)
{

         model = new QSqlTableModel(a, db);
         model->setTable(nameTable);
         model->setEditStrategy(QSqlTableModel::OnFieldChange);
         model->select();
         this->setModel(model);

}


QSqlTableModel *Table::getModel() const
{
    return model;
}


Table::~Table()
{
    delete model;
}
