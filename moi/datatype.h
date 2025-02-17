//khai bao struct
#include <stdbool.h>

struct Date{
	int month,day,year;
};

typedef struct {
    int studentId;
    char classroomId[10];
    char name[30];
    struct Date dateOfBirth;
    bool gender;
    char email[30];
    char phone[12];
} Student;

typedef struct {
	int teacherId;
	char name[30];
	bool gender;
	char subject[30];
	char email[30];
    char phone[12];
} Teacher;



