///////////////////////////////////////////////////////////
//  Tarefas.h
//  Implementation of the Class Tarefas
//  Created on:      15-dez-2011 22:58:00
///////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>

#include <Windows.h>
#include <stdio.h>

using namespace std;

/*
 * OBJETIVOS: 
 * inicializar threads de tarefas específicas como
 * ler vetor de tarefas e fazer o parser para executar threads baseadas nesta
 * lista de tarefas
 */

class Tarefas
{

public:
	Tarefas();
	virtual ~Tarefas();
	static DWORD WINAPI runThread(LPVOID arg);
	int run();
	static void end();
	int start();

	void getTarefas(); // coleta as tarefas
};
