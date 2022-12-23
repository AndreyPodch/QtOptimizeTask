#include "dialogparameters.h"
#include "ui_dialogparameters.h"
#include <qvalidator.h>
#include <QString>

DialogParameters::DialogParameters(OptimizeParameters& _op, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogParameters),
    op(_op)
{
    ui->setupUi(this);

    ui->fGroup->setId(ui->radioButton, 1);
    ui->fGroup->setId(ui->radioButton_2, 2);
    ui->fGroup->setId(ui->radioButton_3, 3);
    ui->fGroup->button(op.fnum)->setChecked(1);

    ui->stopGroup->setId(ui->radioButton_4, 1);
    ui->stopGroup->setId(ui->radioButton_5, 2);
    ui->stopGroup->setId(ui->radioButton_6, 3);
    ui->stopGroup->setId(ui->radioButton_7, 4);
    ui->stopGroup->button(op.stnum)->setChecked(1);

    ui->methodGroup->setId(ui->radioButton_8, 1);
    ui->methodGroup->setId(ui->radioButton_9, 2);
    ui->methodGroup->button(op.omnum)->setChecked(1);

    ui->lomGroup->setId(ui->radioButton_10, 1);
    ui->lomGroup->setId(ui->radioButton_11, 2);
    ui->lomGroup->setId(ui->radioButton_12, 3);
    ui->lomGroup->button(op.lomnum)->setChecked(1);

    ui->lineEdit->setValidator(new QDoubleValidator(0, 1, 5, this));
    ui->lineEdit->setText(QString::fromStdString(std::to_string(op.searchPrecision)));

    ui->lineEdit_2->setValidator(new QDoubleValidator(0, 1, 5));
    ui->lineEdit_2->setText(QString::fromStdString(std::to_string(op.areaCenter[0])));
    ui->lineEdit_3->setValidator(new QDoubleValidator(0, 1, 5));
    ui->lineEdit_3->setText(QString::fromStdString(std::to_string(op.areaCenter[1])));

    ui->lineEdit_4->setValidator(new QDoubleValidator(0, 1, 5));
    ui->lineEdit_4->setText(QString::fromStdString(std::to_string(op.areaSides[0])));
    ui->lineEdit_5->setValidator(new QDoubleValidator(0, 1, 5));
    ui->lineEdit_5->setText(QString::fromStdString(std::to_string(op.areaSides[1])));

    ui->lineEdit_6->setValidator(new QDoubleValidator(0, 1, 5));
    ui->lineEdit_6->setText(QString::fromStdString(std::to_string(op.startPoint[0])));
    ui->lineEdit_7->setValidator(new QDoubleValidator(0, 1, 5));
    ui->lineEdit_7->setText(QString::fromStdString(std::to_string(op.startPoint[1])));

    ui->lineEdit_8->setValidator(new QIntValidator(0, 2000));
    ui->lineEdit_8->setText(QString::fromStdString(std::to_string(op.maxIterations)));
}

DialogParameters::~DialogParameters()
{
    delete ui;
}

void DialogParameters::accept()
{
    OptimizeParameters nop;
    nop.fnum=ui->fGroup->checkedId();
    nop.stnum=ui->stopGroup->checkedId();
    nop.omnum=ui->methodGroup->checkedId();
    nop.lomnum=ui->lomGroup->checkedId();
    nop.searchPrecision=(ui->lineEdit->text()).toDouble();
    nop.areaCenter[0]=(ui->lineEdit_2->text()).toDouble();
    nop.areaCenter[1]=(ui->lineEdit_3->text()).toDouble();
    nop.areaSides[0]=(ui->lineEdit_4->text()).toDouble();
    nop.areaSides[1]=(ui->lineEdit_5->text()).toDouble();
    nop.startPoint[0]=(ui->lineEdit_6->text()).toDouble();
    nop.startPoint[1]=(ui->lineEdit_7->text()).toDouble();
    nop.maxIterations=(ui->lineEdit_8->text()).toInt();
    emit parametersChanged(nop);
    this->close();
}
