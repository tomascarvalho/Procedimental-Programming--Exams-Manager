#include "header.h"
#include <stdio.h>
#include <stdlib.h>

/******************************************************************************/
/*                                Menu Function                               */
/* Receives the current date, to display to the user.                         */
/* Displays a menu to the user, asking for an input.                          */
/* Returns an integer with the option chosen by the user                      */
/******************************************************************************/

int menu(Date *system_date)
{
    char option; /* Using a char to receive input will prevent errors such as receiving a char when asking for an int */
    int int_option; /* After verifying if we indeed got an integer, we can store it here */
    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: Chamada funcao menu\n");
    #endif

    do /* Ask the user for an option... */
    {
        /* We print the menu */
        printf("\n\n\t\t\t\t MENU\n");
        printf("\n 1- Alunos\n");
        printf("\n 2- Disciplinas\n");
        printf("\n 3- Exames\n");
        printf("\n\n 0- Sair\t\t\t\t\tData: %d/%d/%d   Hora: %d:%d", system_date->day, system_date->month, system_date->year, system_date->hour, system_date->minute);
        printf("\n\n\t\tOpcao: ");
        scanf(" %c", &option); /* We ask the user for input */
        fflush(stdin); /* Flush the buffer: "eats" the \n */
        /*DEBUG*/
        #ifdef DEBUG
        printf("\nDEBUG: Chosen option was --> %c\n", option);
        #endif

        if (option < '0' || option >'3') /* If the option is not valid we warn the user */
            printf("\nOpcao incorrecta\n");

    } while (option < '0' || option >'3'); /* While the option is not valid */

    int_option = (int)(option - '0'); /* If the option is valid, it's an integer, so we can cast it to an integer */


    return int_option;
}

int sub_menu(int menu_option, Date *system_date)
{
    char option; /* Using a char to receive input will prevent errors such as receiving a char when asking for an int */
    int int_option; /* After verifying if we indeed got an integer, we can store it here */

    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: Chamada funcao sub_menu com menu_option -> %d\n", menu_option);
    #endif

    /* Switch case */
    switch (menu_option)
    {
        /* Case menu_option == STUDENTS */
        case STUDENTS:
            /* Do ... */
            do
            {
                /* Displays submenu option for STUDENTS */
                printf("\n\nALUNOS\n\n");
                printf("\n 1- Novo Aluno\n");
                printf("\n 2- Alterar Aluno\n");
                printf("\n 3- Apagar Aluno\n");
                printf("\n 4- Listar Alunos\n");
                printf("\n\n 0- Voltar\t\t\t\t\tData: %d/%d/%d   Hora: %d:%d", system_date->day, system_date->month, system_date->year, system_date->hour, system_date->minute);
                printf("\n\n\t\tOpcao: ");
                scanf(" %c", &option); /* We ask the user for input */
                fflush(stdin); /* Flush the buffer: "eats" the \n */

                /*DEBUG*/
                #ifdef DEBUG
                printf("DEBUG: Chosen option was --> %c\n", option);
                #endif

                if (option < '0' || option >'4') /* If the option is not valid we warn the user */
                    printf("\nOpcao incorrecta\n");

            } while(option < '0' || option > '4'); /* While the option is not valid */
            int_option = (int)(option - '0'); /* If the option is valid, it's an integer, so we can cast it to an integer */
            /*DEBUG*/
            #ifdef DEBUG
            printf("DEBUG: int_optinon is --> %d\n", int_option);
            #endif

            break;

        /* Case menu_option == COURSES */
        case COURSES:
            /* Do ... */
            do
            {
                /* Displays submenu option for COURSES */
                printf("\n\nDISCIPLINAS\n\n");
                printf("\n\t 1- Nova Disciplina\n");
                printf("\n\t 2- Alterar Disciplina\n");
                printf("\n\t 3- Apagar Disciplina\n");
                printf("\n\t 4- Listar Disciplinas\n");
                printf("\n\n 0- Voltar\t\t\t\t\tData: %d/%d/%d   Hora: %d:%d", system_date->day, system_date->month, system_date->year, system_date->hour, system_date->minute);
                printf("\n\n\t\tOpcao: ");
                scanf(" %c", &option); /* We ask the user for input */
                fflush(stdin); /* Flush the buffer: "eats" the \n */

                /*DEBUG*/
                #ifdef DEBUG
                printf("DEBUG: Chosen option was --> %c\n", option);
                #endif

                if (option < '0' || option >'4') /* If the option is not valid we warn the user */
                    printf("\nOpcao incorrecta\n");

            } while(option < '0' || option > '4'); /* While the option is not valid */

            int_option = (int)(option - '0'); /* If the option is valid, it's an integer, so we can cast it to an integer */
            /*DEBUG*/
            #ifdef DEBUG
            printf("\nDEBUG: int_optinon is --> %d\n", int_option);
            #endif

            break;

        /* Case menu_option == EXAMS */
        case EXAMS:
            /* Do ... */
            do
            {
                /* Displays submenu option for EXAMS */
                printf("\n\nEXAMES\n\n");
                printf("\n\t 1- Novo Exame\n");
                printf("\n\t 2- Alterar Exame\n");
                printf("\n\t 3- Apagar Exame\n");
                printf("\n\t 4- Listar Exames\n");
                printf("\n\n 0- Voltar\t\t\t\t\tData: %d/%d/%d   Hora: %d:%d", system_date->day, system_date->month, system_date->year, system_date->hour, system_date->minute);
                printf("\n\n\t\tOpcao: ");
                scanf(" %c", &option); /* We ask the user for input */
                fflush(stdin); /* Flush the buffer: "eats" the \n */

                /*DEBUG*/
                #ifdef DEBUG
                printf("\nDEBUG: Chosen option was --> %c\n", option);
                #endif

                if (option < '0' || option >'4') /* If the option is not valid we warn the user */
                    printf("\nOpcao incorrecta\n");

            } while(option < '0' || option > '4'); /* While the option is not valid */

            int_option = (int)(option - '0'); /* If the option is valid, it's an integer, so we can cast it to an integer */
            /*DEBUG*/
            #ifdef DEBUG
            printf("\nDEBUG: int_option is --> %d\n", int_option);
            #endif

            break;

        default:
            /*DEBUG*/
            #ifdef DEBUG
            printf("\nDEBUG: No valid case or option 0? menu_option -> %d\n", menu_option);
            #endif
            int_option = -1;
    }

    return int_option;
}

int menu_exams()
{
    char option;
    int int_option;
    do
    {
        /* Displays submenu option for EXAMS */
        printf("\n\nLISTA EXAMES\n\n");
        printf("\n\t 1- Listar alunos inscritos em exame\n");
        printf("\n\t 2- Adicionar alunos a exame\n");
        printf("\n\t 3- Verificar sala para exame\n");
        printf("\n\t 4- Listar Exames\n");
        printf("\n\n 0- Voltar");
        printf("\n\n\t\tOpcao: ");
        scanf(" %c", &option); /* We ask the user for input */
        fflush(stdin); /* Flush the buffer: "eats" the \n */

        /*DEBUG*/
        #ifdef DEBUG
        printf("\nDEBUG: Chosen option was --> %c\n", option);
        #endif

        if (option < '0' || option >'4') /* If the option is not valid we warn the user */
            printf("\nOpcao incorrecta\n");

    } while(option < '0' || option > '4'); /* While the option is not valid */

    int_option = (int)(option - '0'); /* If the option is valid, it's an integer, so we can cast it to an integer */
    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: int_option is --> %d\n", int_option);
    #endif

    return int_option;
}
