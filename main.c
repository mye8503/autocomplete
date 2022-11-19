#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // format input correctly
    for(int i = 0; argv[1][i] != '\0'; i++){
        if(i == 0){
            if(argv[1][i] >= 'a' && argv[1][i] <= 'z'){
                argv[1][i] = argv[1][i] - 32;
            }
        
        }else if(argv[1][i] >= 'A' && argv[1][i] <= 'Z'){
            argv[1][i] = argv[1][i] + 32;
        }
    }


    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");

/*     printf("SORTED LIST\n");
    for (int n=0; n<nterms; n++){
         printf ("%d || CITY: %s || WEIGHT: %f \n", n, terms[n].term, terms[n].weight);          
    } */

    // int index = lowest_match(terms, nterms, argv[1]);
    // printf("\nINDEX: %d || CITY: %s || PREVIOUS CITY: %s\n", index, terms[index].term, terms[index-1].term); //, terms[index].term);
    // int index_2 = highest_match(terms, nterms, argv[1]);
    // printf("\nINDEX: %d || CITY: %s || NEXT CITY: %s\n\n", index_2, terms[index_2].term, terms[index_2+1].term);
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, argv[1]);

//    for(int i=0; i<n_answer; i++){
//          printf("CITY: %s || WEIGHT: %f\n", answer[i].term, answer[i].weight);
//     }

    for(int i = 0; i < 5; i++){
        printf("%s\n", answer[i].term);
        if(i == n_answer-1) break;
    }
   
    //free allocated blocks here -- not required for the project, but good practice
    free(terms);
    free(answer);
    return 0;

}
