//Написать программу, которая создает файл с именем output.txt,
//записывает в него строку “String from file”, затем считывает ее из файла
//с конца и выводит на экран.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//FILE *file;

void *file_handling(char *file_name, char * data_format, char *file_data, bool printf_by_back);

int main()
{

    char outputText[] = "String from file";
    int length, i;


    file_handling("output.txt", NULL ,NULL , false); // File creating

    file_handling("output.txt", "%s" , "String from file", false); // Write the string "tring from file” to a file

    file_handling("output.txt", NULL , NULL, true); // Prining line from the end


    return 0;

}


void *file_handling(char *file_name, char * data_format, char *file_data, bool printf_by_back)
{
    FILE *file;
    int length, i;

    file = fopen(file_name, "a+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, data_format ,file_data);

    if(printf_by_back)
    {
        fseek(file, 0, SEEK_END);
        length = ftell(file);

        for (i = 1; i <= length; i++) {
            fseek(file, -i, SEEK_END);
            printf("%c", fgetc(file));
            }
        printf("\n");
    }

    fclose(file);
}