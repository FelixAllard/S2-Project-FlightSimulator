/********
* Fichier: testGraphicusGUI.cpp
* Auteurs: C.-A. Brunet
* Date: 10 janvier 2024
* Description: Ce programme teste l'interface utilisateur GraphicusGUI.
*
* Copyright 2024 Département de génie électrique et génie informatique
*                Université de Sherbrooke  
********/

#include "graphicus-03.h"
#include "test.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Hello Qt");
    window.resize(400, 300);
    window.show();

    return app.exec();
}