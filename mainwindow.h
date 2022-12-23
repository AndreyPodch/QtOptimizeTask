#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "optimizeLogic.h"
#include <QPainter>
#include <QMouseEvent>

const size_t WINDOW_WIDTH = 650;
const size_t WINDOW_HEIGHT= 570;
const size_t COLOR_MATRIX_LEFT=10;
const size_t COLOR_MATRIX_ABOVE=70;
const size_t COLOR_MATRIX_WIDTH=441;
const size_t COLOR_MATRIX_HEIGHT=441;

const size_t COLOR_MATRIX_GRID_STEP=4;
const size_t COLOR_MATRIX_SMOOTH_DEGREE=1;

struct OptimizeParameters
{
    int fnum;
    int stnum;
    int lomnum;
    int omnum;
    vector<double> startPoint;
    vector<double> areaCenter;
    vector<double> areaSides;
    double searchPrecision;
    size_t maxIterations;
    OptimizeParameters(): fnum(1), stnum(1), lomnum(3), omnum(1)
      , searchPrecision(1e-6), maxIterations(50)
    {
        vector <double> sp(2);
        sp[0]=0; sp[1]=0;
        vector<double> ac(2);
        ac[0]=0; ac[1]=0;
        vector<double> as(2);
        as[0]=1; as[1]=1;
        startPoint=std::move(sp);
        areaCenter=std::move(ac);
        areaSides=std::move(as);
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    ~MainWindow();
public slots:
    void changeParameters();
    void setParameters(OptimizeParameters _op);
private:
    Ui::MainWindow *ui;
    OptimizeParameters op;
    OptimizatorInterface<vector<double>> *opt;
    inAreaCheck<vector<double>> inArea;
    double** colorMatrix;
    bool needToRecalc;

    void mousePressEvent(QMouseEvent*);
    double** prepareOptimizeAndGenerateColorMatrix();
    void drawColorMatrix();
    std::pair<vector<double>, double> optimizeMake();
    void drawPath();
    double** matrixSmoothing(double ** matrix, size_t width, size_t height);
};
#endif // MAINWINDOW_H
