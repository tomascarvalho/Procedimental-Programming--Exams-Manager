#include "header.h"

/* File with functions to manipulate Files */

/*************************************************************/
/*              reads_from_students_file function            */
/* Function to read data stored in the files                 */
/* Receives the pointer to the first element of student list */
/* Returns a pointer to the first element of student list    */
/*************************************************************/
Snode* reads_from_students_file()
{

    FILE *fp;   /* pointer to file data type */
    char buffer[MAX_CHAR];  /* buffer to get data from file */
    Snode* student_list = NULL;
    Snode* aux = NULL;
    Snode* new_student = NULL;
    // Snode* new_student = NULL;
    // Student stdnt;

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
        printf("DEBUG: Reads something from student file...\n");
        #endif

        if ((new_student = create_student_list(new_student)) == NULL)  /* Alocates memory for new node */
            return NULL;

        removes_newLine(buffer); /* Removes new line from fgets */
        if ((new_student->student.id = (char*) malloc (sizeof(char) * strlen(buffer))) == NULL) /* Alocates memory to student.id */
        {
            printf("Memory Error!\n");
            return NULL;
        }
        strcpy(new_student->student.id, buffer); /* Copies buffer content over to student.degree */

        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        if ((new_student->student.degree = (char*) malloc (sizeof(char) * strlen(buffer))) == NULL) /* Alocates memory to student.degree */
        {
            printf("Memory Error!\n");
            return NULL;
        }
        strcpy(new_student->student.degree, buffer); /* Copies buffer content over to student.degree */


        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        new_student->student.year = atoi(buffer); /* Copies int to student.year with atoi function */
        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        new_student->student.regime = atoi(buffer); /* Copies int to student.regime with atoi function */
        new_student -> next = NULL;

        if (aux == NULL)
        {
            if ((student_list = create_student_list(student_list)) == NULL)  /* Alocates memory for new node */
                return NULL;
            aux = student_list;
            aux = new_student;
            student_list = aux;
        }
        else
        {
            aux->next = new_student;
            aux = aux -> next;
        }
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
    Snode* aux = student_list;
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
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: Writes something to file...\n");
        #endif

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
Cnode* reads_from_courses_file()
{

    FILE *fp;   /* pointer to file data type */
    char buffer[MAX_CHAR];  /* buffer to get data from file */
    Cnode* course_list = NULL;
    Cnode* aux = NULL;
    Cnode* new_course = NULL;
    course_list = NULL;

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

        if ((new_course = create_course_list(new_course)) == NULL) /* Alocates memory for new node */
            return NULL;
        removes_newLine(buffer); /* Removes new line from fgets */
        new_course -> course.name = (char*) malloc (sizeof(char) * strlen(buffer)); /* Alocates memory to course.name */
        strcpy(new_course -> course.name, buffer); /* Copies buffer content over to student.degree */

        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        new_course -> course.regent = (char*) malloc (sizeof(char) * strlen(buffer)); /* Alocates memory to course.regent */
        strcpy(new_course -> course.regent, buffer); /* Copies buffer content over to student.degree */

        new_course -> next = NULL; /* Sets ->next to NULL */

        if (aux == NULL)
        {
            if ((course_list = create_course_list()) == NULL)  /* Alocates memory for new node */
                return NULL;

            aux = new_course;
            course_list = aux;
        }
        else
        {
            aux->next = new_course;
            aux = aux -> next;
        }
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
    Cnode* aux = course_list;
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


/*************************************************************/
/*             writes_to_exams_file function                 */
/* Function to write data from the memory to a file          */
/* Receives the pointer to the first element of exams list   */
/* Returns a pointer to the first element of exams list      */
/*************************************************************/
Enode* writes_to_exams_file(Enode* exam_list)
{

    FILE *fp;   /* pointer to file data type */
    Enode* aux = exam_list;
    Spointer* students_aux = NULL;
    Snode* student_temp = NULL;
    int i = 0;
    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: writes_to_exams_file function called\n");
    #endif

    fp = fopen("exams_list.txt", "w+"); /* Opens the file in write+ mode */
    /* If aux is null */
    if (aux == NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: No entries on exams_list \n");
        #endif
        /* Then there is nothing to write on file and we can return */
        fclose(fp);
        return exam_list;
    }

    if (fp == NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: fp is Null -> Error opening file for writing\n");
        #endif
        printf("Erro a abrir o ficheiro para escrita\n");
        fclose(fp);
        return exam_list;
    }

    /* Iterate through student list nodes */
    while (aux != NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: Writes something to file...\n");
        #endif
        fputs(aux -> exam.course.name, fp); /* save course.name into file */
        fputs("\n", fp);
        fputs(aux -> exam.course.regent, fp); /* save course.regent into file */
        fputs("\n", fp);
        fprintf(fp, "%d\n", aux-> exam.period);
        fprintf(fp, "%d\n", aux-> exam.start_date.day);
        fprintf(fp, "%d\n", aux-> exam.start_date.month);
        fprintf(fp, "%d\n", aux-> exam.start_date.year);
        fprintf(fp, "%d\n", aux-> exam.start_date.hour);
        fprintf(fp, "%d\n", aux-> exam.start_date.minute);
        fprintf(fp, "%d\n", aux-> exam.end_date.day);
        fprintf(fp, "%d\n", aux-> exam.end_date.month);
        fprintf(fp, "%d\n", aux-> exam.end_date.year);
        fprintf(fp, "%d\n", aux-> exam.end_date.hour);
        fprintf(fp, "%d\n", aux-> exam.end_date.minute);
        fprintf(fp, "%d\n", aux-> exam.n_rooms);

        for (i = 0; i < aux->exam.n_rooms; i++)
        {
            fputs(aux-> exam.rooms[i], fp);
            if (i < aux-> exam.n_rooms -1) /* We dont want to put a \n in the last */
                fputs("\n", fp);
        }

        fprintf(fp, "%d\n", aux-> exam.n_students);
        students_aux = aux->exam.students;
        for (i = 0; i < aux->exam.n_students; i++)
        {
            student_temp = (students_aux->student);
            fputs(student_temp->student.id, fp);
            if (i < aux-> exam.n_students -1) /* We dont want to put a \n in the last */
                fputs("\n", fp);
            students_aux = students_aux -> next;

        }
        aux = aux -> next;
    }
    /* Dont forget to close the file */
    fclose(fp);
    return exam_list;
}


/*************************************************************/
/*              reads_from_exams_file function               */
/* Function to read data stored in the files                 */
/* Receives the pointer to the first element of exams list   */
/* Returns a pointer to the first element of exams list      */
/*************************************************************/
Enode* reads_from_exams_file()
{
    Enode* exam_list = NULL;
    FILE *fp;   /* pointer to file data type */
    char buffer[MAX_CHAR];  /* buffer to get data from file */
    Enode* aux = NULL;
    Exam new_exam;
    Enode* new_exam_node;
    Course crs;
    Date sdate;
    Date edate;
    int i = 0;
    /*DEBUG*/
    #ifdef DEBUG
    printf("\nDEBUG: reads_from_exams_file function called\n");
    #endif

    fp = fopen("exams_list.txt", "r"); /* Opens the file in read mode */
    /* If fp is null */
    if (fp == NULL)
    {
        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: No such file exams_list.txt\n");
        #endif
        /* Then there is no file and we can return */
        fclose(fp);
        return exam_list;
    }

    while (fgets(buffer, MAX_CHAR, fp) != NULL)
    {
        #ifdef DEBUG
        printf("DEBUG: Reads something from file...\n");
        #endif

        removes_newLine(buffer); /* Removes new line from fgets */
        crs.name = (char*) malloc (sizeof(char) * strlen(buffer)); /* Alocates memory to course.name */
        strcpy(crs.name, buffer); /* Copies buffer content over to student.degree */

        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        crs.regent = (char*) malloc (sizeof(char) * strlen(buffer)); /* Alocates memory to course.regent */
        strcpy(crs.regent, buffer); /* Copies buffer content over to student.degree */
        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        new_exam.period = atoi(buffer);

        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        sdate.day = atoi(buffer);
        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        sdate.month = atoi(buffer);
        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        sdate.year = atoi(buffer);
        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        sdate.hour = atoi(buffer);
        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        sdate.minute = atoi(buffer);

        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        edate.day = atoi(buffer);
        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        edate.month = atoi(buffer);
        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        edate.year = atoi(buffer);
        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        edate.hour = atoi(buffer);
        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        edate.minute = atoi(buffer);

        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        new_exam.n_rooms = atoi(buffer);

        for (i = 0; i < new_exam.n_rooms; i++)
        {
            fgets(buffer, MAX_CHAR, fp); /* Gets next line */
            removes_newLine(buffer); /* removes the new line from that line */
            if ((new_exam.rooms[i] = (char*) malloc (sizeof(char) * strlen(buffer))) == NULL)
            {
                printf("Erro: Sem memoria!\n");
                /*DEBUG*/
                #ifdef DEBUG
                printf("DEBUG: NO MEMORY AVAILABLE! ERROR\n");
                #endif
                return exam_list;
            }
            strcpy(new_exam.rooms[i], buffer);
        }

        fgets(buffer, MAX_CHAR, fp); /* Gets next line */
        removes_newLine(buffer); /* removes the new line from that line */
        new_exam.n_students = atoi(buffer);

        new_exam.course = crs;
        new_exam.start_date = sdate;
        new_exam.end_date = edate;

        new_exam_node = create_exam_list();
        new_exam_node->exam = new_exam;

        if (aux == NULL)
        {
            if ((exam_list = create_exam_list()) == NULL)  /* Alocates memory for new node */
                return NULL;

            aux = new_exam_node;
            exam_list = aux;
        }
        else
        {
            aux->next = new_exam_node;
            aux = aux -> next;
        }

    }

    fclose(fp); /* Don't forget to close the file */
    return exam_list;
}
