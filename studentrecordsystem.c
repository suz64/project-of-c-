#include <stdio.h>
#include <string.h>

// Maximum number of students we can store
#define MAX_STUDENTS 100
// Name of the file where we save all student data
#define FILE_NAME "student.txt"

// This stores all information about a student
typedef struct {
    int roll_no;
    char name[50];
    int age;
    char address[100];
  
} Student;

// This function saves all student information to a file
void saveToFile(Student students[], int count) {
    // Try to open the file
    FILE *file = fopen(FILE_NAME,"w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    // Write the title and total number of students
    fprintf(file, "=== STUDENT RECORDS SYSTEM ===\n");
    fprintf(file, "Total Students: %d\n\n", count);
    
    // Save each student's information
    for (int i = 0; i < count; i++) {
        fprintf(file, "--- Student %d ---\n", i + 1);
        fprintf(file, "Roll Number: %d\n", students[i].roll_no);
        fprintf(file, "Name: %s\n", students[i].name);
        fprintf(file, "Age: %d\n", students[i].age);
        fprintf(file, "Address: %s\n", students[i].address);
      
    }
      
    
    fclose(file);
    printf("\nData saved successfully to %s!\n", FILE_NAME);
    printf("You can open %s to see the detailed records.\n", FILE_NAME);
}

// This function reads student information from the file
int loadFromFile(Student students[]) {
    // Try to open the file
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        return 0;  // Return 0 if file doesn't exist
    }

    char line[256];
    int count = 0;
    
    // Skip the header lines and get total number of students
    fgets(line, sizeof(line), file);  // Skip the title line
    fgets(line, sizeof(line), file);  // Read line with total students
    sscanf(line, "Total Students: %d", &count);
    fgets(line, sizeof(line), file);  // Skip empty line
    
    // Read each student's information
    for (int i = 0; i < count; i++) {
        // Find the start of student data
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, "Roll Number:")) {
                // Read all details for this student
                sscanf(line, "Roll Number: %d", &students[i].roll_no);
                
                fgets(line, sizeof(line), file);
                sscanf(line, "Name: %[^\n]", students[i].name);
                
                fgets(line, sizeof(line), file);
                sscanf(line, "Age: %d", &students[i].age);
                
                fgets(line, sizeof(line), file);
                sscanf(line, "Address: %[^\n]", students[i].address);
                
               
                // Skip to next student
                while (fgets(line, sizeof(line), file) && !strstr(line, "---")) {}
                break;
            }
        }
    }
    
    fclose(file);
    return count;
}

// This function shows all information about one student
void displayStudent(Student student) {
    printf("\nStudent Details:\n");
    printf("Roll No: %d\n", student.roll_no);
    printf("Name: %s\n", student.name);
    printf("Age: %d\n", student.age);
    printf("Address: %s\n", student.address);
  
}
   
    
  
// This function shows information about all students
void displayAllStudents(Student students[], int count) {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }
    printf("\nAll Student Records:\n");
    for (int i = 0; i < count; i++) {
        printf("\nStudent %d:\n", i + 1);
        displayStudent(students[i]);
    }
}

// Main program starts here
int main() {
    // Create array to store student information
    Student students[MAX_STUDENTS];
    // Load existing students from file
    int count = loadFromFile(students);
    char viewChoice;

    // Keep asking for new students until user wants to stop
    while (1) {
        // Check if we can add more students
        if (count >= MAX_STUDENTS) {
            printf("Student storage is full!\n");
            break;
        }

        printf("\nEnter details for Student %d:\n", count + 1);
        
        // Get student's basic information
        printf("Name: ");
        scanf(" %s\n", students[count].name);
        
        printf("Roll No: ");
        scanf("%d", &students[count].roll_no);
        
        printf("Age: ");
        scanf("%d", &students[count].age);
        
        printf("Address: ");
        scanf(" %s \n", students[count].address);

      

        // Save the new student
        count++;
    
        saveToFile(students, count);

        // Ask if user wants to see all records
        printf("\nDo you want to view all saved records? (y/n): ");
        scanf(" %c", &viewChoice);
        if (viewChoice == 'y' || viewChoice == 'Y') {
            displayAllStudents(students, count);
        }

        // Ask if user wants to add another student
        printf("\nDo you want to add another student? (y/n): ");
        scanf(" %c", &viewChoice);
        if (viewChoice != 'y' && viewChoice != 'Y') {
            break;
        }
    }

    printf("Program ended.\n");
    return 0;
}
