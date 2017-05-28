#include "header.h"

/* File with functions to manipulate the list of exams */


/*************************************************************/
/*               create_exam_list function                   */
/* Function to create a new empty list of exams              */
/* Receives no arguments                                     */
/* Returns a pointer to the first element of the list        */
/*************************************************************/
Enode* create_exam_list()
{
    Enode* exam_list = (Enode*) malloc (sizeof(Enode));
    if (exam_list == NULL)
    {
        printf("Erro: Sem memoria!\n");
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: NO MEMORY AVAILABLE! ERROR\n");
        #endif
        return NULL;

    }
    exam_list -> next = NULL;
    return exam_list;
}

/*************************************************************/
/*                  new_exam function                        */
/* Function to create a new exam and add it to the list      */
/* Receives the pointer to the first element of exams list   */
/* Returns a pointer to the first element of exams list      */
/*************************************************************/
Enode* new_exam(Enode* exam_list, Cnode* course_list)
{
    Enode* new_exam_node = NULL;
    Enode* before = NULL;
    Exam new_exam;
    Cnode* aux_course = NULL;
    Cnode* useless_course = create_course_list();
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
    if (course_list == NULL)
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
        aux_course = course_exists(aux_name, &useless_course, course_list);
        if (aux_course == NULL)
        {
            printf("Nao existe uma disciplina com esse nome...\n");
            printf("Sair?(s/(default nao)): ");
            fgets(aux_name, MAX_CHAR, stdin);
            removes_newLine(aux_name);
            if (strcmp(aux_name, "s") == 0)
                return exam_list;
        }

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
    new_exam.course.name = (char*) malloc (sizeof(char) * strlen(aux_name));

    strcpy(new_exam.course.name, aux_name);
    new_exam.period = aux_period;

    if (exam_exists(new_exam, exam_list) != NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: Exam already exists!\n");
        #endif
        printf("O exame ja existe para esta disciplina e esta epoca!\n");
        return exam_list;
    }


    printf("Data do exame\n");
    aux_date = new_date();




    if ((new_exam_node = create_exam_list()) == NULL)
    {
        printf("Erro: Sem memoria!\n");
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: NO MEMORY AVAILABLE! ERROR\n");
        #endif
        return exam_list;
    }



    new_exam_node -> next = NULL;
    crs.name = (char*) malloc (strlen(aux_course->course.name) * sizeof(char));
    strcpy(crs.name, aux_course->course.name);
    crs.regent = (char*) malloc (strlen(aux_course->course.regent) * sizeof(char));
    strcpy(crs.regent, aux_course->course.regent);
    new_exam.course = crs;
    new_exam.period = aux_period;
    Spointer* list_of_students = (Spointer*) malloc (sizeof(Spointer));
    list_of_students -> next = NULL;
    new_exam.students = list_of_students;
    new_exam.n_students = 0;
    new_exam.start_date = aux_date;
    aux_date = get_duration(aux_date);
    new_exam.end_date = aux_date;



    /* Do... */
    do {
        printf("Numero de salas a reservar para o exame: "); /* Asks for the number of rooms */
        fgets(option_rooms, MAX_CHAR, stdin);
        n_rooms = atoi(option_rooms);
        if (n_rooms == 0)
            printf("Insira um numero valido!\n");
    } while (n_rooms == 0); /* While the number is not valid */

    new_exam.n_rooms = n_rooms;

    while (i < n_rooms)
    {
        printf("%da sala: ", i+1);
        fgets(option_rooms, MAX_CHAR, stdin);
        if (check_room(new_exam, option_rooms, new_exam.start_date, exam_list))
        {
            if ((new_exam.rooms[i] = (char*) malloc (sizeof(char) * strlen(option_rooms))) == NULL)
            {
                printf("Erro: Sem memoria!\n");
                /*DEBUG*/
                #ifdef DEBUG
                printf("DEBUG: NO MEMORY AVAILABLE! ERROR\n");
                #endif
                return exam_list;
            }
            strcpy(new_exam.rooms[i], option_rooms);
            i++;
        }
        else
            printf("Sala ja reservada para um exame. Por favor, selecionar outra sala\n");
    }

    new_exam.students = NULL;

    new_exam_node -> exam = new_exam;

    insert_exam_ordered(&before, new_exam_node, exam_list);
    if (before == NULL)
    {
        exam_list = new_exam_node;
        new_exam_node->next = NULL;
    }
    else
    {
        new_exam_node->next = before->next;
        before->next = new_exam_node;
    }
    return exam_list;

}

int check_room(Exam exam, char* room, Date date, Enode* exam_list)
{
    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: Function check_room called\n");
    #endif
    Enode* aux = exam_list;
    int i;
    if (aux == NULL)
        return 1;

    while (aux != NULL)
    {
        if ((aux->exam.start_date.year == date.year) && (aux->exam.start_date.month == date.month) && (aux->exam.start_date.day == date.day))
        {
            if ((aux->exam.start_date.hour <= date.hour) && (aux->exam.end_date.hour > date.hour))
            {
                for (i = 0; i < aux->exam.n_rooms; i++)
                {
                    if (strcmp(aux->exam.rooms[i], room) == 0)
                    {
                        return 0;
                    }
                }
            }
            else if (aux->exam.end_date.hour == date.hour)
            {
                if (aux->exam.end_date.minute > date.minute)
                {
                    for (i = 0; i < aux->exam.n_rooms; i++)
                    {
                        if (strcmp(aux->exam.rooms[i], room) == 0)
                        {
                            return 0;
                        }
                    }
                }
            }
        }
        aux = aux->next;

    }
    return 1;
}


/****************************************************************/
/*                   list_exams function                        */
/* Function to list the existing examss in the courses list     */
/* Receives no params                                           */
/* Returns void                                                 */
/****************************************************************/
void list_exams(Enode* exam_list)
{
    Enode* aux = exam_list;
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
    printf("\nDisciplina\t\tRegente\tEpoca\tData Inicio\tData Fim\tNum Inscritos\tSalas\n");

    while (aux != NULL)
    {
        if (aux->exam.period == NORMAL)
            printf("\n%s\t\t%s\t%s\t%d/%d/%d %2d:%2d\t%d/%d/%d %2d:%2d\t%d\t", aux->exam.course.name, aux->exam.course.regent, "NORMAL", aux->exam.start_date.day, aux->exam.start_date.month, aux->exam.start_date.year, aux->exam.start_date.hour, aux->exam.start_date.minute, aux->exam.end_date.day, aux->exam.end_date.month, aux->exam.end_date.year, aux->exam.end_date.hour, aux->exam.end_date.minute, aux->exam.n_students);
        else if (aux->exam.period == SECOND)
            printf("\n%s\t\t%s\t%s\t%d/%d/%d %2d:%2d\t%d/%d/%d %2d:%2d\t%d\t", aux->exam.course.name, aux->exam.course.regent, "RECURSO", aux->exam.start_date.day, aux->exam.start_date.month, aux->exam.start_date.year, aux->exam.start_date.hour, aux->exam.start_date.minute, aux->exam.end_date.day, aux->exam.end_date.month, aux->exam.end_date.year, aux->exam.end_date.hour, aux->exam.end_date.minute, aux->exam.n_students);
        else if (aux->exam.period == SPECIAL)
            printf("\n%s\t\t%s\t%s\t%d/%d/%d %2d:%2d\t%d/%d/%d %2d:%2d\t%d\t", aux->exam.course.name, aux->exam.course.regent, "ESPECIAL", aux->exam.start_date.day, aux->exam.start_date.month, aux->exam.start_date.year, aux->exam.start_date.hour, aux->exam.start_date.minute, aux->exam.end_date.day, aux->exam.end_date.month, aux->exam.end_date.year, aux->exam.end_date.hour, aux->exam.end_date.minute, aux->exam.n_students);
        for (i = 0; i < aux->exam.n_rooms; i++)
            if (i == 0)
                printf("\t\t\t\t\t\t\t\t%s\n", aux->exam.rooms[i]);
            else
                printf("\t\t\t\t\t\t\t\t%s\n", aux->exam.rooms[i]);
        aux = aux->next;
    }
}

Enode* exam_exists(Exam exam, Enode* exam_list)
{
    Enode* aux = exam_list;

    if (aux == NULL)
        return NULL;

    while (aux != NULL)
    {
        if (strcmp(aux->exam.course.name, exam.course.name) == 0)
            if (aux-> exam.period == exam.period)
                return aux;
        aux = aux->next;
    }
    return NULL;
}


/*********************************************************************/
/*                    update_course function                         */
/* Function to update a course from the list                         */
/* Receives no params                                                */
/* Returns void                                                      */
/*********************************************************************/
Enode* update_exam(Enode* exam_list)
{
    Exam new_exam;
    Enode* to_update = NULL;
    Enode* before = NULL;
    Date aux_date;
    char aux_name[MAX_CHAR], option_rooms[MAX_CHAR];
    int aux_period = 0, n_rooms = 0, i = 0;
    char option;

    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: update_exam function called\n");
    #endif
    /* "eats" the \n from the previous input */
    getchar();
    printf("\nDisciplina do exame a actualizar: ");
    fgets(aux_name, MAX_CHAR, stdin);
    /* Removes the \n from the aux_name (fgets function) */
    removes_newLine(aux_name);
    do
    {
        /* asks for course period */
        printf("Epoca:\n1- Normal\n2- Recurso\n3- Especial\n");
        scanf("%c", &option);
        getchar();
    } while (option < '1' || option > '3'); /* While option is not in valid range */
    aux_period = (int)(option - '0');

    new_exam.course.name = (char*) malloc (sizeof(char)*strlen(aux_name));
    new_exam.period = aux_period;

    /* Checks if course exists */
    to_update = exam_exists(new_exam, exam_list);
    if (to_update == NULL)
    {
        /* If the course to update does not exist we return */
        printf("Nao existe um exame a essa disciplina nessa epoca\n");
        return exam_list;
    }

    printf("Actualizar exame\n");

    /*Do... */
    do
    {
        /* asks for course period */
        printf("Epoca:\n1- Normal\n2- Recurso\n3- Especial\n");
        scanf("%c", &option);
        getchar();
    } while (option < '1' || option > '3'); /* While option is not in valid range */
    aux_period = (int)(option - '0');
    new_exam.period = aux_period;


    if (exam_exists(new_exam, exam_list) != NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: Exam already exists!\n");
        #endif
        printf("O exame ja existe para esta disciplina e esta epoca!\n");
        return exam_list;
    }

    printf("Data do exame\n");
    aux_date = new_date();
    new_exam.start_date = aux_date;
    aux_date = get_duration(aux_date);
    new_exam.end_date = aux_date;

    to_update -> exam = new_exam;


    /* Do... */
    do {
        printf("Numero de salas a reservar para o exame: "); /* Asks for the number of rooms */
        fgets(option_rooms, MAX_CHAR, stdin);
        n_rooms = atoi(option_rooms);
        if (n_rooms == 0)
            printf("Insira um numero valido!\n");
    } while (n_rooms == 0); /* While the number is not valid */

    to_update -> exam.n_rooms = n_rooms;

    memset(to_update->exam.rooms, '\0', MAX_CHAR); /* Cleans the rooms matrix... we dont want garbage date in it */
    while (i < n_rooms)
    {
        printf("%da sala: ", i+1);
        fgets(option_rooms, MAX_CHAR, stdin);
        if (check_room(to_update->exam, option_rooms, to_update->exam.start_date, exam_list))
        {
            if ((to_update -> exam.rooms[i] = (char*) malloc (sizeof(char) * strlen(option_rooms))) == NULL)
            {
                printf("Erro: Sem memoria!\n");
                /*DEBUG*/
                #ifdef DEBUG
                printf("DEBUG: NO MEMORY AVAILABLE! ERROR\n");
                #endif
                return exam_list;
            }
            strcpy(to_update->exam.rooms[i], option_rooms);
            i++;
        }
        else
            printf("Sala ja reservada para um exame. Por favor, selecionar outra sala\n");
    }

    /* We need to delete the exam from the list and insert it in the correct order */
    exam_list = delete_exam(exam_list, to_update);
    insert_exam_ordered(&before, to_update, exam_list);
    if (before == NULL)
    {
        exam_list = to_update;
        to_update->next = NULL;
    }
    else
    {
        to_update->next = before->next;
        before->next = to_update;
    }
    return exam_list;
}

void insert_exam_ordered(Enode** before, Enode* to_update, Enode* exam_list)
{
    Enode* aux = exam_list;

    if (aux == NULL)
    {
        return;
    }

    while (aux != NULL)
    {
        if (date_cmp(aux->exam.start_date, to_update->exam.start_date) > 0)
        {
            *before = aux;
            return;
        }
    }
}


/*********************************************************************/
/*                   register_student function                       */
/* Function to add a student to an exam student list                 */
/* Receives no params                                                */
/* Returns void                                                      */
/*********************************************************************/
// Enode* register_student(Enode* exam_list, Cnode* course_list, Snode* student_list)
// {
//     char aux_name[MAX_CHAR];
//     Cnode* useless_course = NULL;
//     Cnode* aux_course;
//     Snode* student_aux = create_student_list(student_aux);
//     Snode* new_student = NULL;
//
//     if (exam_list == NULL)
//     {
//         printf("Nao ha exames onde possa inscrever o aluno\n");
//         return;
//     }
//
//     do
//     {   /*Asks for course name... */
//         printf("Nome da Disciplina: ");
//         fgets(aux_name, MAX_CHAR, stdin);
//         removes_newLine(aux_name);
//         aux_course = course_exists(aux_name, &useless_course, course_list);
//         if (aux_course == NULL)
//         {
//             printf("Nao existe uma disciplina com esse nome...\n");
//             printf("Sair?(s/n(default nao)): ");
//             fgets(aux_name, MAX_CHAR, stdin);
//             removes_newLine(aux_name);
//             if (strcmp(aux_name, "s") == 0)
//                 return exam_list;
//         }
//
//     } while(aux_course == NULL); /* While the user fails to provid a valid course name */
//
//     /*Do... */
//     do
//     {
//         /* asks for course period */
//         printf("Epoca:\n1- Normal\n2- Recurso\n3- Especial\n");
//         scanf(" %c", &option);
//         getchar();
//         if (option < '1' || option > '3')
//         {
//             printf("Opcao invalida...\n");
//             printf("Sair?(s/(default nao)): ");
//             fgets(aux_name, MAX_CHAR, stdin);
//             removes_newLine(aux_name);
//             if (strcmp(aux_name, "s") == 0)
//                 return exam_list;
//         }
//
//     } while (option < '1' || option > '3'); /* While option is not in valid range */
//
//
//
//
//
//     printf("Numero do estudante a inscrever no exame\n");
//     fgets(aux_name, MAX_CHAR, stdin); /* gets the student id from the user */
//     removes_newLine(aux_name); /* removes the new line from the fgets function */
//
//     if ((new_student = student_exists(aux_name, &student_aux, exam_list)) != NULL)
//     {
//         if (student_exists_in_exam(exam, new_student->student.name) == 0)
//         {
//             if (exam->exam.period != SPECIAL)
//             {
//                 exam->exam.n_students += 1;
//                 before->next = *new_student;
//
//
//             }
//             else
//             {
//                 if (student_aux ->student.regime == NORMAL_STUDENT || student_aux->student.regime == ERASMUS)
//                 {
//                     exam->n_students += 1;
//                     new_student = (Snode*) malloc (sizeof(Snode));
//                     new_student-> student = student_aux -> student;
//                     new_student -> next = NULL;
//                     exam->students = insert_student(exam->students, new_student);
//                 }
//                 else if (student_aux -> student.year == FINALIST)
//                 {
//                     exam->n_students += 1;
//                     new_student = (Snode*) malloc (sizeof(Snode));
//                     new_student-> student = student_aux -> student;
//                     new_student -> next = NULL;
//                     exam->students = insert_student(exam->students, new_student);
//                 }
//                 else
//                 {
//                     printf("O aluno nao tem estatuto para se poder realizar um exame de epoca especial\n");
//                     return;
//                 }
//
//             }
//         }
//         else
//         {
//             /*DEBUG*/
//             #ifdef DEBUG
//             printf("DEBUG: student_exists returned !null or for exam->students\n");
//             #endif
//             printf("O estudante ja se encontra registado no exame\n");
//             return;
//         }
//     }
//     else
//     {
//         /*DEBUG*/
//         #ifdef DEBUG
//         printf("DEBUG: student_exists returned null or for student_list\n");
//         #endif
//         printf("Nao existe um estudante com esse numero de estudante\n");
//         return;
//     }
//     printf("Aluno inscrito com sucesso\n");
//
//
// }

// int student_exists_in_exam(Exam exam, char* student_id)
// {
//     Spointer* this_exam_slist = NULL;
//     exam_slist = exam.student_list;
//     for (int i = 0; i < exam.n_alunos; i++)
//     {
//         if (strcmp(exam_slist->student.id, student_id) == 0)
//         {
//             return 1;
//         }
//         exam_slist = exam_slist -> next;
//     }
//     return 0;
// }


/*********************************************************************/
/*                     delete_exam function                          */
/* Function to delete a exam from the list                           */
/* Receives a pointer to the beginning of the exam list              */
/* Returns a pointer to the beginning of the exam list               */
/*********************************************************************/
Enode* delete_exam(Enode* exam_list, Enode* to_remove)
{
    Exam to_remove_exam;
    Enode* before = NULL;
    char aux_name[MAX_CHAR];
    char option;
    int aux_period;
    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: delete_exam function called\n");
    #endif
    /* "eats" the \n from the previous input */
    if (to_remove == NULL)
    {
        getchar();
        printf("Nome da disciplina do exame a apagar: ");
        fgets(aux_name, MAX_CHAR, stdin);
        removes_newLine(aux_name);
        /*Do... */
        do
        {
            /* asks for course period */
            printf("Epoca do Exame a Remover:\n1- Normal\n2- Recurso\n3- Especial\n");
            scanf(" %c", &option);
            getchar();

        } while (option < '1' || option > '3'); /* While option is not in valid range */
        aux_period = (int)(option - '0');

        to_remove_exam.course.name = (char*) malloc (sizeof(char) * strlen(aux_name));
        strcpy(to_remove_exam.course.name, aux_name);
        to_remove_exam.period = aux_period;
        to_remove = exam_exists(to_remove_exam, exam_list);

        if (to_remove == NULL)
        {
            printf("Nao existe um exame que obedeca a este criterio.\n");
            return exam_list;
        }
    }


    if (before != NULL)
    {
        before -> next = to_remove->next;
        free(to_remove);
    }

    else
    {
        exam_list = to_remove->next;
        free(to_remove);
    }

    printf("Exame removido com sucesso\n");
    return exam_list;
}


/*********************************************************************/
/*                     destroy_list functions                        */
/* Function to destroy a linked list by free(ing) its nodes          */
/* Receives a pointer to the beginning of the exam list              */
/* Returns void                                                      */
/*********************************************************************/
void destroy_exam_list(Enode* exam_list)
{
    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: Destroying exam's list\n");
    #endif
    Enode* aux = exam_list->next;
    Enode* temp = NULL;
    while (aux != NULL)
    {
        temp = aux -> next;
        /* Do I need to free the student list here ? */
        free(aux);

        aux = temp;
    }
    free(exam_list);
}
