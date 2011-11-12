// StackOverrun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void foo(const char* input)
{
	char buf[10];
	printf("Minha pilha se parece com:\n%p\n%p\n%p\n%p\n%p\n%p\n\n");
	strcpy(buf, input);
	printf("%s\n", buf);

	printf("Agora se parece com:\n%p\n%p\n%p\n%p\n%p\n%p\n\n");
}

void bar()
{
	printf("Fui hackeado!\n");
}


int main(int argc, char* argv[])
{
	printf("Endereço de foo - %p\n", foo);
	printf("Endereço de bar - %p\n", bar);
	if(argc != 2)
	{
		printf("Passe um string como argumento!\n");
		return -1;
	}
	foo(argv[1]);
	return 0;
}
