/* main.c */

#include<stdio.h>
#include"security_data.h"


/*----------------------------START OF MAIN FUNCTION----------------------------*/
int main(int argc, char* argv[])/*receieve argc and argv*/
{
    int count;
    int exit_code = 1;
    security_log_t ** security_logs;
    
    /*Check if arguments include the file*/
    if (argc != 2)
    {
        /*if no file has been given in the arguments, then show the error message*/
        exit_code = 1;
        printf("Error! Please provide a filename\n");
    }
    else
    {
        /*Extract security logs*/
        security_logs = loading_data(argv[1], &count);
        if (security_logs != NULL)
        {
            /*Process and print security logs*/
            process_log(security_logs, count);
            
            exit_code = 0;/*change exit code*/
        }
        /*free logs*/ 
        free(security_logs);
    }

    return exit_code;/*return code*/
}
/*----------------------------END OF MAIN FUNCTION----------------------------*/