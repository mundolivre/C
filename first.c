#include <stdio.h>
#include <windows.h>

#define MAXFILES 500

main() {

    FILE *fptr;
    int count = 0;
    char strpath[60] = "cd ", strfile[81][MAXFILES];
    printf("Enter path:([drive:][path]):\n");
    scanf("%s", &strpath[3]);
    system(&strpath);
    system("dir /b > ZZZZ.ZZZ");
    fptr = fopen("ZZZZ.ZZZ", "r");
    while(fgets(strfile[count++], 80, fptr) != NULL);
    fclose(fptr);
    system("del ZZZZ.ZZZ"); // delete zzzz.zzz, not part of origional dir
    // you now have an array of files strfile[]
    count = count - 3;
    do
	printf("%s", strfile[count]);
    while(--count >= 0);
    return 0;

}
