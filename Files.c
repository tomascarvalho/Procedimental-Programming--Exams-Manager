#include "header.h"

/* File with functions to manipulate Files */

/*************************************************************/
/*              reads_from_students_file function            */
/* Function to read data stored in the files                 */
/* Receives the pointer to the first element of student list */
/* Returns a pointer to the first element of student list    */
/*************************************************************/
Snode* reads_from_students_file(Snode* student_list)
{

    FILE *fp;   /* pointer to file data type */
    char buffer[MAX_CHAR];  /* buffer to get data from file */
    Snode* aux = student_list;
    Snode* new_student = NULL;
    Student stdnt;

    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: reads_from_file function called\n");
    #endif

    fp = fopen("student_list.txt", "r"); /* Opens the file in read mode */
    /* If fp is null */
    if (fp == NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: No such file students_list.txt\n");
        #endif
        /* Then there is no file and we can return */
        fclose(fp);
        return student_list;
    }

    while (fgets(buffer, MAX_CHAR, fp) != NULL)
    {
        #ifdef DEBUG
        printf("DEBUG: Reads something from file...\n");
        #endif

        new_student = (Snode*) malloc (sizeof(Snode)); /* Alocates memory for new node */

        removes_newLine(buffer); /* Removes new line from fgets */
        stdnt.id = (char*) malloc (sizeof(char) * strlen(buffer)); /* Alocates memory to student.id */
        strcpy(stdnt.id, buffer); /* Copies buffer content over to student.degree */

        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        stdnt.degree = (char*) malloc (sizeof(char) * strlen(buffer)); /* Alocates memory to student.degree */
        strcpy(stdnt.degree, buffer); /* Copies buffer content over to student.degree */


        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        stdnt.year = atoi(buffer); /* Copites int to student.year with atoi function */
        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        stdnt.regime = atoi(buffer); /* Copites int to student.regime with atoi function */

        new_student -> student = stdnt;
        new_student -> next = NULL; /* Sets ->next to NULL */
        aux -> next = new_student; /* Adds new_student to student_list */
        aux = new_student;
    }

    fclose(fp); /* Don't forget to close the file */
    return student_list;
}

/*************************************************************/
/*             writes_to_students_file function              */
/* Function to write data from the memory to a file          */
/* Receives the pointer to the first element of student list */
/* Returns a pointer to the first element of student list    */
/*************************************************************/
Snode* writes_to_students_file(Snode* student_list)
{

    FILE *fp;   /* pointer to file data type */
    Snode* aux = student_list -> next;
    char buffer[MAX_CHAR];
    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: writes_to_students_file function called\n");
    #endif

    fp = fopen("student_list.txt", "w+"); /* Opens the file in write+ mode */
    /* If aux is null */
    if (aux == NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: No entries on student_list \n");
        #endif
        /* Then there is nothing to write on file and we can return */
        fclose(fp);
        return student_list;
    }

    if (fp == NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: fp is Null -> Error opening file for writing\n");
        #endif
        printf("Erro a abrir o ficheiro para escrita\n");
        fclose(fp);
        return student_list;
    }

    /* Iterate through student list nodes */
    while (aux != NULL)
    {
        fputs(aux -> student.id, fp); /* save student.id into file */
        fputs("\n", fp);
        fputs(aux -> student.degree, fp); /* save student.degree into file */
        fputs("\n", fp);
        snprintf(buffer, MAX_CHAR, "%d", aux -> student.year);
        fputs(buffer, fp); /* save student.year into file */
        fputs("\n", fp);
        snprintf(buffer, MAX_CHAR, "%d", aux -> student.regime);
        fputs(buffer, fp); /* save student.regime into file */
        fputs("\n", fp);
        aux = aux -> next;
    }
    /* Dont forget to close the file */
    fclose(fp);
    return student_list;
}

/*************************************************************/
/*              reads_from_courses_file function             */
/* Function to read data stored in the files                 */
/* Receives the pointer to the first element of courses list */
/* Returns a pointer to the first element of courses list    */
/*************************************************************/
Cnode* reads_from_courses_file(Cnode* course_list)
{

    FILE *fp;   /* pointer to file data type */
    char buffer[MAX_CHAR];  /* buffer to get data from file */
    Cnode* aux = course_list;
    Cnode* new_course = NULL;
    Course crs;

    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: reads_from_courses_file function called\n");
    #endif

    fp = fopen("courses_list.txt", "r"); /* Opens the file in read mode */
    /* If fp is null */
    if (fp == NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: No such file courses_list.txt\n");
        #endif
        /* Then there is no file and we can return */
        fclose(fp);
        return course_list;
    }

    while (fgets(buffer, MAX_CHAR, fp) != NULL)
    {
        #ifdef DEBUG
        printf("DEBUG: Reads something from file...\n");
        #endif

        new_course = (Cnode*) malloc (sizeof(Cnode)); /* Alocates memory for new node */

        removes_newLine(buffer); /* Removes new line from fgets */
        crs.name = (char*) malloc (sizeof(char) * strlen(buffer)); /* Alocates memory to course.name */
        strcpy(crs.name, buffer); /* Copies buffer content over to student.degree */

        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        crs.regent = (char*) malloc (sizeof(char) * strlen(buffer)); /* Alocates memory to course.regent */
        strcpy(crs.regent, buffer); /* Copies buffer content over to student.degree */

        new_course -> course = crs;
        new_course -> next = NULL; /* Sets ->next to NULL */
        aux -> next = new_course; /* Adds new_course to course_list */
        aux = new_course;
    }

    fclose(fp); /* Don't forget to close the file */
    return course_list;
}

/*************************************************************/
/*             writes_to_courses_file function               */
/* Function to write data from the memory to a file          */
/* Receives the pointer to the first element of courses list */
/* Returns a pointer to the first element of courses list    */
/*************************************************************/
Cnode* writes_to_courses_file(Cnode* course_list)
{

    FILE *fp;   /* pointer to file data type */
    Cnode* aux = course_list -> next;
    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: writes_to_courses_file function called\n");
    #endif

    fp = fopen("courses_list.txt", "w+"); /* Opens the file in write+ mode */
    /* If aux is null */
    if (aux == NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: No entries on course_list \n");
        #endif
        /* Then there is nothing to write on file and we can return */
        fclose(fp);
        return course_list;
    }

    if (fp == NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: fp is Null -> Error opening file for writing\n");
        #endif
        printf("Erro a abrir o ficheiro para escrita\n");
        fclose(fp);
        return course_list;
    }

    /* Iterate through student list nodes */
    while (aux != NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: Writes something to file...\n");
        #endif
        fputs(aux -> course.name, fp); /* save course.name into file */
        fputs("\n", fp);
        fputs(aux -> course.regent, fp); /* save course.regent into file */
        fputs("\n", fp);
        aux = aux -> next;
    }
    /* Dont forget to close the file */
    fclose(fp);
    return course_list;
}
