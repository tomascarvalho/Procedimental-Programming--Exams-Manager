#include "header.h"


/* File with functions to manipulate the list of students */


/* Removes the new line char \n from the end of a string */
void removes_newLine(char *str)
{
    if (str[strlen(str)-1] == '\n')
        str[strlen(str)-1] = '\0';
}


/*************************************************************/
/*                  new_student function                     */
/* Function to create a new student and add it to the list   */
/* Receives the pointer to the first element of student list */
/* Returns a pointer to the first element of student list    */
/*************************************************************/
Snode* new_student(Snode* student_list)
{
    Snode* aux = student_list;
    Snode* new_student = NULL;
    Student stdnt;
    char aux_id[MAX_CHAR], aux_degree[MAX_CHAR];
    char option;
    int aux_year, aux_regime;

    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: funcao new_student chamada \n");
    #endif

    getchar();
    printf("\nNovo Estudante\n");
    printf("Numero de Estudante: ");
    fgets(aux_id, MAX_CHAR, stdin);
    removes_newLine(aux_id);
    printf("Curso: ");
    fgets(aux_degree, MAX_CHAR, stdin);
    removes_newLine(aux_degree);
    printf("Ano: ");
    scanf("%d", &aux_year);
    /* Do...  */
    do
    {
        /* asks for student regime */
        printf("Regime:\n1- Normal\n2- Trabalhador Estudante\n3- Atleta\n4- Dirigente Associativo\n5- Erasmus\n");
        scanf(" %c", &option);

    } while (option < '1' || option > '5'); /* While option is not in valid range */
    /* Converts char to int */
    aux_regime = (int)(option - '0');

    /* If the student number exists, then we can't add it to the list */
    if ((student_exists(aux_id)) != NULL)
    {
        #ifdef DEBUG
        printf("DEBUG: Student exists didnt return NULL\n");
        #endif
        printf("O estudante ja se encontra na lista de estudantes\n");
        return student_list;
    }

    /* We create the new student */
    stdnt.id = (char*) malloc (sizeof(char) * strlen(aux_id));
    strcpy(stdnt.id, aux_id);
    stdnt.degree = (char*) malloc (sizeof(char) * strlen(aux_id));
    strcpy(stdnt.degree, aux_degree);
    stdnt.year = aux_year;
    stdnt.regime = aux_regime;

    /* We alocate memory for the new student */
    new_student = (Snode*) malloc (sizeof(Snode));
    /* Was memory alocated?*/
    if (new_student == NULL)
    {
        printf("ERRO: Sem memoria!\n");
        /*DEBUG*/
        #ifdef DEBUG
        printf("FATAL ERROR: FAILED TO ALOCATE MEMORY FOR new_student NODE AT NEW_STUDENT FUNCTION\n");
        #endif
        return student_list;
    }


    new_student -> student = stdnt;
    new_student -> next = NULL;

    while (aux -> next != NULL)
        aux = aux -> next;
    aux -> next = new_student;

    return student_list;


}


/****************************************************************/
/*                  list_students function                      */
/* Function to create a new student and add it to the list      */
/* Receives the pointer to the first element of student list    */
/* Returns void                                                 */
/****************************************************************/
void list_students()
{
    Snode* aux = student_list -> next;

    if (aux == NULL)
    {
        #ifdef DEBUG
        printf("\nDEBUG: Aux is null!\n");
        #endif
        printf("Nao ha alunos na lista\n");
        return;
    }
    printf("Lista de Estudantes\n");
    printf("\nID\t\t\tCurso\t\t\tAno\t\t\tRegime");

    while (aux != NULL)
    {
        if (aux->student.regime == NORMAL_STUDENT)
            printf("\n%s\t\t%s\t\t\t%d\t\t\t%s", aux->student.id, aux->student.degree, aux->student.year, "Normal");
        if (aux->student.regime == WORKER)
            printf("\n%s\t\t%s\t\t\t%d\t\t\t%s", aux->student.id, aux->student.degree, aux->student.year, "Trabalhador Estudante");
        if (aux->student.regime == ATHLETE)
            printf("\n%s\t\t%s\t\t\t%d\t\t\t%s", aux->student.id, aux->student.degree, aux->student.year, "Atleta");
        if (aux->student.regime == ASSOCIATIVE)
            printf("\n%s\t\t%s\t\t\t%d\t\t\t%s", aux->student.id, aux->student.degree, aux->student.year, "Dirigente Associativo");
        if (aux->student.regime == ERASMUS)
            printf("\n%s\t\t%s\t\t\t%d\t\t\t%s", aux->student.id, aux->student.degree, aux->student.year, "Erasmus");
        aux = aux->next;
    }
}

/******************************************************************************/
/*                count_students function                                     */
/* Function to count the number of students in the student_list               */
/* Receives no params                                                         */
/* Returns void                                                               */
/******************************************************************************/
void count_students()
{
    Snode* aux = student_list -> next;
    int conta = 0;
    printf("Numero de estudantes: ");
    if (aux == 0)
    {
        printf("%d\n", conta);
        return;
    }

    while (aux != NULL)
    {
        conta++;
        aux = aux -> next;
    }
    printf("%d\n", conta);

}


/******************************************************************************/
/*                student_exists functions                                    */
/* Function to create a new student and add it to the list                    */
/* Receives the id of the student we want to find                             */
/* Returns a pointer to the student found or null if the student doesnt exist */
/******************************************************************************/
Snode* student_exists(char s_id[])
{

    #ifdef DEBUG
    printf("DEBUG: studen_exists function\n");
    #endif
    Snode *aux = student_list;
    Snode *st = NULL;

    if ((aux -> next) == NULL)
    {

        return NULL;
    }

    while (aux ->next != NULL)
    {
        st = aux -> next;
        /*DEBUG*/
        #ifdef DEBUG
        printf("\nDEBUG: aux not null..");
        #endif
        if (strcmp(st->student.id, s_id) == 0)
        {
            /*DEBUG*/
            #ifdef DEBUG
            printf("\nDEBUG: Student exists");
            #endif
            return st;
        }
        aux = aux -> next;
    }
    return NULL;
}


/*********************************************************************/
/*                   update_student function                         */
/* Function to update a student from the list                        */
/* Receives no params                                                */
/* Returns void                                                      */
/*********************************************************************/
void update_student()
{
    Snode* to_update = NULL;
    char aux_id[MAX_CHAR], aux_degree[MAX_CHAR];
    char option;
    int aux_year, aux_regime, is_unique = 1;

    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: update_student function called\n");
    #endif
    /* "eats" the \n from the previous input */
    getchar();
    printf("\nNumero do estudante a actualizar: ");
    fgets(aux_id, MAX_CHAR, stdin);
    /* Removes the \n from the aux_id (fgets function) */
    removes_newLine(aux_id);

    /* Checks if student exists */
    to_update = student_exists(aux_id);
    if (to_update == NULL)
    {
        /* If the student to update does not exist we return */
        printf("O estudante com esse ID nao existe\n");
        return;
    }

    /* If it exists, we update it */
    printf("Novos dados do aluno\n");
    /* Do... */
    do
    {
        /* Asks for student ID */
        printf("Numero de Estudante: ");
        fgets(aux_id, MAX_CHAR, stdin);
        removes_newLine(aux_id);
        is_unique = 1;

        if (student_exists(aux_id) != NULL)
        {
            if (student_exists(aux_id) != to_update)
            {
                /*DEBUG*/
                #ifdef DEBUG
                printf("DEBUG: The student number exists\n");
                #endif
                printf("Ja existe um aluno com esse ID\n");
                is_unique = 0;

            }
        }
    } while (!is_unique); /* While student ID is not unique */

    printf("Curso: ");
    fgets(aux_degree, MAX_CHAR, stdin);
    removes_newLine(aux_degree);
    printf("Ano: ");
    scanf("%d", &aux_year);
    /* Do...  */
    do
    {
        /* asks for student regime */
        printf("Regime:\n1- Normal\n2- Trabalhador Estudante\n3- Atleta\n4- Dirigente Associativo\n5- Erasmus\n");
        scanf(" %c", &option);

    } while (option < '1' || option > '5'); /* While option is not in valid range */
    /* Converts char to int */
    aux_regime = (int)(option - '0');

    to_update -> student.id = (char*) malloc (sizeof(char)*strlen(aux_id));
    strcpy(to_update->student.id, aux_id);
    to_update -> student.degree = (char*) malloc (sizeof(char)*strlen(aux_degree));
    strcpy(to_update->student.degree, aux_degree);
    to_update -> student.year = aux_year;
    to_update -> student.regime = aux_regime;
    printf("Actualizado com sucesso\n");

}

/*********************************************************************/
/*                   delete_student functions                        */
/* Function to delete a student from the list                        */
/* Receives a pointer to the beginning of the student list           */
/* Returns a pointer to the beginning of the student list            */
/*********************************************************************/
Snode* delete_student(Snode* student_list)
{
    Snode* to_remove = NULL;
    Snode* after = NULL;
    Snode* aux = student_list;
    char aux_id[MAX_CHAR];
    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: delete_student function called\n");
    /* "eats" the \n from the previous input */
    #endif
    getchar();
    printf("Numero do estudante a apagar: ");
    fgets(aux_id, MAX_CHAR, stdin);
    removes_newLine(aux_id);
    to_remove = student_exists(aux_id);
    if (to_remove == NULL)
    {
        printf("O estudante com esse ID nao existe\n");
        return student_list;
    }
    while (aux -> next != to_remove)
        aux = aux -> next;
    after = to_remove -> next;
    free(to_remove);
    aux -> next = after;
    printf("Aluno removido com sucesso\n");
    return student_list;
}

/*********************************************************************/
/*                     destroy_list functions                        */
/* Function to destroy a linked list by free(ing) its nodes          */
/* Receives a pointer to the beginning of the student list           */
/* Returns void                                                      */
/*********************************************************************/
void destroy_student_list(Snode* student_list)
{
    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: Destroying student's list\n");
    #endif
    Snode* aux = student_list->next;
    Snode* temp = NULL;
    while (aux != NULL)
    {
        temp = aux -> next;
        free(aux);
        aux = temp;
    }
    free(student_list);
}
