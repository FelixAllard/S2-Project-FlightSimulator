#include "test.h"
void Test::tests_unitaires_formes()
{
	cout << "\n---[TESTS UNITAIRES FORMES]---\n";

	string message;
	const string FAIL = "Fail - ";

	Forme* f = new Rectangle(0, 0, 10, 5);

	// Test ancrage initial
	Coordonnee c = f->getAncrage();
	if (c.x != 0 || c.y != 0)
		message += FAIL + "Ancrage initial: (" + to_string(c.x) + ", " + to_string(c.y) + ") attendu: (0, 0)\n";

	// Test translation
	f->translater(3, -2);
	c = f->getAncrage();
	if (c.x != 3 || c.y != -2)
		message += FAIL + "Ancrage apres translation: (" + to_string(c.x) + ", " + to_string(c.y) + "), attendu: 3 and -2\n";

	// Test aire
	if (f->aire() != 50)
		message += FAIL + "aire calculee = " + to_string(f->aire()) + ", Aire attendue = 50.000000" "\n";


	if (message.empty())
		cout << "Success\n";
	else {
		cout << message + "\n";
		throw std::runtime_error("Tests unitaires formes ont echoue");
	}
		

	delete f;
}

void Test::tests_unitaires_vecteur()
{
	cout << "\n---[TESTS UNITAIRES VECTEUR]---\n";

	string message;
	const string FAIL = "Fail - ";

	Vecteur<Forme*> v;

	// Test vecteur vide au depart
	if (!v.empty())
		message += FAIL + "Vecteur devrait etre vide au depart\n";

	if (v.length() != 0)
		message += FAIL + "Taille initiale = " + to_string(v.length()) + ", attendu: 0\n";

	if (v.capacity() != 1)
		message += FAIL + "Capacite initiale = " + to_string(v.capacity()) + ", attendu: 1\n";

	// Ajout d'elements
	Forme* f1 = new Rectangle(0, 0, 2, 3);
	Forme* f2 = new Rectangle(1, 1, 4, 5);

	v += f1;
	v += f2;

	if (v.length() != 2)
		message += FAIL + "Taille apres ajouts = " + to_string(v.length()) + ", attendu: 2\n";

	// Test acces
	if (v[0] != f1)
		message += FAIL + "operator ne retourne pas le bon pointeur\n";

	if (v[1] != f2)
		message += FAIL + "operator ne retourne pas le bon pointeur\n";

	// Test erase
	Forme* retiree = v.erase(0);

	if (retiree != f1)
		message += FAIL + "erase(0) n'a pas retourne le bon pointeur\n";

	if (v.length() != 1)
		message += FAIL + "Taille apres erase = " + to_string(v.length()) + ", attendu: 1\n";

	if (v[0] != f2)
		message += FAIL + "Apres erase(0), l'element restant devrait etre f2\n";

	delete retiree; // delete f1

	// Vider
	v.clear();

	if (!v.empty())
		message += FAIL + "Vecteur devrait etre vide apres clear()\n";

	if (v.length() != 0)
		message += FAIL + "Taille apres clear = " + to_string(v.length()) + ", attendu: 0\n";

	if (v.capacity() != 1)
		message += FAIL + "Capacite apres clear = " + to_string(v.capacity()) + ", attendu: 1\n";

	// Nettoyage memoire restante
	delete f2;

	if (message.empty())
		cout << "Success\n";
	else {
		cout << message + "\n";
		throw std::runtime_error("Tests unitaires Vecteur ont echoue");
	}
}



void Test::tests_unitaires_couche()
{
	cout << "\n---[TESTS UNITAIRES COUCHE]---\n";

	string message;
	const string FAIL = "Fail - ";

	Couche c;

	// Test etat initial
	if (c.getEtat() != EtatCouche::Initialisee)
		message += FAIL + "Etat initial devrait etre Initialisee\n";

	// Test ajouterForme (devrait echouer car couche pas active)
	Forme* f1 = new Rectangle(0, 0, 5, 5);
	if (c.ajouterForme(f1))
		message += FAIL + "ajouterForme devrait echouer si couche pas Active\n";

	// f1 pas ajoutee donc on doit la delete manuellement
	delete f1;

	// Activer la couche
	if (!c.changerEtat(EtatCouche::Active))
		message += FAIL + "changerEtat(Active) devrait reussir\n";

	if (c.getEtat() != EtatCouche::Active)
		message += FAIL + "Etat apres changerEtat devrait etre Active\n";

	// Ajout de formes
	f1 = new Rectangle(0, 0, 5, 5);
	Forme* f2 = new Rectangle(2, 2, 2, 2);

	if (!c.ajouterForme(f1))
		message += FAIL + "ajouterForme(f1) a echoue\n";

	if (!c.ajouterForme(f2))
		message += FAIL + "ajouterForme(f2) a echoue\n";

	if (c.nombreFormes() != 2)
		message += FAIL + "nombreFormes = " + to_string(c.nombreFormes()) + ", attendu: 2\n";

	// Test aire totale
	// Aire rectangle 5x5 = 25
	// Aire rectangle 2x2 = 4
	// Total = 29
	if (c.aire() != 29)
		message += FAIL + "Aire totale = " + to_string(c.aire()) + ", attendu: 29\n";

	// Test translation (translater() translate toutes les formes)
	c.translater(10, -5);

	Coordonnee a = f1->getAncrage();
	if (a.x != 10 || a.y != -5)
		message += FAIL + "Translation forme incorrecte: (" + to_string(a.x) + ", " + to_string(a.y) +
		"), attendu: (10, -5)\n";

	// Test obtenirForme
	if (c.obtenirForme(0) != f1)
		message += FAIL + "obtenirForme(0) ne retourne pas f1\n";

	if (c.obtenirForme(1) != f2)
		message += FAIL + "obtenirForme(1) ne retourne pas f2\n";

	if (c.obtenirForme(5) != nullptr)
		message += FAIL + "obtenirForme(5) devrait retourner nullptr\n";

	// Test changer forme active
	if (!c.changerFormeActive(1))
		message += FAIL + "changerFormeActive(1) devrait reussir\n";

	if (c.formeActive() != 1)
		message += FAIL + "formeActive = " + to_string(c.formeActive()) + ", attendu: 1\n";

	if (c.changerFormeActive(5))
		message += FAIL + "changerFormeActive(5) devrait echouer\n";

	// Test retirer forme (doit fonctionner car couche active)
	Forme* retiree = c.retirerForme(0);

	if (retiree != f1)
		message += FAIL + "retirerForme(0) ne retourne pas f1\n";

	delete retiree; // delete f1

	if (c.nombreFormes() != 1)
		message += FAIL + "nombreFormes apres retrait = " + to_string(c.nombreFormes()) + ", attendu: 1\n";

	// Test reinitialisation (doit fonctionner car couche active)
	if (!c.reinitialiser())
		message += FAIL + "reinitialiser() devrait reussir quand couche Active\n";

	if (c.getEtat() != EtatCouche::Initialisee)
		message += FAIL + "Etat apres reinitialiser devrait etre Initialisee\n";

	if (c.nombreFormes() != 0)
		message += FAIL + "nombreFormes apres reinitialiser = " + to_string(c.nombreFormes()) + ", attendu: 0\n";

	if (c.aire() != 0)
		message += FAIL + "Aire apres reinitialiser = " + to_string(c.aire()) + ", attendu: 0\n";

	// A ce point f2 a ete delete dans reinitialiser()

	if (message.empty())
		cout << "Success\n";
	else {
		cout << message + "\n";
		throw std::runtime_error("Tests unitaires Couche ont echoue");
	}
}



void Test::tests_unitaires_canevas()
{
	cout << "\n---[TESTS UNITAIRES CANEVAS]---\n";

	string message;
	const string FAIL = "Fail - ";

	Canevas can;

	// Test couche active par defaut (couche 0)
	Forme* f1 = new Rectangle(0, 0, 4, 4);
	if (!can.ajouterForme(f1))
		message += FAIL + "Impossible d'ajouter une forme dans la couche active par defaut\n";

	// Test aire apres ajout
	if (can.aire() != 16)
		message += FAIL + "Aire totale = " + to_string(can.aire()) + ", attendu: 16\n";



	Forme* f2 = new Rectangle(1, 1, 2, 2);
	can.ajouterForme(f2);

	// Aire totale sur toutes les couches
	if (can.aire() != 20)
		message += FAIL + "Aire totale apres ajout couche 1 = " + to_string(can.aire()) + ", attendu: 20\n";

	// Test translation (agit seulement sur la couche active - couche 1)
	can.translater(5, 5);

	Coordonnee c = f2->getAncrage();
	if (c.x != 6 || c.y != 6)
		message += FAIL + "Translation couche active incorrecte: (" + to_string(c.x) + ", " + to_string(c.y) + "), attendu: (6, 6)\n";



	// Test reinitialisation
	can.reinitialiser();

	if (can.aire() != 0)
		message += FAIL + "Aire apres reinitialiser = " + to_string(can.aire()) + ", attendu: 0\n";

	// Test couche 0 redevenue active
	Forme* f3 = new Rectangle(0, 0, 1, 1);
	if (!can.ajouterForme(f3))
		message += FAIL + "La couche 0 n'est pas redevenue active apres reinitialiser\n";

	if (can.aire() != 1)
		message += FAIL + "Aire apres ajout post-reinitialisation = " + to_string(can.aire()) + ", attendu: 1\n";

	if (message.empty())
		cout << "Success\n";
	else {
		cout << message + "\n";
		throw std::runtime_error("Tests unitaires Canvas ont echoue");
	}
}


void Test::tests_unitaires()
{
	// Faire tous les tests unitaires
	tests_unitaires_formes();
	tests_unitaires_vecteur();
	tests_unitaires_couche();
	tests_unitaires_canevas();
}


void Test::tests_application_cas_01()
{
	cout << "\n=== [TESTS APPLICATION CAS 01] ===\n";

	string message;
	const string FAIL = "Fail - ";

	Canevas can;

	// Couche 0 (active par defaut)
	Forme* f1 = new Rectangle(0, 0, 10, 10);
	Forme* f2 = new Rectangle(5, 5, 2, 2);

	can.ajouterForme(f1);
	can.ajouterForme(f2);

	// Activation couche 1
	can.activerCouche(1);

	Forme* f3 = new Rectangle(0, 0, 5, 5);
	can.ajouterForme(f3);

	// Verification aire totale
	double aireTotale = can.aire();
	if (aireTotale != 129)
		message += FAIL + "Aire totale = " + to_string(aireTotale) + ", attendu: 129\n";

	// Translation couche active (couche 1)
	can.translater(10, 0);

	Coordonnee c = f3->getAncrage();
	if (c.x != 10 || c.y != 0)
		message += FAIL + "Translation couche 1 incorrecte: (" + to_string(c.x) + ", " + to_string(c.y) + "), attendu: (10, 0)\n";

	// Verification que couche 0 n'a pas bouge
	Coordonnee c0 = f1->getAncrage();
	if (c0.x != 0 || c0.y != 0)
		message += FAIL + "Translation appliquee a une couche inactive\n";

	if (message.empty())
		cout << "Success\n";
	else {
		cout << message + "\n";
		throw std::runtime_error("Tests unitaires Cas 1 ont echoue");
	}
}


void Test::tests_application_cas_02()
{
	cout << "\n=== [TESTS APPLICATION CAS 02] ===\n";

	string message;
	const string FAIL = "Fail - ";

	Canevas can;

	// Ajout initial
	Forme* f1 = new Rectangle(0, 0, 4, 4);
	can.ajouterForme(f1);

	if (can.aire() != 16)
		message += FAIL + "Aire initiale = " + to_string(can.aire()) + ", attendu: 16\n";

	// Changement de couche
	can.activerCouche(2);
	Forme* f2 = new Rectangle(0, 0, 3, 3);
	can.ajouterForme(f2);

	if (can.aire() != 25)
		message += FAIL + "Aire apres ajout couche 2 = " + to_string(can.aire()) + ", attendu: 25\n";

	// Reinitialisation complete
	can.reinitialiser();

	if (can.aire() != 0)
		message += FAIL + "Aire apres reinitialisation = " + to_string(can.aire()) + ", attendu: 0\n";

	// Verification que la couche 0 est de nouveau active
	Forme* f3 = new Rectangle(0, 0, 1, 1);
	if (!can.ajouterForme(f3))
		message += FAIL + "Ajout impossible apres reinitialisation (couche 0 inactive)\n";

	if (can.aire() != 1)
		message += FAIL + "Aire finale = " + to_string(can.aire()) + ", attendu: 1\n";

	if (message.empty())
		cout << "Success\n";
	else {
		cout << message + "\n";
		throw std::runtime_error("Tests unitaires Cas 2 ont echoue");
	}
}