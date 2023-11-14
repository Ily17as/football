#include <stdio.h>
#include <string.h>
#define False 0
#define True 1

// Defining enum of all positions
typedef enum {
    Goalkeeper,
    Defender,
    Midfielder,
    Forward,
} all_positions;

//Defining players structure
typedef struct {
    char ID[1000];
    char name[100];
    all_positions position;
    int age;
    int goals_num;

} player;

//Making char for conversion
const char* positions[] = {"Goalkeeper", "Defender", "Midfielder", "Forward"};

//Making function to convert char <-> enum
all_positions player_position(char *position) {
    if (strcmp(position, positions[Goalkeeper]) == 0) {
        return Goalkeeper;
    } else if (strcmp(position, positions[Defender]) == 0) {
        return Defender;
    } else if (strcmp(position, positions[Midfielder]) == 0) {
        return Midfielder;
    } else if (strcmp(position, positions[Forward]) == 0) {
        return Forward;
    }
}

//Making function to check all values that are needed
int char_values_checking(char *n){
    if (strcmp(n, "Add") == 0 || strcmp(n, "Update") == 0 || strcmp(n, "Delete") == 0
        || strcmp(n, "Search") == 0 || strcmp(n, "Display") == 0){
        return True;
    } else {
        return False;
    }
}

//Defining array of structures
player players[10000];

//Initialising an add function
int add(char *ID, char *name, char *position, int age, int goals_number){

    //getting the index of first non-filled structure
    int i = 0;
    while (strcmp(players[i].ID, "-") != 0) {
        i++;
    }

    //checking and initialising the values
    for (int j = 0; j < i; j++){
        if (strcmp(ID, players[j].ID) == 0){
            return False;
        }
    }
    for (int j = 0; j < strlen(ID); j++){
        if ('0' > ID[j] || '9' < ID[j]){
            return False;
        }
    }
    strcpy(players[i].ID, ID);

    if ('A' > name[0] || 'Z' < name[0]){
        return False;
    }
    if (1 > strlen(name) || strlen(name) > 15){
        return False;
    }
    for (int j = 1; j < strlen(name); j++){
        if (('a' > name[j] || 'z' < name[j]) && ('A' > name[j] || 'Z' < name[j])){
            return False;
        }
    }
    strcpy(players[i].name, name);

    if (strcmp(position, "Goalkeeper") != 0 && strcmp(position, "Defender") != 0 &&
    strcmp(position, "Midfielder") != 0 && strcmp(position, "Forward") != 0){
        return False;
    }
    players[i].position = player_position(position);

    if (18 > age || 100 < age){
        return False;
    }
    players[i].age = age;

    if (0 > goals_number || 1000 <= goals_number){
        return False;
    }
    players[i].goals_num = goals_number;
    return True;
}

//Initializing an update function
int update(char *ID, char *name, char *position, int age, int goals_number){

    //checking the values
    for (int j = 0; j < strlen(ID); j++){
        if ('0' > ID[j] || '9' < ID[j]){
            return False;
        }
    }

    if ('A' > name[0] || 'Z' < name[0]){
        return False;
    }
    if (1 > strlen(name) || strlen(name) > 15){
        return False;
    }
    for (int j = 1; j < strlen(name); j++){
        if (('A' > name[j] || 'Z' < name[j]) && ('a' > name[j] || 'z' < name[j])){
            return False;
        }
    }

    if (strcmp(position, "Goalkeeper") != 0 && strcmp(position, "Defender") != 0 &&
        strcmp(position, "Midfielder") != 0 && strcmp(position, "Forward") != 0){
        return False;
    }

    if (18 > age || 100 < age){
        return False;
    }

    if (0 > goals_number || 1000 <= goals_number){
        return False;
    }

    //updating the values
    for(int i = 0; i < 1000; i++){
        if(strcmp(players[i].ID, ID) == 0){
            strcpy(players[i].name, name);
            players[i].position = player_position(position);
            players[i].age = age;
            players[i].goals_num = goals_number;
            return True;
        }
    }
    return False;
}

//Initializing a delete function
int delete(char *ID){

    //checking if the id exists
    for (int i = 0; i < 1000; i++){
        if (strcmp(players[i].ID, ID) == 0) {

            //moving all structures in array to the previous place
            for (int j = i; j < 1000 - 1; j++){
                strcpy(players[j].ID, players[j + 1].ID);
                strcpy(players[j].name, players[j + 1].name);
                players[j].position = players[j + 1].position;
                players[j].age = players[j + 1].age;
                players[j].goals_num = players[j + 1].goals_num;
            }
            return True;
        }
    }
    return False;
}

//Initializing a search function
int search(char *ID){

    //Checking if player exists or not
    for(int i = 0; i < 1000; i++){
        if(strcmp(players[i].ID, ID) == 0){
            return True;
        }
    }
    return False;
}

//Initializing a display function
int display(){

    //checking if array is empty
    if (strcmp(players[0].ID, "-") == 0){
        return False;
    } else {

        //finding the number of players in the team
        for (int i = 0; i < 1000; i++){
            if (strcmp(players[i].ID, "-") == 0){
                return i;
            }
        }
    }
}

int main(){

    //Opening files
    FILE *fp = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    //Filling the array IDs by "-"
    for (int i = 0; i < 10000; i++){
        strcpy(players[i].ID, "-");
    }

    //Reading the command
    char command[100];
    fscanf(fp, "%s", command);

    //Checking the command
    while (strcmp(command, "Add") == 0 || strcmp(command, "Update") == 0 || strcmp(command, "Delete") == 0
    || strcmp(command, "Search") == 0 || strcmp(command, "Display") == 0) {

        //Initializing new data for player and calling add function
        if (strcmp(command, "Add") == 0) {
            char ID[1000], name[100];
            char position[20];
            int age, goals_number;
            fscanf(fp, "%s", ID);
            fscanf(fp, "%s", name);
            fscanf(fp, "%s", position);
            fscanf(fp, "%d", &age);
            fscanf(fp, "%d", &goals_number);
            if(char_values_checking(ID) || char_values_checking(name) || char_values_checking(position)){
                fprintf(out, "%s", "Invalid inputs\n");
                fclose(fp);
                fclose(out);
                return 0;
            }
            if (add(ID, name, position, age, goals_number) == 0) {
                fprintf(out, "%s", "Invalid inputs\n");
                fclose(fp);
                fclose(out);
                return 0;
            } else {
                fscanf(fp, "%s", command);
                continue;
            }
        }

        //Initializing new data for player and calling update function
        if (strcmp(command, "Update") == 0) {
            char ID[1000], name[100];
            char position[20];
            int age, goals_number;
            fscanf(fp, "%s", ID);
            fscanf(fp, "%s", name);
            fscanf(fp, "%s", position);
            fscanf(fp, "%d", &age);
            fscanf(fp, "%d", &goals_number);
            if(char_values_checking(ID) || char_values_checking(name) || char_values_checking(position)){
                fprintf(out, "%s", "Invalid inputs\n");
                fclose(fp);
                fclose(out);
                return 0;
            }
            if (update(ID, name, position, age, goals_number) == 0) {
                fprintf(out, "%s", "Invalid inputs\n");
                fclose(fp);
                fclose(out);
                return 0;
            } else {
                fscanf(fp, "%s", command);
                continue;
            }
        }

        //Reading ID and calling delete function
        if (strcmp(command, "Delete") == 0) {
            char ID[1000];
            fscanf(fp, "%s", ID);

            //Checking the ID
            for (int j = 0; j < strlen(ID); j++){
                if ('0' > ID[j] || '9' < ID[j]){
                    return False;
                }
            }
            if (delete(ID) == 0) {
                fprintf(out, "%s", "Impossible to delete\n");
            }
            fscanf(fp, "%s", command);
            continue;
        }

        //Reading the ID and calling update function
        if (strcmp(command, "Search") == 0) {
            char ID[1000];
            fscanf(fp, "%s", ID);

            //Checking the ID
            for (int j = 0; j < strlen(ID); j++){
                if ('0' > ID[j] || '9' < ID[j]){
                    return False;
                }
            }
            if (search(ID) == 0) {
                fprintf(out, "%s", "Not found\n");
            } else {
                fprintf(out, "%s", "Found\n");
            }
            fscanf(fp, "%s", command);
            continue;
        }

        //Checking if array is empty or not and displaying it
        if (strcmp(command, "Display") == 0) {
            if (display() == 0) {
                fprintf(out, "%s", "Invalid inputs\n");
                fclose(fp);
                fclose(out);
                return 0;
            } else {
                for (int i = 0; i < display(); i++) {
                    fprintf(out, "ID: %s, ", players[i].ID);
                    fprintf(out, "Name: %s, ", players[i].name);
                    fprintf(out, "Position: %s, ", positions[players[i].position]);
                    fprintf(out, "Age: %d, ", players[i].age);
                    fprintf(out, "Goals: %d", players[i].goals_num);
                    fprintf(out, "\n");
                }
                fclose(fp);
                fclose(out);
                return 0;
            }
        }
    }

    //Closing file and stopping the execution
    fprintf(out, "%s", "Invalid inputs\n");
    fclose(fp);
    fclose(out);
    return 0;
};














