#include <stdio.h>
#include <stdlib.h>

#define N 50
#define SEDENTARIO 1.1;
#define SEMIACTIVO 1.22;
#define ACTIVO 1.5;
#define MUYACTIVO 1.7;

struct Nodo {
    char nombre[N], apellido[N], telefono[N], mail[N], sexo[N];
    float peso, altura;
    int edad;
    struct Nodo *siguiente;
};

struct List {
    struct Nodo *cabecera;
};

void toLowercase(char v1[]);

void seeClient(struct Nodo nodo);

void startList(struct List *l);

int equals(char v1[], char v2[]);

int length(char v1[]);

void toUppercase(char v1[]);

void fillList(FILE *fp, struct List *l);

void searchClient(struct List *l);

void addClient(struct List *l, struct Nodo nodo);

void deleteClient(struct List *l, struct Nodo nodo);

void seeClients(struct List *l);

void editClient(struct List *l);

void saveClients(struct List *l, FILE *fp);

// Calculo del TMB (Tasa Metabolica Basal)
float tasaMetablicaBasalHombre(float peso, float edad, float altura);

float tasaMetablicaBasalMujer(float peso, float edad, float altura);

// Calculo del GET (Gasto Energetico Total)
float gastoEnergeticoTotalHombre(float tmbh);

float gastoEnergeticoTotalMujer(float tmbm);

// Calculo de Proteinas
float calculoProteina(float peso);

// Calculo de Grasas
float calculoGrasas(float peso);

// Calculo de Hidratos
float calculoHidratosHombre(float proteina, float grasas, float tmbh, float geth);

float calculoHidratosMujer(float proteina, float grasas, float tmbm, float getm);

int main()
{
    struct List list;
    struct Nodo client;
    char op;
    
    FILE *fp;
    
    fp = fopen(".Clients.txt", "r");
    
    if (fp == NULL) {
        //printf("Error al abrir el fichero.\n");
        fp = fopen(".Clients.txt", "w");
        fclose(fp);
    }
    else {
        startList(&list);
        fillList(fp, &list);
        
        fclose(fp);
        do {
            printf("\t-----MENU-----\n");
            printf("1. Buscar Cliente\n");
            printf("2. Eliminar Cliente\n");
            printf("3. Añadir Cliente\n");
            printf("4. Editar Cliente\n");
            printf("5. Lista de Clientes\n");
            printf("6. Guardar Clientes\n");
            printf("0. Salir\n\n");
            
            printf("Opcion: ");
            
            fflush(stdin);
            scanf("%c", &op);
            
            switch (op) {
                case '0':
                    printf("\nAdios\n");
                    break;
                case '1':
                    searchClient(&list);
                    break;
                case '2':
                    printf("\nComo se llama el contacto que desea borrar?? ");
                    scanf("%s", client.nombre);
                    deleteClient(&list, client);
                    break;
                case '3':
                    
                    printf("Nombre: "); fflush(stdin); scanf("%s", client.nombre);
                    toUppercase(client.nombre);
                    printf("Apellido: "); fflush(stdin); scanf("%s", client.apellido);
                    toUppercase(client.apellido);
                    do {
                        printf("Telefono: "); fflush(stdin); scanf("%s", client.telefono);
                        if (length(client.telefono) != 9) {
                            printf("Ocurrio un error al guardar el Telefono.\n");
                        }
                    } while (length(client.telefono) != 9 );
                    printf("Mail: "); fflush(stdin); scanf("%s", client.mail);
                    toLowercase(client.mail);
                    printf("El cliente es Hombre o Mujer: "); fflush(stdin); scanf("%s", client.sexo);
                    toUppercase(client.sexo);
                    do {
                        printf("Edad: "); fflush(stdin); scanf("%d", &client.edad);
                        if (client.edad < 1 || client.edad > 99)
                        {
                            printf("La edad Introducida no es Correcta. Vuelva a Intentarlo.\n");
                        }
                    } while (client.edad < 1 || client.edad > 99);
                    printf("Peso: "); fflush(stdin); scanf("%f", &client.peso);
                    printf("Altura (En Centimetros): "); fflush(stdin); scanf("%f", &client.altura);
                    
                    addClient(&list, client);
                    
                    printf("\nContacto Añadido Correctamente!!\n\n");
                    break;
                case '4':
                    editClient(&list);
                    break;
                case '5':
                    seeClients(&list);
                    printf("\n");
                    break;
                case '6':
                    saveClients(&list,fp);
                    break;
                default: printf("\nOpcion Incorrecta.\n\n");
                    break;
            }
        } while (op != '0');
    }
    return EXIT_SUCCESS;
}

void startList(struct List *l) {
    l->cabecera = NULL;
}

int equals(char v1[], char v2[]){
    int i = 0;
    while (v1[i] != '\0' && v2[i] != '\0' && v1[i] == v2[i]) {
        i++;
    }
    return v1[i] == v2[i];
}

void toLowercase(char v1[]){
    int i = 0;
    while (v1[i] != '\0') {
        if (v1[i] >= 'A' && v1[i] <= 'Z') {
            v1[i] += ('a' - 'A') ;
            i++;
        }
        else i++;
    }
}

void toUppercase(char v1[]){
    int i = 0;
    while (v1[i] != '\0') {
        if (v1[i] >= 'a' && v1[i] <= 'z') {
            v1[i] -= ('a' - 'A') ;
            i++;
        }
        else i++;
    }
}

void searchClient(struct List *l){
    char client[N], desicion;
    struct Nodo *nodo;
    int enc = 0;
    float proteina, hidratos, grasas;
    float tmbh = 0, tmbm = 0, geth = 0, getm = 0;
    
    nodo = l->cabecera;
    
    printf("\nCual es el Apellido del cliente? ");
    scanf("%s", client);
    
    toUppercase(client);
    
    while (nodo != NULL && !enc) {
        if (equals(nodo->apellido, client)) {
            enc = 1;
        }
        else nodo = nodo->siguiente;
    }
    if (nodo == NULL) {
        printf("\nEl Cliente que busca no se encuentra en la agenda.\n");
    }
    else {
        printf("\nEl Cliente es: "); seeClient(*nodo);
        
        printf("\nDesea Realizar los Calculos Corporales: (S/N)");
        fflush(stdin);
        scanf("%c", &desicion);
        
        if (desicion == 's' && equals(nodo->sexo, "HOMBRE")) {
            // TMB
            tmbh = tasaMetablicaBasalHombre(nodo->peso, nodo->edad, nodo->altura);
            
            // GET
            geth = gastoEnergeticoTotalHombre(tmbh);
            
            printf("\n");
            
            proteina = calculoProteina(nodo->peso);
            grasas = calculoGrasas(nodo->peso);
            
            printf("\n");
            
            hidratos = calculoHidratosHombre(proteina, grasas, tmbh, geth);
            
            printf("\tLos Calculos son los Siguientes:\n");
            printf("\tTMB: %.2f\n", tmbh);
            printf("\tGET: %.2f\n", geth);
            printf("\tProteina: %.2f\n", proteina);
            printf("\tGrasas: %.2f\n", grasas);
            printf("\tHidratos: %.2f\n", hidratos);
        }
        else if (desicion == 's' && equals(nodo->sexo, "MUJER")){
            // TMB
            tmbm = tasaMetablicaBasalMujer(nodo->peso, nodo->edad, nodo->altura);
            
            // GET
            getm = gastoEnergeticoTotalMujer(tmbm);
            
            printf("\n");
            
            proteina = calculoProteina(nodo->peso);
            grasas = calculoGrasas(nodo->peso);
            
            printf("\n");
            
            hidratos = calculoHidratosMujer(proteina, grasas, tmbm, getm);
            
            printf("\tLos Calculos son los Siguientes:\n");
            printf("\tTMB: %.2f\n", tmbm);
            printf("\tGET: %.2f\n", getm);
            printf("\tProteina: %.2f\n", proteina);
            printf("\tGrasas: %.2f\n", grasas);
            printf("\tHidratos: %.2f\n", hidratos);
        }
        printf("\n");
    }
}

void seeClient(struct Nodo nodo){
    printf("%s %s ( %s )\n", nodo.nombre, nodo.apellido, nodo.telefono);
}

void addClient(struct List *l, struct Nodo nodo){
    struct Nodo *nuevo, *actual, *anterior;
    
    nuevo = (struct Nodo *) malloc(sizeof(struct Nodo));
    
    *nuevo = nodo;
    
    if (l->cabecera == NULL) {
        l->cabecera = nuevo;
        l->cabecera->siguiente = NULL;
    }
    else if (nuevo->nombre[0] <= l->cabecera->nombre[0]){
        nuevo->siguiente = l->cabecera;
        l->cabecera = nuevo;
    }
    else {
        anterior = l->cabecera;
        actual = l->cabecera;
        while (actual->nombre[0] < nuevo->nombre[0] && actual->siguiente != NULL) {
            anterior = actual;
            actual = actual->siguiente;
        }
        if (actual->siguiente == NULL && anterior->nombre[0] <= nuevo->nombre[0] && actual->nombre[0] <= nuevo->nombre[0]) {
            actual->siguiente = nuevo;
            nuevo->siguiente = NULL;
        }
        else {
            anterior->siguiente = nuevo;
            nuevo->siguiente = actual;
        }
    }
}

void deleteClient(struct List *l, struct Nodo nodo){
    struct Nodo *actual, *anterior, *aux;
    int enc = 0;
    
    toUppercase(nodo.nombre);
    
    actual = l->cabecera;
    anterior = NULL;
    
    while (actual != NULL && !enc) {
        if (equals(actual->nombre,nodo.nombre)) {
            enc = 1;
        }
        else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
    if (enc && actual != l->cabecera) {
        aux = actual;
        actual = actual->siguiente;
        anterior->siguiente = actual;
        free(aux);
        printf("\nCliente borrado correctamente!!\n\n");
    }
    else if (enc && actual == l->cabecera) {
        l->cabecera = actual->siguiente;
        free(actual);
        printf("\nCliente borrado correctamente!!\n\n");
    }
    else printf("\nNo se encontro el Cliente en la lista!!\n\n");
}

void fillList(FILE *fp, struct List *l){
    struct Nodo nodo;
    
    fscanf(fp, "%s", nodo.nombre);
    fscanf(fp, "%s", nodo.apellido);
    fscanf(fp, "%s", nodo.telefono);
    fscanf(fp, "%s", nodo.mail);
    fscanf(fp, "%d", &nodo.edad);
    fscanf(fp, "%f", &nodo.peso);
    fscanf(fp, "%f", &nodo.altura);
    fscanf(fp, "%s", nodo.sexo);
    
    while (!feof(fp)) {
        addClient(l, nodo);
        fscanf(fp, "%s", nodo.nombre);
        fscanf(fp, "%s", nodo.apellido);
        fscanf(fp, "%s", nodo.telefono);
        fscanf(fp, "%s", nodo.mail);
        fscanf(fp, "%d", &nodo.edad);
        fscanf(fp, "%f", &nodo.peso);
        fscanf(fp, "%f", &nodo.altura);
        fscanf(fp, "%s", nodo.sexo);
    }
}

void seeClients(struct List *l){
    struct Nodo *nodo;
    nodo = l->cabecera;
    
    if (nodo == NULL) {
        printf("\nLa lista esta vacia.\n\n");
    }
    else {
        while (nodo != NULL) {
            printf("\nNombre: %s %s (%s) %s\n", nodo->nombre, nodo->apellido, nodo->telefono, nodo->mail);
            printf("\tEdad: %d.\n\tPeso: %.2f.\n\tAltura: %.2f\n", nodo->edad, nodo->peso, nodo->altura);
            nodo = nodo->siguiente;
        }
    }
}

void editClient(struct List *l){
    char contact[N], op[N];
    struct Nodo *nodo;
    int enc = 0;
    
    nodo = l->cabecera;
    
    printf("\nCual es el Apellido del Cliente que desea modificar?? ");
    scanf("%s", contact);
    
    toUppercase(contact);
    
    while (nodo != NULL && !enc) {
        if (equals(nodo->apellido, contact)) {
            enc = 1;
        }
        else nodo = nodo->siguiente;
    }
    if (nodo == NULL) {
        printf("\nEl contacto que busca no se encuentra en la agenda.\n\n");
    }
    else {
        printf("\nEl contacto es: "); seeClient(*nodo);
        do {
            printf("\nQue dato desea editar???\n\n");
            printf("1. Telefono\n2. Edad,\n3. Altura.\n4. Peso\n5. Mail\n0. Cancelar\n\n");
            printf("Opcion: ");
            fflush(stdin);
            scanf("%s", op);
            
            if (equals("1", op) || equals("Telefono", op) || equals("telefono", op)){
                do {
                    printf("Cual es su telefono nuevo?? "); fflush(stdin); scanf("%s", nodo->telefono);
                    if (length(nodo->telefono) != 9) {
                        printf("Ocurrio un error al guardar el Telefono.\n");
                    }
                } while (length(nodo->telefono) != 9 );
                printf("Contacto editado correctamente.\n\n");
            } else if (equals("2", op) || equals("Edad", op) || equals("edad", op)){
                do {
                    printf("Cual es su nueva Edad?? "); fflush(stdin); scanf("%d", &nodo->edad);
                    if (nodo->edad < 1 || nodo->edad > 99)
                    {
                        printf("La edad Introducida no es Correcta. Vuelva a Intentarlo.\n");
                    }
                } while (nodo->edad < 1 || nodo->edad > 99);
                printf("Contacto editado correctamente.\n\n");
            } else if (equals("3", op) || equals("Altura", op) || equals("altura", op)){
                printf("Cual es su nueva Altura?? ");
                scanf("%f", &nodo->altura);
                printf("Contacto editado correctamente.\n\n");
            } else if (equals("4", op) || equals("Peso", op) || equals("peso", op)){
                printf("Cual es su nuevo Peso?? ");
                scanf("%f", &nodo->peso);
                printf("Contacto editado correctamente.\n\n");
            } else if (equals("5", op) || equals("Mail", op) || equals("mail", op)){
                printf("Cual es su nuevo Mail?? ");
                scanf("%s", nodo->mail);
                toLowercase(nodo->mail);
                printf("Contacto editado correctamente.\n\n");
            } else if (equals("0", op) || equals("Cancelar", op) || equals("cancelar", op)){
                break;
            }
            else printf("\nLa Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n\n");
        } while (!equals("1", op) && !equals("Telefono", op) && !equals("telefono", op) &&
                 !equals("2", op) && !equals("Edad", op) && !equals("edad", op) &&
                 !equals("3", op) && !equals("Altura", op) && !equals("altura", op) &&
                 !equals("4", op) && !equals("Peso", op) && !equals("peso", op) &&
                 !equals("5", op) && !equals("Mail", op) && !equals("mail", op) &&
                 !equals("0", op) && !equals("Cancelar", op) && !equals("cancelar", op));
    }
}

void saveClients(struct List *l, FILE *fp){
    struct Nodo *nodo;
    
    fp = fopen(".Clients.txt", "w");
    
    nodo = l->cabecera;
    
    while (nodo != NULL) {
        fprintf(fp, "%s\n%s\n%s\n%s\n%d\n%.2f\n%.2f\n%s\n", nodo->nombre, nodo->apellido, nodo->telefono, nodo->mail, nodo->edad, nodo->peso, nodo->altura, nodo->sexo);
        nodo = nodo->siguiente;
    }
    fclose(fp);
    printf("\nClientes guardados con exito.\n\n");
}

float tasaMetablicaBasalHombre(float peso, float edad, float altura)
{
    return 66 + (13.7 * peso) + (5 * altura) - (6.8 * edad);
}

float tasaMetablicaBasalMujer(float peso, float edad, float altura)
{
    return 655 + (9.6 * peso) + (1.8 * altura) - (4.7 * edad);
}

float gastoEnergeticoTotalHombre(float tmbh)
{
    float resul = 0;
    char op[11];
    
    do
    {
        printf("\nIntroduce el Factor de actividad del Cliente: \n");
        printf("1. Sedentario.\n");
        printf("2. Semiactivo.\n");
        printf("3. Activo.\n");
        printf("4. Muy Activo.\n\n");
        
        printf("Opcion: ");
        
        fflush(stdin);
        scanf("%s", op);
        
        if (equals("1", op) || equals("Sedentario", op) || equals("sedentario", op))
        {
            resul = tmbh * SEDENTARIO;
        }
        else if (equals("2", op) || equals("Semiactivo", op) || equals("semiactivo", op))
        {
            resul = tmbh * SEMIACTIVO;
        }
        else if (equals("3", op) || equals("Activo", op) || equals("activo", op))
        {
            resul = tmbh * ACTIVO;
        }
        else if (equals("4", op) || equals("Muy Activo", op) || equals("muy activo", op) || equals("Muy activo", op) || equals("muy Activo", op))
        {
            resul = tmbh * MUYACTIVO;
        }
        else
        {
            printf("\nLa Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n\n");
        }
    } while (!equals("1", op) && !equals("2", op) && !equals("3", op) && !equals("4", op) &&
             !equals("Sedentario", op) && !equals("sedentario", op) &&
             !equals("Semiactivo", op) && !equals("semiactivo", op) &&
             !equals("Activo", op) && !equals("activo", op) &&
             !equals("Muy Activo", op) && !equals("muy activo", op) &&
             !equals("Muy activo", op) && !equals("muy Activo", op));
    
    return resul;
}

float gastoEnergeticoTotalMujer(float tmbm)
{
    float resul = 0;
    char op[11];
    
    do
    {
        printf("\nIntroduce el Factor de actividad del Cliente: \n");
        printf("1. Sedentario.\n");
        printf("2. Semiactivo.\n");
        printf("3. Activo.\n");
        printf("4. Muy Activo.\n\n");
        
        printf("Opcion: ");
        
        fflush(stdin);
        scanf("%s", op);
        
        if (equals("1", op) || equals("Sedentario", op) || equals("sedentario", op))
        {
            resul = tmbm * SEDENTARIO;
        }
        else if (equals("2", op) || equals("Semiactivo", op) || equals("semiactivo", op))
        {
            resul = tmbm * SEMIACTIVO;
        }
        else if (equals("3", op) || equals("Activo", op) || equals("activo", op))
        {
            resul = tmbm * ACTIVO;
        }
        else if (equals("4", op) || equals("Muy Activo", op) || equals("muy activo", op) || equals("Muy activo", op) || equals("muy Activo", op))
        {
            resul = tmbm * MUYACTIVO;
        }
        else
        {
            printf("\nLa Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n\n");
        }
    } while (!equals("1", op) && !equals("2", op) && !equals("3", op) && !equals("4", op) &&
             !equals("Sedentario", op) && !equals("sedentario", op) &&
             !equals("Semiactivo", op) && !equals("semiactivo", op) &&
             !equals("Activo", op) && !equals("activo", op) &&
             !equals("Muy Activo", op) && !equals("muy activo", op) &&
             !equals("Muy activo", op) && !equals("muy Activo", op));
    
    return resul;
}

float calculoProteina(float peso)
{
    float resul = 0;
    
    printf("Introduce los Gr/Kilo para el Calculo de Proteinas: ");
    fflush(stdin);
    scanf("%f", &resul);
    
    resul *= peso;
    
    printf("Gramos de Proteina: %.2f \n", resul);
    
    return resul * 4;
}

float calculoGrasas(float peso)
{
    float resul = 0;
    
    printf("\nIntroduce los Gr/Kilo para el Calculo de Grasas: ");
    fflush(stdin);
    scanf("%f", &resul);
    
    resul *= peso;
    
    printf("Gramos de Grasa: %.2f \n", resul);
    
    return resul * 9;
}

float calculoHidratosHombre(float proteina, float grasas, float tmbh, float geth)
{
    float resul = 0;
    char op[4];
    
    do {
        
        printf("A que Valor lo Quieres Aplicar???\n");
        printf("1. TMB\n");
        printf("2. GET\n\n");
        
        printf("Opcion: ");
        
        fflush(stdin);
        scanf("%s", op);
        
        if (equals("1", op) || equals("TMB", op) || equals("tmb", op))
        {
            resul = tmbh - (proteina + grasas);
        }
        else if (equals("2", op) || equals("GET", op) || equals("get", op))
        {
            resul = geth - (proteina + grasas);
        }
        else
        {
            printf("\nLa Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n");
        }
    } while (!equals("1", op) && !equals("TMB", op) && !equals("tmb", op) &&
             !equals("2", op) && !equals("GET", op) && !equals("get", op));
    
    return resul;
}

float calculoHidratosMujer(float proteina, float grasas, float tmbm, float getm)
{
    float resul = 0;
    char op[4];
    
    do {
        
        printf("\nA que Valor lo Quieres Aplicar???\n");
        printf("1. TMB\n");
        printf("2. GET\n\n");
        
        printf("Opcion: ");
        
        fflush(stdin);
        scanf("%s", op);
        
        if (equals("1", op) || equals("TMB", op) || equals("tmb", op))
        {
            resul = tmbm - (proteina + grasas);
        }
        else if (equals("2", op) || equals("GET", op) || equals("get", op))
        {
            resul = getm - (proteina + grasas);
        }
        else
        {
            printf("\nLa Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n");
        }
    } while (!equals("1", op) && !equals("TMB", op) && !equals("tmb", op) &&
             !equals("2", op) && !equals("GET", op) && !equals("get", op));
    
    return resul;
}

int length(char v1[]){
    int i = 0;
    
    while (v1[i] != '\0') {
        i++;
    }
    
    return i;
}
