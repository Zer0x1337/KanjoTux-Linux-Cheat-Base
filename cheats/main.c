/*

If you have any questions ask in issues.

Check this out: https://www.linuxjournal.com/article/6210

*/
    
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ptrace.h>
#include <errno.h>
#include <limits.h>  // for INT_MAX, INT_MIN
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
//#include "../offsets.h"

int u_option;
int loop = 1;


// offsets
int long sellxploit_addr = 0x161c98838;
int long infmoney_addr = 0x161c98854;


struct StockPid
{
    pid_t pid;
    char buff[512];
    FILE *pid_pipe;
} stockthepid;
     
void Func_StockPid(const char *processtarget)
{
    stockthepid.pid_pipe = popen(processtarget, "r");
    fgets(stockthepid.buff, 512, stockthepid.pid_pipe);
    stockthepid.pid = strtoul(stockthepid.buff, NULL, 10);
     
    if (stockthepid.pid == 0)
    {
        printf("Kanjozoku isn't open! \n");
        pclose(stockthepid.pid_pipe);
        exit(-1);
    }
    else
    {
        printf("Kanjozoku is running - [PID:%d] \n", stockthepid.pid);
        pclose(stockthepid.pid_pipe);
    }
}
     
void ReadProcessMemory(unsigned long address, int pid) {
     
    int buf = 0;
     
    int err_code = ptrace(PTRACE_ATTACH, stockthepid.pid, NULL, NULL);
     
    if (err_code == -1)
    {
        printf("%s\n", "error 1");
        exit(-1);
    }
    wait(NULL);
     
    for (int i = 0; i < 1; i++) 
    {
        buf = ptrace(PTRACE_PEEKDATA, stockthepid.pid, address + i * sizeof(int), NULL);
        if (buf == -1)
        {
            printf("%s\n", "error 2");
            exit(-1);
        }
     
        //printf("%d\n", buf);
           
    }
    err_code = ptrace(PTRACE_DETACH, stockthepid.pid, NULL, NULL);
    if (err_code == -1)
    {
            printf("%s\n", "error 3");
            exit(-1);
    } 
}
     
void WriteProcessMemory(unsigned long address, int pid) {
    int buf = 0;
    //int WhatValue = 0;
        
    //printf("Enter how much you want everything to cost (must be above 0): ");
    //scanf("%d", &WhatValue);

    //printf("Everything is now FREE!\n");

    if (u_option == 1) {
        printf("All items are now FREE\n");
    }
    if (u_option == 2) {
        printf("All Cars Sell For $10000000\n");
    }
        

    while (loop != 0) {

     
        int err_code = ptrace(PTRACE_ATTACH, stockthepid.pid, NULL, NULL);
        if (err_code == -1)
        {
            printf("%s\n", "error 1");
            exit(-1);
        }
        
        wait(NULL);

        for (int i = 0; i < 1; i++) {

            if (u_option == 1) {
                buf = ptrace(PTRACE_POKEDATA, stockthepid.pid, address + i * sizeof(int), 1); // changing value
            }
            else if (u_option == 2) {
                buf = ptrace(PTRACE_POKEDATA, stockthepid.pid, address + i * sizeof(int), 100000000);
            }

            if (buf == -1)
            {
                printf("%s\n", "error 2");
                exit(-1);
            }
        } 
        err_code = ptrace(PTRACE_DETACH, stockthepid.pid, NULL, NULL);
        if (err_code == -1) 
        {
            printf("%s\n", "error 3");
            exit(-1);
        }

        sleep(1);
    }
}
     
     
int main(int argc, char *argv[])
{
    char *p;
    errno = 0;
    long conv = strtol(argv[1], &p, 10);

        
    /* https://stackoverflow.com/a/9748431 */
    //
    // Check for errors: e.g., the string does not represent an integer
    // or the integer is larger than int
    if (errno != 0 || *p != '\0' || conv > INT_MAX || conv < INT_MIN) {
        // Put here the handling of the error, like exiting the program with
        // an error message
    } else {
        // No error
        u_option = conv;
        printf("%d\n", u_option);
    }


    system("clear");

    Func_StockPid("pidof -s Kanjozoku\\ Game.");
    if (u_option == 1) {
        ReadProcessMemory(infmoney_addr, stockthepid.pid); // put address here
        WriteProcessMemory(infmoney_addr, stockthepid.pid); // put same address here too
    }
    if (u_option == 2) {
        ReadProcessMemory(sellxploit_addr, stockthepid.pid); // put address here
        WriteProcessMemory(sellxploit_addr, stockthepid.pid); // put same address here too
    }

        
    return 0;
}
