#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t stringLength(const char* string) {
    size_t length = 0;
    while (*(string++)) {
        length++;
    }
    return length;
}

int main() {
//    char header[13];
//    strcpy(header, "Media player");
//    printf("%s\n", header);
//    int i;
//    for (i = 0; i < strlen(header); i++) {
//        printf("header[%d] : %c \n", i, header[i]);
//    }
    char* error = "ERROR: ";
    char* errorMessage = "Not enough memory";
    char* buffer = (char*) malloc(strlen(error) + strlen(errorMessage));
    strcpy(buffer, error);
    strcat(buffer, errorMessage);

//    printf("%s\n", buffer);
//    printf("%s\n", error);
//    printf("%s\n", errorMessage);
//    for (int i = 0; i < strlen(buffer); i++) {
//        printf("header[%d] : %c \n", i, buffer[i]);
//    }

    printf("%d\n", stringLength("Hello moto"));

    return 0;
}

