#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>

#define TRUE 		1
#define FALSE 		0
#define MAX_BUFFER	64
#define MAX_LIMIT	128

typedef struct admin
{
	char user_id[MAX_BUFFER];
	char password[MAX_BUFFER];
	char email[MAX_BUFFER];
}admin_t;

admin_t admin;

typedef struct Student
{
	char user_id[MAX_BUFFER];
	char name[MAX_BUFFER];
	char department[MAX_BUFFER];
	char course[MAX_BUFFER];
	int  semester;
	char email[MAX_BUFFER];
	char password[MAX_BUFFER];

}student_t;

student_t student;
long size_student= sizeof(student_t);

typedef struct  add_staff_member
{
	char user_id[MAX_BUFFER];
	char name[MAX_BUFFER];
	char email[MAX_BUFFER];
	char department[MAX_BUFFER];
	char designation[MAX_BUFFER];
	char password[MAX_BUFFER];

}faculty_t;

faculty_t faculty;
long size_faculty= sizeof(faculty_t);

typedef struct feedback_data
{
	char faculty_user_id[MAX_BUFFER];
	char student_user_id[MAX_BUFFER];
	char department[MAX_BUFFER];
	char course[MAX_BUFFER];
	char subject[MAX_BUFFER];
	float ready_to_try_new_things;
	float encouraged;
	float excited_about_ideas;
	float confused_or_nervous;
	float confident;
	float resistant_to_take_advice;
	float appreciative;
	float energetic;
	float teaching_skills;
	float punctuality;
	float interaction;
	char comments[MAX_LIMIT];

}feedback_t;

feedback_t feedback;
long size_feedback= sizeof(feedback_t);

typedef enum choice
{
	ADMIN = 1,
	STUDENT,
	FACULTY,
	HOD,
	EXIT,
}choice_t;

int validate_user_id(char *user_id);
int validate_email_id(char *email);
int validate_password(char *password);
int validate_name(char *name);

int search_student(char *user_id);
int search_faculty(char *user_id);
int admin_login();
int display_student();
int add_student();
int update_student();
int delete_student();

int display_staff_member();
int add_staff_member();
int update_staff_member();
int delete_staff_member();

int update_student_self();
int view_faculty_department(char *department);
int submit_feedback(char *student_user_id, char *department, char *course);
void update_feedback_department(char *user_id, char *department);
void delete_feedback_record(char *user_id);
int student_login();
int faculty_login();
int hod_login();
void view_feedback_data();

int admin_module();
int student_module();
int faculty_module();
int hod_module();

/*** Function to validate name ***/
int validate_name(char *name)
{
	int index= 0,
		length= 0;

	length = strlen(name);
	if(length < 5)
	{
		printf("Name should contain atleast 6 Characters,\n");
		return 1;
	}
	else
	{
		for(index= 0; index< length; index++)
		{
			if((name[index] >=65) && (name[index] <= 90))
			{
				continue;
			}
			else if((name[index] >= 97) && (name[index] <= 122))
			{
				continue;
			}
			else if(name[index] == 32)
			{
				continue;
			}
			else
			{
				printf("Name should contain Uppercase and Lowercase characters only.\n");
				return 1;
			}
		}
		return 0;
	}
}


/*** Function to validate user id ***/
int validate_comments(char *comment) 
{
	int index = 0,
		length = 0;

	length = strlen(comment);
	if(length >= 2)
	{
		for(index= 0; index< length; index++)
		{
			if((comment[index] >= 65) && (comment[index] <= 90))
			{
				continue;
			}
			else if((comment[index] >= 97) && (comment[index] <= 122))
			{
				continue;
			}
			else if((comment[index] >= 48) && (comment[index] <= 57))
			{
				continue;
			}
			else if(comment[index] == 32)
			{
				continue;
			}
			else
			{
				printf("Special characters are allowed in Comments.\n");
				return 1; //return 1 on failure
			}
		}
	}
	else
	{
		printf("Comments can't be left Blank\n");
		return 1;
	}
	return 0; //return  on success
}


/*** Function to validate user id ***/
int validate_user_id(char *user_id) 
{
	int index = 0,
		length = 0;

	length = strlen(user_id);
	if(length >= 2)
	{
		for(index= 0; index< length; index++)
		{
			if((user_id[index] >= 65) && (user_id[index] <= 90))
			{
				continue;
			}
			else if((user_id[index] >= 97) && (user_id[index] <= 122))
			{
				continue;
			}
			else if((user_id[index] >= 48) && (user_id[index] <= 57))
			{
				continue;
			}
			else if(user_id[index] == 32)
			{
				printf("Spaces are not allowed in User Id.\n");
				return 1; //return 1 on failure
			}
			else
			{
				printf("Special characters are not allowed in User Id.\n");
				return 1; //return 1 on failure
			}
		}
	}
	else
	{
		printf("User ID should contain atleast 2 Characters\n");
		return 1;
	}
	return 0; //return  on success
}

/*** Function to validate password ***/
int validate_password(char *password)
{
	int length = 0,
		count_upper = 0,
		count_lower = 0,
		count_special = 0,
		count_digit = 0,
		index = 0;

	length = strlen(password);
	if(length > 7)
	{
		for (index = 0; index < length; index++)
   		{
    	   	if ((password[index] >= 65) && (password[index] <= 90)) //validation for Uppercase Character
    	   	{
    	    		count_upper++;
    	   	}
			else if((password[index] >=97) && (password[index] <= 122)) //validation for Lowercase Character
			{
				count_lower++;
			}	
    	   	else if ((password[index] >= 48) && (password[index] <= 57)) //validation Special Character
    	   	{
    	    		count_digit++;
    	    }
    	   	else
    	   	{
    	   		count_special++;
    	   	}
		}

		if (count_special == 0)
		{
			printf("Password should contain Special Character.\n");
			return 1;
		} 
		else if(count_upper == 0)
		{
			printf("Password should contain Uppercase Character.\n");
			return 1;
		} 
		else if(count_lower == 0)
		{
			printf("Password should contain Lowercase Character.\n");
			return 1;
		}  
		else if(count_digit == 0)
		{
			printf("Password should contain Numeric Character.\n");
			return 1;
		}
	}
	else
	{
		printf("Password Length should be Greater than 7 Characters.\n");
		return 1;
	}
	return 0;
}

int admin_module()
{
	char ch;

	int ret_val = 0,
		choice= 0;

	ret_val= admin_login();
	if(!ret_val)
	{
		start: system("clear");
		printf("\n*******************************************************************************************");
		printf("\n*                                                                                         *");
		printf("\n*                                       ADMIN  MODULE                                     *");
		printf("\n*                                                                                         *");
		printf("\n*******************************************************************************************");
		printf("\nPlease Select Desired Choice\n");
		printf("\n1  : Add Student");
		printf("\n2  : Update Student");
		printf("\n3  : Delete Student");
		printf("\n4  : Display Student");
		printf("\n5  : Add Faculty");
		printf("\n6  : Update Faculty");
		printf("\n7  : Delete Faculty");
		printf("\n8  : Display Faculty");
		printf("\n9  : View Feedback Data");
		printf("\n10 : Logout");
		printf("\n\nChoice : ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				add_student();
				goto valid;

			case 2:
				update_student();
				goto valid;

			case 3:
				delete_student();
				goto valid;

			case 4:
				display_student();
				goto valid;

			case 5:
				add_staff_member();
				goto valid;

			case 6:
				update_staff_member();
				goto valid;
			
			case 7:
				delete_staff_member();
				goto valid;

			case 8:
				display_staff_member();
				goto valid;

			case 9:
				view_feedback_data();
				goto valid;

			case 10:
				break;

			default:
				printf("\nInvalid Selection of Choice. Please Select Valid Option.");
				goto start;
		}
		valid: printf("\nPress\n1 : Continue\n2 : Logout\n");
    	scanf("%c", &ch);
    	printf("Choice : ");
    	scanf("%c", &ch);
    	if(ch == '1')
    	{
    		goto start;
    	}
    	else if(ch == '2')
    	{
    		
    	}
    	else
    	{
    		printf("\nPlease Select valid Choice.\n");
    		goto valid;
    	}

	}
}
int admin_login()
{

	char user_id[MAX_BUFFER] = {0},
		 password[MAX_BUFFER] = {0};

	int user_flag= 0,
		password_flag= 0;
	FILE *fp = NULL;
	

	printf("\nPlease provide Login Credentials...\n");
	printf("User ID : ");
	a: scanf(" %[^\n]s", user_id);

	fp= fopen("admin.txt", "r");
	while(fread(&admin, sizeof(admin_t), 1, fp) == 1)
	{
	  	if(!strcmp(user_id, admin.user_id) )
		{
			printf("Password : ");
			b: scanf(" %[^\n]s", password);
			if(!strcmp(password, admin.password))
			{
				printf("Login Successfull.\n");
				return 0;
			}
			else
			{
				printf("Wrong Password\nPlease Enter Correct Password : ");
				goto b;
			}
		}
		else
		{
			fclose(fp);
			printf("Wrong User ID\nPlease Enter Correct User ID : ");
			goto a;
		}
	}
	return 1;
}


/*** Function to Search a Particular Roll no ***/
int search_student(char *user_id)
{
 	FILE *fp= NULL;
 	int c = 0;
 	
 	fp = fopen("student.txt", "r");
 	while (!feof(fp))
 	{
  		fread(&student, sizeof(student_t), 1, fp);

  		if (!strcmp(user_id, student.user_id))
  		{
   			fclose(fp);
   			return 1; //on success
  		}
 	}
 	fclose(fp);
 	return 0; //on Failure
}


/*** Display Student ***/
int display_student()
{

 	FILE *fp= NULL;
 	memset(&student, 0, sizeof(student_t));
 	fp = fopen("student.txt", "r");
 	printf("\n\n");
 	printf("__________________________________________________________________________________________________________________\n");
 	printf("%-15s %-20s %-15s %-15s %-10s %-25s %s\n", "User ID", "Name","Department", "Course", "Semester", "Email ID", "Password");
 	printf("__________________________________________________________________________________________________________________\n");
 	while (fread(&student, sizeof(student_t), 1, fp))
 	printf("%-15s %-20s %-15s %-15s %-10d %-25s %s\n", student.user_id, student.name,student.department, student.course,student.semester, student.email, student.password);
 	if(strlen(student.user_id) == 0)
 	{
 		printf("Student List is Empty.\n");
 	}
 	printf("__________________________________________________________________________________________________________________\n");
 	memset(&student, 0, sizeof(student_t));
 	fclose(fp);
}

/**** Function to add Student ***/
int add_student()
{
	char user_id[MAX_BUFFER]= {0};
	int ret_val= 1;
	FILE *fp;
	memset(&student, 0, sizeof(student_t));
	
	printf("\nEnter New Student Details.\n");
	
 	c: printf("\nEnter the Roll no   :");
    scanf(" %[^\n]s", user_id);
    ret_val= search_student(user_id);
    if(ret_val == 1)
    {
    	printf("\nRoll Number already exist. Try Again\n");
    	goto c;
    }
 	if(validate_user_id(user_id))
 	{
 		memset(&student, 0, sizeof(student_t));
 		goto c;
 	}
 	strcpy(student.user_id, user_id);
 	printf("Enter the Name      :");
 	d: scanf(" %[^\n]s", student.name);
 	if(validate_name(student.name))
 	{
 		bzero(student.name, MAX_BUFFER);
 		printf("Please Enter Valid User Name : ");
 		goto d;
 	}

 	printf("Enter the Department      :");
 	scanf(" %[^\n]s", student.department);
 	
 	printf("Enter the Course      :");
 	scanf(" %[^\n]s", student.course);

 	printf("Enter the Semester      :");
 	scanf(" %d", (&student.semester));
 	 	
 	printf("Enter the Email      :");
 	scanf(" %[^\n]s", student.email);
 	 	
 	printf("Enter the Password     :");
 	e: scanf(" %[^\n]s", student.password);
 	if(validate_password(student.password))
 	{
 		bzero(student.password, MAX_BUFFER);
 		printf("Please Enter Valid Password : ");
 		goto e;
 	}
 	fp = fopen("student.txt", "a");
 	fwrite(&student, sizeof(student_t), 1, fp);
 	fclose(fp);
 	printf("\nSTUDENT ADDED SUCCESSFULLY.\n");
 	display_student();
}

/*** Function to Update Student ***/
int update_student()
{
 	char user_id[MAX_BUFFER]= {0},
 		 temp_user_id[MAX_BUFFER]= {0};

 	FILE *fp= NULL;
 	
 	int ret_val=0,
 		choice= 0,
 		update_flag= 0;

 	memset(&student, 0, sizeof(student_t));
 	start: printf("\nEnter Student User ID to update:");
 	scanf(" %[^\n]s", user_id);
 	ret_val = search_student(user_id);
 	if (ret_val == 0)
	{
  		printf("\nRoll Number %s does not Exists\n", user_id);
  		goto start;
 	}
 	else
 	{
  		fp = fopen("student.txt", "rb+");
  		while (fread(&student, sizeof(student_t), 1, fp))
  		{
  			ret_val= strcmp(user_id, student.user_id);
   			if (!ret_val)
   			{
   				update_flag= TRUE;

    			printf("\n\t1. Update Name of Student");
    			printf("\n\t2. Update Department of Student");
    			printf("\n\t3. Update Course of Student");
    			printf("\n\t4. Update Semester of Student");
    			printf("\n\t5. Update Email of Student");
    			printf("\n\t6. Update Password of Student");
    			printf("\nEnter your choice :");
    			scanf("%d", &choice);
    			switch (choice)
    			{
    				case 1:
    			 		printf("Enter New Name :");
    			 		a: scanf(" %[^\n]s", student.name);
    			 		if(validate_name(student.name))
 						{
 							bzero(faculty.user_id, MAX_BUFFER);
 							printf("Please Enter Correct User Name : ");
 							goto a;
 						}
    			 		break;

    			 	case 2:
    			 		printf("Enter New Department : ");
    			 		scanf(" %[^\n]s", student.department);
    			 		break;
    				
    				case 3:
    			 		printf("Enter New Course : ");
    			 		scanf(" %[^\n]s", student.course);
    			 		break;

    			 	case 4:
    			 		printf("Enter New Semester : ");
    			 		scanf(" %d", &(student.semester));
    			 		break;
    				
    				case 5:
    			 		printf("Enter new Email ID : ");
    			 		scanf(" %[^\n]s", student.email);
    			 		break;

    			 	case 6:
    			 		printf("Enter new Password : ");
    			 		b: scanf(" %[^\n]s", student.password);
    			 		if(validate_password(student.password))
 						{
 							bzero(faculty.password, MAX_BUFFER);
 							printf("Please Enter Valid Password : ");
 							goto b;
 						}
    			 		break;
    				
    				default:
    			 		printf("Invalid Selection");
    			 		break;
    			}
    			fseek(fp, -size_student, 1) ;
    			fwrite(&student, sizeof(student_t), 1, fp);
    			fclose(fp);
    			break;
   			}
  		}
  		if(TRUE == update_flag)
  		{
  			printf("\nRECORD UPDATED SUCCESSFULLY\n");
  			display_student();
  		}
 	}
}

/*** Function to Delete Student Record ***/
int delete_student()
{
	char user_id[MAX_BUFFER]= {0};
	FILE *fp= NULL,
		 *ft= NULL;

	printf("\nEnter Roll No of Student to Delete Records: ");
	scanf(" %[^\n]s", user_id);

	ft= fopen("temp.txt", "a");
	if(search_student(user_id))
	{
		fp= fopen("student.txt", "r");
		while(fread(&student, sizeof(student_t), 1, fp) == 1)
		{
			if (!strcmp(user_id, student.user_id))
  			{
   				continue;
  			}
  			else
  			{
  				fwrite(&student, sizeof(student_t), 1, ft);
  			}
		}
		printf("Record Deleted Successfull.\n");
		fclose(fp);
		fclose(ft);
		system("rm student.txt");
		system("mv temp.txt student.txt");
	}
	else
	{
		printf("Student does not Exit.\n ");
	}
}




/*** Function to Search Faculty by User ID ***/
int search_faculty(char *user_id)
{
 	FILE *fp= NULL;
 	int c = 0;
 	
 	fp = fopen("faculty.txt", "r");
 	while (!feof(fp))
 	{
  		fread(&faculty, sizeof(faculty_t), 1, fp);

  		if (!strcmp(user_id, faculty.user_id))
  		{
   			fclose(fp);
   			return 1; //on success
  		}
 	}
 	fclose(fp);
 	return 0; //on Failure
}

/*** Display Staff Members Details ***/
int display_staff_member()
{
 	FILE *fp= NULL;
 	memset(&faculty, 0, sizeof(faculty_t));
 	fp = fopen("faculty.txt", "r");
 	printf("\n\n");
 	printf("______________________________________________________________________________________________________________\n");
 	printf("%-10s %-25s %-15s %-25s %-15s %-10s\n", "User ID", "Name", "Department", "Email ID", "Designation", "Password");
 	printf("______________________________________________________________________________________________________________\n");
 	while (fread(&faculty, sizeof(faculty_t), 1, fp))
 	printf("%-10s %-25s %-15s  %-25s %-15s %-10s\n", faculty.user_id, faculty.name, faculty.department, faculty.email, faculty.designation, faculty.password);
 	if(strlen(faculty.user_id) == 0)
 	{
 		printf("Faculty List is Empty.\n");
 	}
 	printf("______________________________________________________________________________________________________________\n");
 	memset(&faculty, 0, sizeof(faculty_t));
 	fclose(fp);
}

/**** Function to add Staff Members ***/
int add_staff_member()
{
	int ret_val= 1,
		post= 0;
	FILE *fp;

	printf("Enter Staff Member Details.\n");
	 	
 	start: printf("Enter the User ID   :");
 	a: scanf(" %[^\n]s", faculty.user_id);
 	ret_val= search_faculty(faculty.user_id);
    if(ret_val == 1)
    {
    	printf("\nUser ID already exist. Try Again\n");
    	goto start;
    }
 	if(validate_user_id(faculty.user_id))
 	{
 		bzero(faculty.user_id, MAX_BUFFER);
 		printf("User ID : ");
 		goto a;
 	}

 	printf("Enter the Faculty Name      :");
 	b: scanf(" %[^\n]s", faculty.name);
 	if(validate_name(faculty.name))
 	{
 		bzero(faculty.name, MAX_BUFFER);
 		printf("Please Enter Correct Faculty Name : ");
 		goto b;
 	}

 	printf("Enter the Department      :");
 	scanf(" %[^\n]s", faculty.department);
 	
 	printf("Enter the Email      :");
 	scanf(" %[^\n]s", faculty.email);
 	
 	printf("Select Designation\n");
 	d: printf("\t\t1	: HOD\n\t\t2	: Faculty\n");
 	scanf("%d", &post);
 	if((post == 1) || (post ==2))
 	{
 		if(post == 1)
 		{
 			strcpy(faculty.designation, "HOD");
 		}
 		else
 		{
 			strcpy(faculty.designation, "FACULTY");
 		}

 	}
 	else
 	{
 		printf("Please Select Valid Designation");
 		goto d;
 	}

 	printf("Enter the Password     :");
 	c: scanf(" %[^\n]s", faculty.password);
 	if(validate_password(faculty.password))
 	{
 		bzero(faculty.password, MAX_BUFFER);
 		printf("Please Enter Correct Password : ");
 		goto c;
 	}
	fp = fopen("faculty.txt", "a");
 	fwrite(&faculty, sizeof(faculty_t), 1, fp);
 	fclose(fp);
 	printf("FACULTY ADDED SUCCESSFULLY\n");
 	display_staff_member();
}

void update_feedback_department(char *user_id, char *department)
{
	FILE *fp= NULL;
	memset(&feedback, 0, sizeof(feedback_t));

	fp = fopen("feedback.txt", "rb+");
  	while (fread(&feedback, sizeof(feedback_t), 1, fp) == 1)
  	{
  		if(!strcmp(user_id, feedback.faculty_user_id))
  		{
  			bzero(feedback.department, MAX_BUFFER);
  			strcpy(feedback.department, department);
  			fseek(fp, -size_feedback, 1) ;
    		fwrite(&feedback, sizeof(feedback_t), 1, fp);
  		}
  		memset(&feedback, 0, sizeof(feedback_t));
  	}
  	fclose(fp);
}

void delete_feedback_record(char *user_id)
{
	FILE *fp= NULL,
		 *ft= NULL;

	memset(&feedback, 0, sizeof(feedback_t));
	
	ft= fopen("feedtemp.txt", "a");
	fp= fopen("feedback.txt", "r");
	while(fread(&feedback, sizeof(feedback_t), 1, fp) == 1)
	{
		if (!strcmp(user_id, feedback.faculty_user_id))
  		{
   			continue;
  		}
  		else
  		{
  			fwrite(&feedback, sizeof(feedback_t), 1, ft);
  		}
  		memset(&feedback, 0, sizeof(feedback_t));
	}
	fclose(fp);
	fclose(ft);
	system("rm feedback.txt");
	system("mv feedtemp.txt feedback.txt");
}

/*** Function to Update Student ***/
int update_staff_member()
{
 	char user_id[MAX_BUFFER]= {0},
 		 temp_user_id[MAX_BUFFER]= {0};

 	FILE *fp= NULL;
 	
 	int ret_val=0,
 		choice= 0,
 		update_flag= 0,
 		post= 0;

 	memset(&faculty, 0, sizeof(faculty_t));
 	start: printf("Enter Faculty User ID to update:");
 	scanf(" %[^\n]s", user_id);
 	ret_val = search_faculty(user_id);
 	if (ret_val == 0)
	{
  		printf("Faculty ID %s does not Exists\n", user_id);
  		goto start;
 	}
 	else
 	{
  		fp = fopen("faculty.txt", "rb+");
  		while (fread(&faculty, sizeof(faculty_t), 1, fp))
  		{
  			ret_val= strcmp(user_id, faculty.user_id);
   			if (!ret_val)
   			{
   				update_flag= TRUE;

    			printf("\n\t1. Update Name of Faculty");
    			printf("\n\t2. Update Email of Faculty");
    			printf("\n\t3. Update Department of Faculty");
    			printf("\n\t4. Update Password of Faculty");
    			printf("\n\t5. Update Designation");
    			printf("\nEnter your choice :");
    			scanf("%d", &choice);
    			switch (choice)
    			{
    				case 1:
    			 		printf("Enter New Name :");
    			 		a: scanf(" %[^\n]s", faculty.name);
    			 		if(validate_name(faculty.name))
 						{
 							bzero(faculty.name, MAX_BUFFER);
 							printf("Please Enter Correct Faculty Name : ");
 							goto a;
 						}
    			 		break;
    				
    				case 2:
    			 		printf("Enter New Email ID: ");
    			 		scanf(" %[^\n]s", faculty.email);
    			 		break;
    				
    				case 3:
    			 		printf("Enter new Department of Faculty : ");
    			 		scanf(" %[^\n]s", faculty.department);
    			 		update_feedback_department(faculty.user_id, faculty.department);
    			 		break;

    			 	case 4:
    			 		printf("Enter new Password : ");
    			 		b: scanf(" %[^\n]s", faculty.password);
    			 		if(validate_password(faculty.password))
 						{
 							bzero(faculty.password, MAX_BUFFER);
 							printf("Please Enter Valid Password : ");
 							goto b;
 						}
    			 		break;

    				case 5:
    					printf("Select New Designation\n");
 						d: printf("\t\t1	: HOD\n\t\t2	: Faculty\n");
 						scanf("%d", &post);
 						if((post == 1) || (post ==2))
 						{
 							if(post == 1)
 							{
 								strcpy(faculty.designation, "HOD");
 							}
 							else
 							{
 								strcpy(faculty.designation, "FACULTY");
 							}
 						}
 						else
 						{
 							printf("Please Select Valid Designation");
 							goto d;
 						}
 						break;

    				default:
    			 		printf("Invalid Selection");
    			 		break;
    			}
    			fseek(fp, -size_faculty, 1) ;
    			fwrite(&faculty, sizeof(faculty_t), 1, fp);
    			fclose(fp);
    			break;
   			}
  		}
  		if(TRUE == update_flag)
  		{
  			printf("RECORD UPDATED SUCCESSFULLY\n");
  			display_staff_member();
  		}
 	}
}

/*** Function to Delete Student Record ***/
int delete_staff_member()
{
	char user_id[MAX_BUFFER]= {0};
	FILE *fp= NULL,
		 *ft= NULL;

	memset(&faculty, 0, sizeof(faculty_t));
	printf("\nEnter User ID of Faculty to Delete Records: ");
	scanf(" %[^\n]s", user_id);
	
	ft= fopen("temp.txt", "a");
	if(search_faculty(user_id))
	{

		fp= fopen("faculty.txt", "r");
		while(fread(&faculty, sizeof(faculty_t), 1, fp) == 1)
		{
			if (!strcmp(user_id, faculty.user_id))
  			{
   				continue;
  			}
  			else
  			{
  				fwrite(&faculty, sizeof(faculty_t), 1, ft);
  			}
  			memset(&faculty, 0, sizeof(faculty_t));
		}
		printf("Record Deleted Successfull.\n");
		fclose(fp);
		fclose(ft);
		system("rm faculty.txt");
		system("mv temp.txt faculty.txt");
		delete_feedback_record(user_id);
	}
	else
	{
		printf("Faculty does not Exit.\n ");
	}
}

void view_feedback_data()
{
	int count= 1,
		display_flag= 0;;

	FILE *fp= NULL,
		 *ft= NULL;

	fp= fopen("feedback.txt", "r");
	ft= fopen("faculty.txt", "r");
	memset(&feedback, 0, sizeof(feedback_t));
	while(fread(&feedback, sizeof(feedback_t), 1, fp) == 1)
	{
		display_flag= 1;
		while(fread(&faculty, sizeof(faculty_t), 1, ft) == 1)
		{
			if(!strcmp(faculty.user_id, feedback.faculty_user_id))
			{
				goto b;
			}
		}
		b: printf("\nS.No. %d\n",count++);
		printf("___________________________________________________________________\n");
		printf("\n");
		printf("  Faculty     : %s  \n", faculty.name);
		printf("  Department  : %s  \n", feedback.department);
		printf("  Course      : %s  \n", feedback.course);
		printf("  Subject     : %s  \n", feedback.subject);
		printf("___________________________________________________________________\n");
		printf("   Encouraged               | %.2f \n", feedback.encouraged);
		printf("   Excited About Ideas      | %.2f \n", feedback.excited_about_ideas);
		printf("   Confused/Nervous         | %.2f \n", feedback.confused_or_nervous);
		printf("   Confident                | %.2f \n", feedback.confident);
		printf("   Resistant to Take Advise | %.2f \n", feedback.resistant_to_take_advice);
		printf("   Appreciative             | %.2f \n", feedback.appreciative);
		printf("   Energetic                | %.2f \n", feedback.energetic);
		printf("   Teaching Skills          | %.2f \n", feedback.teaching_skills);
		printf("   Punctuality              | %.2f \n", feedback.punctuality);
		printf("   Interaction              | %.2f \n", feedback.interaction);
		//printf("   Comments               | %s   \n", feedback.comments);
		printf("____________________________|_____________________________________\n\n\n");
		fseek(ft, 0, SEEK_SET);
		memset(&feedback, 0, sizeof(feedback_t));
		memset(&faculty, 0, sizeof(faculty_t));	
	}
	if(display_flag == 0)
	{
		printf("No Feedback Data Found\n");
	}
	fclose(fp);
	fclose(ft);
}

int student_module()
{
	char ch;

	int ret_val = 0,
		choice= 0;

	FILE *fp= NULL;

	ret_val= student_login();
	if(!ret_val)
	{
		start: system("clear");
		printf("\n*******************************************************************************************");
		printf("\n*                                                                                         *");
		printf("\n*                                     STUDENT  MODULE                                     *");
		printf("\n*                                                                                         *");
		printf("\n*******************************************************************************************");
	    printf("\nSelect Desired Option: \n");
		printf("1	:	Update Email\n");
		printf("2	:	Update Password\n");
		printf("3	:	View Faculty Department\n");
		printf("4	:	Submit Faculty Feedback\n");
		printf("Choice : ");
		scanf("%d", &choice);
		switch(choice)
		{

			case 1:
    			printf("\nEnter new Email ID : ");
    			scanf(" %[^\n]s", student.email);
    			fp = fopen("student.txt", "rb+");
    			fseek(fp, -size_student, 1) ;
    			fwrite(&student, sizeof(student_t), 1, fp);
    			fclose(fp);
    			goto valid;

    	 	case 2:
    			printf("\nEnter new Password : ");
    			b: scanf(" %[^\n]s", student.password);
    			if(validate_password(student.password))
 				{
 					bzero(faculty.password, MAX_BUFFER);
 					printf("Please Enter Valid Password : ");
 					goto b;
 				}
 				fp = fopen("student.txt", "rb+");
 				fseek(fp, -size_student, 1) ;
    			fwrite(&student, sizeof(student_t), 1, fp);
    			fclose(fp);
    			goto valid;

    		case 3:
    			view_faculty_department(student.department);
    			goto valid;

    		case 4:
    			submit_feedback(student.user_id, student.department, student.course);
    			goto valid;

    		default:
    			printf("Invalid Selection of Choice. Please Select Valid Choice.\n");
    			goto start;
    	}
    	valid: printf("\n\nPress\n1 : Continue\n2 : Logout\n");
    	scanf("%c", &ch);
    	printf("Choice : ");
    	scanf("%c", &ch);
    	if(ch == '1')
    	{
    		goto start;
    	}
    	else if(ch == '2')
    	{

    	}
    	else
    	{
    		printf("Please Select Valid Choice.\n");
    		goto valid;
    	}
	}
}

int student_login()
{

	char user_id[MAX_BUFFER] = {0},
		 password[MAX_BUFFER] = {0};

	int user_flag= 0,
		password_flag= 0;

	FILE *fp = NULL;
	

	printf("\nPlease provide Login Credentials...\n");
	printf("Roll No : ");
	a: scanf(" %[^\n]s", user_id);

	fp= fopen("student.txt", "r");
	while(fread(&student, sizeof(student_t), 1, fp) == 1)
	{
	  	if(!strcmp(user_id, student.user_id) )
		{
			user_flag= TRUE;
			printf("Password : ");
			b: scanf(" %[^\n]s", password);
			if(!strcmp(password, student.password))
			{
				printf("Login Successfull.\n");
				fclose(fp);
				return 0;
			}
			else
			{
				printf("Wrong Password\nPlease Enter Correct Password : ");
				goto b;
			}
		}
		
	}
	if(0 == user_flag)
	{
		fclose(fp);
		printf("Wrong Roll No.\nPlease Enter Correct Roll No.: ");
		goto a;
	}
	return 1;
} 

int view_faculty_department(char *department)
{
	FILE *fp= NULL;

	fp= fopen("faculty.txt", "r");
	printf("\n\n");
	printf("           *** FACULTY DEPARTMENTS ***\n");
	printf("________________________________________________\n");
	printf("%-20s %s\n", "Name", "Department");
	printf("________________________________________________\n");
 	while (fread(&faculty, sizeof(faculty_t), 1, fp))
 	{
 		if(!strcmp(department, faculty.department))
 		{
 			printf("%-20s %s\n", faculty.name, faculty.department);
 		}
 	}
	printf("________________________________________________\n"); 	
 	fclose(fp);
}

int submit_feedback(char *student_user_id, char *department, char *course)
{
	char faculty_name[MAX_BUFFER]= {0},
		 subject[MAX_BUFFER]= {0},
		 buffer[MAX_BUFFER]= {0};
	
	int index= 0,
		ret_val= 1,
		faculty_flag= 0,
		valid_faculty= 0;

	memset(&feedback, 0, sizeof(feedback_t));

	FILE *fp= NULL,
		 *feed= NULL;

	printf("\n\n");
	view_faculty_department(department);
	memset(&faculty,0, sizeof(faculty_t));
	printf("\nEnter the name of Faculty to submit feedback : ");	
	a: scanf(" %[^\n]s", faculty_name);
	fp= fopen("faculty.txt", "r");
	while(fread(&faculty, sizeof(faculty_t), 1, fp) == 1)
	{
		if(!strcmp(department, faculty.department))
		{
			faculty_flag= TRUE;
			if(!strcmp(faculty_name, faculty.name))
			{
				printf("\nPlease Enter Subject Name to submit feedback:");
				scanf(" %[^\n]s", subject);
				valid_faculty= TRUE;
				strcpy(feedback.student_user_id, student_user_id);
				strcpy(feedback.faculty_user_id, faculty.user_id);
				strcpy(feedback.department, department);
				strcpy(feedback.course, course);
				for(index= 0; index< strlen(subject); index++)
				{
					buffer[index]= toupper(subject[index]);
				}
				strcpy(feedback.subject, buffer);
				printf("\nPlease Provide Rating on a Scale of 0-5\n");
				b: printf("\nReady to try new things: ");
				scanf(" %f", &(feedback.ready_to_try_new_things));
				if((feedback.ready_to_try_new_things < 0) || (feedback.ready_to_try_new_things > 5))
				{
					printf("Rating should be between 0-5\n");
					goto b;
				}
				
				c: printf("\nEncouraged : ");
				scanf("%f", &(feedback.encouraged));
				if((feedback.encouraged < 0) || (feedback.encouraged > 5))
				{
					printf("Rating should be between 0-5\n");
					goto c;
				}

				d: printf("\nExcited about Ideas : ");
				scanf("%f", &(feedback.excited_about_ideas));
				if((feedback.excited_about_ideas < 0) || (feedback.excited_about_ideas > 5))
				{
					printf("Rating should be between 0-5\n");
					goto d;
				}

				e: printf("\nConfused/Nervous : ");
				scanf("%f", &(feedback.confused_or_nervous));
				if((feedback.confused_or_nervous < 0) || (feedback.confused_or_nervous > 5))
				{
					printf("Rating should be between 0-5\n");
					goto e;
				}

				f: printf("\nConfident : ");
				scanf("%f", &(feedback.confident));
				if((feedback.confident < 0) || (feedback.confident > 5))
				{
					printf("Rating should be between 0-5\n");
					goto f;
				}

				g: printf("\nResistant to take Advice : ");
				scanf("%f", &(feedback.resistant_to_take_advice));
				if((feedback.resistant_to_take_advice < 0) || (feedback.resistant_to_take_advice > 5))
				{
					printf("Rating should be between 0-5\n");
					goto g;
				}

				h: printf("\nAppreciative : ");
				scanf("%f", &(feedback.appreciative));
				if((feedback.appreciative < 0) || (feedback.appreciative > 5))
				{
					printf("Rating should be between 0-5\n");
					goto h;
				}

				i: printf("\nEnergenetic : ");
				scanf("%f", &(feedback.energetic));
				if((feedback.energetic < 0) || (feedback.energetic > 5))
				{
					printf("Rating should be between 0-5\n");
					goto i;
				}

				j: printf("\nTeaching Skills : ");
				scanf("%f", &(feedback.teaching_skills));
				if((feedback.teaching_skills < 0) || (feedback.teaching_skills > 5))
				{
					printf("Rating should be between 0-5\n");
					goto j;
				}

				k: printf("\nPunctuality : ");
				scanf("%f", &(feedback.punctuality));
				if((feedback.punctuality < 0) || (feedback.punctuality > 5))
				{
					printf("Rating should be between 0-5\n");
					goto k;
				}

				l: printf("\nInteraction : ");
				scanf("%f", &(feedback.interaction));
				if((feedback.interaction < 0) || (feedback.interaction > 5))
				{
					printf("Rating should be between 0-5\n");
					goto l;
				}

				m: printf("\nComments\n");
				scanf(" %[^\n]s", feedback.comments);
				if(validate_comments(feedback.comments))
				{
					bzero(feedback.comments, MAX_LIMIT);
					goto m;
				}
				feed = fopen("feedback.txt", "a");
				fwrite(&feedback, sizeof(feedback_t), 1, feed);
 				fclose(feed);
			}
		}
	}
	if(0 == valid_faculty)
	{
		printf("Please Provide Correct Name of Faculty: ");
		goto a;
	}
	if(0 == faculty_flag)
	{
		printf("Faculty Not Found.\n");

	}
}

/*** FACULTY CONTROL FUNCTION ***/
int faculty_module()
{
	printf("\n");

	char ch;

	int ret_val = 0,
		count= 1,
		choice= 0,
		display_flag= 0;

	FILE *fp= NULL;
	memset(&faculty, 0, sizeof(faculty_t));
	ret_val= faculty_login();
	if(!ret_val)
	{
		start: system("clear");
		printf("\n*******************************************************************************************");
		printf("\n*                                                                                         *");
		printf("\n*                                     FACULTY  MODULE                                     *");
		printf("\n*                                                                                         *");
		printf("\n*******************************************************************************************");
	    printf("\nSelect Desired Choice\n");
		printf("\nPress 1 : To View Submitted Feedback");
		printf("\nPress 2 : To Logout\n");
		printf("Choice : ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1: 
				count= 1;
				fp= fopen("feedback.txt", "r");
				memset(&feedback, 0, sizeof(feedback_t));
				while(fread(&feedback, sizeof(feedback_t), 1, fp) == 1)
				{
					if(!strcmp(faculty.user_id, feedback.faculty_user_id))
					{
						display_flag= 1;

						printf("\nS.No. %d\n",count++);
						printf("___________________________________________________________________\n");
						printf("\n");
						printf("  Department  : %s  \n", feedback.department);
						printf("  Course      : %s  \n", feedback.course);
						printf("  Subject     : %s  \n", feedback.subject);
						printf("___________________________________________________________________\n");
						printf("   Encouraged               | %.2f \n", feedback.encouraged);
						printf("   Excited About Ideas      | %.2f \n", feedback.excited_about_ideas);
						printf("   Confused/Nervous         | %.2f \n", feedback.confused_or_nervous);
						printf("   Confident                | %.2f \n", feedback.confident);
						printf("   Resistant to Take Advise | %.2f \n", feedback.resistant_to_take_advice);
						printf("   Appreciative             | %.2f \n", feedback.appreciative);
						printf("   Energetic                | %.2f \n", feedback.energetic);
						printf("   Teaching Skills          | %.2f \n", feedback.teaching_skills);
						printf("   Punctuality              | %.2f \n", feedback.punctuality);
						printf("   Interaction              | %.2f \n", feedback.interaction);
						//printf("|   Comments                 | %s                                                        |\n", feedback.comments);
						printf("____________________________|_____________________________________\n\n\n");
					}
					memset(&feedback, 0, sizeof(feedback_t));	
				}
				if((strlen(feedback.faculty_user_id) == 0) && (display_flag == 0))
				{
					printf("No Feedback Data Found for %s.\n", faculty.name);
				}
				fclose(fp);
				valid: printf("\n\nPress\n1 : Continue\n2 : Logout\n");
    			scanf("%c", &ch);
    			scanf("%c", &ch);
    			if(ch == '1')
    			{
    				goto start;
				}
				else if(ch == '2')
				{

				}
				else
				{
					printf("\nPlease Select Valid Choice.\n");
					goto valid;
				}
				break;

			case 2:
				break;

			default:
				printf("Invalid Selection of Choice. Please Try Agrain\n");
				goto start;
		}
	}
}

/*** FACULTY LOGIN FUNCTION ***/
int faculty_login()
{

	char user_id[MAX_BUFFER] = {0},
		 password[MAX_BUFFER] = {0};

	int user_flag= 0,
		password_flag= 0;

	FILE *fp = NULL;
	
	memset(&faculty, 0, sizeof(faculty_t));
	printf("Please provide Login Credentials...\n");
	printf("User ID : ");
	a: scanf(" %[^\n]s", user_id);

	fp= fopen("faculty.txt", "r");
	while(fread(&faculty, sizeof(faculty_t), 1, fp) == 1)
	{
	  	if(!strcmp(user_id, faculty.user_id) )
		{
			user_flag= TRUE;
			printf("Password : ");
			b: scanf(" %[^\n]s", password);
			if(!strcmp(password, faculty.password))
			{
				printf("Login Successfull.\n");
				fclose(fp);
				return 0;
			}
			else
			{
				printf("Wrong Password\nPlease Enter Correct Password : ");
				goto b;
			}
		}
		
	}
	if(0 == user_flag)
	{
		fclose(fp);
		printf("Wrong User ID\nPlease Enter Correct User ID: ");
		goto a;
	}
	return 1;
} 

/*** HOD CONTROL FUNCTION ***/
int hod_module()
{
	char ch,
		 dept[MAX_BUFFER]={0};

	int ret_val = 0,
		count= 1,
		choice= 0,
		display_flag= 0;

	FILE *fp= NULL,
		 *ft= NULL;

	memset(&faculty, 0, sizeof(faculty_t));
	ret_val= hod_login();
	if(!ret_val)
	{
		printf("Login Successfull.\n");
		start: system("clear");
		printf("\n*******************************************************************************************");
		printf("\n*                                                                                         *");
		printf("\n*                                     HOD  MODULE                                         *");
		printf("\n*                                                                                         *");
		printf("\n*******************************************************************************************");
		
		strcpy(dept, faculty.department);
		memset(&faculty, 0, sizeof(faculty_t));
		printf("\nSelect Desired Choice\n");
		printf("\nPress 1 : To View Submitted Feedback");
		printf("\nPress 2 : To Logout\n\n");
		printf("Choice : ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1: 
				count= 1;
				fp= fopen("feedback.txt", "r");
				ft= fopen("faculty.txt", "r");
				memset(&feedback, 0, sizeof(feedback_t));
				while(fread(&feedback, sizeof(feedback_t), 1, fp) == 1)
				{
					if(!strcmp(dept, feedback.department))
					{
						display_flag= 1;

						while(fread(&faculty, sizeof(faculty_t), 1, ft) == 1)
						{
							if((!strcmp(faculty.user_id, feedback.faculty_user_id)) && (!strcmp(dept, faculty.department)))
							{
								goto b;
							}
						}
						b: printf("   S.No. %d\n",count++);
						printf("___________________________________________________________________\n");
						printf("\n");
						printf("  Faculty     : %s  \n", faculty.name);
						printf("  Department  : %s  \n", feedback.department);
						printf("  Course      : %s  \n", feedback.course);
						printf("  Subject     : %s  \n", feedback.subject);
						printf("___________________________________________________________________\n");
						printf("   Encouraged               | %.2f \n", feedback.encouraged);
						printf("   Excited About Ideas      | %.2f \n", feedback.excited_about_ideas);
						printf("   Confused/Nervous         | %.2f \n", feedback.confused_or_nervous);
						printf("   Confident                | %.2f \n", feedback.confident);
						printf("   Resistant to Take Advise | %.2f \n", feedback.resistant_to_take_advice);
						printf("   Appreciative             | %.2f \n", feedback.appreciative);
						printf("   Energetic                | %.2f \n", feedback.energetic);
						printf("   Teaching Skills          | %.2f \n", feedback.teaching_skills);
						printf("   Punctuality              | %.2f \n", feedback.punctuality);
						printf("   Interaction              | %.2f \n", feedback.interaction);
						//printf("|   Comments                 | %s                                                        |\n", feedback.comments);
						printf("____________________________|_____________________________________\n\n\n");
					
						fseek(ft, 0, SEEK_SET);
						memset(&feedback, 0, sizeof(feedback_t));
						memset(&faculty, 0, sizeof(faculty_t));
					}	
				}
				if(display_flag == 0)
				{
					printf("No Feedback Data Found for Department '%s'.\n", dept);
				}
				fclose(fp);
				fclose(ft);
				valid: printf("\n\nPress\n1 : Continue\n2 : Logout\n");
    			scanf("%c", &ch);
    			scanf("%c", &ch);
    			if(ch == '1')
    			{
    				goto start;
				}
				else if(ch == '2')
				{
					break;
				}
				else
				{
					printf("\nPlease Select Valid Choice.\n");
					goto valid;
				}

			case 2:
				break;

			default:
				printf("Invalid Selection of Choice. Please Try Again\n");
				goto start;
		}
	}
}

/*** FUNCTION FOR HOD LOGIN ***/
int hod_login()
{
	char user_id[MAX_BUFFER] = {0},
		 password[MAX_BUFFER] = {0};

	int user_flag= 0,
		password_flag= 0;

	FILE *fp = NULL;
	
	memset(&faculty, 0, sizeof(faculty_t));
	printf("\nPlease provide Login Credentials...\n");
	printf("User ID : ");
	a: scanf(" %[^\n]s", user_id);

	fp= fopen("faculty.txt", "r");
	while(fread(&faculty, sizeof(faculty_t), 1, fp) == 1)
	{
	  	if(!strcmp(user_id, faculty.user_id))
		{
			if(!strcmp(faculty.designation,"HOD"))
			{
				user_flag= TRUE;
				printf("Password : ");
				b: scanf(" %[^\n]s", password);
				if(!strcmp(password, faculty.password))
				{
					fclose(fp);
					return 0;
				}
				else
				{
					printf("Wrong Password\nPlease Enter Correct Password : ");
					goto b;
				}
			}
			else
			{
				printf("Insufficient Permission to Login\n");
				return 1;
			}	
		}
		
	}
	if(0 == user_flag)
	{
		fclose(fp);
		printf("Wrong User ID\nPlease Enter Correct User ID: ");
		goto a;
	}
	return 1;
} 

/*** MAIN DRIVER FUNCTION ***/
int main()
{
	char ch,
		choice;
	

	while(TRUE)
	{
		start: system("clear");
		printf("\n****************************************************************");
		printf("\n*                                                              *");
		printf("\n*              Student Feedback Management                     *");
		printf("\n*                                                              *");
		printf("\n****************************************************************");
		printf("\n\nPlease Select Desired Choice\n\n");
		printf("1 : Admin Login\n");
		printf("2 : Student Login\n");
		printf("3 : Faculty Login\n");
		printf("4 : HOD Login\n");
		printf("5 : Exit\n");
		printf("Choice : ");
		scanf("%c", &choice);
		if(choice >=48 && choice <=57)
		{
			switch(atoi(&choice))
			{
				case ADMIN:	
					admin_module();
					memset(&student, 0, sizeof(student_t));
					memset(&faculty, 0, sizeof(faculty_t));
					memset(&feedback, 0, sizeof(feedback_t));
					goto start;

				case STUDENT:
					student_module();
					memset(&student, 0, sizeof(student_t));
					memset(&faculty, 0, sizeof(faculty_t));
					memset(&feedback, 0, sizeof(feedback_t));
					goto start;

				case FACULTY:
					faculty_module();
					memset(&student, 0, sizeof(student_t));
					memset(&faculty, 0, sizeof(faculty_t));
					memset(&feedback, 0, sizeof(feedback_t));
					goto start;

				case HOD:
					hod_module();
					memset(&student, 0, sizeof(student_t));
					memset(&faculty, 0, sizeof(faculty_t));
					memset(&feedback, 0, sizeof(feedback_t));
					goto start;

				case EXIT:
					memset(&student, 0, sizeof(student_t));
					memset(&faculty, 0, sizeof(faculty_t));
					memset(&feedback, 0, sizeof(feedback_t));
					return 0;

				default: 
					printf("Please Enter Valid Choice...!!\n\n");
					goto start;
			}
		}
	}
}