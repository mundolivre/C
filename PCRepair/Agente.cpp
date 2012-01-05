///////////////////////////////////////////////////////////
//  Agente.cpp
//  Implementation of the Class Agente
//  Created on:      15-dez-2011 23:52:33
//  Original author: neriberto
///////////////////////////////////////////////////////////

#include "Agente.h"
#include <windows.h> 

string myself;
char OS[256]; // Sistema Operacional

Agente::Agente(){
	// Pega o Sistema Operacional
	OS = m_Sistema->leRegistro(HKEY_LOCAL_MACHINE, "software\\microsoft\\windows nt\\currentversion", "productname");
}

Agente::~Agente(){

}

void Agente::showMenu() {
	int opcao = 0;
	do {
		system("cls");
		cout << "### Menu ###" << endl;
		cout << "1) Fix Gedas" << endl;
		cout << "2) Limpar temporario" << endl;
		cout << "3) Prompt" << endl;
		cout << "4) Painel de Controle" << endl;
		cout << "5) Destravar" << endl;
		cout << "6) Travar" << endl;
		cout << "7) Spark - Desativar Buzz" << endl;
		cout << "9) Sair" << endl;
		cout << "Digite uma opcao: ";
		cin >> opcao;
		switch(opcao) {
			case 1:
				m_Sistema->KillProcessByName("gedasCom.exe");
				m_Sistema->CleanTemporaryFiles();
				system("pause");
			break;
			case 2:
				m_Sistema->CleanTemporaryFiles();
				system("pause");
			break;
			case 3:
				system("cmd.exe");
			break;
			case 4:
				system("control.exe");
			break;
			case 5:
				if (OS.compare("Microsoft Windows XP") == 0)
					system("c:\\windows\\mask\\libera.wpp");
				else 
					system("c:\\windows\\mask\\trava.exe");
			break;
			case 6:
				if (OS.compare("Microsoft Windows XP") == 0)
					system("c:\\windows\\mask\\trava.wpp");
				else 
					system("c:\\windows\\mask\\trava.exe");
			break;
			case 7:
				m_Sistema->SparkBuzzDisable();
				system("pause");
			break;
			default:
				if(opcao != 9)
					cout << "Opcao invalida!" << endl;
		}
	} while (opcao != 9);
}
