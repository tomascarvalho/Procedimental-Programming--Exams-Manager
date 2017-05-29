#include "header.h"

void search_student(Snode* student_list)
{
    char aux_id[MAX_CHAR];
    Snode* aux = NULL;
    Snode* useless = NULL;
    printf("Numero de Estudante: ");
    fgets(aux_id, MAX_CHAR, stdin);
    removes_newLine(aux_id);

    if ((aux = student_exists(aux_id, &useless, student_list)) != NULL)
    {
        if (aux->student.regime == NORMAL_STUDENT)
            printf("\nID: %s\nCurso: %s\nAno: %d\nRegime: %s", aux->student.id, aux->student.degree, aux->student.year, "Normal");
        if (aux->student.regime == WORKER)
            printf("\nID: %s\nCurso: %s\nAno: %d\nRegime: %s", aux->student.id, aux->student.degree, aux->student.year, "Trabalhador Estudante");
        if (aux->student.regime == ATHLETE)
            printf("\nID: %s\nCurso: %s\nAno: %d\nRegime: %s", aux->student.id, aux->student.degree, aux->student.year, "Atleta");
        if (aux->student.regime == ASSOCIATIVE)
            printf("\nID: %s\nCurso: %s\nAno: %d\nRegime: %s", aux->student.id, aux->student.degree, aux->student.year, "Dirigente Associativo");
        if (aux->student.regime == ERASMUS)
            printf("\nID: %s\nCurso: %s\nAno: %d\nRegime: %s", aux->student.id, aux->student.degree, aux->student.year, "Erasmus");
    }
    else
    {
        printf("\nNao foi encontrado nenhum aluno com esse numero de estudante\n");
    }
    printf("\n");
    return;
}


void search_student_in_exam(Enode* exam_list)
{
    char aux_id[MAX_CHAR], aux_name[MAX_CHAR];
    char option;
    int aux_period;
    Enode* exam_aux = NULL;
    Exam new_exam;
    Student aux;
    Spointer* before = NULL;

    printf("\nDisciplina do exame: ");
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
    strcpy(new_exam.course.name, aux_name);
    new_exam.period = aux_period;

    /* Checks if course exists */
    exam_aux = exam_exists(new_exam, exam_list, NULL);
    if (exam_aux == NULL)
    {
        /* If the course to update does not exist we return */
        printf("Nao existe um exame a essa disciplina nessa epoca\n");
        return;
    }


    printf("Numero de Estudante: ");
    fgets(aux_id, MAX_CHAR, stdin);
    removes_newLine(aux_id);

    if (student_exists_in_exam(exam_aux->exam, &before, aux_id))
    {
        if (before == NULL)
            aux = *((exam_aux->exam.students)->student);
        else
            aux = *((before->next)->student);

        if (aux.regime == NORMAL_STUDENT)
            printf("\nID: %s\nCurso: %s\nAno: %d\nRegime: %s", aux.id, aux.degree, aux.year, "Normal");
        if (aux.regime == WORKER)
            printf("\nID: %s\nCurso: %s\nAno: %d\nRegime: %s", aux.id, aux.degree, aux.year, "Trabalhador Estudante");
        if (aux.regime == ATHLETE)
            printf("\nID: %s\nCurso: %s\nAno: %d\nRegime: %s", aux.id, aux.degree, aux.year, "Atleta");
        if (aux.regime == ASSOCIATIVE)
            printf("\nID: %s\nCurso: %s\nAno: %d\nRegime: %s", aux.id, aux.degree, aux.year, "Dirigente Associativo");
        if (aux.regime == ERASMUS)
            printf("\nID: %s\nCurso: %s\nAno: %d\nRegime: %s", aux.id, aux.degree, aux.year, "Erasmus");

    }
    else
        printf("\nNao ha nenhum aluno com esse numero de estudante inscrito no exame\n");
    return;
}

void search_exam(Enode* exam_list)
{
    char aux_name[MAX_CHAR];
    char option;
    int aux_period;
    Enode* aux = NULL;
    Exam new_exam;


    printf("\nDisciplina do exame: ");
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
    strcpy(new_exam.course.name, aux_name);
    new_exam.period = aux_period;

    /* Checks if course exists */
    aux = exam_exists(new_exam, exam_list, NULL);
    if (aux == NULL)
    {
        /* If the course to update does not exist we return */
        printf("Nao existe um exame a essa disciplina nessa epoca\n");
        return;
    }

    if (aux->exam.period == NORMAL)
        printf("Disciplina: %s\nRegente: %s\nEpoca: %s\nData Inicio: %d/%d/%d %2d:%2d\nData Fim: %d/%d/%d %2d:%2d\nNum Inscritos: %d\n", aux->exam.course.name, aux->exam.course.regent, "NORMAL", aux->exam.start_date.day, aux->exam.start_date.month, aux->exam.start_date.year, aux->exam.start_date.hour, aux->exam.start_date.minute, aux->exam.end_date.day, aux->exam.end_date.month, aux->exam.end_date.year, aux->exam.end_date.hour, aux->exam.end_date.minute, aux->exam.n_students);
    else if (aux->exam.period == SECOND)
        printf("Disciplina: %s\nRegente: %s\nEpoca: %s\nData Inicio: %d/%d/%d %2d:%2d\nData Fim: %d/%d/%d %2d:%2d\nNum Inscritos: %d\n", aux->exam.course.name, aux->exam.course.regent, "RECURSO", aux->exam.start_date.day, aux->exam.start_date.month, aux->exam.start_date.year, aux->exam.start_date.hour, aux->exam.start_date.minute, aux->exam.end_date.day, aux->exam.end_date.month, aux->exam.end_date.year, aux->exam.end_date.hour, aux->exam.end_date.minute, aux->exam.n_students);
    else if (aux->exam.period == SPECIAL)
        printf("Disciplina: %s\nRegente: %s\nEpoca: %s\nData Inicio: %d/%d/%d %2d:%2d\nData Fim: %d/%d/%d %2d:%2d\nNum Inscritos: %d\n", aux->exam.course.name, aux->exam.course.regent, "ESPECIAL", aux->exam.start_date.day, aux->exam.start_date.month, aux->exam.start_date.year, aux->exam.start_date.hour, aux->exam.start_date.minute, aux->exam.end_date.day, aux->exam.end_date.month, aux->exam.end_date.year, aux->exam.end_date.hour, aux->exam.end_date.minute, aux->exam.n_students);

    printf("Salas: ");
    for (int i = 0; i < aux->exam.n_rooms; i++)
            printf("%s   ", aux->exam.rooms[i]);

    return;
}


void search_course(Cnode* course_list)
{
    char aux_name[MAX_CHAR];
    Cnode* aux = NULL;
    Cnode* useless = NULL;

    printf("\nDisciplina: ");
    fgets(aux_name, MAX_CHAR, stdin);
    removes_newLine(aux_name);

    if ((aux = course_exists(aux_name, &useless, course_list)) == NULL)
    {
        /* If the course to update does not exist we return */
        printf("Nao existe uma disciplina com este nome\n");
        return;
    }
    printf("\nNome: %s\nRegente: %s\n\n", aux->course.name, aux->course.regent);
}
