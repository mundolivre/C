///////////////////////////////////////////////////////////
//  Registro.h
//  Implementation of the Class Registro
//  Created on:      15-dez-2011 22:58:02
///////////////////////////////////////////////////////////


#include <cstdlib>
#include <iostream>

#include <windows.h>

using namespace std;

class Registro
{

public:
	Registro();
	virtual ~Registro();
	string leRegistro(HKEY root, char *path, char *key);
	int deletaRegistro(HKEY root, char *path, char *key);
};
