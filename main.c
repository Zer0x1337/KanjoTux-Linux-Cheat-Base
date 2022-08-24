    #include <stdio.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <sys/ptrace.h>
    #include <errno.h>
    #include <string.h>
    #include <fcntl.h>
    #include <stdlib.h>

    int u_option = 1;

     
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

        printf("Everything is now FREE!\n");
        while (u_option != 0) {

     
            int err_code = ptrace(PTRACE_ATTACH, stockthepid.pid, NULL, NULL);
            if (err_code == -1)
            {
                printf("%s\n", "error 1");
                exit(-1);
            }
        
            wait(NULL);

            for(int i = 0; i < 1; i++) {
                buf = ptrace(PTRACE_POKEDATA, stockthepid.pid, address + i * sizeof(int), 1);
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
     
     
    int main()
    {
        /*
        int addr;

        system("clear");

        printf("Enter Current Address (Example: 0x79508c94): ");

        scanf("%x", &addr);
        */

        system("clear");

        Func_StockPid("pidof -s Kanjozoku\\ Game.");
        ReadProcessMemory(0x79508c94, stockthepid.pid); // put address here
        WriteProcessMemory(0x79508c94, stockthepid.pid); // put same address here too

        
        return 0;
    }
