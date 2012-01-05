///////////////////////////////////////////////////////////
//  Sistema.h
//  Implementation of the Class Sistema
//  Created on:      15-dez-2011 23:33:11
//  Original author: neriberto
///////////////////////////////////////////////////////////
#include <dirent.h>
#include <windows.h>
#include <tlhelp32.h> // requer para a função KillProcessByName
#include <cstring>
#include <iostream>
#include <fstream>

#include "Registro.h"

using namespace std;

class Sistema : public Registro
{

public:
	Sistema();
	virtual ~Sistema();
	string getTempDir();
	bool IsDirectory(char path[]);
	bool RemoveDirectory(string path);
	void CleanDirectory(string Directory);
	void CleanTemporaryFiles();
	string PathNormalize(string path);
	string getDiretorio();
	BOOL KillProcessByName(char *szProcessToKill);
	void SparkBuzzDisable();
};
