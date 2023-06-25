#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *word;
    int priority;
} dictionary_entry;


//function in which I build each word
void construct_words_struct(int dictionary_size, dictionary_entry *dictionary, char *str) {
    int start = 0, i, end = 0, k;

//each word in the dictionary will start with priority 0
    for (i = 0; i < dictionary_size; i++) {
        dictionary[i].priority = 0;

//end represents the length of each word
        while (end < strlen(str) && str[end] != ' ') {
            end++;
        }

//allocate how much memory is needed for each word
        dictionary[i].word = (char *) calloc(end - start + 1, sizeof(char));
        int count = 0;

//start represents the position of the first letter
        for (k = start; k < end; k++) {
            dictionary[i].word[count] = str[k];
            count++;
        }
        end++;
        start = end;
    }
}

//function in which I read the strings
void read_input(int size, dictionary_entry *input) {
    int max_size = size * 21;
    char *str = (char *) calloc(max_size, sizeof(char));

    fgets(str, max_size, stdin);

    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    construct_words_struct(size, input, str);
    free(str);
}

//function in which I print the final result and in which I compare the criteria required for the word in the 2nd string
void auto_complete(dictionary_entry *dictionary, dictionary_entry *input, int size_dictionary, int size_input) {
    int i, j;

    for (j = 0; j < size_input; j++) {
        dictionary_entry *best_value = NULL;
        int match_full_word = 0;

//if the word contains an asterisk, I get rid of it and give the flag (match_full_word) the value 1
        if (input[j].word[strlen(input[j].word) - 1] == '*') {
            match_full_word = 1;
            input[j].word[strlen(input[j].word) - 1] = '\0';
        }

//with this loop I go through all the elements in the dictionary and compare them with the respective word in the second string
        for (i = 0; i < size_dictionary; i++) {

//if the word contained the asterisk and if it is the same as the one in the best_value dictionary, it receives that word and its priority
            if (match_full_word == 1) {
                if (strcmp(input[j].word, dictionary[i].word) == 0) {
                    best_value = &dictionary[i];
                }
            }

/*otherwise, I check if they are equal, if so, I compare their priority:
  if the priority of the word with which it matches with other words in the dictionary
  is equal, I compare their length and if it is not equal, best_value takes the value
  the word with the higher priority*/
            else {
                if (strncmp(dictionary[i].word, input[j].word, strlen(input[j].word)) == 0) {
                    if (best_value == NULL || dictionary[i].priority > best_value->priority) {
                        best_value = &dictionary[i];
                    } else if (best_value == NULL || dictionary[i].priority == best_value->priority) {
                        if (strcmp(dictionary[i].word, best_value->word) < 0) {
                            best_value = &dictionary[i];
                        }
                    }
                }
            }
        }

//if best_value is null, I print the respective word, increase the size of the dictionary by 1 and add it to the dictionary
        if (best_value == NULL) {
            printf("%s ", input[j].word);
            size_dictionary++;
            dictionary = (dictionary_entry *) realloc(dictionary, size_dictionary * sizeof(dictionary_entry));
            dictionary[size_dictionary - 1].word = (char *) calloc(strlen(input[j].word) + 1, sizeof(char));
            strcpy(dictionary[size_dictionary - 1].word, input[j].word);
            dictionary[size_dictionary - 1].priority = 1;
        }

//otherwise, I print the word from the dictionary and increase its priority by one
        else {
            printf("%s ", best_value->word);
            best_value->priority += 1;
        }
    }

    for (i = 0; i < size_dictionary; i++) {
        free(dictionary[i].word);
    }
    for (i = 0; i < size_input; i++) {
        free(input[i].word);
    }

    free(dictionary);
    free(input);
}

int main() {
    int size_dictionary, size_input;
    dictionary_entry *dictionary;
    dictionary_entry *input;

    scanf("%d\n", &size_dictionary);
    dictionary = (dictionary_entry *) calloc(size_dictionary, sizeof(dictionary_entry));
    read_input(size_dictionary, dictionary);

    scanf("%d\n", &size_input);
    input = (dictionary_entry *) calloc(size_input, sizeof(dictionary_entry));
    read_input(size_input, input);

    auto_complete(dictionary, input, size_dictionary, size_input);
    return 0;
}