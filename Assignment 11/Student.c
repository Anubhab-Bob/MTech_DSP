#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROLLSIZE 10
#define NAMESIZE 25
#define PHONESIZE 13	// might contain prefix
#define EMAILSIZE 30

/** Structure: studentRecord
 * ------------------
 *  A data structure to hold details of a student
 */
struct studentRecord
{
    char rollNo[ROLLSIZE];
    char name[NAMESIZE];
    char phone[PHONESIZE];
    char email[EMAILSIZE];
};

typedef struct studentRecord Student;

/** Function: loadFile
 * -----------------------
 *  Performs initial loading of a record file
 * 
 *  file: Name of the file containing the records
 *  
 *  returns: 1 if loading is successful, 0 otherwise.
 */
int loadFile(char file[]) {
	FILE *fin = NULL, *fout = NULL;

    fin = fopen(file, "rb");
    if(fin == NULL){	// new file
    	return 1;
	}
    char newFile[] = "newFile.dat";     // hardcoded name of temporary file
    fout = fopen(newFile, "wb");
    if(fout == NULL) {
		printf("Unable to create file!");
		return 0;
    }
    // Read from existing record file those records that are 
    // not marked as deleted
    while(!feof(fin)) {
		Student s;
		if(fread(&s, sizeof(Student), 1, fin)) {
			if(strcmp(s.rollNo, "#DELETE#"))
		    	fwrite(&s, sizeof(Student), 1, fout);
		}
    }
    fclose(fin);
    fclose(fout);       // close files after using
    
    remove(file);       // remove the previous record file
    rename(newFile, file);  // save the temporary file as new record file
    return 1;       // loading successful
}

/** Function: addStudent
 * -----------------------
 *  Adds the details of a new student at the end of record file
 * 
 *  file: Name of the file containing the records
 *  
 *  returns: 1 if adding is successful, 0 otherwise.
 */
int addStudent(char file[]) {
	FILE *fp = NULL;
    fp = fopen(file, "ab");     // file opened in append mode to add to the end
    if(fp == NULL) {
		printf("Unable to create output file!");
		return 0;
    }    
    // read new details
    Student s;
	printf("Enter the roll Number: ");
	scanf("%s", s.rollNo);
	getchar();      // to remove \n from input buffer
	printf("Enter the name: ");
	scanf ("%[^\n]%*c", s.name);
	printf("Enter the phone number: ");
	scanf("%s", s.phone);
	printf("Enter the email id: ");
	scanf("%s", s.email);
	fwrite(&s, sizeof(Student), 1, fp);     // append details in the file
	fclose(fp);     // close file after using
	
	return 1;       // added successfully
}

/** Function: searchRecord
 * -----------------------
 *  Searches the details of a student from record file based on name
 * 
 *  file: Name of the file containing the records
 *  name: The name of the student whose details are to be searched
 *  
 *  returns: 1 if search is successful, 0 otherwise.
 */
int searchRecord(char file[], char name[]) {
	FILE *fp = NULL;
	fp = fopen(file, "rb");     // open file in read mode
    if(fp == NULL) {
		printf("Unable to open file to display!");
		return 0;
	}
	int found = 0;      // stores the search status
	while(!feof(fp))
    {
		Student s;
		// read each entry and compare the name
		if(fread(&s, sizeof(Student), 1, fp)) {
			if(!strcmp(name, s.name)) {
				found = 1;
				printf("Entry exists!\n");
				printf("Details -->\t%s, %s, %s, %s\n", s.rollNo, s.name, s.phone, s.email);
			}
		}		    
	}
	fclose(fp);     // close file after using
	
	return found;
}

/** Function: modifyRecord
 * -----------------------
 *  Searches the details of a student from record file based on roll number
 *  and then modifies the details of the student
 * 
 *  file: Name of the file containing the records
 *  roll: The roll number of the student whose details are to be modified
 *  
 *  returns: 1 if modification is successful, 0 otherwise.
 */
int modifyRecord (char file[], char roll[]) {
	FILE *fp = NULL;
	fp = fopen(file, "rb+");     // open file in read and write mode
    if(fp == NULL) {
		printf("Unable to open file to modify!");
		return 0;
	}
	int modified = 0;   // stores the status of modification
	int i = 0;          // counts the number of records traversed
	while(!feof(fp))
    {
		Student s;
		// read each entry and compare the roll number
		if(fread(&s, sizeof(Student), 1, fp)) {
			if(!strcmp(roll, s.rollNo)) {
				modified = 1;
				printf("Entry exists! Enter new details - \n");
				printf("Enter the roll Number: ");
				scanf("%s", s.rollNo);
				getchar();      // to remove \n from input buffer
				printf("Enter the name: ");
				scanf ("%[^\n]%*c", s.name);
				printf("Enter the phone number: ");
				scanf("%s", s.phone);
				printf("Enter the email id: ");
				scanf("%s", s.email);
				// reposition file pointer to the start of current student details
				fseek(fp, sizeof(Student) * i, SEEK_SET);
				// overwrite current student details
				fwrite(&s, sizeof(Student), 1, fp);
			}
		}
		if(modified)
			break;
		i++;	    
	}
	fclose(fp);     // close file after using
	
	return modified;
}

/** Function: deleteRecord
 * -----------------------
 *  Searches the details of a student from record file based on roll number
 *  and then marks it as deleted.
 * 
 *  file: Name of the file containing the records
 *  roll: The roll number of the student whose details are to be modified
 *  
 *  returns: 1 if deletion is successful, 0 otherwise.
 */
int deleteRecord(char file[], char roll[]) {
	FILE *fp = fopen(file, "rb+");     // open file in read and write mode
    if(fp == NULL) {
		printf("Unable to open file to delete!");
		return 0;
	}
	int deleted = 0;   // stores the status of deletion
	int i = 0;          // counts the number of records traversed
	while(!feof(fp))
    {
		Student s;
		// read each entry and compare the roll number
		if(fread(&s, sizeof(Student), 1, fp)) {
			if(!strcmp(roll, s.rollNo)) {
				deleted = 1;
				printf("Entry exists! Deleting record - \n");
				strcpy(s.rollNo, "#DELETE#");
				// reposition file pointer to the start of current student details
				fseek(fp, sizeof(Student) * i, SEEK_SET);
				// overwrite current student details
				fwrite(&s, sizeof(Student), 1, fp);
			}
		}
		if(deleted)
			break;
		i++;	    
	}
	fclose(fp);     // close file after using
	
	return deleted;
}

/** Function: displayRecords
 * -----------------------
 *  Display the students' details from a record file
 * 
 *  file: Name of the file containing the records
 *  
 *  returns: 1 if display is successful, 0 otherwise.
 */
int displayRecords(char file[]) {
	FILE *fp = fopen(file, "rb");     // open file in read mode
    if(fp == NULL) {
		printf("Unable to open file to display!");
		return 0;
	}
	while(!feof(fp))
    {
		Student s;
		// read each entry and dsplay
		if(fread(&s, sizeof(Student), 1, fp)) {
			//if(strcmp(s.rollNo, "#DELETE#"))
		    printf("%s, %s, %s, %s\n", s.rollNo, s.name, s.phone, s.email);
		}
	}
	fclose(fp);     // close file after using
	
	return 1;       // display successful
}

int main(int argc, char **argv)
{
    if(argc != 2) {
		printf("Invalid arguments: File name missing!");
		exit(0);
    }
	if(!loadFile(argv[1])) {	// initial loading
        printf("Error occurred...\nTerminating program!");
        exit(0);
    }    
	int cont = 1;       // stores the choice of continuing
	while(cont) {
		printf("Enter choice of operation :\n");
		printf("1: Add entry\t2: Modify Entry\n");
		printf("3: Search Entry\t4: Delete Entry\n");
		printf("5: Display Entries\n");
		int choice;
		char input[NAMESIZE];       // stores input
		scanf("%d", &choice);       // stores choice of operation
		switch (choice) {
			case 1 :	if(addStudent(argv[1]))
							printf("Entry added\n");
						else
							printf("Error occurred\n");
						break;
			case 2 :	printf("Enter roll number to modify : ");
						scanf("%s", input);
						if(modifyRecord(argv[1], input))
							printf("Entry Modified\n");
						else
							printf("Record does not exit or error occurred\n");
						break;
			case 3 :	printf("Enter name to search : ");
			            getchar();
                        scanf ("%[^\n]%*c", input);
                        if(!searchRecord(argv[1], input))
                            printf("Record does not exit or error occurred\n");
                        break;
			case 4 :	printf("Enter roll number to delete : ");
                        scanf("%s", input);
                        if(deleteRecord(argv[1], input))
                            printf("Entry Deleted\n");
                        else
                            printf("Record does not exit or error occurred\n");
                        break;
			case 5 :	printf("File contains : \n");
						displayRecords(argv[1]);
						break;
			default:	printf("Wrong input!\n");
						break;
		}
		printf("1: Continue\t0: End\t: ");
		scanf("%d", &cont);
	}
}
