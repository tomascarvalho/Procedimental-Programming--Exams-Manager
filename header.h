#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>


/* DEBUG - Coment next line define to disable DEBUG */
#define DEBUG
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
#define BACK 0

/* Functions in Menu.c file */
int sub_menu(int menu_option, Date *system_date);
int menu(Date *system_date);

/* Functions in Date.c file */
void get_currentDate(Date *system_date);
Date new_date();
Date get_duration(Date date);

/* Funtions in Files.c file */
Snode* reads_from_students_file(Snode* student_list);
Snode* writes_to_students_file(Snode* student_list);
Cnode* reads_from_courses_file(Cnode* course_list);
Cnode* writes_to_courses_file(Cnode* course_list);
Enode* writes_to_exams_file(Enode* exam_list);
Enode* reads_from_exams_file(Enode* exam_list);

/* Functions in Students.c file */
Snode* new_student(Snode* student_list);
Snode* delete_student(Snode* student_list);
Snode* student_exists(char s_id[]);
void removes_newLine(char *str);
void destroy_student_list(Snode* student_list);
void update_student();
void count_students();
void list_students();


/* Functions in Courses.c file */
Cnode* new_course(Cnode* course_list);
Cnode* course_exists(char c_id[]);
Cnode* delete_course(Cnode* course_list);
void destroy_course_list(Cnode* course_list);
void list_courses();
void update_course();

/* Functions in Exams.c file */
Enode* new_exam(Enode* exam_list);
Enode* exam_exists(char cname[], int time);
Enode* delete_exam(Enode* exam_list);
int check_room(char* room, Date date);
void destroy_exam_list(Enode* exam_node);
void list_exams();
