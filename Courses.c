#include "header.h"

/* File with functions to manipulate the list of courses */

/*************************************************************/
/*                  new_course function                      */
/* Function to create a new course and add it to the list    */
/* Receives the pointer to the first element of courses list */
/* Returns a pointer to the first element of courses list    */
/*************************************************************/
Cnode* new_course(Cnode* course_list)
{
    Cnode* aux = course_list;
    Cnode* new_course = NULL;
    Course crs;
    char aux_name[MAX_CHAR], aux_regent[MAX_CHAR];

    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: funcao new_course chamada \n");
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
    if ((course_exists(aux_name)) != NULL)
    {
        #ifdef DEBUG
        printf("DEBUG: Course exists didnt return NULL\n");
        #endif
        printf("Ja existe uma disciplina com este nome!\n");
        return NULL;
    }

    /* We create the new course */
    crs.name = (char*) malloc (sizeof(char) * strlen(aux_name));
    strcpy(crs.name, aux_name);
    crs.regent = (char*) malloc (sizeof(char) * strlen(aux_regent));
    strcpy(crs.regent, aux_regent);

    /* We alocate memory for the new course */
    new_course = (Cnode*) malloc (sizeof(Cnode));
    /* Was memory alocated?*/
    if (new_course == NULL)
    {
        printf("ERRO: Sem memoria!\n");
        /*DEBUG*/
        #ifdef DEBUG
        printf("FATAL ERROR: FAILED TO ALOCATE MEMORY FOR new_course NODE AT NEW_COURSE FUNCTION\n");
        #endif
        return NULL;
    }


    new_course -> course = crs;
    new_course -> next = NULL;

    while (aux -> next!= NULL)
        aux = aux -> next;
    aux -> next = new_course;

    return course_list;


}


/****************************************************************/
/*                   list_courses function                      */
/* Function to list the existing courses in the courses list    */
/* Receives no params                                           */
/* Returns void                                                 */
/****************************************************************/
void list_courses()
{
    Cnode* aux = course_list-> next;

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
Cnode* course_exists(char c_id[])
{

    #ifdef DEBUG
    printf("DEBUG: course_exists function\n");
    #endif
    Cnode* aux = course_list -> next;


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
void update_course()
{
    Cnode* to_update = NULL;
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
    to_update = course_exists(aux_name);
    if (to_update == NULL)
    {
        /* If the course to update does not exist we return */
        printf("A disciplina com esse nome nao existe\n");
        return;
    }

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

        if (course_exists(aux_name) != NULL)
        {
            if (course_exists(aux_name) != to_update)
            {
                /*DEBUG*/
                #ifdef DEBUG
                printf("DEBUG: The course name exists\n");
                #endif
                printf("Ja existe uma disciplina com esse nome\n");
                is_unique = 0;

            }
        }
    } while (!is_unique); /* While course is not unique */

    printf("Regente: ");
    fgets(aux_regent, MAX_CHAR, stdin);
    removes_newLine(aux_regent);

    to_update -> course.name = (char*) malloc (sizeof(char)*strlen(aux_name));
    strcpy(to_update->course.name, aux_name);
    to_update -> course.regent = (char*) malloc (sizeof(char)*strlen(aux_regent));
    strcpy(to_update->course.regent, aux_regent);

    printf("Actualizado com sucesso\n");

}


/*********************************************************************/
/*                     delete_course function                        */
/* Function to delete a course from the list                         */
/* Receives a pointer to the beginning of the course list            */
/* Returns a pointer to the beginning of the course list             */
/*********************************************************************/
Cnode* delete_course(Cnode* course_list)
{
    Cnode* to_remove = NULL;
    Cnode* after = NULL;
    Cnode* aux = course_list;
    char aux_name[MAX_CHAR];
    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: delete_course function called\n");
    #endif
    /* "eats" the \n from the previous input */
    getchar();
    printf("Nome da disciplina a apagar: ");
    fgets(aux_name, MAX_CHAR, stdin);
    removes_newLine(aux_name);
    to_remove = course_exists(aux_name);
    if (to_remove == NULL)
    {
        printf("A disciplina com esse nome nao existe\n");
        return course_list;
    }
    while (aux -> next != to_remove)
        aux = aux -> next;
    after = to_remove -> next;
    free(to_remove);
    aux -> next = after;
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
