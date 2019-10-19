#include <stdio.h>
#include <string.h>

#define SEDENTARIO 1.1;
#define SEMIACTIVO 1.22;
#define ACTIVO 1.5;
#define MUYACTIVO 1.7;

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
    
    char sexo[7];
    float edad, altura, peso;
    float proteina, hidratos, grasas;
    float tmbh = 0, tmbm = 0, geth = 0, getm = 0;
    int repeat = 0;
    
    do
    {
        printf("\t Selecione el Sexo del Cliente: \n");
        printf("1. Hombre\n");
        printf("2. Mujer \n");
        
        fflush(stdin);
        scanf("%s", sexo);
        
        if (strncmp(sexo,"1",6) == 0 || strncmp(sexo,"Hombre",6) == 0 || strncmp(sexo,"hombre",6) == 0 ||
            strncmp(sexo,"H",6) == 0 || strncmp(sexo,"h",6) == 0)
        {
            do
            {
                printf("\t Introduce la Edad del Cliente: ");
                fflush(stdin);
                scanf("%f", &edad);
                if (edad < 1 || edad > 99)
                {
                    printf("La edad Introducida no es Correcta. Vuelva a Intentarlo.\n");
                }
            } while (edad < 1 || edad > 99);
            printf("\t Introduce la Altura del Cliente (En Centimetros): ");
            fflush(stdin);
            scanf("%f", &altura);
            printf("\t Introduce el Peso del Cliente: ");
            fflush(stdin);
            scanf("%f", &peso);
            
            printf("\n");
            
            // TMB
            tmbh = tasaMetablicaBasalHombre(peso, edad, altura);
            
            // GET
            geth = gastoEnergeticoTotalHombre(tmbh);
            
            printf("\n");
            
            proteina = calculoProteina(peso);
            grasas = calculoGrasas(peso);
            
            printf("\n");
            
            hidratos = calculoHidratosHombre(proteina, grasas, tmbh, geth);
            
            printf("\tLos Calculos son los Siguientes:\n");
            printf("\tTMB: %.2f\n", tmbh);
            printf("\tGET: %.2f\n", geth);
            printf("\tProteina: %.2f\n", proteina);
            printf("\tGrasas: %.2f\n", grasas);
            printf("\tHidratos: %.2f\n", hidratos);
        }
        else if (strncmp(sexo,"2",6) == 0 || strncmp(sexo,"Mujer",6) == 0 || strncmp(sexo,"mujer",6) == 0 ||
                 strncmp(sexo,"M",6) == 0 || strncmp(sexo,"m",6) == 0)
        {
            do
            {
                printf("\t Introduce la Edad del Cliente: ");
                fflush(stdin);
                scanf("%f", &edad);
                if (edad < 1 || edad > 99)
                {
                    printf("La edad Introducida no es Correcta. Vuelva a Intentarlo.\n");
                }
            } while (edad < 1 || edad > 99);
            printf("\t Introduce la Altura del Cliente (En Centimetros): ");
            fflush(stdin);
            scanf("%f", &altura);
            printf("\t Introduce el Peso del Cliente: ");
            fflush(stdin);
            scanf("%f", &peso);
            
            printf("\n");
            
            // TMB
            tmbm = tasaMetablicaBasalMujer(peso, edad, altura);
            
            // GET
            getm = gastoEnergeticoTotalMujer(tmbm);
            
            printf("\n");
            
            proteina = calculoProteina(peso);
            grasas = calculoGrasas(peso);
            
            printf("\n");
            
            hidratos = calculoHidratosMujer(proteina, grasas, tmbm, getm);
            
            printf("\tLos Calculos son los Siguientes:\n");
            printf("\tTMB: %.2f\n", tmbm);
            printf("\tGET: %.2f\n", getm);
            printf("\tProteina: %.2f\n", proteina);
            printf("\tGrasas: %.2f\n", grasas);
            printf("\tHidratos: %.2f\n", hidratos);
        }
        else
        {
            printf("La Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n");
        }
        
        printf("¿Desea introducir a otro cliente?\n1 = Yes\n0 = No\n");
        fflush(stdin);
        scanf("%d", &repeat);
        
    } while ((strncmp(sexo,"1",6) != 0 && strncmp(sexo,"Hombre",6) != 0 && strncmp(sexo,"hombre",6) != 0 && strncmp(sexo,"H",6) != 0 && strncmp(sexo,"h",6) != 0 &&
             strncmp(sexo,"2",6) != 0 && strncmp(sexo,"Mujer",6) != 0 && strncmp(sexo,"mujer",6) != 0 && strncmp(sexo,"M",6) != 0 && strncmp(sexo,"m",6) != 0) || repeat != 0);
    
    return 0;
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
        printf("Introduce el Factor de actividad del Cliente: \n");
        printf("1. Sedentario.\n");
        printf("2. Semiactivo.\n");
        printf("3. Activo.\n");
        printf("4. Muy Activo.\n");
        
        fflush(stdin);
        scanf("%s", op);
        
        if (strncmp(op,"1",10) == 0 || strncmp(op,"Sedentario",10) == 0 || strncmp(op,"sedentario",10) == 0)
        {
            resul = tmbh * SEDENTARIO;
        }
        else if (strncmp(op,"2",10) == 0 || strncmp(op,"Semiactivo",10) == 0 || strncmp(op,"semiactivo",10) == 0)
        {
            resul = tmbh * SEMIACTIVO;
        }
        else if (strncmp(op,"3",10) == 0 || strncmp(op,"Activo",6) == 0 || strncmp(op,"activo",6) == 0)
        {
            resul = tmbh * ACTIVO;
        }
        else if (strncmp(op,"4",10) == 0 || strncmp(op,"Muy Activo",10) == 0 || strncmp(op,"muy activo",10) == 0 || strncmp(op,"Muy activo",10) == 0 || strncmp(op,"muy Activo",10) == 0)
        {
            resul = tmbh * MUYACTIVO;
        }
        else
        {
            printf("\nLa Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n\n");
        }
    } while (strncmp(op,"1",10) != 0 && strncmp(op,"2",10) != 0 && strncmp(op,"3",10) != 0 && strncmp(op,"4",10) != 0 &&
             strncmp(op,"Sedentario",10) != 0 && strncmp(op,"sedentario",10) != 0 &&
             strncmp(op,"Semiactivo",10) != 0 && strncmp(op,"semiactivo",10) != 0 &&
             strncmp(op,"Activo",6) != 0 && strncmp(op,"activo",6) != 0 &&
             strncmp(op,"Muy Activo",10) != 0 && strncmp(op,"muy activo",10) != 0 &&
             strncmp(op,"Muy activo",10) != 0 && strncmp(op,"muy Activo",10) != 0);
    
    return resul;
}

float gastoEnergeticoTotalMujer(float tmbm)
{
    float resul = 0;
    char op[11];
    
    do
    {
        printf("Introduce el Factor de actividad del Cliente: \n");
        printf("1. Sedentario.\n");
        printf("2. Semiactivo.\n");
        printf("3. Activo.\n");
        printf("4. Muy Activo.\n");
        
        fflush(stdin);
        scanf("%s", op);
        
        if (strncmp(op,"1",10) == 0 || strncmp(op,"Sedentario",10) == 0 || strncmp(op,"sedentario",10) == 0)
        {
            resul = tmbm * SEDENTARIO;
        }
        else if (strncmp(op,"2",10) == 0 || strncmp(op,"Semiactivo",10) == 0 || strncmp(op,"semiactivo",10) == 0)
        {
            resul = tmbm * SEMIACTIVO;
        }
        else if (strncmp(op,"3",10) == 0 || strncmp(op,"Activo",6) == 0 || strncmp(op,"activo",6) == 0)
        {
            resul = tmbm * ACTIVO;
        }
        else if (strncmp(op,"4",10) == 0 || strncmp(op,"Muy Activo",10) == 0 || strncmp(op,"muy activo",10) == 0 || strncmp(op,"Muy activo",10) == 0 || strncmp(op,"muy Activo",10) == 0)
        {
            resul = tmbm * MUYACTIVO;
        }
        else
        {
            printf("\nLa Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n\n");
        }
    } while (strncmp(op,"1",10) != 0 && strncmp(op,"2",10) != 0 && strncmp(op,"3",10) != 0 && strncmp(op,"4",10) != 0 &&
             strncmp(op,"Sedentario",10) != 0 && strncmp(op,"sedentario",10) != 0 &&
             strncmp(op,"Semiactivo",10) != 0 && strncmp(op,"semiactivo",10) != 0 &&
             strncmp(op,"Activo",6) != 0 && strncmp(op,"activo",6) != 0 &&
             strncmp(op,"Muy Activo",10) != 0 && strncmp(op,"muy activo",10) != 0 &&
             strncmp(op,"Muy activo",10) != 0 && strncmp(op,"muy Activo",10) != 0);
    
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
    
    printf("Introduce los Gr/Kilo para el Calculo de Grasas: ");
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
        printf("2. GET\n");
        
        fflush(stdin);
        scanf("%s", op);
        
        if (strncmp(op,"1",3) == 0 || strncmp(op,"TMB",3) == 0 || strncmp(op,"tmb",3) == 0)
        {
            resul = tmbh - (proteina + grasas);
        }
        else if (strncmp(op,"2",3) == 0 || strncmp(op,"GET",3) == 0 || strncmp(op,"get",3) == 0)
        {
            resul = geth - (proteina + grasas);
        }
        else
        {
            printf("La Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n");
        }
    } while (strncmp(op,"1",3) != 0 && strncmp(op,"TMB",3) != 0 && strncmp(op,"tmb",3) != 0 &&
             strncmp(op,"2",3) != 0 && strncmp(op,"GET",3) != 0 && strncmp(op,"get",3) != 0);
    
    return resul;
}

float calculoHidratosMujer(float proteina, float grasas, float tmbm, float getm)
{
    float resul = 0;
    char op[4];
    
    do {
        
        printf("A que Valor lo Quieres Aplicar???\n");
        printf("1. TMB\n");
        printf("2. GET\n");
        
        fflush(stdin);
        scanf("%s", op);
        
        if (strncmp(op,"1",3) == 0 || strncmp(op,"TMB",3) == 0 || strncmp(op,"tmb",3) == 0)
        {
            resul = tmbm - (proteina + grasas);
        }
        else if (strncmp(op,"2",3) == 0 || strncmp(op,"GET",3) == 0 || strncmp(op,"get",3) == 0)
        {
            resul = getm - (proteina + grasas);
        }
        else
        {
            printf("La Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n");
        }
    } while (strncmp(op,"1",3) != 0 && strncmp(op,"TMB",3) != 0 && strncmp(op,"tmb",3) != 0 &&
             strncmp(op,"2",3) != 0 && strncmp(op,"GET",3) != 0 && strncmp(op,"get",3) != 0);
    
    return resul;
}
