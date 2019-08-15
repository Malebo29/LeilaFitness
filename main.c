#include <stdio.h>

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

int main() {

    int sexo;
    float edad, altura, peso;
    float proteina, hidratos, grasas;
    float tmbh = 0, tmbm = 0, geth = 0, getm = 0;

    do {
        printf("\t Selecione el Sexo del Cliente: \n");
        printf("1. Hombre\n");
        printf("2. Mujer \n");

        scanf("%d", &sexo);

        if (sexo == 1) {
            do {
                printf("\t Introduce la Edad del Cliente: ");
                fflush(stdin);
                scanf("%f", &edad);
                if (edad < 1 || edad > 99) {
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
        } else if (sexo == 2) {
            do {
                printf("\t Introduce la Edad del Cliente: ");
                fflush(stdin);
                scanf("%f", &edad);
                if (edad < 1 || edad > 99) {
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
        } else {
            printf("La Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n");
        }
    } while (sexo != 1 && sexo != 2);
    return 0;
}

float tasaMetablicaBasalHombre(float peso, float edad, float altura) {
    float resul = 0;

    resul = 66 + (13.7 * peso) + (5 * altura) - (6.8 * edad);

    return resul;
}

float tasaMetablicaBasalMujer(float peso, float edad, float altura) {
    float resul = 0;

    resul = 655 + (9.6 * peso) + (1.8 * altura) - (4.7 * edad);

    return resul;
}

float gastoEnergeticoTotalHombre(float tmbh) {
    float resul = 0;
    int op;

    do {
        printf("Introduce el Factor de actividad del Cliente: \n");
        printf("1. Sedentario.\n");
        printf("2. Semiactivo.\n");
        printf("3. Activo.\n");
        printf("4. Muy Activo.\n");

        fflush(stdin);
        scanf("%d", &op);

        if (op < 1 || op > 4) {
            printf("La Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n");
        } else {
            switch (op) {
                case 1:
                    resul = tmbh * SEDENTARIO;
                    break;
                case 2:
                    resul = tmbh * SEMIACTIVO;
                    break;
                case 3:
                    resul = tmbh * ACTIVO;
                    break;
                case 4:
                    resul = tmbh * MUYACTIVO;
                    break;
            }
        }
    } while (op < 1 || op > 4);

    return resul;
}

float gastoEnergeticoTotalMujer(float tmbm) {
    float resul = 0;
    int op;
    do {
        printf("Introduce el Factor de actividad del Cliente: \n");
        printf("1. Sedentario.\n");
        printf("2. Semiactivo.\n");
        printf("3. Activo.\n");
        printf("4. Muy Activo.\n");

        fflush(stdin);
        scanf("%d", &op);

        if (op < 1 || op > 4) {
            printf("La Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n");
        } else {
            switch (op) {
                case 1:
                    resul = tmbm * SEDENTARIO;
                    break;
                case 2:
                    resul = tmbm * SEMIACTIVO;
                    break;
                case 3:
                    resul = tmbm * ACTIVO;
                    break;
                case 4:
                    resul = tmbm * MUYACTIVO;
                    break;
            }
        }
    } while (op < 1 || op > 4);

    return resul;
}

float calculoProteina(float peso) {
    float resul = 0;

    printf("Introduce los Gr/Kilo para el Calculo de Proteinas: ");
    fflush(stdin);
    scanf("%f", &resul);

    resul *= peso;

    printf("Gramos de Proteina: %.2f \n", resul);

    return resul * 4;
}

float calculoGrasas(float peso) {
    float resul = 0;

    printf("Introduce los Gr/Kilo para el Calculo de Grasas: ");
    fflush(stdin);
    scanf("%f", &resul);

    resul *= peso;

    printf("Gramos de Grasa: %.2f \n", resul);

    return resul * 9;
}

float calculoHidratosHombre(float proteina, float grasas, float tmbh, float geth) {
    float resul = 0;
    int op;

    do {
        printf("A que Valor lo Quieres Aplicar???\n");
        printf("1. TMB\n");
        printf("2. GET\n");

        fflush(stdin);
        scanf("%d", &op);

        if (op < 1 || op > 2) {
            printf("La Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n");
        } else {
            switch (op) {
                case 1:
                    resul = tmbh - (proteina + grasas);
                    break;
                case 2:
                    resul = geth - (proteina + grasas);
                    break;
            }
        }
    } while (op < 1 || op > 2);
    return resul;
}

float calculoHidratosMujer(float proteina, float grasas, float tmbm, float getm) {
    float resul = 0;
    int op;

    do {
        printf("A que Valor lo Quieres Aplicar???\n");
        printf("1. TMB\n");
        printf("2. GET\n");

        fflush(stdin);
        scanf("%d", &op);

        if (op < 1 || op > 2) {
            printf("La Opcion Introducida no es Correcta. Vuelve a Intentarlo.\n");
        } else {
            switch (op) {
                case 1:
                    resul = tmbm - (proteina + grasas);
                    break;
                case 2:
                    resul = getm - (proteina + grasas);
                    break;
            }
        }
    } while (op < 1 || op > 2);
    return resul;
}