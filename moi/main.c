#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // Thu vien cho _getch()
#include "function.h" 
#include "datatype.h"
#define MAX_STUDENTS 40
#define MAX_PASSLENGTH 20
#define MAX_TEACHER 40 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char *argv[]) {
	//khai bao
	Student students[MAX_STUDENTS];
	Teacher teachers[MAX_TEACHER];
	int n=0;
	int choice,MenuChoice=-1,teacherChoice;
	char username[20], password[MAX_PASSLENGTH];
	
	//man hinh dang nhap
	printf("-------------------- LOGIN --------------------\n");
	printf("chao mung den voi trang dang nhap\n");
	while(1){
		
		printf("nhap vao username: ");
		fgets(username, sizeof(username),stdin);
		username[strcspn(username,"\n")]='\0';
		printf("nhap vao password: ");
		getPassword(&password,MAX_PASSLENGTH);
		
		int isCheck = checkLogin(username,password);
		
		if(isCheck){
			printf("\ndang nhap thanh cong\n");
			break; 
		}else{
			 printf("\nthong tin khong chinh xa vui long thu lai \n");
		}
	}
	
	//chon menu quan ly
	system("cls");
	selectFunctionMenu();
	printf("\nEnter your choice: ");
	scanf("%d",&MenuChoice);
	
	
	//quan ly sinh vien  
	while(MenuChoice==1){
		system("cls");
		displayMainMenu();
	
		//nhap lua chon
		printf("\nnhap lua chon: ");
		scanf(" %d",&choice);
		while (getchar() != '\n');
		system("cls");
		switch(choice){
		case 1:{
			int tmp;
			tmp=n;
			printf("nhap so sinh vien muon them ");
			scanf("%d",&n);
			InputStudent(students,tmp);
			saveStudentToFile(students,n);
			n+=tmp;
			GoBackOrExit();
			break;
		}
		case 2: 
			ShowAllStudents(students,n);
			GoBackOrExit();
			break;
		case 3:
			editStudent(students,n);
			GoBackOrExit();
			break;
		case 4:
			deleteStudent(students, &n);
			GoBackOrExit();
			break;
		case 5:
			searchStudentByName(students,n);
			GoBackOrExit();
			break;
		case 6:
			sortStudentMenu();
			int choiceSort;
			scanf("%d",&choiceSort);
			switch(choiceSort){
				case 1:
					 sortStudentsByNameZA(students,n);
					 ShowAllStudents(students,n);
					 break;
				case 2:
					sortStudentsByNameAZ(students,n);
					ShowAllStudents(students,n);
					break;
			}
			GoBackOrExit();
			break;
		case 7:
			saveChangeToFile(students, n);
			GoBackOrExit();
			break;
		case 8:
			LoadStudentsFromFile(students, &n);
			GoBackOrExit();
			break;
		case 9:
			return 0;
			break;
		default:
			printf("lua chon khong hop le");
			break;	
			}
		}
	
	//quan ly giao vien
	while(MenuChoice==2){
		system("cls");
		displayTeacherMenu();
		printf("\nEnter your choice: ");
		scanf("%d",&teacherChoice);
		while (getchar() != '\n');
		system("cls");
		switch(teacherChoice){
		case 1:
			{
			int tmp;
			tmp=n;
			printf("nhap so giao vien muon nhap ");
			scanf("%d",&n);
			inputTeacher(teachers,n,tmp);
			saveTeacherToFile(teachers,n);
			n+=tmp;
			GoBackOrExit();
			break;
			}
		case 2:
			ShowAllTeachers(teachers,n);
			GoBackOrExit();
			break;
		case 3:
			editTeacher(teachers,n);
			GoBackOrExit();
			break;
		case 4:
			deleteTeacher(teachers,&n);
			GoBackOrExit();
			break;
		case 5:
			searchTeacherByName(teachers,n);
			GoBackOrExit();
			break;
		case 6:
			sortStudentMenu();
			int choiceSort;
			scanf("%d",&choiceSort);
			switch(choiceSort){
				case 1:
					sortTeacherByNameZA(teachers,n);
					ShowAllTeachers(teachers,n);
					break;
				case 2:
					sortTeacherByNameAZ(teachers,n);
					ShowAllTeachers(teachers,n);
					break;
			}
			GoBackOrExit();
			break;
		case 7:
			saveTeacherChangeToFile(teachers,n);
			break;
		case 8:
			LoadTeachersFromFile(teachers, &n);
			GoBackOrExit();
			break;
		case 9:
			return 0;
		default:
			printf("Invalid choice");
			break;
		}
	}
	return 0;
}
