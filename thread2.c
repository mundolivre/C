#include <Windows.h>
#include <stdio.h>

// Shared global variables

CRITICAL_SECTION g_cs;
WCHAR message[] = L"Hello I'm new Thread";

DWORD WINAPI thread_function(LPVOID arg)
{
      int count2;
      wprintf(L"thread_function() is running. Argument received was: %s\n", arg);
      wprintf(L"Child thread entering critical section, doing job & leaving critical section...\n");
      wprintf(L"\n");
      for (count2 = 0; count2 < 10; count2++)
      {
            // Waits for ownership of the specified critical section object.
            // The function returns when the calling thread is granted ownership.
            // This function does not return a value.
            EnterCriticalSection(&g_cs);
            wprintf(L"Y ");
            // Releases ownership of the specified critical section object.
            // This function does not return a value.
            LeaveCriticalSection(&g_cs);
      }
      Sleep(4000);
      return 0;
}

int main()
{
      HANDLE a_thread;
      DWORD a_threadId;
      DWORD thread_result;
      int count1;
      // Some info
      wprintf(L"The current process ID is %u\n", GetCurrentProcessId());
      wprintf(L"The main thread ID is %u\n", GetCurrentThreadId());
      wprintf(L"\n");
      // Initializes a critical section object.
      // This function does not return a value.
      InitializeCriticalSection(&g_cs);
      // Create a new thread.
      a_thread = CreateThread(NULL, 0, thread_function, (LPVOID)message, 0, &a_threadId);
      if (a_thread == NULL)
      {
            wprintf(L"CreateThread() - Thread creation failed, error %u\n", GetLastError());
            exit(EXIT_FAILURE);
      }
      else
	  wprintf(L"CreateThread() is OK, thread ID is %u\n", a_threadId);
      wprintf(L"main() thread entering critical section, doing job & leaving critical section...\n");
      wprintf(L"Entering main() loop...\n");
      for (count1 = 0; count1 < 10; count1++)
      {
            EnterCriticalSection(&g_cs);
            wprintf(L" X");
            LeaveCriticalSection(&g_cs);
      }
      Sleep(3000);
      wprintf(L"\n\nWaiting for thread %u to finish...\n", a_threadId);
      if (WaitForSingleObject(a_thread, INFINITE) != WAIT_OBJECT_0)
      {
            wprintf(L"WaitForSingleObject() - Thread join failed, error %u", GetLastError());
            exit(EXIT_FAILURE);
      }
      else
            wprintf(L"WaitForSingleObject() is OK! An object was signaled\n");
           // Retrieve the code returned by the thread.
      if(GetExitCodeThread(a_thread, &thread_result) != 0)
            wprintf(L"GetExitCodeThread() is OK! Thread joined, exit code %u\n", thread_result);
      else
            wprintf(L"GetExitCodeThread() failed, error %u\n", GetLastError());
      if(CloseHandle(a_thread) != 0)
            wprintf(L"a_thread handle was closed successfully!\n");
      else
            wprintf(L"Failed to close a_thread handle, error %u\n", GetLastError());
      // Releases all resources used by an unowned critical section object.
      // This function does not return a value.
      wprintf(L"Deleting critical section resources...\n");
      DeleteCriticalSection(&g_cs);
      system("pause");
      exit(EXIT_SUCCESS);
}
