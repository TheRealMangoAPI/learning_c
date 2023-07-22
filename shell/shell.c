#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGUMENTS 10

void readUserInput(char* buffer) {
    printf("MangoAPI>> ");
    fgets(buffer, MAX_INPUT_LENGTH, stdin);
    size_t len = strlen(buffer);
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

void parseInput(char* input, char* command, char* arguments[]) {
    char* token = strtok(input, " ");
    strcpy(command, token);
    int argIndex = 0;
    while (token != NULL) {
        token = strtok(NULL, " ");
        if (token != NULL) {
            arguments[argIndex] = token;
            argIndex++;
        }
    }
    arguments[argIndex] = NULL;
}

void executeCommand(char* command, char* arguments[]) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char commandLine[MAX_INPUT_LENGTH];
    snprintf(commandLine, MAX_INPUT_LENGTH, "%s", command);
    for (int i = 0; arguments[i] != NULL && i < MAX_ARGUMENTS; i++) {
        strcat(commandLine, " ");
        strcat(commandLine, arguments[i]);
    }

    if (!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Failed to execute the command. Error: %lu\n", GetLastError());
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char command[MAX_INPUT_LENGTH];
    char* arguments[MAX_ARGUMENTS];

    while (1) {
        readUserInput(input);

        if (strcmp(input, "exit") == 0) {
            printf("Exiting the shell.\n");
            break;
        }

        parseInput(input, command, arguments);
        executeCommand(command, arguments);
    }

    return 0;
}
