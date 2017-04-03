#include "header.h"


/******************************************************************************/
/*                              Main function                                 */
/*  Inicializes all the necessary structures and variables and calls the menu */
/******************************************************************************/
int main(int argc, char const *argv[]) {

    /* Pointer to the begining of our students list. Initialized with garbage on the first element*/
    student_list = (Snode*) malloc (sizeof(Snode));
    if (student_list == NULL)
    {
        printf("Erro: Sem memoria!\n");
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: NO MEMORY AVAILABLE! ERROR\n");
        #endif
        return 1;
    }
    student_list -> next = NULL;

    /* Pointer to the begining of the Courses list */
    course_list = (Cnode*) malloc (sizeof(Cnode));
    if (course_list == NULL)
    {
        printf("Erro: Sem memoria!\n");
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: NO MEMORY AVAILABLE! ERROR\n");
        #endif
        return 1;

    }
    course_list -> next = NULL;

    /* Pointer to the begining of the Courses list */
    exam_list = (Enode*) malloc (sizeof(Enode));
    if (exam_list == NULL)
    {
        printf("Erro: Sem memoria!\n");
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: NO MEMORY AVAILABLE! ERROR\n");
        #endif
        return 1;

    }
    exam_list -> next = NULL;
    /* Integers to save menu options */
    int menu_option, option;
    /* Pointer to Date data type */
    Date *system_date = (Date*) malloc(sizeof(Date));

    /*LOAD LISTS AND STRUCTURES FROM FILES HERE ....*/
    student_list = reads_from_students_file(student_list);
    course_list = reads_from_courses_file(course_list);
    exam_list = reads_from_exams_file(exam_list);
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
                    update_student();
                    break;

                case DELETE_STUDENT:
                    student_list = delete_student(student_list);
                    break;

                case LIST_STUDENTS:
                    count_students();
                    list_students();
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
                    update_course();
                    break;

                case DELETE_COURSE:
                    course_list = delete_course(course_list);
                    break;

                case LIST_COURSES:
                    list_courses();
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
                    exam_list = new_exam(exam_list);
                    break;

                case UPDATE_EXAM:
                    update_exam();
                    break;

                case DELETE_EXAM:
                    exam_list = delete_exam(exam_list);
                    break;

                case LIST_EXAMS:
                    list_exams();
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
    destroy_student_list(student_list);
    destroy_course_list(course_list);
    destroy_exam_list(exam_list);

    return 0;
}
