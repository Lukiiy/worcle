#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define WORD_LEN 5
#define MAX_ATTEMPTS 6

const char *word_list[] = { "apple", "grape", "chair", "table", "brick", "stone", "light", "plant", "river", "cloud" };
const int WORD_COUNT = sizeof(word_list) / sizeof(word_list[0]);

void String_toLower(char *s) {
    for (int i = 0; s[i]; i++) s[i] = tolower(s[i]);
}

char *getFeedback(const char *guess, const char *target) {
    static char output[WORD_LEN * 3 + 1]; // matches worst case..! by that I mean '(x)(x)(x)(x)(x)\0'

    int used[WORD_LEN] = {0};
    int result[WORD_LEN] = {0}; // 2 = correct; 1 = present; 0 = absent
    int pos = 0;

    for (int i = 0; i < WORD_LEN; i++) { // correct pos
        if (guess[i] == target[i]) {
            result[i] = 2;
            used[i] = 1;
        }
    }

    for (int i = 0; i < WORD_LEN; i++) { // somewhere else
        if (result[i] == 0) {
            for (int j = 0; j < WORD_LEN; j++) {
                if (!used[j] && guess[i] == target[j]) {
                    result[i] = 1;
                    used[j] = 1;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < WORD_LEN; i++) { // Build output string
        if (result[i] == 2) {
            output[pos++] = '[';
            output[pos++] = toupper(guess[i]);
            output[pos++] = ']';
        } else if (result[i] == 1) {
            output[pos++] = '(';
            output[pos++] = guess[i];
            output[pos++] = ')';
        } else {
            output[pos++] = ' ';
            output[pos++] = guess[i];
            output[pos++] = ' ';
        }
    }

    output[pos] = '\0';

    return output;
}

int isValidGuess(const char *guess) {
    if (strlen(guess) != WORD_LEN) return 0;

    for (int i = 0; i < WORD_LEN; i++) {
        if (!isalpha(guess[i])) return 0;
    }

    return 1;
}

int main() {
    srand(time(NULL));

    const char *target = word_list[rand() % WORD_COUNT];

    char guess[100];

    printf("Guess the word! You have %d attempts.\n", MAX_ATTEMPTS);

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        printf("Attempt %d/%d: ", attempt, MAX_ATTEMPTS);
        scanf("%99s", guess);

        String_toLower(guess);

        if (!isValidGuess(guess)) {
            printf("Invalid guess. \n");
            attempt--;
            continue;
        }

        printf("%s\n", getFeedback(guess, target));

        if (strcmp(guess, target) == 0) {
            printf("\nCongrats! The word was \"%s\".\n", target);
            return 0;
        }
    }

    printf("\nGame over! The word was \"%s\".\n", target);
    return 0;
}