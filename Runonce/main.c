#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "registro.h"

TCHAR subChave[MAX_KEY_LENGTH];

int main(int argc, char *argv[])
{
	HKEY hTestKey;
	int i, digit;

	if( RegOpenKeyEx( HKEY_USERS,
		//TEXT("Software\\Microsoft\\Internet Explorer\\Main"),
		0,
		0,
		KEY_READ,
		&hTestKey) == ERROR_SUCCESS
	)
	{
		QueryKey(hTestKey);
	} else {
		printf("Nao foi possivel ler\n");
	}

	RegCloseKey(hTestKey);

	// Coleta subkey escolhida
	scanf ("%d",&digit);
	digit--;
	for(i = 0; i<8; i++) {
		if(digit == i) {
			printf("Subkey escolhido : %s\n",listKeys[i].chosenKey);
			break;
		}
	}
	
	// Enumera as subkeys
	sprintf(subChave, listKeys[i].chosenKey);
	sprintf(subChave, "\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones");
	if( RegOpenKeyEx( HKEY_USERS, listKeys[i].chosenKey, 0,	KEY_WRITE, &hTestKey) == ERROR_SUCCESS
	)
	{
		// Grava o valor correto para a subChave selecionada	
		if(!RegSetKeyValueEx(HKEY_USERS, subChave, TEXT("SelfHealCount"), REG_DWORD, 00000001, 0)) {
			printf("Erro ao gravar SubChave %s\n", subChave);
		}
	} else {
		printf("Nao foi possivel abrir a subChave %s\n", subChave);
	}
	RegCloseKey(hTestKey);
	
	system("PAUSE");	

	return 0;
}
