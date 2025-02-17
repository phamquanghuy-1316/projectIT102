//funsion.c khai bao ham
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <conio.h> // Thu vien cho _getch() 
#include "datatype.h"
#define MAX_STUDENTS 40

//hien thi danh sach sinh vien
void ShowAllStudents(Student *students, int n){ 
	printf("+-----------+--------------------------------+-----------+--------+------------+--------------------+--------------------------------+\n");
	printf("| %-9s | %-30s | %-9s | %-6s | %-10s | %-18s | %-30s |\n","Id","Name","Classroom","Gender","DOB","phone","email");
	printf("+-----------+--------------------------------+-----------+--------+------------+--------------------+--------------------------------+\n");
	int i;
	for(i=0; i<n; i++){
		printf("| %-9d | %-30s | %-9s | %-6s | %02d/%02d/%04d | %-18s | %-30s |\n",students[i].studentId, 
               students[i].name, 
               students[i].classroomId, 
               students[i].gender ? "Male" : "Female",  
               students[i].dateOfBirth.day, students[i].dateOfBirth.month, students[i].dateOfBirth.year, 
               students[i].phone, 
               students[i].email);
	}
	printf("+-----------+--------------------------------+-----------+--------+------------+--------------------+--------------------------------+\n");

}

void InputStudent(Student *students, int n, int tmp){
	int i;
	for(i=0;i<n;i++){
		//nhap ID
		int id;
		printf("Enter the ID: ");
		while(1){
			scanf("%d",&id);
			if(isStudentIdExist(students,tmp,id)){
				printf("Id is duplicated, please re-enter: ");
				continue; 
			}
			break; 
		}
		students[i].studentId=id;
		while (getchar() != '\n');
		
		//nhap ten
		while(1){
		printf("Enter name: ");
		fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = 0;
        if (strlen(students[i].name) == 0) {
            printf("Name cannot be empty. please re-enter: ");
            continue;
        }
        break;
		}
		
		//nhap lop
		printf("Enter Classroom: ");
		fgets(students[i].classroomId, sizeof(students[i].classroomId), stdin);
        students[i].classroomId[strcspn(students[i].classroomId, "\n")] = 0;
		
		//nhap gioi tinh
		char gender; 
		printf("Enter gender: (M/F)");
		scanf("%c",&gender);
		while (getchar() != '\n');
		if(gender == 'M' || gender == 'm'){
			students[i].gender=true;
		}else if(gender == 'F' || gender == 'f'){
			students[i].gender=false;
		}else{
			printf("Invalid gender, default is (Male)");
			students[i].gender=true;
		}
		
		//nhap ngay sinh
		printf("Enter Date of Birth (dd mm yyyy): ");
        scanf("%d %d %d", &students[i].dateOfBirth.day, &students[i].dateOfBirth.month, &students[i].dateOfBirth.year);
        while (getchar() != '\n');
        
        //nhap sdt
        char phone[12]; 
        printf("Enter Phone Number: ");
        while (1) {
        fgets(phone, sizeof(phone), stdin);
        phone[strcspn(phone, "\n")] = 0; // xoa ky tu xuong dong neu co 

        // Kiem tra do dai sdt 
        if (strlen(phone) != 11) {
            printf("The phone number must have 11 digits, please re-enter: ");
            continue;
        }

        // Kiem tra trung sdt 
        if (isPhoneExist(students, tmp, phone)) {
            printf("Phone number is duplicated, please re-enter: ");
            continue;
        }

        break; // neu sdt hop le thoat vong lap 
    }
		strcpy(students[i].phone,phone);
        while (getchar() != '\n');
		
		//nhap email
		char email[30]; 
        printf("Enter Email: ");
        while (1) {
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = 0; 

        // Kiem tra email co bi bo trong khong 
        if (strlen(email) == 0) {
            printf("Email cannot be empty., please re-enter: ");
            continue;
        }

        // Kiem tra trung email 
        if (isEmailExist(students, tmp, email)) {
            printf("Email is duplicated, please re-enter: ");
            continue;
        }

        break; // neu email hop le thoat vong lap 
    }
		strcpy(students[i].email,email);
        
        printf("Add succesfully\n"); 
	}
}

int checkLogin(char *username, char *password){
	FILE *file;
	file = fopen("users.txt","r");
	if (file == NULL) {
        printf("Error: Cannot open user file!\n");
        return 0;
    }
	char user[20]; 
	char pass[20];
	if (fscanf(file, "%s %s", user, pass) != 2) {
    fclose(file);
    return 0; // File khong dung dinh dang  
}
	return strcmp(username,user)==0 && strcmp(password,pass)==0;
}

void editStudent(Student *students, int n) {
    int searchId;
    printf("Enter Student ID to edit: ");
    scanf("%d", &searchId);
    getchar(); 
 
	int i; 
    for ( i = 0; i < n; i++) {
        if (students[i].studentId == searchId) { 
            printf("\nStudent found! Current information:\n");

            printf("ID: %d\n", students[i].studentId);
            printf("Name: %s\n", students[i].name);
            printf("Classroom: %s\n", students[i].classroomId);
            printf("Gender: %s\n", students[i].gender ? "Male" : "Female");
            printf("Date of Birth: %02d/%02d/%04d\n", students[i].dateOfBirth.day, students[i].dateOfBirth.month, students[i].dateOfBirth.year);
            printf("Phone: %s\n", students[i].phone);
            printf("Email: %s\n", students[i].email);

            
            printf("Enter new Name: ");
            char temp[50];
            fgets(temp, sizeof(temp), stdin);
            if (temp[0] != '\n') {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(students[i].name, temp);
            }

            
            printf("Enter new Classroom: ");
            fgets(temp, sizeof(temp), stdin);
            if (temp[0] != '\n'){
                temp[strcspn(temp, "\n")] = 0;
                strcpy(students[i].classroomId, temp);
            }

            
            printf("Enter new Gender (M/F): ");
            char gender;
            scanf(" %c", &gender);
            getchar();
            if (gender == 'M' || gender == 'm'){
                students[i].gender = true;
            } else if (gender == 'F' || gender == 'f'){
                students[i].gender = false;
            }

           
            printf("Enter new Date of Birth (dd mm yyyy): ");
            int day, month, year;
            if (scanf("%d %d %d", &day, &month, &year) == 3){
                students[i].dateOfBirth.day = day;
                students[i].dateOfBirth.month = month;
                students[i].dateOfBirth.year = year;
            }
            getchar();

            
            printf("Enter new Phone Number: ");
            fgets(temp, sizeof(temp), stdin);
            if (temp[0] != '\n') {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(students[i].phone, temp);
            }

            
            printf("Enter new Email: ");
            fgets(temp, sizeof(temp), stdin);
            if (temp[0] != '\n') {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(students[i].email, temp);
            }

            printf("\nStudent information updated successfully!\n");
            return;
        }
    }

    printf("Error: Student with ID %d not found!\n", searchId);
}

void deleteStudent(Student *students, int *n) {
    int deleteID;
    printf("Enter Student ID to delete: ");
    scanf("%d", &deleteID);

    int i, pos = -1;
    char confirm;

    for (i = 0; i < *n; i++) {
        if (students[i].studentId == deleteID){
            pos = i;
            printf("Confirm deletion (Y/N): ");
            
            // Xu ly bo nho dem truoc khi nhap ky tu
            while (getchar() != '\n');  
            scanf("%c", &confirm);
			
            if (confirm == 'Y' || confirm == 'y'){
                int j;
                for (j = pos; j < *n - 1; j++){
                    students[j] = students[j + 1];
                }
                (*n)--;
                printf("Student with ID %d deleted successfully.\n", deleteID);
            }else{
                printf("Deletion canceled.\n");
            }
            return;  //thoat khoi ham ngay sau khi xoa hoac huy
        }
    }

    // Neu khong tim thay sinh vien
    if (pos == -1){
        printf("Error: Student with ID %d not found!\n", deleteID);
    }
}

void displayMainMenu(){
	printf("---------------chao mung den voi menu quan ly---------------\n");
	printf("====================================================");
		printf("\n%s\n","***Students Management System Using C***");
		printf("\n%25s\n","STUDENT MENU");
		printf("\n%s\n","[1].Add A New Student");
		printf("\n%s\n","[2].Show All Student");
		printf("\n%s\n","[3].Edit A Student");
		printf("\n%s\n","[4].Delete A Student");
		printf("\n%s\n","[5].Search A Student");
		printf("\n%s\n","[6].Sort Student");
		printf("\n%s\n","[7].Save change"); 
		printf("\n%s\n","[8].Load student from file");
		printf("\n%s\n","[9].Exit the program");
		printf("====================================================");
}

void GoBackOrExit(){
    int choice;
    printf("\nGo back (1) or Exit (2): ");
    scanf("%d", &choice);
    if (choice == 2){
        exit(0); //dung exit vi neu dung return se chi ket thuc ham chu khong ket thuc ca chuong trinh 
    }
}

void sortStudentMenu(){
	printf("1. sap xep sinh vien theo ten tu Z-A\n");
    printf("2. sap xep sinh vien theo ten tu A-Z\n");
}

//hoan doi vi tri 2 sinh vien
void swap(Student *a, Student *b){
    Student temp = *a;  
    *a = *b;            
    *b = temp;          
}

//sap xep theo ten tu A-Z 
void sortStudentsByNameZA(Student *students, int n){
	int i;
    for (i = 0; i < n - 1; i++){
    	int j;
        for (j = i + 1; j < n; j++){
            if (strcmp(students[i].name, students[j].name) < 0){
                swap(&students[i], &students[j]);
            }
        }
    }
}

//sap xep theo ten tu A-Z
void sortStudentsByNameAZ(Student *students, int n){
	int i;
    for (i = 0; i < n - 1; i++){
    	int j;
        for (j = i + 1; j < n; j++){
            if (strcmp(students[i].name, students[j].name) > 0){
                swap(&students[i], &students[j]);
            }
        }
    }
}

//tim kiem sinh vien bang ten 
void searchStudentByName(Student *students, int *n){
	printf("Enter name student to search: ");
	char searchName[50];
	fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; //xoa ky tu xuong dong
    printf("\n===== SEARCH RESULTS =====\n");
    int found = 0; // bien kiem tra co tim thay hay khong;
    int i;
	for(i=0; i<n; i++){
		if(strstr(students[i].name,searchName) != NULL){
			found =1;
			printf("+-----------+--------------------------------+-----------+--------+------------+--------------------+--------------------------------+\n");
			printf("| %-9s | %-30s | %-9s | %-6s | %-10s | %-18s | %-30s |\n","Id","Name","Classroom","Gender","DOB","phone","email");
			printf("+-----------+--------------------------------+-----------+--------+------------+--------------------+--------------------------------+\n");
			printf("| %-9d | %-30s | %-9s | %-6s | %02d/%02d/%04d | %-18s | %-30s |\n",students[i].studentId, 
               students[i].name, 
               students[i].classroomId, 
               students[i].gender ? "Male" : "Female",  
               students[i].dateOfBirth.day, students[i].dateOfBirth.month, students[i].dateOfBirth.year, 
               students[i].phone, 
               students[i].email);
            printf("+-----------+--------------------------------+-----------+--------+------------+--------------------+--------------------------------+\n");
		}
	}
	if(!found){
		printf("No students found!");
	}
}

//kiem tra id nhap vao trung khong
int isStudentIdExist(Student *students, int n, int id){
	int i;
    for (i = 0; i < n; i++){
        if (students[i].studentId == id) return 1; //bi trung
    }
    return 0; //khong trung
}

//kiem tra email SINH VIEN co trung khong
int isEmailExist(Student *students, int n, char *email){
	int i; 
    for (i = 0; i < n; i++){
        if (strcmp(students[i].email, email) == 0) return 1;
    }
    return 0;
}

//kiem tra email GIAO VIEN co bi trung khong
int isEmailTeacherExist(Teacher *teachers, int n, char *email){
	int i; 
    for (i = 0; i < n; i++){
        if (strcmp(teachers[i].email, email) == 0) return 1;
    }
    return 0;
}

//kiem tra sdt SINH VIEN co trung khong
int isPhoneExist(Student *students, int n, char *phone){
	int i;
    for (i = 0; i < n; i++){
        if (strcmp(students[i].phone, phone) == 0) return 1;
    }
    return 0;
}

//kiem tra sdt GIAO VIEN co trung khong
int isPhoneTeacherExist(Teacher *teachers, int n, char *phone){
	int i;
    for (i = 0; i < n; i++){
        if (strcmp(teachers[i].phone, phone) == 0) return 1;
    }
    return 0;
}

void saveStudentToFile(Student *students, int n){
    FILE *file = fopen("datastudent.txt", "a");

    if (file == NULL){
        printf("Error: Cannot open file to write!\n");
        return;
    }
	
	int i;
    for (i = 0; i < n; i++){
        fprintf(file, "%d, %s, %s, %6d, %02d, %02d, %04d, %s, %s\n",  
                students[i].studentId,  
                students[i].name,  
                students[i].classroomId,  
                students[i].gender, 
                students[i].dateOfBirth.day, 
                students[i].dateOfBirth.month, 
                students[i].dateOfBirth.year,  
                students[i].phone,  
                students[i].email);
    }

    fclose(file);
    printf("Save to file successfully!\n");
}

void saveChangeToFile(Student *students, int n){
    FILE *file = fopen("datastudent.txt", "w");

    if (file == NULL){
        printf("Error: Cannot open file to write!\n");
        return;
    }
	
	int i;
    for (i = 0; i < n; i++){
        fprintf(file, "%d, %s, %s, %6d, %02d, %02d, %04d, %s, %s\n",  
                students[i].studentId,  
                students[i].name,  
                students[i].classroomId,  
                students[i].gender, 
                students[i].dateOfBirth.day, 
                students[i].dateOfBirth.month, 
                students[i].dateOfBirth.year,  
                students[i].phone,  
                students[i].email);
    }

    fclose(file);
    printf("Save to file successfully!\n");
}

void LoadStudentsFromFile(Student *students, int *n){
    FILE *file = fopen("datastudent.txt", "r");
    if (file == NULL){
        printf("? Error: Cannot open file!\n");
        return;
    }

    *n = 0;
    
    while (*n < MAX_STUDENTS && fscanf(file, "%9d , %30[^,] , %9[^,] , %6d , %02d , %02d , %04d , %18[^,] , %30[^\n]",
                  &students[*n].studentId,  
                  students[*n].name,  
                  students[*n].classroomId,
                  &students[*n].gender,  
                  &students[*n].dateOfBirth.day,  
                  &students[*n].dateOfBirth.month,  
                  &students[*n].dateOfBirth.year,
				  students[*n].phone, 
                  students[*n].email) == 9){
        (*n)++;
    }

    printf("Load successful! Total students: %d\n", *n);
    fclose(file);
}

void getPassword(char *password, int MAX_PASSLENGTH){
    int i = 0;
    char ch;

    while (1) {
        ch = _getch(); // Doc ky tu nhung khong hien thi len man hinh 
        if (ch == 13) { // Neu nhan Enter (ma ASCII 13) thi ket thuc nhap
            password[i] = '\0';
            break;
        } else if (ch == 8) { // Neu nhan Backspace (ma ASCII 8) thi xoa 1 ky tu
            if (i > 0) {
                i--;
                printf("\b \b"); // Xoa ky tu '*' hien thi tren man hinh
            }
        } else if (i < MAX_PASSLENGTH - 1) { // Kiem tra gioi han do dai mat khau
            password[i++] = ch;
            printf("*"); // Hien thi dau '*'
        }
    }
}

void selectFunctionMenu(){
	printf("==================================\n");
	printf("[1].student management menu\n");
	printf("[2].teacher management menu\n");
	printf("==================================");
}

void displayTeacherMenu(){
	printf("---------------chao mung den voi menu quan ly---------------\n");
	printf("====================================================");
		printf("\n%s\n","***Students Management System Using C***");
		printf("\n%25s\n","TEACHER MENU");
		printf("\n%s\n","[1].Add A New Teacher");
		printf("\n%s\n","[2].Show All Teacher");
		printf("\n%s\n","[3].Edit A Teacher");
		printf("\n%s\n","[4].Delete A Teacher");
		printf("\n%s\n","[5].Search A Teacher");
		printf("\n%s\n","[6].Sort Teacher");
		printf("\n%s\n","[7].Load Teacher From File");
		printf("\n%s\n","[8].Exit The Program");
		printf("====================================================");
}

//kiem tra id giao vien co bi trung khong
int isTeacherIdExist(Teacher *teachers, int n, int id){
	int i; 
    for (i = 0; i < n; i++){
        if (teachers[i].teacherId == id) return 1; //bi trung
    }
    return 0; //khong trung
}

void inputTeacher(Teacher *teachers, int n){
	int i;
	for(i=0;i<n;i++){
		//nhap ID
		int id;
		printf("Enter the ID: ");
		while(1){
			scanf("%d",&id);
			if(isTeacherIdExist(teachers, n, id)){
				printf("Id is duplicated, please re-enter: ");
				continue; 
			}
			break; 
		}
		teachers[i].teacherId=id;
		while (getchar() != '\n');
		
		//nhap ten
		printf("Enter name: ");
		while(1){
			fgets(teachers[i].name, sizeof(teachers[i].name), stdin);
        	teachers[i].name[strcspn(teachers[i].name, "\n")] = 0;
        	if(strlen(teachers[i].name)==0){
        		printf("Name cannot be empty. please re-enter: ");
        		continue;
			}
			break;
		}
        
        //nhap gioi tinh
        char gender; 
		printf("Enter gender: (M/F)");
		scanf("%c",&gender);
		while (getchar() != '\n');
		if(gender == 'M' || gender == 'm'){
			teachers[i].gender=true;
		}else if(gender == 'F' || gender == 'f'){
			teachers[i].gender=false;
		}else{
			printf("Invalid gender, default is (Male)");
			teachers[i].gender=true;
		}
		
		//nhap mon hoc
		while(1){
			printf("Enter subject: ");
			fgets(teachers[i].subject, sizeof(teachers[i].subject), stdin);
        	teachers[i].subject[strcspn(teachers[i].subject, "\n")] = 0;
        	if(strlen(teachers[i].subject)==0){
        		printf("Subject cannot be empty. please re-enter: ");
        		continue;
			}
			break;
		}
		
		//nhap email
		char email[30]; 
        printf("Enter Email: ");
        while (1) {
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = 0; 

        // Kiem tra email co bi bo trong khong 
        if (strlen(email) == 0) {
            printf("Email cannot be empty., please re-enter: ");
            continue;
        }

        // Kiem tra trung email 
        if (isEmailTeacherExist(teachers,n,email)) {
            printf("Email is duplicated, please re-enter: ");
            continue;
        }
        break; // neu email hop le thoat vong lap 
    	}
    	
    	//nhap sdt
    	char phone[12]; 
        printf("Enter Phone Number: ");
        while (1) {
        fgets(phone, sizeof(phone), stdin);
        phone[strcspn(phone, "\n")] = 0; // xoa ky tu xuong dong neu co 

        // Kiem tra do dai sdt 
        if (strlen(phone) != 11) {
            printf("The phone number must have 11 digits, please re-enter: ");
            continue;
        }

        // Kiem tra trung sdt 
        if (isPhoneTeacherExist(teachers,n,phone)) {
            printf("Phone number is duplicated, please re-enter: ");
            continue;
        }

        break; // neu sdt hop le thoat vong lap 
    	}
	}
}
