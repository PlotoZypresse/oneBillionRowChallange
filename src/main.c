#include <string.h>
#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX_ROWS 50000
#define MAX_CHAR 100


typedef struct {
    char name[MAX_CHAR];        // city name
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
    char line[MAX_CHAR];
    char **data = NULL;
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
    file = fopen("data/measurements1m.txt", "r");
    if (file == NULL){
            perror("Error opening file");
            return 1;
    }
    calculations(file);
    fclose(file);
    return 0;
}
