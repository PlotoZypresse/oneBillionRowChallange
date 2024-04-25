#include <string.h>
#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX_ROWS 50000
#define MAX_CHAR 50


typedef struct {
    char name[MAX_CHAR];
    float total_temperature;    // total temperature
    float min;                  // lowest temperature
    float max;                  // maximum temperature
    float average;              // average temperature
    int total_data_points;      // Total number of temperature data points for the city
} City;

// creates a city
City create_city(const char* name, float temperature){
    City* newCity = malloc(sizeof(City));
    if(newCity == NULL){
        printf("ERROR allocating new City");
    }
    strcpy(newCity->name, name);
    newCity->total_temperature = temperature;
    newCity->min = temperature;
    newCity->max = temperature;
    newCity->average = 0.0;
    newCity->total_data_points = 1;

    return *newCity;
}


void calculations(FILE *file){
    int numberCities = 0;
    City *cities[MAX_ROWS] = {NULL};
    char line[MAX_CHAR];
    char *data[MAX_ROWS];
    int numberTokens = 0;

    while(fgets(line, MAX_CHAR, file)){
        char *token = strtok(line, ";");
        while (token != NULL) {
            data[numberTokens] = strdup(token);
            numberTokens++;
            token = strtok(NULL, ";");
        }
    }

    for(int i = 0; i < numberTokens; i+=2){
        int cityFound = 0;
        //search for a city
        for(int j = 0; j < numberCities; j++){
            if(strcmp(data[i], cities[j]->name) == 0){
               cityFound = 1;
               //update data
               cities[j]->total_temperature += atof(data[i+1]);
               cities[j]->total_data_points++;
               // update min if necesary
               float temperature = atof(data[i+1]);
               if(cities[j]->min > temperature){
                   cities[j]->min = temperature;
               }
               // update max if necesary
               if(cities[j]->max < temperature){
                   cities[j]->max = temperature;
               }
               break;
            }
        }
    if(!cityFound){
        //allocate memory for a new city
        cities[numberCities] = (City*)malloc(sizeof(City));
        if (cities[numberCities] == NULL) {
            perror("Error allocating memory for City");
            exit(EXIT_FAILURE);
        }
        //create and initialize the new city
        *cities[numberCities] = create_city(data[i], atof(data[i+1]));
        numberCities++;
        }
    }

    // free ing data array
    for (int i = 0; i < numberTokens; i++) {
            free(data[i]); // Free allocated memory for data
    }

    for(int i = 0; i < numberCities; i++){
        cities[i]->average = cities[i]->total_temperature/cities[i]->total_data_points;
    }

    for(int i = 0; i < numberCities; i++){
        printf("%s = %.2f/%.2f/%.2f\n", cities[i]->name, cities[i]->min, cities[i]->average, cities[i]->max);
        free(cities[i]);
    }
}

int main(){
    FILE *file;
    file = fopen("data/test2K.csv", "r");
    if (file == NULL){
            perror("Error opening file");
            return 1;
    }
    calculations(file);
    fclose(file);
    return 0;
}


/*
loop throug list if a city is encountered the first time create a city struct.
Init with the initial values. Add the city to a list of structs of cities. Check everytime if the city is in the struct.
If it is just update the parameters otherwise create a new city. If the end of the file is reached,
call the average function. The function will go through the list of city structs and calculate the
average for every city using the data points in the struct. At the end we call the print function,
the print city function prints the city and its values as follows "<City Name>;<min/average/max>"
*/
