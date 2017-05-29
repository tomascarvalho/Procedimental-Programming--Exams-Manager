#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* DEBUG - Coment next line define to disable DEBUG */
//#define DEBUG
/* List of defined variables -> avoid magic numbers! */
#define STUDENTS 1
#define COURSES 2
#define EXAMS 3
#define NORMAL_STUDENT 1
#define WORKER 2
#define ATHLETE 3
#define ASSOCIATIVE 4
#define ERASMUS 5
#define NORMAL 1
#define SECOND 2
#define SPECIAL 3
#define FINALIST 3
#define NEW_STUDENT 1
#define UPDATE_STUDENT 2
#define DELETE_STUDENT 3
#define LIST_STUDENTS 4
#define NEW_COURSE 1
#define UPDATE_COURSE 2
#define DELETE_COURSE 3
#define LIST_COURSES 4
#define NEW_EXAM 1
#define UPDATE_EXAM 2
#define DELETE_EXAM 3
#define LIST_EXAMS 4
#define LIST_STUDENTS_IN_EXAM 1
#define ADD_STUDENT_TO_EXAM 2
#define CHECK_EXAM_ROOMS 3
#define CAPACITY 30
#define BACK 0

/* Functions in Menu.c file */
int sub_menu(int menu_option, Date *system_date);
int menu(Date *system_date);
int menu_exams();

/* Functions in UsefulFunctions.c*/
void removes_newLine(char *str);


/* Functions in Date.c file */
void get_currentDate(Date *system_date);
Date new_date();
Date get_duration(Date date);
int date_cmp(Date d1, Date d2);

/* Funtions in Files.c file */
Snode* reads_from_students_file();
Snode* writes_to_students_file(Snode* student_list);
Cnode* reads_from_courses_file();
Cnode* writes_to_courses_file(Cnode* course_list);
Enode* writes_to_exams_file(Enode* exam_list);
Enode* reads_from_exams_file(Snode* student_list);

/* Functions in Students.c file */
Snode* create_student_list();
Snode* new_student(Snode* student_list);
Snode* delete_student(Snode* list, char* aux_id);
Snode* student_exists(char* s_id, Snode** before, Snode* student_list);
Snode* insert_student(Snode* list, Snode* new_student);
Snode* update_student(Snode* student_list);
void destroy_student_list(Snode* student_list);
void count_students(Snode* student_list);
void list_students(Snode* student_list);


/* Functions in Courses.c file */
Cnode* create_course_list();
Cnode* new_course(Cnode* course_list);
Cnode* course_exists(char* c_id, Cnode** before, Cnode* list);
Cnode* delete_course(char* aux_id, Cnode* course_listc);
Cnode* update_course(Cnode* course_list);
void destroy_course_list(Cnode* course_list);
void list_courses(Cnode* course_list);

/* Functions in Exams.c file */
Enode* create_exam_list();
Enode* new_exam(Enode* exam_list, Cnode* course_list);
Enode* exam_exists(Exam exam, Enode* exam_list);
Enode* delete_exam(Enode* exam_list, Enode* to_delete);
Enode* update_exam(Enode* exam_list);
Enode* register_student(Enode* exam_list, Cnode* course_list, Snode* student_list);
int student_exists_in_exam(Exam exam, Spointer** before, char* student_id);
void insert_exam_ordered(Enode** before, Enode*, Enode* exam_list);
int check_room(Exam exam, char* room, Date date, Enode* exam_list);
void destroy_exam_list(Enode* exam_list);
void list_exams(Enode* exam_list, Cnode* course_list, Snode* student_list);
void check_rooms_capacity(Enode* exam_list);
void list_students_exam(Enode* exam_list);
Spointer* create_student_in_exam_list();
