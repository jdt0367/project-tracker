/********* a1_data_structures.h *********/

#ifndef __A1_DATA_STRUCTURES_H__
#define __A1_DATA_STRUCTURES_H__

#include <stdbool.h>

#define NUM_ACTIVITIES 3
#define AVG_WAGE 30
/********** DON'T MODIFY FROM HERE **********/

typedef struct activity {
    unsigned short int id;
    char name[100];
    float planned_cost, actual_cost;
    unsigned short int planned_duration, actual_duration;
    _Bool completed;
}activity_t;

typedef struct milestone {
    int index;
    unsigned short int id;
    char name[100];
    activity_t *activity_list;
    int num_activities;
    _Bool completed;
    float actual_cost;
    short int actual_duration;
    unsigned short int *activity_ids;
}milestone_t;

typedef struct project {
    char name[100]; 
    int num_milestones;
    float planned_cost, actual_cost;
    unsigned short int planned_duration, actual_duration;
    _Bool completed;
}project_t;

/********** DON'T MODIFY UNTIL HERE **********/

#endif
