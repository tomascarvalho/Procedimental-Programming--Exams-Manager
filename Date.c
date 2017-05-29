#include "header.h"

/* Gets the current date and time */
void get_currentDate(Date *date)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now); /* Get the system date using time.h functions */
    date->day = t->tm_mday;
    date->month = t->tm_mon+1;
    date->year = t->tm_year+1900;
    date->hour = t->tm_hour;
    date->minute = t->tm_min;
}

Date new_date()
{
    Date date;
    int is_valid = 0;
    char aux_day[MAX_CHAR], aux_month[MAX_CHAR], aux_year[MAX_CHAR], aux_hour[MAX_CHAR], aux_minute[MAX_CHAR];

    /*DEBUG*/
    #ifdef DEBUG
    printf("DEBUG: new_date called\n");
    #endif

    while(!is_valid)
    {

        printf("\nPor favor insira a data\n");
        printf("Dia: ");
        fgets(aux_day, MAX_CHAR, stdin);
        printf("Mes: ");
        fgets(aux_month, MAX_CHAR, stdin);
        printf("Ano: ");
        fgets(aux_year, MAX_CHAR, stdin);
        date.day = atoi(aux_day); /* Convert to int using atoi (returns 0 if is invalid) */
        date.month = atoi(aux_month);
        date.year = atoi(aux_year);

        /*DEBUG*/
        #ifdef DEBUG
        printf("DEBUG: date.day: %d date.month: %d date.year: %d\n", date.day, date.month, date.year);
        #endif

        if ((date.month == 2) && (date.day > 0)) /* If the date is February */
        {
            if (((date.year % 4) == 0) && ((date.day <=29))) /* If it's a leap year we can go up to day 29 */
            {
                is_valid = 1;
            }
            else if ((date.year % 4 != 0) && (date.day<29)) /* Else, we can only go up to 28 */
            {
                is_valid = 1;
            }
            else /* Else the date is invalid */
            {
                printf("Data invalida!!");
            }

        }
        /* If we choose a month with 31 days */
        else if ((date.month==1) || (date.month==3) || (date.month==5) || (date.month==7) || (date.month==8) || (date.month==10) || (date.month==12))
        {
            /* We can have up to 31 days*/
            if ((date.day <= 31) && (date.day >=1))
            {
                is_valid = 1;
            }
            else /* else, it's invalid */
            {
                printf("Data invalida!!");
            }
        }
        /* Else if the month has only 30 days */
        else if ((date.month == 4)||(date.month == 6)||(date.month == 9)||(date.month == 11))
        {
            if ((date.day <= 30)&&(date.day >= 1))
            {
                is_valid = 1;
            }
            else
            {
                printf("Data invalida!!");
            }
        }
        /* Else our date is invalid */
        else
        {
            printf("Data invalida!!");
        }

    }

    is_valid = 0;

    while (!is_valid)
    {
        printf("\nPor favor insira as horas\n");
        printf("Hora: ");
        fgets(aux_hour, MAX_CHAR, stdin);
        printf("Minutos: ");
        fgets(aux_minute, MAX_CHAR, stdin);
        date.hour = atoi(aux_hour);
        date.minute = atoi(aux_minute);

        if ((date.hour >= 0) && (date.hour <= 23))
        {
            if ((date.minute >= 0) || (date.minute <= 59))
            {
                is_valid = 1;
            }
            else
            {
                printf("Data invalida!!");
            }
        }
        else
        {
            printf("Hora invalida!!");
        }

    }
    return date;
}

Date get_duration(Date start_date)
{
    Date date;
    date.year = 0;
    date.month = 0;
    date.day = 0;
    date.hour = 0;
    date.minute = 0;
    char aux_hour[MAX_CHAR], aux_minute[MAX_CHAR];
    int hour = 0, minute = 0;
    int is_valid = 0;

    while (!is_valid)
    {
        printf("\nPor favor insira a duracao do exame (ex: 2:00)\n");
        printf("Horas: ");
        fgets(aux_hour, MAX_CHAR, stdin);
        printf("Minutos: ");
        fgets(aux_minute, MAX_CHAR, stdin);
        hour = atoi(aux_hour);
        minute = atoi(aux_minute);

        if ((hour >= 0) && (hour <= 23))
        {
            if ((minute >= 0) || (minute <= 59))
            {
                is_valid = 1;
            }
            else
            {
                printf("Duracao invalida!!");
            }
        }
        else
        {
            printf("Duracao invalida!!");
        }

    }

    if ((minute + start_date.minute) > 59)
        date.hour++;
    date.minute += (start_date.minute + minute)%60;

    if ((hour + start_date.hour) > 23)
        date.day++;
    date.hour += (hour + start_date.hour)%24;
    date.day += start_date.day;
    date.year += start_date.year;
    date.month += start_date.month;

    if ((date.day > 28 && date.month == 2))
    {
        if (date.day == 30)
        {
            date.day = 1;
            date.month +=1;
        }
        else
        {
            if (date.year % 4 != 0)
            {
                date.day = 1;
                date.month += 1;
            }
        }
    }

    else if ((date.day > 30) && ((date.month == 4)||(date.month == 6)||(date.month == 9)||(date.month == 11)))
    {
        date.day = 1;
        date.month += 1;
    }

    else if ((date.day > 31) && ((date.month==1) || (date.month==3) || (date.month==5) || (date.month==7) || (date.month==8) || (date.month==10) || (date.month==12)))
    {
        date.day = 1;
        date.month += 1;
    }

    if (date.month > 12)
    {
        date.month = 1;
        date.year +=1;
    }




    return date;
}

/*  Compares two dates.
    Returns:    1- if d1 > d2
                -1 if d2 > d1
                0 if d1 == d2
*/

int date_cmp(Date d1, Date d2)
{

    if (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year && d1.hour == d2.hour && d1.minute == d2.minute)
        return 0;

    else if ((d1.year > d2.year) ||
            (d1.year == d2.year && d1.month > d2.month) ||
            (d1.year == d2.year && d1.month == d2.month && d1.day > d2.day) ||
            (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day && d1.hour > d2.hour) ||
            (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day && d1.hour == d2.hour && d1.minute > d2.minute))
        return 1;

    else
        return -1;

}
