#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX_ROWS 50000
#define MAX_CHAR 100


typedef struct {
    char name[MAX_CHAR];
    float total_temperature;    // total temperature
    float min;                  // lowest temperature
    float max;                  // maximum temperature
    float average;              // average temperature
    int total_data_points;      // Total number of temperature data points for the city
} City;

//prints an array
void arrayPrint(int max, char *data[]){
    for(int i = 0; i < max; i++){
        printf("%s ", data[i]);
    }
}

// creates a city
City create_city(const char* name, float temperature){
    City* newCity = malloc(sizeof(City));

    strcpy(newCity->name, name);
    newCity->total_temperature = temperature;
    newCity->min = temperature;
    newCity->max = temperature;
    newCity->average = 0.0;
    newCity->total_data_points = 1;

    return *newCity;
}

void cityCalculations(FILE *file){
    int i = 0;
    City cities[MAX_ROWS];
    char line[MAX_CHAR];
    char lineCopy[MAX_CHAR];
    int rows = 0;
    char *data[MAX_ROWS];
    int numberTokens = 0;


    while(fgets(line, MAX_CHAR, file)){
        strcpy(lineCopy, line);

        char *token = strtok(lineCopy, ";");
        while (token != NULL) {
            data[numberTokens] = strdup(token);
            numberTokens++;
            token = strtok(NULL, ";");
            // printf("%s ", token);
        }
    }

    //printf("%s", data[0]);
    arrayPrint(numberTokens, data);
}

int main(){
    FILE *file;
    file = fopen("data/testData2.csv", "r");

    cityCalculations(file);

    fclose(file);
}


/*
loop throug list if a city is encountered the first time create a city struct.
Init with the initial values. Add the city to a list of structs of cities. Check everytime if the city is in the struct.
If it is just update the parameters otherwise create a new city. If the end of the file is reached,
call the average function. The function will go through the list of city structs and calculate the
average for every city using the data points in the struct. At the end we call the print function,
the print city function prints the city and its values as follows "<City Name>;<min/average/max>"
*/
