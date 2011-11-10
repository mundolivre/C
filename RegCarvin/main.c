// QueryKey - Enumerates the subkeys of key and its associated values.
//     hKey - Key whose subkeys and values are to be enumerated.

#include <stdio.h>
#include "registro.h"

void query();

int main(void)
{
   query();
   system("pause");
   return 0;
}

void query() {
   HKEY hTestKey;

   if( RegOpenKeyEx( HKEY_CURRENT_USER,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
      )
   {
      QueryKey(hTestKey);
   }
   
   RegCloseKey(hTestKey);	

   if( RegOpenKeyEx( HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
      )
   {
      QueryKey(hTestKey);
   }
   
   RegCloseKey(hTestKey);	
}
