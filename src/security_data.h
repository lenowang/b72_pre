#ifndef SECURITY_DATA_H
#define SECURITY_DATA_H

#define MAX_DESCRIPTION_LENGTH 255
#define MAX_NAME_LENGTH 127

#include<stdio.h>
#include<stdlib.h>
#include"string.h"
#include<time.h>

typedef struct object
{
    int ID;
    char * name;
    char * description;

} object_t;/*Object Struct*/

typedef struct log_entry
{
    time_t start_time;
    time_t end_time;
    char cameras;
    float confidence_value;
    object_t * object;

} log_entry_t;/*Log Entry Struct*/

typedef struct date
{
    int year;
    int month;
    int date;

} date_t;/*Date Struct*/

typedef struct security_log
{
    date_t * date;
    log_entry_t * log_entry_array; /* A one-dimensional array of log entries of log_entry data-type*/
    
} security_log_t;/*Security Log Struct*/

security_log_t** loading_data(const char* filename, int * count);
int process_log(security_log_t ** security_logs, int count);
void free_security_logs(security_log_t ** security_logs, int count);
#endif