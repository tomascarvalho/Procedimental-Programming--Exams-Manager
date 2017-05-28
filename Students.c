#include "header.h"


/* File with functions to manipulate the list of students */

/*************************************************************/
/*               create_student_list function                */
/* Function to create a new empty list of students           */
/* Receives no arguments                                     */
/* Returns a pointer to the first element of the list        */
/*************************************************************/
Snode* create_student_list(Snode* list)
{
    list = (Snode*) malloc (sizeof(Snode));
    if (list == NULL)
    {
        printf("Erro: Sem memoria!\n");
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: NO MEMORY AVAILABLE! ERROR\n");
        #endif
        return NULL;
    }
    list -> next = NULL;
    return list;
}



/*************************************************************/
/*                 insert_student function                   */
/* Function to create insert a student to a student list     */
/* Receives the pointer to the first element of student list */
/* and the new node to insert                                */
/* Returns a pointer to the first element of student list    */
/*************************************************************/
Snode* insert_student(Snode* list, Snode* new_student)
{
    Snode* aux = list;
    if (list == NULL)
    {
        if ((list = create_student_list(list)) == NULL)
            return NULL;
        aux = list;
    }
    while (aux !=  NULL)
        aux = aux->next;
    aux = new_student;
    return list;
}



/*************************************************************/
/*                  new_student function                     */
/* Function to create a new student and add it to the list   */
/* Receives the pointer to the first element of student list */
/* Returns a pointer to the first element of student list    */
/*************************************************************/
Snode* new_student(Snode* student_list)
{
    Snode* aux = NULL;
    Snode* before = NULL;
    Snode* after = NULL;
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
    if ((student_exists(aux_id, &before, student_list)) != NULL)
    {
        #ifdef DEBUG
        printf("DEBUG: Student exists didnt return NULL\n");
        #endif
        printf("O estudante ja se encontra na lista de estudantes\n");
        return student_list;
    }

    #ifdef DEBUG
    printf("DEBUG: Student exists returned NULL\n");
    #endif

    if ((aux = create_student_list(aux)) == NULL)
        return student_list;


    if (before == NULL)
    {
        after = student_list;
        student_list = aux;
        #ifdef DEBUG
        printf("DEBUG: Inserts in the first position of the list\n");
        #endif
    }
    else
    {
        after = before->next;
        before->next = aux;
    }


    #ifdef DEBUG
    printf("DEBUG: Allocing memory for the new student...\n");
    #endif
    /* We create the new student */

    aux-> student.id = (char*) malloc (sizeof(char) * strlen(aux_id));
    strcpy(aux->student.id, aux_id);
    aux->student.degree = (char*) malloc (sizeof(char) * strlen(aux_id));
    strcpy(aux->student.degree, aux_degree);
    aux->student.year = aux_year;
    aux->student.regime = aux_regime;
    #ifdef DEBUG
    printf("DEBUG: Setting aux->next...\n");
    #endif
    aux -> next = after;
    #ifdef DEBUG
    printf("DEBUG: Returning student_list...\n");
    #endif
    return student_list;


}


/****************************************************************/
/*                  list_students function                      */
/* Function to create a new student and add it to the list      */
/* Receives the pointer to the first element of student list    */
/* Returns void                                                 */
/****************************************************************/
void list_students(Snode* student_list)
{
    Snode* aux = student_list;
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
void count_students(Snode* student_list)
{
    Snode* aux = student_list;
    int count = 0;
    printf("Numero de estudantes: ");

    while (aux != NULL)
    {
        count++;
        aux = aux -> next;
    }
    printf("%d\n", count);

}


/******************************************************************************/
/*                student_exists functions                                    */
/* Function to create a new student and add it to the list                    */
/* Receives the id of the student we want to find                             */
/* Returns a pointer to the student found or null if the student doesnt exist */
/******************************************************************************/
Snode* student_exists(char* s_id, Snode** before, Snode* student_list)
{

    #ifdef DEBUG
    printf("DEBUG: studen_exists function\n");
    #endif
    Snode *aux = student_list;

    if (aux == NULL)
        return NULL;

    while (aux != NULL)
    {
        printf("--\n");
        printf("Iterating over id: %s\n", aux->student.id);
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: aux not null...\n");
        #endif
        if (strcmp(aux->student.id, s_id) == 0)
        {
            /*DEBUG*/
            #ifdef DEBUG
            printf("DEBUG: Student exists\n");
            #endif
            return aux;
        }
        if (strcmp(aux->student.id, s_id) > 0)
            return NULL;
        *before = aux;
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
Snode* update_student(Snode* student_list)
{
    Snode* to_update = NULL;
    Snode* before = NULL;
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

    // /* Checks if student exists */
    to_update = student_exists(aux_id, &before, student_list);
    if (to_update == NULL)
    {
        /* If the student to update does not exist we return */
        printf("O estudante com esse ID nao existe\n");
        return student_list;
    }
    /* we remove the node from the list */
    student_list = delete_student(student_list, aux_id);

    list_students(student_list);
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

        if (student_exists(aux_id, &before, student_list) != NULL)
        {
                /*DEBUG*/
                #ifdef DEBUG
                printf("DEBUG: The student number exists\n");
                #endif
                printf("Ja existe um aluno com esse ID\n");
                is_unique = 0;

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

    if ((to_update = create_student_list(to_update)) ==  NULL)
        return student_list;
    /* Converts char to int */
    aux_regime = (int)(option - '0');
    to_update -> student.id = (char*) malloc (sizeof(char)*strlen(aux_id));
    strcpy(to_update->student.id, aux_id);
    to_update -> student.degree = (char*) malloc (sizeof(char)*strlen(aux_degree));
    strcpy(to_update->student.degree, aux_degree);
    to_update -> student.year = aux_year;
    to_update -> student.regime = aux_regime;

    if (before == NULL)
    {
        printf("O before esta a null como suposto\n");
        to_update->next = student_list;
        student_list = to_update;
    }
    else
    {
        printf(" Meh\n");
        to_update->next = before->next;
        before->next = to_update;
    }
    printf("Actualizado com sucesso\n");
    return student_list;

}

/*********************************************************************/
/*                   delete_student functions                        */
/* Function to delete a student from the list                        */
/* Receives a pointer to the beginning of the student list           */
/* Returns a pointer to the beginning of the student list            */
/*********************************************************************/
Snode* delete_student(Snode* student_list, char* aux_id)
{
    Snode* to_remove = NULL;
    Snode* before = NULL;

    to_remove = student_exists(aux_id, &before, student_list);
    if (to_remove == NULL)
    {
        printf("O estudante com esse ID nao existe\n");
        return student_list;
    }
    if (before != NULL)
    {
        before -> next = to_remove->next;
        free(to_remove);
    }
    else
    {
        student_list = to_remove->next;
        free(to_remove);
    }

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
    Snode* aux = student_list -> next;
    Snode* temp = NULL;
    while (aux != NULL)
    {
        temp = aux -> next;
        free(aux);
        aux = temp;
    }
    free(student_list);
}
