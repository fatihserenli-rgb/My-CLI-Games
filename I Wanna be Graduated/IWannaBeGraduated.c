#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char array[256];/*This array will contain the game board.*/
int outer_wall_locations[32];/*I will use this array for control purposes in the move_player function.*/
int inner_wall_locations[16];/*I will use this array for control purposes in the move_player function.*/
int ects1 = 0, ects2 = 0;

int random(int a){/*A function that generates a random number between 0 and a (I will use it for random distribution of 1 and 2).*/
    int x = rand()%a;
    return x;
}
void random_distribution_1(int x,int wall){
    int a = random(3);/*I am randomly selecting a row within the inner wall.*/
    int number = random(3)+1;/*I am randomly selecting a column within the inner wall.*/
    switch(a){
        case 0:
            if(array[wall+x+number] != '.'){
                random_distribution_1(x,wall);
            }
            else{
                array[wall+x+number] = '1';
            }
            break;
        case 1:
            if(array[wall+2*x+number] != '.'){
                random_distribution_1(x,wall);
            }
            else{
                array[wall+2*x+number] = '1';
            }
            break;
        case 2:
            if(array[wall+3*x+number] != '.'){
                random_distribution_1(x,wall);
            }
            else{
                array[wall+3*x+number] = '1';
            }
            break;
    }
}
void random_distribution_2(int x,int wall){
    int a = random(3);
    int b = random(2);/*I will select random columns based on the randomly chosen row and values a and b.*/
    int number = random(7)+1;/*I am randomly selecting a row within the outer wall.*/
    switch(a){
        case 0:
            if(array[wall+x+number] != '.'){
                random_distribution_2(x,wall);
            }
            else{
                array[wall+x+number] = '2';
            }
            break;
        case 1:
            switch(b){
                case 0:
                    if(array[wall+number*x+1] != '.'){
                        random_distribution_2(x,wall);
                    }
                    else{
                        array[wall+number*x+1] = '2';
                    }
                    break;
                case 1:
                    if(array[wall+number*x+1] != '.'){
                        random_distribution_2(x,wall);
                    }
                    else{
                        array[wall+number*x+x/2-1] = '2';
                    }
                    break;
            }
            break;
        case 2:
            if(array[wall+7*x+number] != '.'){
                random_distribution_2(x,wall);
            }
            else{
                array[wall+7*x+number] = '2';
            }
            break;
    }
}
int move_player(char direction,int p_location,int x){
    if(direction >= 'a' && direction <= 'z'){
        direction -= 32;
    }
    int i;
    int diff;
    int new_p_location;
    switch(direction){
        case 'W':
            if(p_location < x){
                new_p_location = p_location;
            }
            else{
                new_p_location = p_location - x;
                diff = -x;
            }
            break;
        case 'S':
            if(p_location >= x*x -x){
                new_p_location = p_location;
            }
            else{
                new_p_location = p_location + x;
                diff = x;
            }
            break;
        case 'A':
            if(p_location % x == 0){
                new_p_location = p_location;
            }
            else{
                new_p_location = p_location-1;
                diff = -1;
            }
            break;
        case 'D':
            if(p_location % x == 15){
                new_p_location = p_location;
            }
            else{
                new_p_location = p_location +1;
                diff = 1;
            }
            break;
        default:
            printf("%c IS AN INVALID BUTTON(MOVE BUTTONS:W,A,S,D)\n",direction);
            new_p_location = p_location;
    }
    switch(array[new_p_location]){
        case '1':
            ects1 += 8;
            array[p_location] = '.';
            p_location = new_p_location;
            array[new_p_location] = 'P';
            break;
        case '2':
            ects2 += 8;
            array[p_location] = '.';
            p_location = new_p_location;
            array[new_p_location] = 'P';
            break;
        case '#':
            for(i = 0; i<2*(x/4+1)+2*(x/4-1); i++){
                if(inner_wall_locations[i] == new_p_location){
                    if(ects1 == 32){
                        if(array[new_p_location + diff] != '#'){
                            array[p_location] = '.';
                            p_location = new_p_location + diff;
                            if(array[p_location] == '2'){
                                ects2+=8;
                            }
                            array[p_location] = 'P';
                        }
                    }
                    else{
                        printf("YOU DON'T HAVE ENOUGH ECTS FOR PASS THROUGH THIS WALL!\n");
                    }
                }
            }
            for(i=0; i<2*(x/2+1)+2*(x/2-1); i++){
                if(outer_wall_locations[i] == new_p_location){
                    if(ects2 == 24){
                        if(array[new_p_location + diff] != '#'){
                            array[p_location] = '.';
                            p_location = new_p_location + diff;
                            array[p_location] = 'P';
                        }
                    }
                    else{
                        printf("YOU DON'T HAVE ENOUGH ECTS FOR PASS THROUGH THIS WALL!\n");
                    }
                }
            }
            break;
        default:
            array[p_location] = '.';
            p_location = new_p_location;
            array[p_location] = 'P';
        }
        return p_location;
}
void print_board(char array[],int x){
    int i = 0;
    int j;
    for(i; i<x; i++){
        j = x*i;
        for(j; j<x*(i+1); j++){
            printf("%c  ",array[j]);
        }
        printf("\n");
    }
}
void initialize_game(int x){
    int i = 0;
    for(i; i<x*x; i++){
        array[i] = '.';
    }
    array[x*x-1] = 'X';
    int p_location = x*x/2 + x/2;
    array[p_location] = 'P';  /*I placed the dots, P, and X in the array, now I will place the walls.*/
    int outer_wall_start = x*(x/4) + x/4;  /*The starting point for creating the outer wall.*/
    for(i = 0;i < x/2+1; i++){
        array[outer_wall_start+i] = '#';
        array[outer_wall_start+i + x*(x/2)] = '#';
        array[outer_wall_start + x*i] = '#';
        array[outer_wall_start + x*i + x/2] = '#';
    }/*The formation of the outer wall has been completed.*/
    int j = 0;
    for(i = 0; i< x*x;i++){/*In this loop, I will place the positions of the squares creating the outer wall in the global space into the outer_wall_locations array.*/
        if(array[i] == '#'){
            outer_wall_locations[j] = i;
            j++;
        }
    }
    j = 0;
    int k;
    int c = 1;
    int inner_wall_start = x*(x/4+2)+x/4+2;/*Now, I will perform the same operations for the inner wall as I did for the outer wall.*/
    for(i = 0; i<x/4+1; i++){
        array[inner_wall_start+i] = '#';
        array[inner_wall_start+i + x*(x/4)] = '#';
        array[inner_wall_start + x*i] = '#';
        array[inner_wall_start + x*i + x/4] = '#';
    }
    for(i = 0; i<x*x;i++){
        c = 1;
        if(array[i] == '#'){
            for(k = 0; k<2*(x/2+1)+2*(x/2-1);k++){
                if(outer_wall_locations[k] == i){
                    c = 0;
                    break;
                }
            }
            if(c == 1){
                inner_wall_locations[j] = i;
                j++;
            }
        }
    }
    i = 0;
    /*I have placed the walls, now I will create a random distribution for 1s and 2s.*/
    while(i<4){
        random_distribution_1(16,inner_wall_start);
        i++;
    }
    i = 0;
    while(i < 3){
        random_distribution_2(16,outer_wall_start);
        i++;
    }
    
}
int main(){
    srand(time(NULL));
    initialize_game(16);
    char move;
    int p_location = 136;
    int new_p_location,total_ects = 0;
    while(array[255] != 'P'){
        print_board(array,16);
        printf("TOTAL ECTS:%d\n",total_ects);
        printf("ENTER YOUR MOVE:");
        scanf(" %c",&move);
        new_p_location = move_player(move,p_location,16);
        p_location = new_p_location;
        total_ects = ects1 + ects2;
    }
    return 0;
}