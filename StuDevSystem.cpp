#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
using namespace std;
#define N 2000

struct Student
{
	char name[N];
	long int ID;
	char major[N];
	float score;
	char career[N];
	Student *next;
};

Student head = { 0 };

void AddStudent(Student *ptr, int get)
{
	Student *p1 = head.next;
	Student *p2 = &head;
	switch (get)
	{
	case 1:
		while (p1 != NULL)
		{
			if (ptr->ID < p1->ID)
			{
				break;
			}
			p2 = p1;
			p1 = p1->next;
		}
		ptr->next = p2->next;
		p2->next = ptr;
		break;
	case 2:
		while (p1 != NULL)
		{
			if (ptr->score < p1->score)
			{
				break;
			}
			p2 = p1;
			p1 = p1->next;
		}
		ptr->next = p2->next;
		p2->next = ptr;
		break;
	default:
		cout << "You input the wrong number" << endl;
		break;
	}
}

void CreatStudent()
{
	void AddStudent(Student *ptr, int get);
	void ListStudent();
	cout << "How would you like to sort the information? <1:ID/2:score>" << endl;
	int get;
	cin >> get;
	char choice = 'y';
	while (choice == 'y')
	{
		Student *ptr = (Student*)malloc(sizeof(Student));
		cout << "Please input the name of the student" << endl;
		cin >> ptr->name;
		cout << "Please input the ID of the student" << endl;
		cin >> ptr->ID;
		cout << "Please input the major of the student" << endl;
		cin >> ptr->major;
		cout << "Please input the score of the student" << endl;
		cin >> ptr->score;
		cout << "Please input the career of the student" << endl;
		cin >> ptr->career;
		AddStudent(ptr, get);
		cout << "If you want to add again? <y/n>" << endl;
		choice = 'n';
		cin >> choice;
	}
	ListStudent();
}

void DelStudent()

{
	void ListStudent();
	char choice = 'y';
	while (choice == 'y')
	{
		cout << "Please input the ID of the student who you want to delete" << endl;
		long int DelID;
		cin >> DelID;
		int flag = 0;
		Student *p = &head;
		Student *ptr = head.next;
		while (ptr)
		{
			if (DelID == ptr->ID)
			{
				flag = 1;
				p->next = ptr->next;
				free(ptr);
				break;
			}
			p = ptr;
			ptr = ptr->next;
		}
		if (flag == 0)
		{
			cout << "There is not the student or you put the wrong ID" << endl;
		}
		cout << "If you want to delete again? <y/n>" << endl;
		choice = 'n';
		cin >> choice;
	}
	ListStudent();
}

void ListStudent()
{
	Student *p = head.next;
	if (p == NULL)
	{
		cout << "There is not a student" << endl;
	}
	else
	{
		cout << "name\t" << "ID\t\t" << "major\t\t" << "score\t\t" << "career\t\t" << endl;
		while (p)
		{
			cout << p->name << "\t" << p->ID << "\t" << p->major << "\t\t" << p->score << "\t\t" << p->career << "\t\t" << endl;
			p = p->next;
		}
	}
}

void SaveStudent()
{
	void ListStudent();
	FILE *SaveFile = fopen("StuDevInformation.txt", "w");
	if (SaveFile == NULL)
	{
		cout << "The file does not exist" << endl;
	}
	else
	{
		Student *ptr = head.next;
		while (ptr)
		{
			fprintf(SaveFile, "%s \t %ld \t\t %s \t\t %f \t\t %s \n", ptr->name, ptr->ID, ptr->major, ptr->score, ptr->career);
			ptr = ptr->next;
		}
		cout << "The file has saved successfully" << endl;
		ListStudent();
	}
}

void ReadStudent()
{
	void AddStudent(Student *ptr, int get);
	void ListStudent();
	cout << "How would you like to sort the information? <1:ID/2:score>" << endl;
	int get;
	cin >> get;
	FILE *ReadFile = fopen("StuDevInformation.txt", "r");
	if (ReadFile == NULL)
	{
		cout << "The file does not exist" << endl;
	}
	else
	{
		Student *p1 = &head;
		Student *p2 = head.next;
		while (p2)
		{
			p1 = p2;
			free(p1);
			p2 = p2->next;
		}
		while (!feof(ReadFile))
		{
			Student *ptr = (Student*)malloc(sizeof(Student));
			fscanf(ReadFile, "%s \t %ld \t\t %s \t\t %f \t\t %s \n", ptr->name, &ptr->ID, ptr->major, &ptr->score, ptr->career);
			AddStudent(ptr, get);
		}
		cout << "The information read successfully" << endl;
		ListStudent();
	}
}

void CheckStudent_1(int choice, Student *ptr)
{
	switch (choice)
	{
	case 1:
		cout << "The name of the student is" << endl;
		cout << ptr->name << endl;
		break;
	case 2:
		cout << "The ID of the student is" << endl;
		cout << ptr->ID << endl;
		break;
	case 3:
		cout << "The major of the student is" << endl;
		cout << ptr->major << endl;
		break;
	case 4:
		cout << "The score of the student is" << endl;
		cout << ptr->score << endl;
		break;
	case 5:
		cout << "The career of the student is" << endl;
		cout << ptr->career << endl;
		break;
	default:
		cout << "You input the wrong number" << endl;
		break;
	}
}

void CheckStudent()
{
	void CheckStudent_1(int choice, Student *ptr);
	Student *p = head.next;
	Student *ptr;
	cout << "Please input the ID of the student" << endl;
	long int ID;
	cin >> ID;
	if (p != NULL)
	{
		while (p != NULL && p->ID != ID)
		{
			p = p->next;
		}
		if (p != NULL)
		{
			ptr = p;
			cout << "What information do you want? <1:name/2:ID/3:major/4:score/5:career>" << endl;
			int choice;
			cin >> choice;
			CheckStudent_1(choice, ptr);
		}
		else
		{
			cout << "Have not got the student in the system" << endl;
		}
	}
	else
	{
		cout << "There is not a student in the system" << endl;
	}
}

void StaStudent()
{
	cout << "Statistics the student information. <1:the number of the students/2:the pass student>" << endl;
	int choice;
	cin >> choice;
	Student *p = head.next;
	int sum = 0;
	switch (choice)
	{
	case 1:
		while (p != NULL)
		{
			sum++;
			p = p->next;
		}
		cout << "The number of the students is " << sum << endl;
		break;
	case 2:
		while (p != NULL && p->score > 60)
		{
			sum++;
			p = p->next;
		}
		cout << "The number of the pass student is " << sum << endl;
		break;
	default:
		cout << "You input the wrong number" << endl;
		break;
	}
}

void MenuList()
{
	cout << "_____________________________________________________________________" << endl;
	cout << "|---------------Welcome to use Student Develop System---------------|" << endl;
	cout << "|-----------------Please input the following number-----------------|" << endl;
	cout << "|-----------------1:Add the student into the system-----------------|" << endl;
	cout << "|-----------------2:Delete the student in the system----------------|" << endl;
	cout << "|-----------------3:Show up the information-------------------------|" << endl;
	cout << "|-----------------4:Save the information of the students------------|" << endl;
	cout << "|-----------------5:Read the information of the students------------|" << endl;
	cout << "|---------------[(5):Only use it in the first step!]----------------|" << endl;
	cout << "|-----------------6:Check the information of the student------------|" << endl;
	cout << "|-----------------7:Statistics the student information--------------|" << endl;
	cout << "|-----------------8:Exit the system---------------------------------|" << endl;
	cout << "|___________________________________________________________________|" << endl;
}

int main()
{
	void CreatStudent();
	void DelStudent();
	void AddStudent(Student *ptr, int get);
	void ListStudent();
	void SaveStudent();
	void ReadStudent();
	void CheckStudent();
	void StaStudent();
	void MenuList();
	cout << "Welcome to use the Student Develop System" << endl;
	int choice = 1;
	while (choice != 0)
	{
		MenuList();
		cout << "Please input the right number" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: CreatStudent();
			break;
		case 2: DelStudent();
			break;
		case 3: ListStudent();
			break;
		case 4: SaveStudent();
			break;
		case 5: ReadStudent();
			break;
		case 6: CheckStudent();
			break;
		case 7: StaStudent();
			break;
		case 8: choice = 0;
			break;
		default: cout << "You input the wrong number" << endl;
			break;
		}
	}
	cout << "______________________________________________________" << endl;
	cout << "|----------------------------------------------------|" << endl;
	cout << "|------------------Thanks for using!-----------------|" << endl;
	cout << "|----------------------------------------------------|" << endl;
	cout << "|-----Designer:Ross----------From:BigData Class2-----|" << endl;
	cout << "|----------------------------------------------------|" << endl;
	cout << "|____________________________________________________|" << endl;
	return 0;
}
