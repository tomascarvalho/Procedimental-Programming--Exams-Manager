#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR 64

/*******************************************/
/* Data structure for Student type of data */
/*******************************************/
typedef struct student
{
    char* id; /* Student id */
    char* degree; /* Degree */
    int year; /* Year of study */
    int regime; /*  1- Normal
                    2- Student worker
                    3- Athlete
                    4- Associative Leader
                    5- Erasmus
                */
} Student;

/******************************************/
/* Data structure for Course type of data */
/******************************************/
typedef struct course
{
    char* name; /* Course name */
    char* regent; /* Teacher responsible for the course */

} Course;

/****************************************/
/* Data structure for Date type of data */
/****************************************/
typedef struct date
{
    int year;
    int month;
    int day;
    int hour;
    int minute;

} Date;


/***************************************/
/* Node for a linked list of Students  */
/***************************************/
typedef struct student_node
{
    Student student; /* Student data type */
    struct student_node *next; /* Pointer to next student node */
} Snode;

/***************************************************/
/* Node for a linked list of pointers to students  */
/***************************************************/
typedef struct student_pointers_node
{
    Student* student;
    struct student_pointers_node *next; /* Pointer to next student node */
} Spointer;

/***************************************/
/* Node for a linked list of Courses   */
/***************************************/
typedef struct course_node
{
    Course course; /* Course data type */
    struct course_node *next; /* Pointer to next course node */
} Cnode;


/*******************************************/
/* Data structure for Exam type of data */
/*******************************************/
typedef struct exam
{
    Course course; /* The exam points to its course */
    Date start_date; /* The exam has a start date associated */
    Date end_date; /* end_date = start_date + the duration of the exam */
    char* rooms[MAX_CHAR]; /* The exam has one or more rooms associated */
    int n_rooms; /* Number of rooms alocated for the exam */
    int n_students; /* Number of students */
    int period; /*  The exam can be:
                    NORMAL- Normal Period
                    SECOND- Second Period
                    SPECIAL- Special Period */
    struct student_pointers_node *students; /*  List of pointers to students.
                                        The exam has a list of enrolled students
                                    */

} Exam;



/***********************************/
/* Node for a linked list of Exams */
/***********************************/
typedef struct exam_node
{
    Exam exam;
    struct exam_node *next;

}Enode;
