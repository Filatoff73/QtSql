#ifndef DIALOGMY_H
#define DIALOGMY_H

#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVector>
#include <QSizePolicy>
class DialogMy : public QDialog
{
public:
    explicit DialogMy(QDialog *parent = 0);
        ~DialogMy();
    QTextEdit* SetTextQuestion(QString textQuestion, QString defaultUserText);


private:
    QPushButton okButton,cancelButton;
     QVBoxLayout layout;

    QVector <QLabel*> arrLabel;
    QVector <QTextEdit*> arrTextEdit;


};

#endif // DIALOGMY_H
