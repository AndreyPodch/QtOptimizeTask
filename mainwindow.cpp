#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BasicDef.h"
#include "LinearOptimizator.h"
#include "LlnearOptimizeMethods.h"
#include "StochasticOptimizator.h"
#include "StopCriterias.h"
#include "ExampleFunctions.h"
#include "AreasAndCovers.h"
#include "StopCriterias.h"
#include "GradOptFR.h"
#include "dialogparameters.h"
#include <boost/numeric/ublas/vector.hpp>
#include <utility>
#include <functional>
#include <iterator>
#include <list>
#include <deque>
#include <exception>
#include <random>
#include <ctime>
#include <numbers>
#include <iostream>
using namespace boost::numeric::ublas;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , op()
    , opt(nullptr)
    , inArea(nullptr)
    , needToRecalc(true)
    , colorMatrix(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);
    if(needToRecalc)
    {
        colorMatrix=prepareOptimizeAndGenerateColorMatrix();
        auto pr=optimizeMake();
        ui->label->setText(QString::number(op.areaCenter[0]-op.areaSides[0]));
        ui->label_2->setText(QString::number(op.areaCenter[0]+op.areaSides[0]));
        ui->label_3->setText(QString::number(op.areaCenter[1]-op.areaSides[1]));
        ui->label_4->setText(QString::number(op.areaCenter[1]+op.areaSides[1]));
        ui->label_6->setText(QString::number(pr.second));
        ui->label_8->setText(QString::number(pr.first[0]));
        ui->label_9->setText(QString::number(pr.first[1]));
        needToRecalc=false;
    }
    drawColorMatrix();
    drawPath();
    }

double** MainWindow::matrixSmoothing(double ** matrix, size_t width, size_t height)
{
    double **smoothedMatrix= new double* [width];
    for(size_t i=0; i<width; ++i)
    {
        smoothedMatrix[i]=new double [height];
    }

    for(size_t i=0; i<width; ++i)
    {
        for(size_t j=0; j<height; ++j)
        {
            size_t termsCount=1;
            smoothedMatrix[i][j]=matrix[i][j];
            if(j>0)
            {
                ++termsCount;
                smoothedMatrix[i][j]+=matrix[i][j-1];
            }
            if(i>0)
            {
                ++termsCount;
                smoothedMatrix[i][j]+=matrix[i-1][j];
            }
            if(j<height-1)
            {
                ++termsCount;
                smoothedMatrix[i][j]+=matrix[i][j+1];
            }
            if(i<width-1)
            {
                ++termsCount;
                smoothedMatrix[i][j]+=matrix[i+1][j];
            }
            smoothedMatrix[i][j]/=termsCount;
        }
    }
    return(std::move(smoothedMatrix));
}

double** MainWindow::prepareOptimizeAndGenerateColorMatrix()
{
    size_t left=COLOR_MATRIX_LEFT;
    size_t above=COLOR_MATRIX_ABOVE;
    size_t width=COLOR_MATRIX_WIDTH;
    size_t height=COLOR_MATRIX_HEIGHT;
    double **colorMatrix=new double* [COLOR_MATRIX_WIDTH];
    smoothFunction<double, vector<double>> f;
    smoothFunction<vector<double>, vector<double>> gf;
    linearOptimizeMethod lom;
    stopCriteria<vector<double>> stopCr;
    vector<double> center=op.areaCenter;
    vector<double> sidesSizes=op.areaSides;
    randomPointInCoveringArea coverArea = [center, sidesSizes]()->vector<double> {return coverBallBoxAreaRG(center, sidesSizes); };
    LinearOptimizeParameters lp(1e-3,1);
    double cutRadius=op.searchPrecision*10;
    double stopPrecision=op.searchPrecision;

    switch(op.fnum)
    {
        case 1:
            f=f1;
            gf=gf1;
            break;
        case 2:
            f=f2;
            gf=gf2;
            break;
        case 3:
            f=f4;
            gf=gf4;
            break;
    }

    switch (op.stnum)
    {
        case 1:
            stopCr = [stopPrecision](auto x0, auto f0, auto x1, auto f1)->bool {return absValueDiffStop(x0, f0, x1, f1, stopPrecision); };
            break;
        case 2:
            stopCr = [stopPrecision](auto x0, auto f0, auto x1, auto f1)->bool {return absCoordDiffStop(x0, f0, x1, f1, stopPrecision); };
            break;
        case 3:
            stopCr = [stopPrecision](auto x0, auto f0, auto x1, auto f1)->bool {return relValueDiffStop(x0, f0, x1, f1, stopPrecision); };
            break;
        case 4:
            stopCr = [stopPrecision](auto x0, auto f0, auto x1, auto f1)->bool {return relCoordDiffStop(x0, f0, x1, f1, stopPrecision); };
            break;
    }

    switch (op.lomnum)
    {
        case 1:
            lom = linearSearch;
            break;
        case 2:
            lom = ternarySearch;
            break;
        case 3:
            lom = goldenSectionSearch;
            break;
    }

    LinearOptimizator lo(nullptr, nullptr, lom, lp, op.maxIterations);
    inArea = [center, sidesSizes](vector<double> x)->bool {return boxArea(x, center, sidesSizes); };
    delete opt;
    switch(op.omnum)
    {
        case 1:
            opt=new GradOptFR(f, gf, stopCr, lo, op.maxIterations);
            break;
        case 2:
            opt=new StochasticOptimizator(f, stopCr, coverArea, cutRadius, op.maxIterations);
            break;
    }




    for(size_t i=0;i<width;++i)
    {
        colorMatrix[i]=new double [COLOR_MATRIX_HEIGHT] {0};
    }
    double leftfborder=op.areaCenter[0]-op.areaSides[0]/2;
    double rightfborder=op.areaCenter[0]+op.areaSides[0]/2;
    double abovefborder=op.areaCenter[1]+op.areaSides[1]/2;
    double belowfborder=op.areaCenter[1]-op.areaSides[1]/2;

//    std::cout<<leftfborder<<" "<<rightfborder<<std::endl;
//    std::cout<<abovefborder<<" "<<belowfborder<<std::endl;
    int step=COLOR_MATRIX_GRID_STEP;
    for(size_t i=0;i<width;i+=step)
    {
        for(size_t j=0; j<height; j+=step)
        {
            vector<double> curp(2);
            curp[0]=leftfborder+(op.areaSides[0]*i)/width;
            curp[1]=abovefborder-(op.areaSides[1]*j)/height;
            double val=f(curp);
            //print(curp);
            for(int k=-step/2; k<=step/2;++k)
            {
                for(int w=-step/2; w<=step/2;++w)
                {
                    if(((int)i>=-k)&&((int)j>=-w)&&(width>i+k)&&(height>j+w)) {
                        colorMatrix[i+k][j+w]=val;
                    }
                }
            }
        }
    }
    for(size_t i=0;i<COLOR_MATRIX_SMOOTH_DEGREE;++i)
    {
        colorMatrix=matrixSmoothing(colorMatrix, width, height);
//        std::cout<<colorMatrix[0][0]<<std::endl;
    }

    double mmax=1e-15, mmin=1e15;
    for(size_t i=0;i<width;++i)
    {
        for(size_t j=0; j<height; ++j)
        {
            mmax=std::max(colorMatrix[i][j],mmax);
            mmin=std::min(colorMatrix[i][j],mmin);
        }
    }
    return std::move(colorMatrix);
}

void MainWindow::drawColorMatrix()
{
    QPainter painter(this);

    size_t left=COLOR_MATRIX_LEFT;
    size_t above=COLOR_MATRIX_ABOVE;
    size_t width=COLOR_MATRIX_WIDTH;
    size_t height=COLOR_MATRIX_HEIGHT;

    double mmax=1e-15, mmin=1e15;
    for(size_t i=0;i<width;++i)
    {
        for(size_t j=0; j<height; ++j)
        {
            mmax=std::max(colorMatrix[i][j],mmax);
            mmin=std::min(colorMatrix[i][j],mmin);
        }
    }
    for(size_t i=0;i<width;++i)
    {
        for(size_t j=0; j<height; ++j)
        {
            int decCol=(int) (255*(colorMatrix[i][j]-mmin)/(mmax-mmin));
            decCol=255-decCol;
            std::stringstream tempss;
            tempss<<std::hex<<decCol;
            std::string rawHexCol;
            tempss>>rawHexCol;
            tempss.flush();
            if (rawHexCol.length()==0) rawHexCol="00";
            if (rawHexCol.length()==1) rawHexCol='0'+rawHexCol;
            char hexCol[8]="#c56c00";
            hexCol[1]=rawHexCol[0];
            hexCol[2]=rawHexCol[1];
            hexCol[5]=rawHexCol[0];
            hexCol[6]=rawHexCol[1];
            painter.fillRect(left+i, above+j, 1, 1, QBrush(hexCol));
        }
    }
}

void MainWindow::changeParameters()
{
    DialogParameters *dp=new DialogParameters(op);
    QObject::connect(dp, SIGNAL(parametersChanged(OptimizeParameters))
                     ,this, SLOT(setParameters(OptimizeParameters)));
    dp->open();
}

void MainWindow::setParameters(OptimizeParameters _op)
{
    op=_op;
    needToRecalc=true;
}

std::pair<vector<double>, double> MainWindow::optimizeMake()
{
    return opt->optimize(op.startPoint, inArea);
}

void MainWindow::drawPath()
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 1));

    double left=op.areaCenter[0]-op.areaSides[0]/2;
    double right=op.areaCenter[0]+op.areaSides[0]/2;
    double above=op.areaCenter[1]+op.areaSides[1]/2;
    double below=op.areaCenter[1]-op.areaSides[1]/2;

    auto pp=opt->getPathPointer();

    int num=0;
    int len=pp->size();
//    std::cout<<len<<std::endl;
    int PrevXPixel, PrevYPixel;
    for(vector<double> curPoint: *pp)
    {
        double dxp=COLOR_MATRIX_LEFT+COLOR_MATRIX_WIDTH*(curPoint[0]-left)/(right-left);
        int CurXPixel=(int)dxp;
        double dyp=COLOR_MATRIX_ABOVE+COLOR_MATRIX_HEIGHT*(above-curPoint[1])/(above-below);
        int CurYPixel=(int)dyp;
        if(num==0) painter.fillRect(CurXPixel-2, CurYPixel-2, 5, 5, QBrush("#ffffff"));
        else if (num==len-1) painter.fillRect(CurXPixel-2, CurYPixel-2, 5, 5, QBrush("#000000"));
        else painter.fillRect(CurXPixel-2, CurYPixel-2, 5, 5, QBrush("#ff0000"));
        if(num!=0)
        {
            painter.drawLine(PrevXPixel, PrevYPixel, CurXPixel, CurYPixel);
        }
        PrevXPixel=CurXPixel;
        PrevYPixel=CurYPixel;
        ++num;
    }
}

void MainWindow::mousePressEvent(QMouseEvent* ev)
{
    const QPoint p = ev->pos();
//    std::cout<<p.x()<<" "<<p.y()<<std::endl;
    if((p.x()>COLOR_MATRIX_LEFT)&&(p.x()<COLOR_MATRIX_LEFT+COLOR_MATRIX_WIDTH)
      &&(p.y()>COLOR_MATRIX_ABOVE)&&(p.y()<COLOR_MATRIX_ABOVE+COLOR_MATRIX_HEIGHT))
    {
        vector<double> curPoint(2);
        curPoint[0]=(((double)(p.x()-COLOR_MATRIX_LEFT))/COLOR_MATRIX_WIDTH)
                    *op.areaSides[0]+(-op.areaSides[0]/2+op.areaCenter[0]);
        curPoint[1]=-(((double)(p.y()-COLOR_MATRIX_ABOVE))/COLOR_MATRIX_HEIGHT)
                *op.areaSides[1]+(op.areaSides[1]/2+op.areaCenter[1]);
        op.startPoint=curPoint;
        auto pr=optimizeMake();
        ui->label_6->setText(QString::number(pr.second));
        ui->label_8->setText(QString::number(pr.first[0]));
        ui->label_9->setText(QString::number(pr.first[1]));
        this->update();
    }
}
