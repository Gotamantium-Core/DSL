/*In a faculty room, several teachers share a single WiFi-enabled printer. Each teacher sends
PDF documents to the printer which are placed into the printer spool where the documents wait
to be printed in the order they arrive. The printer operates at a speed of 30 ppm (pages per
minute). Simulate this printing scenario with a menu to display the following:
(a) name of the teacher whose PDF is currently being printed
(b) waiting time for the prof. who submitted the doc PCCSL307 Lab cycle.pdf
(c) name of the teacher who has to wait the most
*/
#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char docName[100];
    char teacherName[100];
    int pages;
} Document;

Document queue[MAX];
int totalDocs = 0;
int currentDoc = 0;

void addJob(char docName[], char teacherName[], int pages) {
    strcpy(queue[totalDocs].docName, docName);
    strcpy(queue[totalDocs].teacherName, teacherName);
    queue[totalDocs].pages = pages;
    totalDocs++;
}

void displayMenu() {
    printf("\n==== Printer Queue Menu ====\n");
    printf("a. Show current printing document's teacher\n");
    printf("b. Waiting time for PCCSL307 Lab cycle.pdf\n");
    printf("c. Teacher who waits the most\n");
    printf("d. Exit\n");
    printf("Select an option: ");
}

void currentPrinting() {
    if (currentDoc >= totalDocs) {
        printf("No document is being printed currently.\n");
    } else {
        printf("Currently printing: %s by %s\n",
            queue[currentDoc].docName,
            queue[currentDoc].teacherName);
    }
}

void waitTimeForDoc(char targetDoc[]) {
    int waitTime = 0;
    for (int i = currentDoc; i < totalDocs; i++) {
        if (strcmp(queue[i].docName, targetDoc) == 0) {
            printf("Waiting time for '%s': %d seconds (%.2f minutes)\n",
                targetDoc, waitTime, waitTime / 60.0);
            return;
        }
        waitTime += queue[i].pages * 2;
    }
    printf("Document '%s' not found in queue.\n", targetDoc);
}

void teacherWithMaxWait() {
    int maxWait = -1;
    char maxTeacher[100] = "";
    int waitTime = 0;

    for (int i = currentDoc; i < totalDocs; i++) {
        int docWait = waitTime;
        if (docWait > maxWait) {
            maxWait = docWait;
            strcpy(maxTeacher, queue[i].teacherName);
        }
        waitTime += queue[i].pages * 2;
    }

    if (maxWait == -1) {
        printf("No documents in queue.\n");
    } else {
        printf("Teacher who waits the most: %s (%d seconds / %.2f minutes)\n",
            maxTeacher, maxWait, maxWait / 60.0);
    }
}

int main() {
    // Sample data
    addJob("DSA_Lab_1.pdf", "Dr. A", 6);
    addJob("PCCSL307 Lab cycle.pdf", "Prof. B", 12);
    addJob("Math_Paper.pdf", "Dr. C", 10);
    addJob("ML_Notes.pdf", "Dr. D", 20);

    char option;

    do {
        displayMenu();
        scanf(" %c", &option);

        switch (option) {
            case 'a':
                currentPrinting();
                break;
            case 'b':
                waitTimeForDoc("PCCSL307 Lab cycle.pdf");
                break;
            case 'c':
                teacherWithMaxWait();
                break;
            case 'd':
                printf("Exiting simulation.\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (option != 'd');

    return 0;
}
