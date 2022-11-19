#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
// #include "autocomplete.h"
#include <math.h>

struct term{ // had to re-add this bc i moved this file into a separate folder so i could debug
             // you can delete this part 
    char term[200]; // assume terms are not longer than 200
    double weight;
};


void f(int *b){
    *b = 6;
}

int find_first_char(char *line){
    int i = 0;
    while(isdigit(line[i]) == 1){
        i++;
    }
    printf("%d\n", i);
    //*line = line;
    return i;
}

int *put_in_array(int *a, char *line, int term_num){
    struct term *search_term = (struct term *)malloc(sizeof(struct term));

    int b = 0;
    while(isdigit(line[b]) == 1){
        b++;
    }

    //char city_name[strlen(line)-b+1];
    char weight[b+1];
    for(int i=0; i < strlen(line); i++){
        if(i<b){
            weight[i] = line[i];
        }else if (i>b){
            search_term->term[i-b-1] = line[i];
        }
    }
    search_term->weight = atoi(weight);

    return a;
}

static int myCompare(const void *a, const void *b) 
{ 
    // setting up rules for comparison 

    struct term *termA = (struct term *)a;
    struct term *termB = (struct term *)b;

    return strcmp(termA->term, termB->term); 
} 

void read_in_terms(struct term **terms, int *pnterms, char *filename){
    char line[200];
    FILE *fp = fopen(filename, "r");
    fgets(line, sizeof(line), fp);
    *pnterms = atoi(line);

    //struct term *array = *terms;
    struct term *terms;
    terms = (struct term *)malloc(sizeof(struct term)*(*pnterms));

    for(int i = 0; i < *pnterms; i++){
        fgets(line, sizeof(line), fp);

        int b = 0;
        while(isdigit(line[b]) == 0){ //get past the dumb spaces
            b++;
        }
        int c = b; // c marks the index of the first digit
        while(isdigit(line[b]) == 1){
            b++;
        }
        b++; // space between number and city
        int d = b; // d marks the index of the first character

        if(i != *pnterms-1){
            b = strlen(line)-1; // b marks the index of the newline character
        }else{
            b = strlen(line);
        }

        char str_weight[d-c];

        char city[b-d+1];

        for(int j=c; j<=b; j++){
            if(j<d-1){
                str_weight[j-c] = line[j];
            }else if (j>d-1){
                city[j-d] = line[j];
            }
        }
        str_weight[d-c-1] = '\0';
        city[b-d] = '\0';

        strcpy(terms[i].term, city);
        terms[i].weight = atof(str_weight);
    }
    
/*     printf("BEFORE SORTING\n");
    for(int i=0; i<*pnterms; i++){ 
        printf ("CITY: %s || WEIGHT: %f\n", array[i].term, array[i].weight);           
    }
 */
    qsort(terms, *pnterms, sizeof(struct term), myCompare); 

   printf("\nAFTER SORTING\n");
    for (int n=0; n<*pnterms; n++){
         printf ("CITY: %s || WEIGHT: %f \n", terms[n].term, terms[n].weight);          
    }
}


int main(void){
    char *filename = "small_cities.txt";
    int *pnterms;

    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, filename);


    return 0;
}