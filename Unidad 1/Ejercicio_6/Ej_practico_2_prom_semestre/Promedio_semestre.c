#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char FILE_TO_READ[] = "datos_lectura.txt";
char *concat(const char *s1, const char *s2);

int main()
{
    //printf("llega hasta 0");
    int num_materias, won, lost, num_creditos;
    double promedio, promedio_ponderado;

    char linea;
    //printf("llega hasta 1");

    int won, lost;
    double promedio;
    char nota[4];
    char creditos[1];
    int counter = 1;
    FILE *read, *write;

    read = fopen(FILE_TO_READ, "r");
    write = fopen("informe_semestre.txt", "r+");
    if (read == NULL)
    {
        printf("Error al abrir el archivo: %s", FILE_TO_READ);
    }
    while (1)
    {
        if (feof(read))
            break;
        linea = fgetc(read);

        if (linea == '\n')
        {

            if (counter == 3)
            {
                if (feof(read))
                    break;
                fputc(' ', write);
            }
            else
            {
                fputc('-', write);
                fputc('-', write);
            }
            if (feof(read))
                break;
            linea = fgetc(read);

            if (counter == 3)
            {
                fputc('\n', write);
                counter = 0;
                if (feof(read))
                    break;
            }
            counter++;
        }

        fputc(linea, write);
    }



    fclose(read);
    fclose(write);
}
char *concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}