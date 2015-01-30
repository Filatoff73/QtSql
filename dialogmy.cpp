#include "dialogmy.h"

DialogMy::DialogMy(QDialog *parent) : QDialog(parent)
{
    okButton.setText(tr("OK"));
    cancelButton.setText(tr("Cancel"));

    //layout.setDirection(QBoxLayout::BottomToTop);

    layout.addWidget(&okButton);
    layout.addWidget(&cancelButton);


    this->setLayout(&layout);
    QObject::connect(&okButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(&cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    this->setVisible(true);
}

QTextEdit* DialogMy::SetTextQuestion(QString textQuestion, QString defaultUserText)
{

    arrLabel.append(new QLabel);
    arrTextEdit.append(new QTextEdit);

    arrLabel.last()->setText(textQuestion);
    arrTextEdit.last()->setText(defaultUserText);
    arrTextEdit.last()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout.addWidget(arrLabel.last());
    layout.addWidget(arrTextEdit.last());


    return arrTextEdit.last();
}

DialogMy::~DialogMy()
{
    for(int i=0;i<arrLabel.size();i++)
        delete arrLabel[i];

    for(int i=0;i<arrTextEdit.size();i++)
        delete arrTextEdit[i];

}
