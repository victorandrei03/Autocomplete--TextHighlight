#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//function that underlines the required word in the request
int highlight_one_word(char **matrix, char *word, int columns, int last_lenght_word, int aux, int i) {
    int limit = last_lenght_word + strlen(word);
    if (limit >= columns) {
        limit = columns;
    }

//this loop runs through the entire word, aux representing the position of the first letter
    for (i = aux; i < limit; i++) {
        if (strcmp(word, "for") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "from") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "in") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "is") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "unit") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "or") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "while") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "int") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "float") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "double") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "string") == 0) {
            matrix[1][i] = '_';
        }
        last_lenght_word++;
    }
    return last_lenght_word;
}

//function that underlines the 2 words
void highlight_two_words(char **matrix, char *word, char *word2, int columns, int aux, int limit) {
    int i;
    if (limit >= columns) {
        limit = columns;
    }

//this loop goes from the first letter of the first word to the last letter of the 2nd
    for (i = aux; i < limit; i++) {
        if (strcmp(word, "first") == 0 && strcmp(word2, "of") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "for") == 0 && strcmp(word2, "each") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "is") == 0 && strcmp(word2, "a") == 0) {
            matrix[1][i] = '_';
        } else if (strcmp(word, "list") == 0 && strcmp(word2, "of") == 0) {
            matrix[1][i] = '_';
        }
    }
}

//function that equals all elements of the string to 0
void cleararray(char *v, int size) {
    int i;

    for (i = 0; i < size; i++)
        v[i] = 0;
}

//function that prints the required result and in which the words are created
void text_highlight(char *str) {
    char **matrix;
    char *word;
    char *word2;
    int rows = 2;
    int columns = strlen(str);
    int last_lenght_word = 0;
    int aux, i, j, k;

//I took a matrix of 2 lines and the number of columns equal to the length of the string
    matrix = (char **) calloc(rows, sizeof(char *));
    for (i = 0; i < rows; i++) {
        matrix[i] = (char *) calloc(columns, sizeof(char));
    }

//the first line represents the elements of the string, and I load the second one only with spaces
    for (j = 0; j < columns; j++) {
        matrix[1][j] = ' ';
        matrix[0][j] = str[j];
    }

    word2 = (char *) calloc(20, sizeof(char));
    word = (char *) calloc(20, sizeof(char));

//I use a loop that goes through each word
    for (j = 0; j < columns; j++) {
        if (j < last_lenght_word) {
            continue;
        }
        if (matrix[0][j] == ' ') {
            last_lenght_word++;
            continue;
        }
        cleararray(word, strlen(word));
        cleararray(word2, strlen(word2));
        aux = last_lenght_word;

//I build the first word and if I find a space, I exit it
        for (k = last_lenght_word; k < columns; k++) {
            if (str[k] == ' ') {
                break;
            }
            word[k - last_lenght_word] = str[k];
        }

//count the spaces between the first word and the one that follows
        int spaces_number = 0;
        for (i = last_lenght_word + strlen(word); i < columns; i++) {
            if (str[i] != ' ') {
                break;
            }
            spaces_number++;
        }

/* form the second word, so that this loop starts from the number of elements
 from the first word plus the spaces, until the next space*/
        for (k = last_lenght_word + strlen(word) + spaces_number; k < columns; k++) {
            if (str[k] == ' ') {
                break;
            }
            word2[k - last_lenght_word - strlen(word) - spaces_number] = str[k];
        }

        int limit;
        last_lenght_word = highlight_one_word(matrix, word, columns, last_lenght_word, aux, i);

//limit represents the length from the first letter of the first word to the last letter of the second
        limit = aux + strlen(word) + spaces_number + strlen(word2);
        highlight_two_words(matrix, word, word2, columns, aux, limit);

    }

//I print each matrix separately, the second line, representing the highlight made on the basis of the first
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            if (matrix[i][j] != '\n')
                printf("%c", matrix[i][j]);
        }

        printf("\n");
    }

    free(word);
    free(word2);

    for (i = 0; i < rows; i++)
        free(matrix[i]);

    free(matrix);
}


int main() {
    int N, i;
    char *line_read = (char *) calloc(102, sizeof(char));
    scanf("%d", &N);
    fgets(line_read, 102, stdin);
    line_read[strlen(line_read) - 1] = '\0';

//I read each line separately
    for (i = 0; i < N; i++) {
        fgets(line_read, 102, stdin);
        line_read[strlen(line_read) - 1] = '\0';

        text_highlight(line_read);
    }

    free(line_read);
    return 0;
}