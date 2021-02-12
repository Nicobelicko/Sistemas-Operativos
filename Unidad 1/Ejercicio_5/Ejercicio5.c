#include <stdio.h>

int main()
{
    float num1, num2,resultado;
    char signo, control;
    control = 's';
    do{
        printf("Ingrese el Primer digito \n");
        scanf("%f", &num1);
        printf("El primer digito es: %.3f\n", num1);
        printf("Ingrese el segundo digito \n");
        scanf("%f", &num2);
        printf("El segundo digito es ..: %.3f\n", num2);
        printf("Ingrese la operacion a realizar: + , - , / , * \n");
        scanf("\n%c", &signo);
        printf("El signo de la operacion es : %c\n", signo);

        switch(signo){

           case '+': 
                printf("\nLa operación es suma");
                 resultado = num1 + num2;
                break;

            case '-': 
                printf("\nLa operación es resta");
                resultado = num1 - num2;
                break;

            case '*': 
                printf("\nLa operación es Multiplicacion");
                resultado = num1 * num2;
                break;

            case '/': 
                printf("\nLa operación es Division");
                resultado = num1 / num2;
                break;
        } 

        printf("\n\nEl resultado de la operación es: %.3f\n", resultado);
         scanf("\n%c", &control);


    }while(control != 'q');
    return 0;
}