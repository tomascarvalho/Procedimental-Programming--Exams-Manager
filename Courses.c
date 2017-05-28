#include "header.h"

/* File with functions to manipulate the list of courses */

/*************************************************************/
/*               create_course_list function                 */
/* Function to create a new empty list of courses            */
/* Receives no arguments                                     */
/* Returns a pointer to the first element of the list        */
/*************************************************************/
Cnode* create_course_list()
{
    Cnode* list = (Cnode*) malloc (sizeof(Cnode));
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
/*                  new_course function                      */
/* Function to create a new course and add it to the list    */
/* Receives the pointer to the first element of courses list */
/* Returns a pointer to the first element of courses list    */
/*************************************************************/
Cnode* new_course(Cnode* course_list)
{
    Cnode* aux = NULL;
    Cnode* before = NULL;
    Cnode* after = NULL;

    char aux_name[MAX_CHAR], aux_regent[MAX_CHAR];

    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: funcao new_course chamada\n");
    #endif

    getchar();
    printf("\nNova Disciplina\n");
    printf("Nome da Disciplina: ");
    fgets(aux_name, MAX_CHAR, stdin);
    removes_newLine(aux_name);
    printf("Nome do Regente: ");
    fgets(aux_regent, MAX_CHAR, stdin);
    removes_newLine(aux_regent);

    /* If the student number exists, then we can't add it to the list */
    if ((course_exists(aux_name, &before, course_list)) != NULL)
    {
        #ifdef DEBUG
        printf("DEBUG: Course exists didnt return NULL\n");
        #endif
        printf("Ja existe uma disciplina com este nome!\n");
        return course_list;
    }


    if ((aux = create_course_list()) == NULL)
        return course_list;

    else if (before == NULL)
    {
        after = course_list;
        course_list = aux;
    }
    else
    {
        after = before->next;
        before->next = aux;
    }

    /* We create the new course */
    aux->course.name = (char*) malloc (sizeof(char) * strlen(aux_name));
    strcpy(aux->course.name, aux_name);
    aux->course.regent = (char*) malloc (sizeof(char) * strlen(aux_regent));
    strcpy(aux->course.regent, aux_regent);

    aux -> next = after;

    return course_list;


}


/****************************************************************/
/*                   list_courses function                      */
/* Function to list the existing courses in the courses list    */
/* Receives no params                                           */
/* Returns void                                                 */
/****************************************************************/
void list_courses(Cnode* course_list)
{
    Cnode* aux = course_list;

    if (aux == NULL)
    {
        #ifdef DEBUG
        printf("\nDEBUG: Aux is null!\n");
        #endif
        printf("Nao ha disciplinas na lista\n");
        return;
    }
    printf("Lista de Disciplinas\n");
    printf("\nNome\t\tRegente");

    while (aux != NULL)
    {
        printf("\n%s\t\t%s", aux->course.name, aux->course.regent);
        aux = aux->next;
    }
}


/******************************************************************************/
/*                       course_exists functions                              */
/* Function to search for a course                                            */
/* Receives the name of the course we want to find                            */
/* Returns a pointer to the course found or null if the student doesnt exist  */
/******************************************************************************/
Cnode* course_exists(char* c_id, Cnode** before, Cnode* list)
{

    #ifdef DEBUG
    printf("DEBUG: course_exists function\n");
    #endif
    Cnode* aux = list;

    if (aux == NULL)
        return NULL;

    while (aux != NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: aux not null...\n");
        #endif
        if (strcmp(aux->course.name, c_id) == 0)
        {
            /*DEBUG*/
            #ifdef DEBUG
            printf("DEBUG: Course exists\n");
            #endif
            return aux;
        }
        else if (strcmp(aux->course.name, c_id) > 0)
            return NULL;
        *before = aux;
        aux = aux -> next;
    }
    return NULL;
}


/*********************************************************************/
/*                    update_course function                         */
/* Function to update a course from the list                         */
/* Receives no params                                                */
/* Returns void                                                      */
/*********************************************************************/
Cnode* update_course(Cnode* course_list)
{
    Cnode* to_update = NULL;
    Cnode* aux = NULL;
    Cnode* before = NULL;
    Cnode* after = NULL;
    char aux_name[MAX_CHAR], aux_regent[MAX_CHAR];
    int is_unique = 1;

    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: update_course function called\n");
    #endif
    /* "eats" the \n from the previous input */
    getchar();
    printf("\nNome da disciplina para actualizar: ");
    fgets(aux_name, MAX_CHAR, stdin);
    /* Removes the \n from the aux_name (fgets function) */
    removes_newLine(aux_name);

    /* Checks if course exists */
    to_update = course_exists(aux_name, &before, course_list);
    if (to_update == NULL)
    {
        /* If the course to update does not exist we return */
        printf("A disciplina com esse nome nao existe\n");
        return course_list;
    }

    course_list = delete_course(aux_name, course_list);

    /* If it exists, we update it */
    printf("Novos dados da disciplina\n");
    /* Do... */
    do
    {
        /* Asks for new course name */
        printf("Nome: ");
        fgets(aux_name, MAX_CHAR, stdin);
        removes_newLine(aux_name);
        is_unique = 1;

        if ((aux = course_exists(aux_name, &before, course_list)) != NULL)
        {
            /*DEBUG*/
            #ifdef DEBUG
            printf("DEBUG: The course name exists\n");
            #endif
            printf("Ja existe uma disciplina com esse nome\n");
            is_unique = 0;

        }
    } while (!is_unique); /* While course is not unique */

    if ((to_update = create_course_list()) == NULL)
        return course_list;

    printf("Regente: ");
    fgets(aux_regent, MAX_CHAR, stdin);
    removes_newLine(aux_regent);

    to_update -> course.name = (char*) malloc (sizeof(char)*strlen(aux_name));
    strcpy(to_update->course.name, aux_name);
    to_update -> course.regent = (char*) malloc (sizeof(char)*strlen(aux_regent));
    strcpy(to_update->course.regent, aux_regent);
    to_update->next = after;

    if (before == NULL)
    {
        to_update->next = course_list;
        course_list = to_update;
    }
    else
    {

        to_update->next = before->next;
        before->next = to_update;
    }

    printf("Actualizado com sucesso\n");
    return course_list;

}


/*********************************************************************/
/*                     delete_course function                        */
/* Function to delete a course from the list                         */
/* Receives a pointer to the beginning of the course list            */
/* Returns a pointer to the beginning of the course list             */
/*********************************************************************/
Cnode* delete_course(char* aux_name, Cnode* course_list)
{
    Cnode* to_remove = NULL;
    Cnode* before = NULL;

    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: delete_course function called\n");
    #endif

    to_remove = course_exists(aux_name, &before, course_list);

    if (to_remove == NULL)
    {
        printf("A disciplina com esse nome nao existe\n");
        return course_list;
    }

    // else if ((exam_exists(aux_name, NORMAL) != NULL) || (exam_exists(aux_name, SECOND) != NULL) || (exam_exists(aux_name, SPECIAL) != NULL))
    // {
    //     printf("Ha pelo menos um exame marcado a essa desciplina. Por favor apague o exame antes de tentar apagar a disciplina\n");
    //     return course_list;
    // }

    if (before != NULL)
    {
        before -> next = to_remove->next;
        free(to_remove);
    }
    else
    {
        course_list = to_remove->next;
        free(to_remove);
    }


    printf("Disciplina removida com sucesso\n");
    return course_list;
}

/*********************************************************************/
/*                     destroy_list functions                        */
/* Function to destroy a linked list by free(ing) its nodes          */
/* Receives a pointer to the beginning of the course list            */
/* Returns void                                                      */
/*********************************************************************/
void destroy_course_list(Cnode* course_list)
{
    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: Destroying course's list\n");
    #endif
    Cnode* aux = course_list->next;
    Cnode* temp = NULL;
    while (aux != NULL)
    {
        temp = aux -> next;
        free(aux);
        aux = temp;
    }
    free(course_list);
}
