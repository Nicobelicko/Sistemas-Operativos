#include <studio.h>

int main(void){
    int num1,num2;
    char op;
    do{
        printf("Ingrese los numeros y luego el operando");
        printf("\n 'x' Multiplicar\n'+' Sumar\n'-'Restar");
        num1 = getchar();
        num2 = getchar();
        op = getchar();

        if(op == 'x') producto(num1,num2)
        else if (op == '+') suma(num1,num2)
        else if (op == '-') resta(num1,num2)
        else printf('El operando no se reconoce');
    }while(num1!= 'q' && num2!= 'q')
    return(0);
}
void producto(int n1, int n2){
    printf(n1*n2);
}
void suma(int n1, int n2){
    printf(n1*n2);
}
void resta(int n1, int n2){
    printf(n1*n2);
}