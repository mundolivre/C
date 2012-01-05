///////////////////////////////////////////////////////////
//  Registro.cpp
//  Implementation of the Class Registro
//  Created on:      15-dez-2011 22:58:02
///////////////////////////////////////////////////////////

#include "Registro.h"

Registro::Registro(){

}

Registro::~Registro(){

}

string Registro::leRegistro(HKEY root, char *path, char *key) {
	HKEY phkey;
	BYTE data[256];
	char dados[256];
	unsigned long datalen = 255;
	if (RegOpenKeyExA(root, path, (DWORD)NULL, KEY_QUERY_VALUE, &phkey) == ERROR_SUCCESS)
	{
		if (RegQueryValueExA(phkey, key, NULL, NULL, data, &datalen) == ERROR_SUCCESS)
		{
			memcpy(dados, data, sizeof(data));
		}
		RegCloseKey(phkey);
		return dados;
	}
}

int Registro::deletaRegistro(HKEY root, char *path, char *key) {
	HKEY hkey;
	unsigned long datalen = 255;
	if (!RegOpenKeyExA(root, path, 0, KEY_ALL_ACCESS, &hkey) == ERROR_SUCCESS)
	{
		return GetLastError();
	}
	RegDeleteValue(hkey,key);
	RegCloseKey(hkey);
}
