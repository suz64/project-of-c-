#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define TOTAL_QUESTIONS 10
#define TIME_LIMIT 10

typedef struct {
    char question[256];
    char options[4][100];
    char correct_option;
} QuizQuestion;

char ask_question(QuizQuestion q) {
    printf("%s\n", q.question);
    printf("a. %s\n", q.options[0]);
    printf("b. %s\n", q.options[1]);
    printf("c. %s\n", q.options[2]);
    printf("d. %s\n", q.options[3]);
    
    time_t start_time = time(NULL);
    char answer = 'x'; 
    printf("Enter your answer (a/b/c/d): ");
    while (difftime(time(NULL), start_time) <= TIME_LIMIT) {
        if (_kbhit()) {
            answer = _getch();
            if (answer >= 'a' && answer <= 'd') {
                printf("%c\n", answer); 
                break;
            } else {
                printf("\nInvalid input. Please enter a, b, c, or d: ");
            }
        }
    }
    if (difftime(time(NULL), start_time) > TIME_LIMIT) {
        printf("\nTime is up!\n");
    }
    return answer;
}

void display_grade(int score, char *name) {
    printf("\n%s, your final score: %d/%d\n", name, score, TOTAL_QUESTIONS);
    float percentage = ((float)score / TOTAL_QUESTIONS) * 100;
    printf("Percentage: %.2f%%\n", percentage);
    if (percentage >= 100) {
        printf("Grade: A (Excellent!)\n");
    } else if (percentage >= 70) {
        printf("Grade: B (Good Job!)\n");
    } else if (percentage >= 50) {
        printf("Grade: C (Needs Improvement!)\n");
    } else {
        printf("Grade: F (Better Luck Next Time!)\n");
    }
    
    FILE *file = fopen("quiz_scores.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s: %d/%d (%.2f%%)\n", name, score, TOTAL_QUESTIONS, percentage);
        fclose(file);
    } else {
        printf("Error saving score to file.\n");
    }
}

int main() {
    char name[50];
    printf("Enter your name: ");
    scanf("%s", name);
    
    QuizQuestion questions[TOTAL_QUESTIONS] = {
        {"C language was created by which of the following?", {"Dennis Ritchie", "Ken Thompson", "Bjarne Stroustrup", "James Gosling"}, 'a'},
        {"Which of the following is not a valid C variable name?", {"myVar", "my_var", "my-var", "myVar1"}, 'c'},
        {"What is a correct syntax to output Hello World in C?", {"printf(\"Hello World\");", "echo \"Hello World\";", "print(\"Hello World\");", "printf(\"Hello World\");"}, 'a'},
        {"How can you create a variable with the numeric value 5?", {"int x = 5;", "int a = 5;", "int z = 5;", "all of the above"}, 'd'},
        {"Which header file is required to use the 'printf' function?", {"stdio.h", "stdlib.h", "conio.h", "string.h"}, 'a'},
        {"What does the '++' operator do in C?", {"Decrements a variable's value by 1", "Increments a variable's value by 1", "Multiplies a variable's value by 2", "Divides a variable's value by 2"}, 'b'},
        {"Which of the following is used to terminate a statement in C?", {",", ".", ":", ";"}, 'd'},
        {"What is the correct way to comment out multiple lines in C?", {"/* comment */", "// comment", "# comment", "-- comment"}, 'a'},
        {"What is the value of '5 / 2' in C?", {"2.3", "2", "2.5", "2.0"}, 'c'},
        {"Which format specifier is often used to print integers?", {"%c", "%s", "%f", "%d"}, 'd'},
        
    };
    
    char answers[TOTAL_QUESTIONS] = {'x'};
    int score = 0;

    printf("\nWelcome to the Quiz, %s! You have %d seconds for each question.\n\n", name, TIME_LIMIT);

    for (int i = 0; i < TOTAL_QUESTIONS; i++) {
        system("cls"); // Clear the screen
        printf("Question %d/%d\n", i + 1, TOTAL_QUESTIONS);
        answers[i] = ask_question(questions[i]);
    }

    for (int i = 0; i < TOTAL_QUESTIONS; i++) {
        if (answers[i] == questions[i].correct_option) {
            score++;
        }
    }

    display_grade(score, name);
    return 0;
}