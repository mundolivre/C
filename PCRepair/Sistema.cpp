///////////////////////////////////////////////////////////
//  Sistema.cpp
//  Implementation of the Class Sistema
//  Created on:      15-dez-2011 23:33:11
//  Original author: neriberto
///////////////////////////////////////////////////////////

#include "Sistema.h"

string Diretorio;

Sistema::Sistema(){

}

Sistema::~Sistema(){

}

string Sistema::getDiretorio() {
	Diretorio = getTempDir();
	return Diretorio;
}

string Sistema::getTempDir(){
	char USER_TEMP_DIR [MAX_PATH];
	GetTempPath(MAX_PATH, USER_TEMP_DIR);
	return PathNormalize(USER_TEMP_DIR);
}

/*
*	TODO mudar char path[] para string path
*/
bool Sistema::IsDirectory(char path[]) {
	int i = strlen(path) - 1;
	// exception for directories
  if (path[strlen(path)] == '.') { return true; }
  // such as \. and \..
  for(i; i >= 0; i--) {
		// if we first encounter a . then it's a file
  	if (path[i] == '.') { return false; }
		// if we first encounter a \ it's a dir
    else if (path[i] == '\\' || path[i] == '/') {
			// Obs. Quando o diretório não existe cai aqui
			return true;
		}
  }
	// O caminho deve conter barras duplas : \\
	return false;
}

bool Sistema::RemoveDirectory(string path) {
    if (path[path.length()-1] != '\\') path += "\\";
    // first off, we need to create a pointer to a directory
    DIR *pdir = NULL; // remember, it's good practice to initialise a pointer to NULL!
    pdir = opendir (path.c_str());
    struct dirent *pent = NULL;
    if (pdir == NULL) { // if pdir wasn't initialised correctly
        return false; // return false to say "we couldn't do it"
    } // end if
    char file[MAX_PATH];
		
		// use this to skip the first TWO which cause an infinite loop (and eventually, stack overflow)
    int counter = 1;
		// while there is still something in the directory to list
    while (pent = readdir (pdir)) {
        if (counter > 2) {
						// For abaixo limpa o conteúdo da variável file
            for (int i = 0; i < MAX_PATH; i++) file[i] = '\0';
						// Copia o path para file
            strcat(file, path.c_str());
            if (pent == NULL) { // if pent has not been initialised correctly
                return false; // we couldn't do it
            } // otherwise, it was initialised correctly, so let's delete the file~
            strcat(file, pent->d_name); // concatenate the strings to get the complete path
						// se o valor de file for diretório e diferente do diretório passado...
            if (IsDirectory(file) == true){
								RemoveDirectory(file); // recursivo para limpar diretório
            } else { // it's a file, we can use remove
							FILE * pFile = fopen (file,"w");
							if (pFile!=NULL)
							{
								fclose(pFile);
							  if( remove(file) != 0 ) {
							    cout << "Erro ao apagar arquivo: " << file << endl;
							  } else {
							    cout << "Arquivo apagado com sucesso: " << file << endl;
								}
							} else {
							    cout << "Erro ao abrir arquivo: " << file << endl;
							}
            }
        }
			counter++;
    }
    // finally, let's clean up
		// close the directory
    closedir (pdir);

		// se o diretório for igual ao passado sai fora,...
		if (Diretorio.compare(path) == 0) {
			return false;
		}

		// continua...
    if (!rmdir(path.c_str())) {
				cout << "Erro ao apagar diretorio " << path << endl;
			return false;
    } else {
			// delete the directory
			cout << "Diretorio apagado " << path << endl;
	   	return true;
		}

}

void Sistema::CleanDirectory(string Directory) {
	// copia o diretório para a variável Global
	Diretorio = PathNormalize(Directory);
	// Manda remover o diretório
  RemoveDirectory(Diretorio);
}

void Sistema::CleanTemporaryFiles() {
	Diretorio = getTempDir();
	// Limpa diretorio temporario do usuario logado
	if(IsDirectory((char *)Diretorio.c_str())) {
		RemoveDirectory(Diretorio);
	}
	// Se for windows XP limpa diretorio temporario do usuario administrador
	string OS = leRegistro(HKEY_LOCAL_MACHINE, "software\\microsoft\\windows nt\\currentversion", "productname");
	if(OS.compare("Microsoft Windows XP") == 0) {
		string key = leRegistro(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", "Logon User Name");
		size_t found = Diretorio.rfind(key);
		if(found != string::npos) { Diretorio.replace(found,key.length(),"administrador"); }
	}
	// Limpa diretorio temporario do Windows
	Diretorio = "C:\\Windows\\Temp\\";
	if(IsDirectory((char *)Diretorio.c_str())) {
		RemoveDirectory(Diretorio);
	}
}

string Sistema::PathNormalize(string path) {
	if(path.at(path.length()-1) != '\\') {
		path.append("\\");
		cout << "Path Normalizado" << endl;
	}
	return path;
}

BOOL Sistema::KillProcessByName(char *szProcessToKill){
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  // Takes a snapshot of all the processes

	if(hProcessSnap == INVALID_HANDLE_VALUE){
		return( FALSE );
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if(!Process32First(hProcessSnap, &pe32)){
		CloseHandle(hProcessSnap);     
		return( FALSE );
	}

	do{
		if(!strcmp(pe32.szExeFile,szProcessToKill)){    //  checks if process at current position has the name of to be killed app
			hProcess = OpenProcess(PROCESS_TERMINATE,0, pe32.th32ProcessID);  // gets handle to process
			TerminateProcess(hProcess,0);   // Terminate process by handle
			CloseHandle(hProcess);  // close the handle
		} 
	} while(Process32Next(hProcessSnap,&pe32));  // gets next member of snapshot

	CloseHandle(hProcessSnap);  // closes the snapshot handle
	return( TRUE );
}

void Sistema::SparkBuzzDisable() {
	string OS = leRegistro(HKEY_LOCAL_MACHINE, "software\\microsoft\\windows nt\\currentversion", "productname");
	string key = leRegistro(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", "Logon User Name");
	if(OS.compare("Microsoft Windows XP") == 0) {
		string filename = "C:\\Documents And Settings\\";
		filename += key;
		filename += "\\Dados de Aplicativos\\Spark\\spark.properties";
		fstream file;
		file.open(filename.c_str());

	  int length;
  	char * buffer;
	  if (file.is_open())
	  {
		  // get length of file:
		  file.seekg (0, ios::end);
		  length = file.tellg();
		  file.seekg (0, ios::beg);

		  // allocate memory:
		  buffer = new char [length];

			// Comprova leitura do conteudo do arquivo
			file.read(buffer, length);
			cout << buffer << endl;

			// Faz a substituição da string

			// Salva o buffer no arquivo
	    file.close();
	  }
	  else
	  {
	    cout << "Error opening file";
	  }
	}
}
