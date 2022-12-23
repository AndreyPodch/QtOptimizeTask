QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AreasAndCovers.cpp \
    BasicDef.cpp \
    DerivativeOptimizatorInterface.cpp \
    ExampleFunctions.cpp \
    GradOptFR.cpp \
    LinearOptimizator.cpp \
    LlnearOptimizeMethods.cpp \
    OptimizatorInterface.cpp \
    StochasticOptimizator.cpp \
    StopCriterias.cpp \
    dialogparameters.cpp \
    lines.cpp \
    main.cpp \
    mainwindow.cpp \
    optimizeLogic.cpp

HEADERS += \
    AreasAndCovers.h \
    BasicDef.h \
    DerivativeOptimizatorInterface.h \
    ExampleFunctions.h \
    GradOptFR.h \
    LinearOptimizator.h \
    LlnearOptimizeMethods.h \
    OptimizatorInterface.h \
    StochasticOptimizator.h \
    StopCriterias.h \
    dialogparameters.h \
    lines.h \
    mainwindow.h \
    optimizeLogic.h

FORMS += \
    dialogparameters.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourse.qrc
