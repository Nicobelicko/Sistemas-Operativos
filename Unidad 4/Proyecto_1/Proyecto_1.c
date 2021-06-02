#include <stdio.h>
#include <string.h>
#include <dirent.h>

void listar(char *nombre );
int main(int argc, char const *argv[])
{
    char *direccion;
    direccion = argv[1];
    printf("%s",direccion);
    listar(direccion);
    return 0;
}
void listar(char *nombre){
    DIR *dir = opendir(nombre);
    if(dir == NULL){
        return;
    }

    struct dirent* var;
    var = readdir(dir);
    while (var != NULL)
    {
        printf("%hd %s %s\n",var->d_type,nombre,var->d_name);
        if(var->d_type == 4 && strcmp(var->d_name,".") && strcmp(var->d_name,"..")){
            char direccion[100] = {0};
            strcat(direccion,nombre);
            strcat(direccion,"/");
            strcat(direccion,var->d_name);
            listar(direccion);
        }
        var = readdir(dir);
        
    }
    

    closedir(dir);
    
}

