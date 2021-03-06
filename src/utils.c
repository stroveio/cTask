#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "trip.h"

int display_average_time_spent(int **average_time_spent) {
    if (average_time_spent == NULL) {
        printf("NULL\n");
        return 0;
    }
    char *row = malloc(163 * sizeof(char));
    char *line = (char *) malloc(163 * sizeof(char));
    if (row == NULL || line == NULL) {
        free(row);
        free(line);
        return 1;
    }
    for (int i = 0; i < 161; i++) {
        line[i] = '-';
        row[i] = '|';
    }
    row[161] = line[161] = '\n';
    row[162] = line[162] = '\0';

    for (int i = 1; i < 10; i++)
        row[i] = ' ';
    for (int i = 0; i < 24; i++) {
        row[6 * i + 11] = (char) ('0' + i / 10);
        row[6 * i + 12] = (char) ('0' + i % 10);
        row[6 * i + 13] = ':';
        row[6 * i + 14] = row[6 * i + 15] = '0';
    }
    row[155] = 'T';
    row[156] = 'o';
    row[157] = 't';
    row[158] = 'a';
    row[159] = 'l';
    printf("%s", line);
    printf("%s", row);
    printf("%s", line);
    for (int i = 0; i < 7; i++) {
        switch (i) {
            case 0:
                memcpy(row + 1, "Monday   ", 9);
                break;
            case 1:
                memcpy(row + 1, "Tuesday  ", 9);
                break;
            case 2:
                memcpy(row + 1, "Wednesday", 9);
                break;
            case 3:
                memcpy(row + 1, "Thursday ", 9);
                break;
            case 4:
                memcpy(row + 1, "Friday   ", 9);
                break;
            case 5:
                memcpy(row + 1, "Saturday ", 9);
                break;
            case 6:
                memcpy(row + 1, "Sunday   ", 9);
                break;
            default:
                return 1;
        };
        for (int j = 0; j < 25; j++) {
            int k = average_time_spent[i][j];
            int l = 10000;
            for (int m = 0; m < 5; m++) {
                row[6 * j + 11 + m] = (char) ('0' + k / l);
                k %= l;
                l /= 10;
            }
            for (int m = 0; m < 5; m++) {
                if (row[6 * j + 11 + m] == '0' && m != 4)
                    row[6 * j + 11 + m] = ' ';
                else
                    break;
            }
        }
        printf("%s", row);
    }
    printf("%s", line);
    free(row);
    free(line);
    return 0;
}

static timestamp_t *
create_timestamp(enum WeekDay day, int hr, int min, int sec) {
    timestamp_t *timestamp = malloc(sizeof(timestamp_t));
    if (timestamp == NULL)
        return NULL;
    timestamp->day = day;
    timestamp->hr = hr;
    timestamp->min = min;
    timestamp->sec = sec;
    return timestamp;
}

trip_t *create_trip(enum WeekDay day1, int hr1, int min1, int sec1,
                    enum WeekDay day2, int hr2, int min2, int sec2) {
    trip_t *trip = malloc(sizeof(trip_t));
    if (trip == NULL)
        return NULL;

    trip->start = create_timestamp(day1, hr1, min1, sec1);
    trip->end = create_timestamp(day2, hr2, min2, sec2);

    if (trip->start == NULL || trip->end == NULL) {
        free(trip->end);
        free(trip->start);
        free(trip);
        return NULL;
    }
    return trip;
}

trip_t **get_trips_from_stdin(int trips_num) {
    int args[8];
    trip_t **trips;

    trips = malloc(trips_num * sizeof(trip_t *));
    if (trips == NULL)
        return NULL;

    for (int i = 0; i < trips_num; i++) {
        for (int j = 0; j < 8; j++)
            scanf("%d", &args[j]);/*
        fprintf(stderr, "%d %d %d %d %d %d %d %d\n", args[0], args[1], args[2],
                args[3], args[4], args[5], args[6], args[7]);*/
        trips[i] = create_trip(args[0], args[1], args[2], args[3],
                               args[4], args[5], args[6], args[7]);
    }
    for (int i = 0; i < trips_num; i++) {
        if (trips[i] == NULL) {
            for (int j = 0; j < trips_num; j++)
                free(trips[j]);
            free(trips);
            return NULL;
        }
    }
    return trips;
}

int get_trips_num_from_stdin() {
    int num;
    scanf("%d", &num);
    return num;
}