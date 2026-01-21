# Security system

This simple security system is built in C that deals with security camera data. It will only let you to read security camera data from a file and print the data.
The security log is given and should not be modified or deleted.

## How to Build
Make sure that the following commands are exceuted form the root of the directory (where makefile is located basically).

To build the project, you can use the `make` command:

```
make
```

This will create an executable file named `security_program` in bin.

## How to Run

To run the program, you can use the following command with the file:

```bash
./bin/security_program logs/securitylogs.txt
```

To run valgrid to see if there are any memory leaks:

```
make runval PARAMS="logs/securitylogs.txt"
```


## Files

*   **main.c**: The main program file.
*   **security_data.c**: Contains the functions for managing security camera data.
*   **security_data.h**: The header file for `security_data.c`.
*   **securitylogs.txt**: The default data file.
*   **makefile**: The makefile for building the project.

## Author

Jevi Waugh