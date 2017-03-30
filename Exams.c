#include "header.h"

/* File with functions to manipulate the list of exams */

/*************************************************************/
/*                  new_exam function                        */
/* Function to create a new exam and add it to the list      */
/* Receives the pointer to the first element of exams list   */
/* Returns a pointer to the first element of exams list      */
/*************************************************************/
Enode* new_exam(Enode* exam_list)
{
    Enode* aux = exam_list;
    Enode* new_exam = NULL;
    Cnode* aux_course = NULL;
    Date aux_date;
    Course crs;
    int aux_period = 0, n_rooms = 0, i = 0;
    char aux_name[MAX_CHAR], option_rooms[MAX_CHAR];
    char option;
    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: new_exam function called \n");
    #endif

    getchar();
    if (course_list -> next == NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: No courses... leaving new_exam func\n");
        #endif
        printf("Insira primeiro disciplinas antes de tentar criar exames!");
        return exam_list;
    }

    printf("\nNovo Exame\n");

    /*Do... */
    do
    {   /*Asks for course name... */
        printf("Nome da Disciplina: ");
        fgets(aux_name, MAX_CHAR, stdin);
        removes_newLine(aux_name);
        aux_course = course_exists(aux_name);
        if (aux_course == NULL)
            printf("Nao existe uma disciplina com esse nome...\n");

    } while(aux_course == NULL); /* While the user fails to provid a valid course name */


    /*Do... */
    do
    {
        /* asks for course period */
        printf("Epoca:\n1- Normal\n2- Recurso\n3- Especial\n");
        scanf(" %c", &option);
        getchar();

    } while (option < '1' || option > '3'); /* While option is not in valid range */
    aux_period = (int)(option - '0');


    if (exam_exists(aux_name, aux_period) != NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: Exam already exists!");
        #endif
        printf("O exame ja existe para esta disciplina e esta epoca!\n");
        return exam_list;
    }


    printf("Data do exame\n");
    aux_date = new_date();




    if ((new_exam = (Enode*) malloc (sizeof(Enode))) == NULL)
    {
        printf("Erro: Sem memoria!\n");
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: NO MEMORY AVAILABLE! ERROR\n");
        #endif
        return exam_list;
    }



    new_exam -> next = NULL;
    id +=1;
    new_exam-> id = id;
    crs.name = (char*) malloc (strlen(aux_course->course.name) * sizeof(char));
    strcpy(crs.name, aux_course->course.name);
    crs.regent = (char*) malloc (strlen(aux_course->course.regent) * sizeof(char));
    strcpy(crs.regent, aux_course->course.regent);
    new_exam-> course = crs;
    new_exam-> period = aux_period;

    new_exam-> n_students = 0;
    new_exam-> start_date = aux_date;
    aux_date = get_duration(aux_date);
    new_exam -> end_date = aux_date;


    /* Do... */
    do {
        printf("Numero de salas a reservar para o exame: "); /* Asks for the number of rooms */
        fgets(option_rooms, MAX_CHAR, stdin);
        n_rooms = atoi(option_rooms);
        if (n_rooms == 0)
            printf("Insira um numero valido!\n");
    } while (n_rooms == 0); /* While the number is not valid */

    new_exam-> n_rooms = n_rooms;

    while (i < n_rooms)
    {
        printf("%da sala: ", i+1);
        fgets(option_rooms, MAX_CHAR, stdin);
        if (check_room(option_rooms, new_exam->start_date))
        {
            if ((new_exam -> rooms[i] = (char*) malloc (sizeof(char) * strlen(option_rooms))) == NULL)
            {
                printf("Erro: Sem memoria!\n");
                /*DEBUG*/
                #ifdef DEBUG
                printf("DEBUG: NO MEMORY AVAILABLE! ERROR\n");
                #endif
                return exam_list;
            }
            strcpy(new_exam->rooms[i], option_rooms);
            i++;
        }
        else
            printf("Sala ja reservada para um exame. Por favor, selecionar outra sala\n");
    }

    new_exam -> students = NULL;


    while (aux -> next!= NULL)
        aux = aux -> next;
    aux -> next = new_exam;

    return exam_list;

}

int check_room(char* room, Date date)
{
    Enode* aux = exam_list -> next;
    int i;
    if (aux == NULL)
        return 1;

    while (aux != NULL)
    {
        if ((aux->start_date.year == date.year) && (aux->start_date.month == date.month) && (aux->start_date.day == date.day))
        {
            if ((aux->start_date.hour <= date.hour) && (aux->end_date.hour > date.hour))
            {
                for (i = 0; i < aux->n_rooms; i++)
                {
                    if (strcmp(aux->rooms[i], room) == 0)
                    {
                        return 0;
                    }
                }
            }
            else if (aux->end_date.hour == date.hour)
            {
                if (aux->end_date.minute > date.minute)
                {
                    for (i = 0; i < aux->n_rooms; i++)
                    {
                        if (strcmp(aux->rooms[i], room) == 0)
                        {
                            return 0;
                        }
                    }
                }
            }
        }

    }
    return 1;
}


/****************************************************************/
/*                   list_courses function                      */
/* Function to list the existing courses in the courses list    */
/* Receives no params                                           */
/* Returns void                                                 */
/****************************************************************/
void list_exams()
{
    Enode* aux = exam_list-> next;
    int i = 0;
    if (aux == NULL)
    {
        #ifdef DEBUG
        printf("\nDEBUG: Aux is null!\n");
        #endif
        printf("Nao ha exames na lista\n");
        return;
    }
    printf("Lista de Exames\n");
    printf("\nID\tDisciplina\tRegente\tEpoca\tData Inicio\tData Fim\tNum Inscritos\tSalas\n");

    while (aux != NULL)
    {
        if (aux->period == NORMAL)
            printf("\n%d\t%s\t\t%s\t%s\t%d/%d/%d %2d:%2d\t%d/%d/%d %2d:%2d\t%d\t", aux->id, aux->course.name, aux->course.regent, "NORMAL", aux->start_date.day, aux->start_date.month, aux->start_date.year, aux->start_date.hour, aux->start_date.minute, aux->end_date.day, aux->end_date.month, aux->end_date.year, aux->end_date.hour, aux->end_date.minute, aux->n_students);
        else if (aux->period == SECOND)
            printf("\n%d\t%s\t\t%s\t%s\t%d/%d/%d %2d:%2d\t%d/%d/%d %2d:%2d\t%d\t", aux->id, aux->course.name, aux->course.regent, "RECURSO", aux->start_date.day, aux->start_date.month, aux->start_date.year, aux->start_date.hour, aux->start_date.minute, aux->end_date.day, aux->end_date.month, aux->end_date.year, aux->end_date.hour, aux->end_date.minute, aux->n_students);
        else if (aux->period == SPECIAL)
            printf("\n%d\t%s\t\t%s\t%s\t%d/%d/%d %2d:%2d\t%d/%d/%d %2d:%2d\t%d\t", aux->id, aux->course.name, aux->course.regent, "ESPECIAL", aux->start_date.day, aux->start_date.month, aux->start_date.year, aux->start_date.hour, aux->start_date.minute, aux->end_date.day, aux->end_date.month, aux->end_date.year, aux->end_date.hour, aux->end_date.minute, aux->n_students);
        for (i = 0; i < aux->n_rooms; i++)
            if (i == 0)
                printf("\t\t\t\t\t\t\t\t%s\n", aux->rooms[i]);
            else
                printf("\t\t\t\t\t\t\t\t%s\n", aux->rooms[i]);
        aux = aux->next;
    }
}

Enode* exam_exists(char cname[], int per)
{
    Enode* aux = exam_list -> next;

    if (aux == NULL)
        return NULL;

    while (aux != NULL)
    {
        if (strcmp(aux->course.name, cname) == 0)
            if (aux-> period == per)
                return aux;
    }
    return NULL;
}


/*********************************************************************/
/*                    update_course function                         */
/* Function to update a course from the list                         */
/* Receives no params                                                */
/* Returns void                                                      */
/*********************************************************************/
// void update_course()
// {
//     Cnode* to_update = NULL;
//     char aux_name[MAX_CHAR], aux_regent[MAX_CHAR];
//     int is_unique = 1;
//
//     /*DEBUG*/
//     #ifdef DEBUG
//     printf("DEBUG: update_course function called\n");
//     #endif
//     /* "eats" the \n from the previous input */
//     getchar();
//     printf("\nNome da disciplina para actualizar: ");
//     fgets(aux_name, MAX_CHAR, stdin);
//     /* Removes the \n from the aux_name (fgets function) */
//     removes_newLine(aux_name);
//
//     /* Checks if course exists */
//     to_update = course_exists(aux_name);
//     if (to_update == NULL)
//     {
//         /* If the course to update does not exist we return */
//         printf("A disciplina com esse nome nao existe\n");
//         return;
//     }
//
//     /* If it exists, we update it */
//     printf("Novos dados da disciplina\n");
//     /* Do... */
//     do
//     {
//         /* Asks for new course name */
//         printf("Nome: ");
//         fgets(aux_name, MAX_CHAR, stdin);
//         removes_newLine(aux_name);
//         is_unique = 1;
//
//         if (course_exists(aux_name) != NULL)
//         {
//             if (course_exists(aux_name) != to_update)
//             {
//                 /*DEBUG*/
//                 #ifdef DEBUG
//                 printf("DEBUG: The course name exists\n");
//                 #endif
//                 printf("Ja existe uma disciplina com esse nome\n");
//                 is_unique = 0;
//
//             }
//         }
//     } while (!is_unique); /* While course is not unique */
//
//     printf("Regente: ");
//     fgets(aux_regent, MAX_CHAR, stdin);
//     removes_newLine(aux_regent);
//
//     to_update -> course.name = (char*) malloc (sizeof(char)*strlen(aux_name));
//     strcpy(to_update->course.name, aux_name);
//     to_update -> course.regent = (char*) malloc (sizeof(char)*strlen(aux_regent));
//     strcpy(to_update->course.regent, aux_regent);
//
//     printf("Actualizado com sucesso\n");
//
// }
//
//
// /*********************************************************************/
// /*                     delete_course function                        */
// /* Function to delete a course from the list                         */
// /* Receives a pointer to the beginning of the course list            */
// /* Returns a pointer to the beginning of the course list             */
// /*********************************************************************/
// Cnode* delete_course(Cnode* course_list)
// {
//     Cnode* to_remove = NULL;
//     Cnode* after = NULL;
//     Cnode* aux = course_list;
//     char aux_name[MAX_CHAR];
//     /*DEBUG*/
//     #ifdef DEBUG
//     printf("DEBUG: delete_course function called\n");
//     #endif
//     /* "eats" the \n from the previous input */
//     getchar();
//     printf("Nome da disciplina a apagar: ");
//     fgets(aux_name, MAX_CHAR, stdin);
//     removes_newLine(aux_name);
//     to_remove = course_exists(aux_name);
//     if (to_remove == NULL)
//     {
//         printf("A disciplina com esse nome nao existe\n");
//         return course_list;
//     }
//     while (aux -> next != to_remove)
//         aux = aux -> next;
//     after = to_remove -> next;
//     free(to_remove);
//     aux -> next = after;
//     printf("Disciplina removida com sucesso\n");
//     return course_list;
// }
//
// /*********************************************************************/
// /*                     destroy_list functions                        */
// /* Function to destroy a linked list by free(ing) its nodes          */
// /* Receives a pointer to the beginning of the course list            */
// /* Returns void                                                      */
// /*********************************************************************/
// void destroy_course_list(Cnode* course_list)
// {
//     /*DEBUG*/
//     #ifdef DEBUG
//     printf("DEBUG: Destroying course's list\n");
//     #endif
//     Cnode* aux = course_list->next;
//     Cnode* temp = NULL;
//     while (aux != NULL)
//     {
//         temp = aux -> next;
//         free(aux);
//         aux = temp;
//     }
//     free(course_list);
// }
