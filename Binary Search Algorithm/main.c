#include <stdio.h>
#include <stdlib.h>

struct account{
    long studentID;
    int lessonID;
    int score;
};
struct binOffset {
    long studentID;
    int offset;
};
long userID_input;           //for search binary alghorithm.
int studentCount=0;
struct account student[60];
struct binOffset offsets[60];

int findOffset(long a){

    for (int i = 0; i < studentCount; ++i) {
        if(a==offsets[i].studentID)
            return offsets[i].offset;
    }
}

void sort() {
    struct account temp2;
    for (int i = 0; i < studentCount; ++i) {
        for (int j = 0; j <studentCount; ++j)
        {
            if(student[i].studentID>student[j].studentID)
            {
                temp2.studentID = student[j].studentID;
                temp2.lessonID = student[j].lessonID;
                temp2.score = student[j].score;

                student[j].studentID= student[i].studentID;
                student[j].lessonID= student[i].lessonID;
                student[j].score= student[i].score;

                student[i].studentID= temp2.studentID;
                student[i].lessonID = temp2.lessonID;
                student[i].score= temp2.score;
            }
        }
    }
}
void createIndex(){
    FILE *fptr;
    fptr = fopen ("indexFile.txt", "w+");
    for (int i = 0; i < studentCount; ++i) {
        fprintf(fptr, "%3d %ld\n",findOffset(student[i].studentID),student[i].studentID);
    }
    fclose(fptr);
}
void findStudent() {
    struct binOffset temp[studentCount];
    long first = 0 ;
    long last = studentCount-1;
    long middle = (first + last) / 2;
    printf("Enter the number you want to see his registry : ");
    scanf("%ld", &userID_input);
    FILE *fptr;
    if ((fptr = fopen("indexFile.txt", "r")) == NULL) {
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    for (int i = 0; i < studentCount; ++i) {
        fscanf(fptr, "%3d %ld", &temp[i].offset, &temp[i].studentID);
    }
    fclose(fptr);

    while (first <= last) {
        if (temp[middle].studentID > userID_input) {
            first = middle + 1;
        }
        else if (temp[middle].studentID == userID_input) {
            printf("\n%ld ID Found at Offset %d.\n",userID_input,temp[middle].offset);
            break;
        } else
            last = middle - 1;
        middle = (first + last) / 2;
    }
    if (first > last)
        printf("Not found! %ld\n", userID_input);
}


int main() {


    FILE *fptr;
    if ((fptr = fopen("data.bin", "rb+")) == NULL) {
        printf("Error while opening the existing data.bin file");    // This is the proccess of reading the existing binary file for using sorting
        exit(1);                                                      // searching, deleting methods over memory via struct variables.
    }



        while(fread(&student[studentCount], sizeof (struct account), 1,fptr)==1){
            offsets[studentCount].studentID = student[studentCount].studentID;
            offsets[studentCount].offset = studentCount * sizeof( struct account );
            studentCount++;
        }
        fclose(fptr);
        int option;
        while(option!=0) {
            printf("Welcome to the Registry Unit of Kocaeli Uni.\n");
            entryMenu:
            printf("Here are the options you can do. \n\n");
            printf("Option 1: Create a new random data file...\n");
            printf("Option 2: Show the binary data file...\n");
            printf("Option 3: Create the sorted index file...\n");
            printf("Option 4: List Index File sorted...\n");
            printf("Option 5: Delete Index File...\n");
            printf("Option 6: Find the student via bin.search alghorithm...\n");
            printf("Option 7: Add the student...\n\n");
            printf("Choose the operation you want to do or press '0' to exit...");
            scanf("%d", &option);

            switch (option) {
                case 1:       //Make a random binary file of students.
                {
                    FILE *fptr;
                    if ((fptr = fopen("data.bin", "wb")) == NULL) {
                        printf("Error while opening binary file");
                        exit(1);
                    }

                    for (int i = 0; i < 50; ++i) {
                        student[i].studentID = 190200000 + rand() % 10001;
                        student[i].lessonID = rand() % 10;
                        student[i].score = rand() % 101;
                        fwrite(&student[i], sizeof(struct account), 1, fptr);
                    }
                    fclose(fptr);
                    printf("Binary File has been created succesfully!\n");

                    break;
                }
                case 2:        //List the binary file of student data
                {
                    FILE *fptr;
                    if ((fptr = fopen("data.bin", "rb+")) == NULL) {
                        printf("Error while opening the existing data.bin file");
                        exit(1);
                    }
                    struct account example[studentCount];
                    for (int i = 0; i < studentCount; ++i) {

                        fread(&example[i], sizeof(struct account), 1, fptr);
                        printf("Number: %d |ID: %ld, Lecture: %d, Score: %d \n", i + 1, example[i].studentID, example[i].lessonID,
                               example[i].score);
                    }
                    printf("\n");
                    break;
                }
                case 3:          //Create index txt file.
                {
                    remove("indexFile.txt");
                    sort();
                    createIndex();
                    printf("the Index file has been created succesfully!\n");
                    break;
                }
                case 4:          //Show the index file.
                {

                    struct binOffset temp[studentCount];
                    FILE *fptr;
                    if ((fptr = fopen("indexFile.txt","r")) == NULL){
                        printf("Error! opening file");

                        // Program exits if the file pointer returns NULL.
                        exit(1);
                    }
                    for (int i = 0; i < studentCount; i++) {

                        fscanf(fptr,"%3d %ld",&temp[i].offset,&temp[i].studentID);
                    }
                    for (int i = 0; i < studentCount; i++) {

                        printf("%3d %ld\n",temp[i].offset,temp[i].studentID);
                    }
                    printf("\n");
                    fclose(fptr);
                    break;
                }
                case 5:           //Delete the Index File.
                {
                    remove("indexFile.txt");
                    printf("Index file has been deleted succesfully! \n");
                    break;
                }
                case 6:           //Find the student via bin algh.
                {
                    findStudent();
                    break;
                }
                case 7:
                {
                    FILE *fptr;            //Add student...
                    if ((fptr = fopen("data.bin","rb")) == NULL)
                    {
                        printf("Error! opening file");

                        // Program exits if the file pointer returns NULL.
                        exit(1);
                    }
                    for (int i = 0; i < studentCount; ++i) {
                        fread(&student,sizeof (struct account),1,fptr);
                    }
                    studentCount++;
                    printf("Enter ID:");
                    scanf("%ld",&student[studentCount].studentID);
                    printf("Enter LessonId:");
                    scanf("%d",&student[studentCount].lessonID);
                    printf("Enter Point:");
                    scanf("%d",&student[studentCount].score);
                    fseek(fptr,12, SEEK_END);
                    fptr = fopen("data.bin","ab+");

                    fwrite(&student[studentCount], 12,1,fptr);
                    fclose(fptr);
                    sort();
                    createIndex();
                    break;
                }
                case 8:     //Update the student score.
                {

                }
                case 9:             //Delete the student data.
                {

                }
            }
            if(option==0) {
                printf("\nThank you for your using it!!");
                break;
            }
            else
                goto entryMenu;
        }







    return 0;
}






