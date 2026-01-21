#include<stdio.h>
#include<stdlib.h>
#include"string.h"
#include"security_data.h"

/*Read security log and allocate*/
security_log_t** loading_data(const char* filename, int* count)
{
    /* Declaring all variables first */
    
    FILE* security_file;
    char line[256];
    char* token;
    security_log_t* log;
    security_log_t** security_logs;

    /* To store the most recent date */
    int current_year = 0, current_month = 0, current_day = 0; 
    /* Temporary variables for parsing date line */
    int temp_year, temp_month, temp_day; 

    *count = 0;
    security_file = fopen(filename, "r");
    if (security_file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    /* This is the first pass to count the number of log entries */
    while (fgets(line, sizeof(line), security_file) != NULL) {
        if (line[0] == '\n') {
            continue;
        }
        /* Check if it's a date line, if not, it's a log entry */
        if (sscanf(line, "%d-%d-%d", &temp_year, &temp_month, &temp_day) != 3) {
            (*count)++;
        }
    }
    
    rewind(security_file);

    /* Allocate memory for the array of pointers and the log structs in a single block */
    security_logs = malloc(*count * sizeof(security_log_t*) + *count * sizeof(security_log_t));
    if (security_logs == NULL) {
        perror("Failed to allocate memory for security logs");
        fclose(security_file);
        return NULL;
    }

    /* The log structs start right after the array of pointers */
    log = (security_log_t*)(security_logs + *count);

    /* We reset the count for the second pass */
    *count = 0;

    /* Initialize current date variables in case the first entry was a log without a preceding date */
    current_year = 0;
    current_month = 0;
    current_day = 0;

    while (fgets(line, sizeof(line), security_file) != NULL) {
        if (line[0] == '\n') {
            continue;
        }

        if (sscanf(line, "%d-%d-%d", &temp_year, &temp_month, &temp_day) == 3) {
            /* This is a date line, update current date variables */
            current_year = temp_year;
            current_month = temp_month;
            current_day = temp_day;
            continue;
        }

        /* If we reach here the block of code, then it's a
            log entry line, use the current date */
        /* Point to the next available log struct */
        security_logs[*count] = &log[*count];

        log[*count].date = malloc(sizeof(date_t));
        log[*count].log_entry_array = malloc(sizeof(log_entry_t));
        log[*count].log_entry_array->object = malloc(sizeof(object_t));
        log[*count].log_entry_array->object->name = malloc(MAX_NAME_LENGTH * sizeof(char));
        log[*count].log_entry_array->object->description = malloc(MAX_DESCRIPTION_LENGTH * sizeof(char));


        log[*count].date->year = current_year;
        log[*count].date->month = current_month;
        log[*count].date->date = current_day;

        /*Passing start and end time*/
        token = strtok(line, "$");
        log[*count].log_entry_array->start_time = atol(token);

        token = strtok(NULL, "$");
        log[*count].log_entry_array->end_time = atol(token);

        /*Get camera data*/
        fgets(line, sizeof(line), security_file);
        sscanf(line, " %c", &log[*count].log_entry_array->cameras);

        /*Get confidence value*/
        fgets(line, sizeof(line), security_file);
        sscanf(line, "%f", &log[*count].log_entry_array->confidence_value);

        /*Get the last line of teh log which has ID, name and desc*/
        fgets(line, sizeof(line), security_file);
        token = strtok(line, "$");
        log[*count].log_entry_array->object->ID = atoi(token);
        token = strtok(NULL, "$");

        strcpy(log[*count].log_entry_array->object->name, token);
        token = strtok(NULL, "\n");
        strcpy(log[*count].log_entry_array->object->description, token);

        /*Increment the log count*/
        (*count)++;
    }

    /*Close the file and return */
    fclose(security_file);
    return security_logs;
}

/*Process security log and print*/
int process_log(security_log_t ** security_logs, int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (security_logs[i]->log_entry_array->confidence_value > 70.0)
        {
            printf("Date: %d-%d-%d\n", security_logs[i]->date->year, security_logs[i]->date->month, security_logs[i]->date->date);
            printf("Object name and description: %s %s\n", security_logs[i]->log_entry_array->object->name, security_logs[i]->log_entry_array->object->description);
            printf("Cameras: %c\n", security_logs[i]->log_entry_array->cameras);
            printf("Confidence: %.2f%%\n", security_logs[i]->log_entry_array->confidence_value);
        }
    }

    return 0;
}
