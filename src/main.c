#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX_CHAR 1000

int main(){
    FILE *fp;
    char row[MAX_CHAR];

   fp = fopen("data/testData.csv", "r");

  while(feof(fp) != true){
      fgets(row, MAX_CHAR, fp);
      printf("%s", row);
  }
}
