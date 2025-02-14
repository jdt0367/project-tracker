/********* a1_functions.h ********
	
	Student Name 	= Jordan Trach
	Student Number	= 101293174
*/

/************ TASK 5 ********
 Proposed solution: each milestone now contains a list of all of its activity ids. 
 Additionally, each milestone has its milestone index stored inside it. This allows
 init_milestone to access other milestones' activity lists with pointer arithmetic.

    for (int i = 0; i < num_activities; i++){
      int id_unique = 0;
      do{
         printf("Initializing Activity %d for %s\n", i+1, (milestone_to_int->name));
         printf("Please create a unique numerical activity ID greater than 0:");
         arr_id_activities[i] = get_input_usi();
         id_unique = 0;
         for(int j = milestone_to_int->index; j >= 0; j--){//go backwards to start at index 0 in the milestone list, then increase
            for(int k = 0; k < (sizeof((milestone_to_int - j)->activity_ids)/sizeof(unsigned short int)); k++){
               if (arr_id_activities[i] == (milestone_to_int - j)->activity_ids[k]){ //this still seg faults
                  id_unique++;
               }
            }
         }    
      } while (id_unique > 1);
      ((milestone_to_int->activity_list) + i) -> id = arr_id_activities[i];
      *((milestone_to_int->activity_ids) + i) = arr_id_activities[i];
      init_activity((milestone_to_int->activity_list) + i); //sends the appropriate pointer to required activity
   }

The code above replaces a block in a1_functions.c, and currently seg faults during the innermost for loop. There's almost certainly
an issue with the attempt to access milestones earlier in the milestone array by (milestone_to_int - j).
 */


#ifndef __A1_FUNCTIONS_H__
#define __A1_FUNCTIONS_H__

#include "a1_data_structures.h"
#include <stdlib.h>  
#include <stdio.h>   
#include <math.h>
#include <string.h>


/********** DON'T MODIFY - FROM HERE **********/
/* 
   Get unsigned short integer user input.
   The value entered by the user must be positive.
   If the user enters a negative value, the function asks user to re-enter a positive value.
*/
unsigned short int get_input_usi(void);

/*
   Get float user input. The value must be positive.
   The value entered by the user must be positive.
   If the user enters a negative value, the function asks user to re-enter a positive value.
*/
float get_input_f(void);

/* 
   Initialize all fields in an activity as per the instructions (3)
*/
void init_activity(activity_t * activity_to_int);
/* 
   Initialize all fields in the milestone as per the instructions (3)
   The implementation of your function MUST call the function init_activity.
*/
void init_milestone(milestone_t * milestone_to_int, unsigned short int num_activities);


/* 
   Initialize all fields in the project as per the instructions (4)
   number_activities contains the number of activities per milestone
*/
project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int * number_activities);


/* 
   Print the main menu as per the instructions (5)
*/
void print_main_menu(void);

/*
   Print out milestone stats as per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities);

/*
   Print out project stats as per the instructions (6)
   number_activities contains the number of activities per milestone
   The implementation MUST call print_stats_milestone
*/
void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities);

/*
   Update activity per the instructions (6)
*/
void update_activity(activity_t * activity_to_update);
/*
   Update milestone per the instructions (6)
*/
void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone);

/*
   Update project per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project);

/********** DON'T MODIFY - UNTIL HERE **********/


// Extra function prototypes/declarations go here

#endif