#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char word[100];
    struct Node* next;
} Node;

int hash(char* word) {
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
        sum += tolower(word[i]);
    return sum % 25; // table size
}
void insert(Node** table, char* word) {
    int idx = hash(word);
    Node* new = malloc(sizeof(Node));
    strcpy(new->word, word);
    new->next = table[idx];
    table[idx] = new;
}
int search(Node** hashtable, char *word) {
    int idx = hash(word);
    Node* temp = hashtable[idx];
    while (temp) {
        if (strcasecmp(temp->word, word) == 0)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int min3(int a, int b, int c) {
    return (a < b ? (a < c ? a : c) : (b < c ? b : c));
}
// Levenshtein Distance
int editDistance(char* s1, char* s2) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++)
        dp[i][0] = i;
    for (int j = 0; j <= len2; j++)
        dp[0][j] = j;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (tolower(s1[i - 1]) == tolower(s2[j - 1]))
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
        }
    }
    return dp[len1][len2];
}

int loadVocab(Node** hashtable, char vocab[][100]) {
    FILE* fp = fopen("Vocabulary.txt", "r");
    if (!fp) {
        printf("Error: Could not open Vocabulary.txt\n");
        return -1;
    }

    int count = 0;
    while (fscanf(fp, " %99s", vocab[count]) != EOF) {
        insert(hashtable, vocab[count]);
        count++;
    }
    fclose(fp);
    return count;
}
void suggestWords(Node** hashtable, char vocab[][100], int vocabSize, char* word) {
    printf(" -> Suggestions: ");
    int found = 0;
    for (int i = 0; i < vocabSize; i++) {
        int dist = editDistance(word, vocab[i]);
        if (dist <= 2) {
            printf("%s ", vocab[i]);
            found = 1;
        }
    }
    if (!found) printf("no close match");
    printf("\n");
}
void checkDocument(Node** hashtable, char vocab[][100], int vocabSize) {
    FILE* fp = fopen("Document.txt", "r");
    if (!fp) {
        printf("Error: Could not open myDocument.txt\n");
        return;
    }

    char word[100];
    int misspelled = 0;
    while (fscanf(fp, " %99s", word) != EOF) 
        if (!search(hashtable, word)) {
            printf("Misspelled: %s", word);
            suggestWords(hashtable, vocab, vocabSize, word);
            misspelled++;
        }
    printf("\nTotal misspelled words: %d\n", misspelled);
    fclose(fp);
}

int main() {
    Node* hashtable[25];
    for (int i = 0; i < 25; i++)
        hashtable[i] = NULL;

    char vocab[1000][100];
    int vocabSize = loadVocab(hashtable, vocab);

    checkDocument(hashtable, vocab, vocabSize);
    return 0;
}
