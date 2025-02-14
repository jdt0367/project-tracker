/********* a1_functions.c *********/

#include "a1_functions.h"
#include "a1_data_structures.h"
#include <assert.h>

/* 
   Get unsigned short integer user input.
   The value entered by the user must be positive.
   If the user enters a negative value, the function asks user to re-enter a positive value.
*/
unsigned short int get_input_usi(void){
	unsigned short int i;
	scanf("%hu", &i);
	while (i<0){
		printf("\n Invalid. Please enter a value above 0: ");
		scanf("%hu", &i);
	}
	return i;
}

/*
   Get float user input. The value must be positive.
   The value entered by the user must be positive.
   If the user enters a negative value, the function asks user to re-enter a positive value.
*/
float get_input_f(void){
	float i;
	scanf(" %f", &i);
	while(i<=0){
		printf("\nInvalid result. Please enter a positive value: ");
   	scanf("%f", &i);
	}
	return i;
}

/* 
   Initialize all fields in an activity as per the instructions (3)
*/
void init_activity(activity_t * activity_to_int){
   printf("Please enter the activity name: ");
   scanf("%s", activity_to_int->name);
   printf("Please enter the planned duration of the activity (in hours): ");
   activity_to_int->planned_duration = get_input_usi();
   activity_to_int->actual_duration = 0; //0 until it's updated by menu
	activity_to_int->planned_cost = activity_to_int->planned_duration * AVG_WAGE;
	activity_to_int->actual_cost = 0;
	activity_to_int->completed = false;
}
/* 
   Initialize all fields in the milestone as per the instructions (3)
   The implementation of your function MUST call the function init_activity.
*/
void init_milestone(milestone_t * milestone_to_int, unsigned short int num_activities){
   bool milestone_got = false;
   printf("Please enter the milestone name: ");
   scanf("%s", milestone_to_int->name);
   milestone_to_int->actual_cost = 0;
   milestone_to_int->actual_duration = 0;
   milestone_to_int->completed = false;
   milestone_to_int->num_activities = num_activities;
   milestone_to_int->activity_list = malloc(sizeof(activity_t) * num_activities);
   assert(milestone_to_int->activity_list != NULL);
   unsigned short int arr_id_activities[num_activities];
   
   /******* VVV TASK 5 REPLACES THIS CODE VVV******/
   for (int i = 0; i < num_activities; i++){
      bool id_unique = false; 
      do{
         printf("Initializing Activity %d for %s\n", i+1, milestone_to_int->name);
         printf("Please create a unique numerical activity ID greater than 0: ");
         arr_id_activities[i] = get_input_usi();
         int id_unique = 0;
         for (int j = 0; j < num_activities; j++){
            if (arr_id_activities[i] == arr_id_activities[j]){
               id_unique++;
            }
         }
         if (id_unique > 1 || arr_id_activities[i] == 0){
            printf("ID not unique or ID <= 0\n");
         }
      } while (id_unique > 1);
      ((milestone_to_int->activity_list) + i) -> id = arr_id_activities[i];
      init_activity((milestone_to_int->activity_list) + i);
      
   }
   /*****TASK 5 ENDS HERE*******/
   milestone_to_int->activity_ids = arr_id_activities;
}


/* 
   Initialize all fields in the project as per the instructions (4)
   number_activities contains the number of activities per milestone
*/
project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int * number_activities){
   project_t proj;

   float total_cost = 0;
   unsigned short int total_time = 0;
   
   for (int i = 0; i < number_milestones; i++)
   {
      for (int j = 0; j < *number_activities; j++)
      {
         total_cost += ((milestone_list+i)->activity_list+j)->planned_cost;
         total_time += ((milestone_list+i)->activity_list+j)->planned_duration;
      }
   }

   if (total_time % 8 != 0){
      total_time += total_time % 8;
   }
   proj.planned_duration = total_time / 8;
   proj.planned_cost = total_cost;
   proj.actual_cost = 0;
   proj.actual_duration = 0;
   proj.completed = false;
   strcpy(proj.name, name);
   return proj;
}


/* 
   Print the main menu as per the instructions (5)
*/
void print_main_menu(void){
   printf("\nMAIN MENU\n Please enter one of the following options:\n1. Update Activity\n2.Print Current Progress\n3.Exit\n");
}

/*
   Print out milestone stats as per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities){
   unsigned short int diff_time = 0;
   float diff_cost = 0;
   for (int i = 0; i < num_milestones; i++){
      printf("Milestone:", (list_milestones + i)->name, "\n");
      unsigned short int planned_duration = 0;
      float planned_cost = 0;
      if ((list_milestones + i)->completed == true){
         printf("Completed\n");
         for (int j = 0; j < num_milestones; j++){ //can just do NUM_ACTIVITIES because every milestone has 3 activities (uninitialized will have 0 cost/duration)
            planned_cost += (((list_milestones + i)->activity_list) + j)->planned_cost;
            planned_duration += (((list_milestones + i)->activity_list) + j)->planned_duration;
         }
         diff_cost = ((list_milestones + i) -> actual_cost) - planned_cost;
         diff_time = ((list_milestones + i) -> actual_duration) - planned_duration;

         if (diff_cost < -0.05){ //float compare, adjust for floating point math error
            printf("Over Budget by $%f\n", (-1 *diff_cost));
         } else if (diff_cost > 0.05){
            printf("Under Budget by $%f\n", diff_cost);
         } else {
            printf("On Budget\n");
         }
         if (((list_milestones + i) -> actual_duration) < planned_duration){
            printf("Behind Schedule by %d days\n", (planned_duration - ((list_milestones + i) -> actual_duration) ));
         } else if (diff_time > 0){
            printf("Ahead of Schedule by %d days\n", (((list_milestones + i) -> actual_duration) - planned_duration));
         } else {
            printf("On Schedule\n");
         }
      } else { //incomplete milestones need planned cost and duration, num completed activities
         printf("Not Completed\n");
         unsigned short int completed_activities = 0;
         unsigned short int uninit = 0;
         for (int j = 0; j < ((list_milestones + i)->num_activities); j++){
            if (((list_milestones + i)->activity_list+j)->completed){
               completed_activities++;
            }
            if (((list_milestones + i)->activity_list+j)->id == 0){
               uninit++;
            }
            planned_cost += ((list_milestones + i)->activity_list+j)->planned_cost;
            planned_duration += ((list_milestones + i)->activity_list+j)->planned_duration;
         }
         printf("%d Activities Completed out of %d\n", completed_activities, *number_activities - uninit);
         printf("Planned Cost: $%f\n", planned_cost);
         printf("Planned Duration: %f\n", planned_duration);
      }
      
   }
}

/*
   Print out project stats as per the instructions (6)
   number_activities contains the number of activities per milestone
   The implementation MUST call print_stats_milestone
*/
void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities){
   printf("%s\n", details.name);
   if (details.completed){
      printf("Completed\n");
      
      float diff_cost = details.actual_cost - details.planned_cost;

      if (diff_cost < -0.05){ //float compare, adjust for floating point math error
         printf("Over Budget by $%f\n", (-1 *diff_cost));
      } else if (diff_cost > 0.05){
         printf("Under Budget by $%f\n", diff_cost);
      } else {
         printf("On Budget\n");
      }

      int diff_time = (details.actual_duration - details.planned_duration);
      if (diff_time < 0){
         diff_time -= diff_time % 8;
         diff_time /= 8;
         printf("Behind Schedule by %d days\n", (-1 * diff_time));
      } else if (diff_time > 0){
         diff_time += diff_time % 8;
         diff_time /= 8;
         printf("Ahead of Schedule by %d days\n", diff_time);
      } else {
         printf("On Schedule\n");
      }

   }else{
      printf("Not Completed\n");
      print_milestone_stats(list_milestones, num_milestones, number_activities);
   }
}

/*
   Update activity per the instructions (6)
*/
void update_activity(activity_t * activity_to_update){
   printf("Updating activity: %s\n", activity_to_update->name);
   printf("What is the actual duration in hours?");
   (activity_to_update)->actual_duration = get_input_usi();
   printf("What is the actual cost in dollars?");
   scanf("%f", &((activity_to_update)->actual_cost));
   printf("Is this activity complete (Y/N)? ");
   char complete = 'N';
   scanf(" %c", &complete);
   if (complete == 'Y' || complete == 'y'){
      (activity_to_update)->completed = true;
   }
}
/*
   Update milestone per the instructions (6)
*/
void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone){
   int completed_activities = 0;
   int uninit = 0;
   for (int i = 0; i < activities_in_milestone; i++){
      if (((milestone_to_update)->activity_list+i)->completed){
               completed_activities++;
      }
      if (((milestone_to_update)->activity_list+i)->id == 0){
               uninit++;
      }
   }
   if (completed_activities == NUM_ACTIVITIES - uninit){
      milestone_to_update->completed = true;
      printf("%d",milestone_to_update->completed);
      for(int j = 0; j < activities_in_milestone; j++){
         milestone_to_update->actual_cost += ((milestone_to_update)->activity_list+j)->actual_cost;
         milestone_to_update->actual_duration += ((milestone_to_update)->activity_list+j)->actual_duration;
      }
   }
}

/*
   Update project per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project){
   int completed_milestones = 0;
   for (int i = 0; i < num_milestones; i++){
      if ((milestone_array[i].activity_list)->completed){
               completed_milestones++;
      }
      if (completed_milestones == num_milestones){
         my_project->completed = true;
         for(int j = 0; j < num_milestones; j++){
            my_project->actual_cost += milestone_array[j].actual_cost;
            my_project->actual_duration += milestone_array[j].actual_duration;
         }
      }
   }
}
