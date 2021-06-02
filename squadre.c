#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>


#define MAX 100
#define TRUE 0
#define FALSE 1

//struct definition for players
typedef struct {
    char player_name[MAX];
    int played_game;
}player_t;

//protos
int check_presence(int length, int to_check, int*vector, int range);

//printing a vector
void print_vector(int length, int *vector){
    int i;
    for (i=0;i<length;i++){
        fprintf(stdout, "%d\n", vector[i]);
    }
    return;
}

int main(int argc, char *argv[]){

    //variables
    FILE *fp_in, *fp_out;
    
    int count, rounds, pl_team, match_time;
    player_t str_mat[MAX];

    int *play_order;
    //char str_match[TOT][100];

    //checking arguments
    if (argc != 1){
        fprintf(stdout, "Error! Invalid number of arguments!\n");
        return EXIT_FAILURE;
    }

    //opening files
    fp_in = fopen("giocatori.txt", "r");
    fp_out = fopen("match.txt", "w");

    //reading files
    int i=0;
    while (fscanf(fp_in, "%s\n", str_mat[i].player_name) != EOF){
        str_mat[i].played_game = 0;
        i++;
    }

    count = i;

    //scanning requests
    fprintf (stdout, "Finished Loading\n");
    fprintf(stdout, "Number of players: %d\n", count);
    fprintf(stdout, "How many players per team?\n");
    fscanf(stdin, "%d", &pl_team);
    fprintf(stdout, "How long does a match last?\n");
    fscanf(stdin, "%d", &match_time);
    fprintf(stdout, "How many rounds do you want to generate?\n");
    fscanf(stdin, "%d", &rounds);

    //setting counting variables and difference to fill exact number of rounds
    
    int difference;
    int pl_per_match = 2*pl_team;

    difference = (pl_per_match) - (count%pl_per_match);

    int allocation_space; 
    allocation_space = rounds*(count + difference);

    int approx = (match_time+5)*(allocation_space/pl_per_match);
    int hour = floor(approx/60);
    int min = approx - (hour*60);
    fprintf(fp_out, "Approx. of Game time (%d min/match + 5 min change): %dmin, %dh%dmin\n\n", match_time, approx, hour, min);


    //fprintf(stdout, "%d, %d, %d\n", total, difference, allocation_space);

    //memory allocation for generation of playing order vector
    play_order = (int*)malloc(allocation_space*sizeof(int));

    for(i=0;i<allocation_space;i++){
        play_order[i] = 0;
    }

    //fprintf(stdout, "%d, %d, %d\n", play_order[0], play_order[1], play_order[2]);

    //print_vector(allocation_space, play_order);
    srand(time(NULL));

    //setting commodities
    int tmp;
    int trial;
    int max_reached = 0; 

    //filling playing order
    for (i=0;i<allocation_space;i++){

        tmp = rand()%count;
        trial = 1; 

        while(((check_presence(allocation_space, tmp, play_order, (2*pl_per_match)) != TRUE) || (str_mat[tmp].played_game >= max_reached)) && (trial<=count+2)){
            
            tmp = rand()%count;

            trial++;

            //fprintf(stdout, "Try...\n");
        }
        //fprintf(stdout, "Found...\n");

        play_order[i] = tmp;
        str_mat[play_order[i]].played_game++;

        if( str_mat[play_order[i]].played_game > max_reached){//setting of max
            max_reached = str_mat[play_order[i]].played_game;
        }

    }

    //print_vector(allocation_space, play_order);

    for(i=0;i<allocation_space;i++){
        if(i==0){ //separation for different games
            fprintf(fp_out, "Game: %d\n", 1);
        }else if((i%pl_per_match) == 0){
            fprintf(fp_out, "\n\nGame: %d\n", ((i/pl_per_match)+1));
        }

        fprintf(fp_out, "%s\n", str_mat[play_order[i]].player_name);

        if(((i+1)%pl_team) == 0){
            fprintf(fp_out, "\n");
        }
    }

    //printing stats for players
    fprintf(fp_out, "Stats:\n\n");

    for(i=0;i<count;i++){
        fprintf(fp_out, "%s->has played %d\n", str_mat[i].player_name, str_mat[i].played_game);

    }


    //final freeing of memory and pointers
    free(play_order);
    fclose (fp_in);
    fclose (fp_out);

    fprintf(stdout, "\nTo find out matches, go to file match.txt\n>See you soon =)\n");
    return 0;
}

int check_presence(int length, int to_check, int *vector, int range){

    int i, count;

    for(i=0;i<length;i++){
        if(vector[i] != to_check){
            count++;
        }else{
            count = 0;
        }
        if (count >= range){
            return TRUE;
        }

    }

    return FALSE;
}