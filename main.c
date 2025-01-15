#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 1

typedef struct {
    int id;
    char name[50];
} Candidate;

void addVote(int **votes, int *size, int *capacity, int vote) {
    if ( *size == *capacity) {
        (*capacity)++;
        *votes = realloc(*votes ,*capacity * sizeof(int));
        if (*votes == NULL) {
             exit(EXIT_FAILURE);
        }

    }
    (*votes)[(*size)++] = vote;
}

void addCandidate(Candidate **candidates, int *candidateAmount, int *candidateCapacity, int id, char name[50]) {
    if ( *candidateAmount == *candidateCapacity){
        (*candidateCapacity)++;
        *candidates = realloc(*candidates, *candidateCapacity * sizeof(Candidate));
        if (*candidates == NULL) {
            exit(EXIT_FAILURE);
        }
    }

    (*candidates)[*candidateAmount].id = id;
    strncpy((*candidates)[*candidateAmount].name, name, sizeof((*candidates)[*candidateAmount].name) - 1);
    (*candidates)[*candidateAmount].name[sizeof((*candidates)[*candidateAmount].name) - 1] = '\0';
    (*candidateAmount)++;
}

int main() {
    int *votes = malloc( INITIAL_CAPACITY * sizeof(int));
    if (votes == NULL) {
        return EXIT_FAILURE;
    };
    int size = 0;
    int capacity = INITIAL_CAPACITY;

    Candidate *candidates = malloc( INITIAL_CAPACITY * sizeof(Candidate));
    if (candidates == NULL) {
        return EXIT_FAILURE;
    }
    int candidateAmount = 0;
    int candidateCapacity = INITIAL_CAPACITY;

    while(1) {
        int choice;
        printf("\n1. Create Candidate\n2.Vote for a Candidate\n3. Return results\n");
        printf("Choose an option(1-3):");
        scanf("%d", &choice);
        if (choice == 1) {
            int id;
            char name[50];
            printf("Enter Candidate ID");
            scanf("%d", &id);
            printf("Enter Candidate Name");
            scanf("%s", name);
            addCandidate(&candidates, &candidateAmount, &candidateCapacity, id, name);
            printf("Candidate %s successfully added", name);
        } else if (choice == 2) {
            int vote;
            printf("Choose one of these Candidates(by id):\n");
            for (int i = 0; i < candidateAmount; i++) {
                printf("Candidate %s with ID %d\n", candidates[i].name, candidates[i].id);
            }
            scanf("%d", &vote);
            addVote(&votes, &size, &capacity, vote);
            printf("Vote recorded for candidate ID %d.\n", vote);
        } else if (choice == 3) {
            printf("Voting Results:\n");
            for (int i = 0; i < candidateAmount; i++) {
                int voteCount = 0;
                for (int j = 0; j < size; j++) {
                    if (votes[j] == candidates[i].id) {
                        voteCount++;
                    }
                }
                printf("%s: %d votes\n", candidates[i].name, voteCount);
            }
            break;
        } else {
            printf("Error");
        }
    }
    free(votes);
    free(candidates);
    return 0;
}

// Program in der Konsole, dass dir 3 Optionen bietet
// 1. Create Candidate
//
// 2. Vote for a Candidate
// -> Create a pool of all votes
// 3. Return results -> Sobald dass ausgeqwählt wurde, kann man nur noch Return results auswählen+
// -> return and close votes