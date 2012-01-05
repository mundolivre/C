///////////////////////////////////////////////////////////
//  Agente.h
//  Implementation of the Class Agente
//  Created on:      15-dez-2011 23:52:33
//  Original author: neriberto
///////////////////////////////////////////////////////////

#include <dirent.h>
#include <windows.h>

#include "Rede.h"
#include "Sistema.h"
#include "Tarefas.h"

class Agente: public Tarefas
{

public:
	Agente();
	virtual ~Agente();
	string myself;
	string OS; // Sistema Operacional
	Rede *m_Rede;
	Sistema *m_Sistema;
	void showMenu();
};
