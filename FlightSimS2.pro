TEMPLATE     = vcapp
TARGET       = Flight-Sim-S3
CONFIG      += warn_on qt debug windows c++20
HEADERS     += test.h
SOURCES     += source/main.cpp test.cpp
INCLUDEPATH += include
QT          += widgets
