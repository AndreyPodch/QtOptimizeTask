#ifndef DIALOGPARAMETERS_H
#define DIALOGPARAMETERS_H

#include <QMainWindow>
#include "optimizeLogic.h"
#include "mainwindow.h"
#include <QPainter>
#include <QDialog>

namespace Ui {
class DialogParameters;
}

class DialogParameters : public QDialog
{
    Q_OBJECT

public:
    explicit DialogParameters(OptimizeParameters& _op, QWidget *parent = nullptr);
    ~DialogParameters();
signals:
    void parametersChanged(OptimizeParameters _op);
public slots:
    void accept();
private:
    Ui::DialogParameters *ui;
    OptimizeParameters op;
};

#endif // DIALOGPARAMETERS_H
