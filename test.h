#pragma once

#include <iostream>
#include <string>
#include "canevas.h"
#include "rectangle.h"
#include "cercle.h"
#include "carre.h"
using namespace std;
class Test
{
public:
	// Méthodes pour les tests unitaires des classes
	void tests_unitaires_formes();
	void tests_unitaires_vecteur();
	void tests_unitaires_couche();
	void tests_unitaires_canevas();
	void tests_unitaires(); // Appel de tous les tests unitaires
	// Méthodes pour les tests unitaires applicatifs
	void tests_application_cas_01();
	void tests_application_cas_02();
};
