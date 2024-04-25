#include <string.h>
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

// creates a city
City* create_city(const char* name, float temperature){
    City* newCity = malloc(sizeof(City));
    if(newCity == NULL){
        printf("ERROR allocating new City");
        exit(EXIT_FAILURE);
    }
    strcpy(newCity->name, name);
    newCity->total_temperature = temperature;
    newCity->min = temperature;
    newCity->max = temperature;
    newCity->average = 0.0;
    newCity->total_data_points = 1;

    return newCity;
}


void calculations(FILE *file){
    int numberCities = 0;
    City **cities = NULL;
    // malloc(MAX_ROWS * sizeof(City*));
    // if(cities == NULL){
    //     printf("ERROR allocating array of city structs");
    //     exit(EXIT_FAILURE);
    // }
    char line[MAX_CHAR];
    char **data = NULL;
    // malloc(MAX_ROWS * sizeof(char*));
    // if(data == NULL){
    //     printf("ERROR allocating data array");
    //     exit(EXIT_FAILURE);
    // }
    int numberTokens = 0;
    int totalTokens = 0;

    while(fgets(line, MAX_CHAR, file)){
        char *token = strtok(line, ";");
        while (token != NULL) {
            // reallocate data array if needed
            data = realloc(data, (totalTokens + 1)*sizeof(char*));
            if (data == NULL) {
                perror("Memory allocation error for data array");
                exit(EXIT_FAILURE);
            }

            data[totalTokens] = strdup(token);
            totalTokens++;
            token = strtok(NULL, ";");
        }
        char* cityName = data[totalTokens-2];
        float temperature = atof(data[totalTokens-1]);

        int cityFound = 0;

        // for(int i = 0; i < numberTokens; i+=2) {
        //     char* cityName = data[i];
        //     float temperature = atof(data[i+1]);

        
            // Search for a city
        for(int j = 0; j < numberCities; j++) {
            if(strcmp(cityName, cities[j]->name) == 0) {
                cityFound = 1;
                // Update data
                cities[j]->total_temperature += temperature;
                cities[j]->total_data_points++;
                // Update min if necessary
                if(cities[j]->min > temperature) {
                    cities[j]->min = temperature;
                }
                // Update max if necessary
                if(cities[j]->max < temperature) {
                    cities[j]->max = temperature;
                }
                break;
        }
    }
        if(!cityFound) {
            // Create and initialize the new city
            cities = realloc(cities, (numberCities + 1) * sizeof(City*));
            if (cities == NULL) {
                perror("Memory allocation error for cities array");
                exit(EXIT_FAILURE);
            }
            cities[numberCities] = create_city(cityName, temperature);
            numberCities++;
    }
}

    // freeing data array
    for (int i = 0; i < numberTokens; i++) {
            free(data[i]); // Free allocated memory for data
    }
    free(data);

    // calculate average temperature
    for(int i = 0; i < numberCities; i++){
        cities[i]->average = cities[i]->total_temperature/cities[i]->total_data_points;
    }

    // print the data
    for(int i = 0; i < numberCities; i++){
        printf("%s = %.2f/%.2f/%.2f\n", cities[i]->name, cities[i]->min, cities[i]->average, cities[i]->max);
        free(cities[i]);
    }
    free(cities);
}

int main(){
    FILE *file;
    file = fopen("data/weather_stations.csv", "r");
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
