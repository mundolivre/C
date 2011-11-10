#include <stdio.h>
#include <windows.h>
#include <process.h>     // needed for _beginthread()

void Produzir( void * );
void verificaEstoque( void * );
int cont=0;
int produtos=0;
int contar=1;

int main()
{
    // Our program's first thread starts in the main() function.
    printf( "Now in the main() function.\n" );
    // Let's now create our second thread and ask it to start
    // in the silly() function.
    _beginthread( Produzir, 0, (void*)1 );
    _beginthread( verificaEstoque, 0, (void*)2 );
    // From here on there are two separate threads executing
    // our one program.
    Sleep( 1000 );
    system("pause");
}

void Produzir(void *arg) {
	while(contar) {
		produtos++;
		printf("Produzindo: %d\n", produtos);
	}
	// _endthread(); // terminaria esta thread
}

void verificaEstoque( void *arg )
{
	while (contar) {
		if(produtos==10) { 
			contar=0;
		} else {
			printf("Em estoque: %d\n", produtos);
		}
	}
	// _endthread(); // terminaria esta thread
}
