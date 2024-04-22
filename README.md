# oneBillionRowChallange
Idear is from this https://github.com/gunnarmorling/1brc

## Planned way to implement right now
loop throug list if a city is encountered the first time create a city struct.
Init with the initial values. Add the city to a list of structs of cities. Check everytime if the city is in the struct.
If it is just update the parameters otherwise create a new city. If the end of the file is reached,
call the average function. The function will go through the list of city structs and calculate the
average for every city using the data points in the struct. At the end we call the print function,
the print city function prints the city and its values as follows "<City Name>;<min/average/max>"

