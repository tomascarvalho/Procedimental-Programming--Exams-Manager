#include "header.h"

/* TODO !!!
    Nao devo poder marcar duas salas iguais
    No update_student deveria poder fazer update mas por o mesmo numero de estudante
*/

/******************************************************************************/
/*                              Main function                                 */
/*  Inicializes all the necessary structures and variables and calls the menu */
/******************************************************************************/
int main(int argc, char const *argv[]) {

    /* we initialized our three linked lists*/
    Snode* student_list = NULL;
    Cnode* course_list = NULL;
    Enode* exam_list = NULL;

    char aux_id[MAX_CHAR];

    /* Integers to save menu options */
    int menu_option, option;
    /* Pointer to Date data type */
    Date *system_date = (Date*) malloc(sizeof(Date));

    /*LOAD LISTS AND STRUCTURES FROM FILES HERE ....*/
    student_list = reads_from_students_file();
    course_list = reads_from_courses_file();
    exam_list = reads_from_exams_file(student_list);
    // exam_list = reads_from_exams_file();

    /* Save the system date in Date data type */
    get_currentDate(system_date);

    #ifdef DEBUG
    printf("\nDEBUG: System date day: %d\n", system_date->day);
    printf("\nDEBUG: System date month: %d\n", system_date->month);
    printf("\nDEBUG: System date year: %d\n", system_date->year);
    printf("\nDEBUG: System date hour: %d\n", system_date->hour);
    printf("\nDEBUG: System date minute: %d\n", system_date->minute);
    #endif
    /* While we dont choose the option 0 in the menu */
    while ((menu_option = menu(system_date)))
    {
        fflush(stdin);
        /* Update the date and time */
        get_currentDate(system_date);

        /* Call the sub_menu funcion */
        option = sub_menu(menu_option, system_date);
        fflush(stdin);
        /* Switch Case */
        if (menu_option == STUDENTS)
        {
            switch (option)
            {
                case NEW_STUDENT:
                    student_list = new_student(student_list);
                    break;

                case UPDATE_STUDENT:
                    student_list = update_student(student_list);
                    break;

                case DELETE_STUDENT:
                    /*DEBUG*/
                    #ifdef DEBUG
                    printf("DEBUG: delete_student function called\n");
                    /* "eats" the \n from the previous input */
                    #endif
                    getchar();
                    printf("Numero do estudante a apagar: ");
                    fgets(aux_id, MAX_CHAR, stdin);
                    removes_newLine(aux_id);
                    student_list = delete_student(student_list, aux_id);
                    break;

                case LIST_STUDENTS:
                    count_students(student_list);
                    list_students(student_list);
                    break;

                case BACK:
                    break;
                default:
                    printf("Opcao invalida\n");
            }
        }
        else if (menu_option == COURSES)
        {
            switch (option)
            {
                case NEW_COURSE:
                    course_list = new_course(course_list);
                    break;

                case UPDATE_COURSE:
                    course_list = update_course(course_list);
                    break;

                case DELETE_COURSE:
                    /*DEBUG*/
                    #ifdef DEBUG
                    printf("DEBUG: delete_course function called\n");
                    #endif
                    getchar();
                    printf("Nome da disciplina a apagar: ");
                    fgets(aux_id, MAX_CHAR, stdin);
                    removes_newLine(aux_id);

                    course_list = delete_course(aux_id, course_list);
                    break;

                case LIST_COURSES:
                    list_courses(course_list);
                    break;

                case BACK:
                    break;
                default:
                    printf("Opcao invalida\n");
            }
        }
        else if (menu_option == EXAMS)
        {
            switch (option)
            {
                case NEW_EXAM:
                    exam_list = new_exam(exam_list, course_list);
                    break;

                case UPDATE_EXAM:
                    exam_list = update_exam(exam_list);
                    break;

                case DELETE_EXAM:
                    exam_list = delete_exam(exam_list, NULL);
                    break;

                case LIST_EXAMS:
                    list_exams(exam_list, course_list, student_list);
                    break;

                case BACK:
                    break;
                default:
                    printf("Opcao invalida\n");
            }
        }
        else if (menu_option == SEARCHES)
        {
            switch (option)
            {
                case SEARCH_STUDENT:
                    search_student(student_list);
                    break;

                case SEARCH_COURSE:
                    search_course(course_list);
                    break;

                case SEARCH_EXAM:
                    search_exam(exam_list);
                    break;

                case SEARCH_STUDENT_IN_EXAM:
                    search_student_in_exam(exam_list);
                    break;

                case BACK:
                    break;
                default:
                    printf("Opcao invalida\n");
            }
        }

    }

    #ifdef DEBUG
    printf("\nDEBUG: Option 0 \n");
    #endif
    printf("\nA encerrar....\n");

    /*SAVE SYSTEM STATE INTO FILES*/
    student_list = writes_to_students_file(student_list);
    course_list = writes_to_courses_file(course_list);
    exam_list = writes_to_exams_file(exam_list);

    /* Destroy linked lists from memory */
    if (student_list != NULL)
        destroy_student_list(student_list);
    if (course_list != NULL)
        destroy_course_list(course_list);
    if (exam_list != NULL)
        destroy_exam_list(exam_list);

    return 0;
}
