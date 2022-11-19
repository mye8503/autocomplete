#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"

/* Part 1:
The function takes in a pointer to a pointer to struct term, a pointer to an int, and the name of a file that is 
formatted like cities.txt.
The function allocates memory for all the terms in the file and stores a pointer to the block in *terms. The function 
stores the number of terms in *pnterms. The function reads in all the terms from filename, and places them in the 
block pointed to by *terms. The terms should be sorted in lexicographic order. */
static int myCompare(const void *a, const void *b){ 
    struct term *termA = (struct term *)a;
    struct term *termB = (struct term *)b;

    return strcmp(termA->term, termB->term); 
} 

void read_in_terms(struct term **terms, int *pnterms, char *filename){
    char line[200];
    FILE *fp = fopen(filename, "r");
    fgets(line, sizeof(line), fp);
    *pnterms = atoi(line);

    struct term *array = (struct term *)malloc(sizeof(struct term)*(*pnterms));
    *terms = array;

    for(int i = 0; i < *pnterms; i++){
        fgets(line, sizeof(line), fp);

        int b = 0;
        while(isdigit(line[b]) == 0){ //get past the spaces
            b++;
        }
        int c = b; // c marks the index of the first digit
        while(isdigit(line[b]) != 0){
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

        strcpy(array[i].term, city);
        array[i].weight = atof(str_weight);
    }
    
/*     printf("BEFORE SORTING\n");
    for(int i=0; i<*pnterms; i++){ 
        printf ("CITY: %s || WEIGHT: %f\n", array[i].term, array[i].weight);           
    }
 */
    qsort(array, *pnterms, sizeof(struct term), myCompare); 
}


/* Part 2 (a):
The function returns the index in terms of the first term in lexicographic ordering that matches the string substr.
This function must run in O(log(nterms)) time, where nterms is the number of terms in terms. You can assume that terms 
is sorted in ascending lexicographic ordering. */

int lowest_match(struct term *terms, int nterms, char *substr){

    // find substr len
    int len = strlen(substr);

    // int counter = nterms;
    int start = 0;
    int end = nterms;
    int index = -3; // (start + end)/2;
    // int prev_index = -1;

    char middle[len+1];

    /* PROBLEM: 
        Integer division always rounds down, so there's no way we can check
        the very last index. We'll get an infinite loop.
       SOLUTION:
        Make end 1 larger than the actual end index */

    while(start != end-1){ // FIXED TO RUN IN O(log(n) HOPEFULLY
        index = (start + end)/2;

        memcpy(middle, terms[index].term, len);
        middle[len] = '\0';

        if(strcmp(middle, substr) == 0){
            // currently has found AN index matching substr. We want to get to the FIRST index.
            start = 0;
            end = index;
        }else if(strcmp(middle, substr) > 0){ // comes after substr in alphabet
            end = index;
        }else if(strcmp(middle, substr) < 0){ // comes before substr in alphabet
            start = index;
        }
        // counter--;
    }
    
    // currently index is showing the index of a term that matches substr
    // or the function has iterated through all indices that are similar to substr

    if(start == end-1){ // need to check these indices
         memcpy(middle, terms[start].term, len);
         middle[len] = '\0';

         if(strcmp(middle, substr) == 0){
             return start;
         }else{
             memcpy(middle, terms[end].term, len);
             middle[len] = '\0';

             if(strcmp(middle, substr) == 0){
                 return end;
             }else{
                 return -1;
             }
         }
    }

    memcpy(middle, &terms[index].term, len);
    middle[len] = '\0';

    if(strcmp(middle, substr) != 0){
        return -1;
    }else{
        return index;
    }

/*     if(strcmp(middle, substr) != 0){
        return -1;
    }else{
        while(index > 0){
            index--;
            memcpy(middle, terms[index].term, len);
            middle[len] = '\0';
            if(strcmp(middle, substr) != 0){
                index++; // index is currently one too small; need to increase it to
                         // go back to the first term that matches substr
                break;
            }
        }
        return index;
    } */
}

/* Part 2 (b): 
The function returns the index in terms of the last term in lexicographic order that matches the string substr.
This function must run in O(log(nterms)) time, where nterms is the number of terms in terms.
You can assume that terms is sorted in ascending lexicographic ordering. */
int highest_match(struct term *terms, int nterms, char *substr){
        // find substr len
    int len = strlen(substr);

    // int counter = nterms;
    int start = 0;
    int end = nterms;
    int index = -3; // (start + end)/2;
    int prev_index = -1;

    char middle[len+1];

    /* PROBLEM: 
        Integer division always rounds down, so there's no way we can check
        the very last index. We'll get an infinite loop.
       SOLUTION:
        Make end 1 larger than the actual end index */

    while(start != end-1){ // FIXED TO RUN IN O(log(n) HOPEFULLY
        prev_index = index;
        index = (start + end)/2;
        
        memcpy(middle, terms[index].term, len);
        middle[len] = '\0';

        if(strcmp(middle, substr) == 0){
            // currently has found AN index matching substr. We want to get the HIGHEST index.
            end = nterms;
            start = index;
        }else if(strcmp(middle, substr) > 0){ // comes after substr in alphabet
            end = index;
        }else if(strcmp(middle, substr) < 0){ // comes before substr in alphabet
            start = index;
        }
    }

    // currently index is showing the index of a term that matches substr
    // or the function has iterated through all indices that are similar to substr

    if(start == end-1){ // need to check these indices
         memcpy(middle, terms[start].term, len);
         middle[len] = '\0';

         if(strcmp(middle, substr) == 0){
             return start;
         }else{
             memcpy(middle, terms[end].term, len);
             middle[len] = '\0';

             if(strcmp(middle, substr) == 0){
                 return end;
             }else{
                 return -1;
             }
         }
    }

    memcpy(middle, &terms[index].term, len);
    middle[len] = '\0';

    if(strcmp(middle, substr) != 0){
        return -1;
    }else{
        return index;
    }
/* 
    memcpy(middle, &terms[index].term, len);
    middle[len] = '\0';

    if(strcmp(middle, substr) != 0){
        return -1;
    }else{
        while(index > 0){
            index++;
            memcpy(middle, terms[index].term, len);
            middle[len] = '\0';
            if(strcmp(middle, substr) != 0){
                index--; // index is currently one too large; need to increase it to
                         // go back to the first term that matches substr
                break;
            }
        }
        return index;
    } */
}

/* Part 3:
The function takes terms (assume it is sorted lexicographically), the number of terms nterms, 
and the query string substr, and places the answers in answer, with *n_answer being the number of answers. */
static int myCompare2(const void *a, const void *b) { 
    struct term *termA = (struct term *)a;
    struct term *termB = (struct term *)b;
    
    if(termA->weight == termB->weight){
        return 0;
    }else if(termA->weight > termB->weight){
        return -1;
    }else{
        return 1;
    }
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){
    int lowest = lowest_match(terms, nterms, substr);
    int highest = highest_match(terms, nterms, substr);

    if(highest == -1 && lowest == -1){
        *n_answer = 0;
    }else{
        *n_answer = highest-lowest+1;
    }

    struct term *array2 = *answer;
    array2 = (struct term *)malloc(sizeof(struct term)*(*n_answer));

    for(int i = lowest; i < highest+1; i++){ // copy to answer
        strcpy(array2[i-lowest].term, terms[i].term);
        array2[i-lowest].weight = terms[i].weight;
    }

    qsort(array2, *n_answer, sizeof(struct term), myCompare2); 
    *answer = array2;

}