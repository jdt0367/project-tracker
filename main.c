/********* main.c ********
	
	Student Name 	= Jordan Trach
	Student Number	= 101293174
*/

//Complete the includes
#include "a1_data_structures.h"
#include "a1_functions.h"
#include <assert.h>

int main()
{

    /** 1-  Display a welcome message **/
    printf("Welcome to Project Tracker\n");

    /** 2- Get the project's name and number of milestones **/

    project_t proj;
    printf("Please enter your project name (max 99 characters): ");
    scanf("%s", proj.name);
    
    printf("Please enter the number of milestones: ");
    unsigned short int num_milestones = get_input_usi(); //how to make this not a global variable?
    
    /** 3- Initialize all milestones and activities.
     * You need an array of milestones. 
     * The capacity of the array must be the max number of milestones the program 
     * can handle as per the instructions **/
    //malloc to allocate memory for the number of milestones required
    milestone_t *arr_milestones;
    arr_milestones = malloc(sizeof(milestone_t) * num_milestones);
    assert(arr_milestones != NULL);
    int num_activities = 0; //can't be usi or none of the functions in function.c work as per their declarations
    
    unsigned short int arr_id_milestones[num_milestones];
    for (int i = 0; i < num_milestones; i++){
        do{
            printf("Initializing Milestone %d\n", i + 1);
            printf("Please enter the number of activities in milestone %d", i + 1);
            scanf("%d", &num_activities);
            if (num_activities < 1){
                printf("There must be at least 1 activity.\n");
            }
        } while (num_activities < 1);
        int id_unique; //need to figure out a way to check milestone IDs without using global variables
        do{
            id_unique = 0;
            printf("Please create a unique numerical milestone ID: ");
            arr_id_milestones[i] = get_input_usi();
            for (int j = 0; j < num_milestones; j++){
                if (arr_id_milestones[i] == arr_id_milestones[j]){
                    id_unique++;
                }
                if(id_unique > 1){
                    printf("ID not unique\n");
                    break;
                }
            }
        } while (id_unique > 1);   
        (arr_milestones + i) -> id = arr_id_milestones[i];
        (arr_milestones + i) -> index = i;
        init_milestone(arr_milestones + i, num_activities); //sends the appropriate pointer to required milestone in arr_milestone
    }
    
    /** 4- Initialize the project **/
    proj = init_project(proj.name, arr_milestones, num_milestones, &num_activities);
    /** 5- Print the main menu **/
    /** 6- Get user choice and handle it as per the instructions**/
    print_main_menu();
    unsigned short int menu_choice = get_input_usi();
    while (menu_choice != 3)
    {
        switch (menu_choice){
            case 1: //could be a function call to simplify
                printf("Completed Activities:\n");
                for(int i = 0; i < num_milestones; i++){
                    for(int j = 0; j < arr_milestones[i].num_activities; j++){ 
                        if (arr_milestones[i].activity_list[j].completed == true && arr_milestones[i].activity_list[j].id)
                        {
                            printf("Milestone %s - %d: %s\n", arr_milestones[i].name, arr_milestones[i].activity_list[j].id, arr_milestones[i].activity_list[j].name);
                        }
                    }
                }
                printf("Activities In Progress:\n");
                for(int i = 0; i < num_milestones; i++){
                    for(int j = 0; j < arr_milestones[i].num_activities; j++){
                        if (arr_milestones[i].activity_list[j].completed == false && arr_milestones[i].activity_list[j].id)
                        {
                            printf("Milestone %s - %d: %s\n", arr_milestones[i].name, arr_milestones[i].activity_list[j].id, arr_milestones[i].activity_list[j].name);
                        }
                    }
                }
                printf("Please enter the ID of the incomplete activity you wish to update, or type 0 to exit: "); //need to be able to make this unique, so far no global checker for activity lists
                unsigned short activity_id = get_input_usi();
                if(activity_id != 0){
                    for(int i = 0; i < num_milestones; i++){
                        for(int j = 0; j < arr_milestones[i].num_activities; j++){
                            if (arr_milestones[i].activity_list[j].id == activity_id)
                            {
                                update_activity(&(arr_milestones[i].activity_list[j]));
                                num_activities = sizeof(arr_milestones[i].activity_list) / sizeof (arr_milestones[i].activity_list[j]);
                                update_milestone(&(arr_milestones[i]), num_activities);
                                update_project(&(arr_milestones[i]), num_milestones, &num_activities, &proj);
                            }
                        }
                    }
                }
                print_main_menu();
                menu_choice = get_input_usi();
                break;
            case 2:
                print_project_stats(proj, arr_milestones, num_milestones, &num_activities);
                print_main_menu();
                menu_choice = get_input_usi();
                break;
            case 3:
                break;
        }
    }
    exit(EXIT_SUCCESS);
}