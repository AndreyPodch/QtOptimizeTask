#include "lines.h"
#include "optimizeLogic.h"

Lines::Lines(QWidget *parent)
    : QWidget{parent}
{

}

void Lines::paintEvent(QPaintEvent *e) {

  Q_UNUSED(e);

  QPainter qp(this);
  drawLines(&qp);
}

void Lines::drawLines(QPainter *qp) {

    QPainter painter(this);
//      painter.setPen(QColor("#d4d4d4"));
//      painter.setBrush(QBrush("#c56c00"));
//      painter.fillRect(COLOR_MATRIX_LEFT, COLOR_MATRIX_ABOVE
//                       , COLOR_MATRIX_WIDTH, COLOR_MATRIX_HEIGHT, QBrush("#c56c00"));

    size_t left=COLOR_MATRIX_LEFT;
    size_t above=COLOR_MATRIX_ABOVE;
    size_t width=COLOR_MATRIX_WIDTH;
    size_t height=COLOR_MATRIX_HEIGHT;
    double **colorMatrix=new double* [COLOR_MATRIX_WIDTH];
    for(size_t i=0;i<width;++i)
    {
        colorMatrix[i]=new double [COLOR_MATRIX_HEIGHT] {0};
    }

    for(size_t i=0;i<width;i+=COLOR_MATRIX_GRID_STEP)
    {
        for(size_t j=0; j<height; j+=COLOR_MATRIX_GRID_STEP)
        {
            colorMatrix[i][j]=1;
        }
    }
    for(int i=0;i<25;++i)
    {
 //       colorMatrix=matrixSmoothing(colorMatrix, width, height);
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
//    std::cout<<mmin<<" "<<mmax<<std::endl;
    for(size_t i=0;i<width;++i)
    {
        for(size_t j=0; j<height; ++j)
        {
//            if(i+j<4) std::cout<<colorMatrix[i][j]<<std::endl;
            int decCol=(int) (255*(colorMatrix[i][j]-mmin)/(mmax-mmin));
//            if(i+j<4) std::cout<<decCol<<std::endl;
            std::stringstream tempss;
            tempss<<std::hex<<decCol;
            std::string rawHexCol;
            tempss>>rawHexCol;
            tempss.flush();
            if (rawHexCol.length()==0) rawHexCol="00";
            if (rawHexCol.length()==1) rawHexCol='0'+rawHexCol;
            char hexCol[8]="#c56c00";
            hexCol[5]=rawHexCol[0];
            hexCol[6]=rawHexCol[1];
 //           if(i+j<5) std::cout<<rawHexCol<<std::endl;
            painter.fillRect(left+i, above+j, 1, 1, QBrush(hexCol));
        }
    }
    for(size_t i=0;i<width;++i)
    {
       delete[] colorMatrix[i];
    }
    delete[] colorMatrix;
}
