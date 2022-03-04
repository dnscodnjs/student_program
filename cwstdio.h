#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define SUBJECT_SUM 5

// ������ ��� : �������� �� �޴� ���� ���
enum MAIN_MENU { END, READ, PRINT, EDIT, WRITE };
enum MAIN_MENU main_select;

//������ ��� : �������� �� �޴� ���� ���
enum EDIT_MENU { EXIT, PREV, NEXT, INSERT, MODIFY, DELETE, SEARCH };
enum EDIT_MENU edit_select;

void read_student_data(); // student_data.txt ���Ͽ��� ������ �о����
void write_student_data(); // student_data.txt ������ ������ �����ϱ�
char student_file_name[] = "student_data.txt";
void edit_student_data();
void update_student_data(STUDENT_t* current);


//STUDENT_t* search_student_data();
char make_grade(double avr);
int check_id(int id);


typedef struct STUDENT {
	char name[20];
	int id;
	char gender[5];
	int java;
	int android;
	int kotlin;
	int react_native;
	int javascript;
	int total;
	double avr;
	char grade;

	struct STUDENT* prev; //struct STUDENT ����Ű�� �����ͺ��� (�� ����ü)
	struct STUDENT* next; //struct STUDENT ����Ű�� �����ͺ��� (�� ����ü)
}STUDENT_t;


STUDENT_t* head = NULL;     //���߿��Ḯ��Ʈ ���۳������
STUDENT_t* current = NULL;  //����ȭ�鿡 ǥ�õǴ� �������

//���� 1 head �����ϱ�
void initialize_student() {
	head = (STUDENT_t*)calloc(1, sizeof(STUDENT_t));
	if (head == NULL) {
		puts("�������� STUDENT ����ü ���� ����");
		getchar();
	}
	return;
}

//���� 2 ��� �߰��ϱ�(ó�� �߰��ϱ� , �������߰��ϱ�)
void append_node(STUDENT_t* data) {
	STUDENT_t* p = head;

	//next NULL �� ������ ���� �̵�
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = data;

	//�߰��� node���� �ٷ� �� node ����Ŵ.
	if (p != head) {
		data->prev = p;
	}
	return;
}

//���� 3 ��� ����ϱ�
void print_student_data() {
	STUDENT_t* p = head;

	if (p == NULL) {
		puts("����� ����Ÿ�� �����ϴ�.");
		return;
	}

	puts("=====================================================================");
	puts("�̸�\t�й�\t����\t\t����\t\t����\t���\t���");
	puts("=====================================================================");

	while (p->next != NULL) {
		p = p->next;
		printf("%s\t%d\t%s\t%d %d %d %d %d\t%d\t%5.2lf\t%3c\n",
			p->name, p->id, p->gender, p->java, p->android,
			p->kotlin, p->react_native, p->javascript, p->total,
			p->avr, p->grade);
	}
	return;
}

void print_one_student_data(STUDENT_t* current) {
	if (current == NULL) {
		printf("����� STUDENT ����ü�� �����ϴ�.");
		getchar();
		return;
	}
	puts("================================");
	printf("%14s [%s] \n ", "�̸�", current->name);
	printf("%14s [%4d] \n ", "�й�", current->id);
	printf("%14s [%s] \n ", "����", current->gender);
	printf("%14s [%3d] \n ", "�ڹ�", current->java);
	printf("%14s [%3d] \n ", "�ȵ���̵�", current->android);
	printf("%14s [%3d] \n ", "��Ʋ��", current->kotlin);
	printf("%14s [%3d] \n ", "����Ʈ", current->react_native);
	printf("%14s [%3d] \n ", "�ڹٽ�ũ��Ʈ", current->javascript);
	printf("%14s [%3d] \n ", "����", current->total);
	printf("%14s [%5.2lf] \n ", "���", current->avr);
	printf("%14s [%c] \n ", "���", current->grade);
	puts("================================");


	return;
}

STUDENT_t* new_student_data() {
	STUDENT_t* data = (STUDENT_t*)calloc(1, sizeof(STUDENT_t));
	int flag_id = 0;

	if (data == NULL) {
		puts("�� ������ STUDENT ����ü �Է� ����");
		getchar();
		return NULL;
	}

	printf("================================\n");
	printf("%14s :  ", "�̸�");
	scanf_s("%s", data->name, sizeof(data->name));

	// id �ߺ� üũ ���
	while (!flag_id) {
		printf("%14s :  ", "�й�(1000-9999) ");
		scanf_s("%d", &data->id, sizeof(data->id));

		if (check_id(data->id != 0)) {
			puts("���� �й��� �����մϴ�.");
			continue;
		}
		flag_id = 1; // == break;
	}

	printf("%14s :  ", "����");
	scanf_s("%s", data->gender, sizeof(data->gender));

	data->java = input_score("�ڹ�");
	data->android = input_score("�ȵ���̵�");
	data->kotlin = input_score("��Ʋ��");
	data->react_native = input_score("����Ʈ����Ƽ��");
	data->javascript = input_score("�ڹٽ�ũ��Ʈ");

	data->total = data->java + data->android + data->kotlin + data->react_native + data->javascript;
	data->avr = data->total / (double)SUBJECT_SUM;
	data->grade = make_grade(data->avr);

	return data;
}

void update_student_data(STUDENT_t* current) {

	if (current == NULL) {
		puts("������ STUDENT ����ü ���� X");
		getchar();
		return NULL;
	}

	printf("================================\n");

	current->java = input_score("���� �ڹ�");
	current->android = input_score("���� �ȵ���̵�");
	current->kotlin = input_score("���� ��Ʋ��");
	current->react_native = input_score("���� ����Ʈ����Ƽ��");
	current->javascript = input_score("���� �ڹٽ�ũ��Ʈ");

	current->total = current->java + current->android + current->kotlin + current->react_native + current->javascript;
	current->avr = current->total / (double)SUBJECT_SUM;
	current->grade = make_grade(current->avr);

	return;
}

STUDENT_t* search_student_data() {
	STUDENT_t* p = head;
	STUDENT_t* data = NULL;

	int id = 0;

	printf("�л� ��ȣ(1000-9999) �Է�: ");
	scanf("%d", &id);

	while (p->next != NULL) {
		p = p->next;
		if (p->id == id) {
			data = p;
			break;
		}
	}

	if (data == NULL) {
		puts("�ش�Ǵ� id[%4d]�� �����ϴ�.", id);
		getchar();
		getchar();
	}
	return data;
}


int input_score(char* subject) {
	int score = 0;
	int input_flag = 0;
	while (!input_flag) {
		printf("%14s :  ", subject);
		scanf_s("%d", &score);
		if (score < 0 || score > 100) {
			printf("%s ����(0 -100) �Է��ϼ���.\n", subject);
			continue;
		}
		input_flag = 1; // == break;
	} // end of while

	return score;
	//   printf("%14s :  ", "�ڹ�(0-100) ");
	//scanf_s("%d", &data->java, sizeof(data->java)); �� �Լ��� ���� ��
}

char make_grade(double avr) {
	char grade = 0;

	if (avr >= 90) {
		grade = 'A';
	}
	else if (avr >= 80 && avr < 90) {
		grade = 'B';
	}
	else if (avr >= 70 && avr < 80) {
		grade = 'C';
	}
	else if (avr >= 60 && avr < 70) {
		grade = 'D';
	}
	else
		grade = 'F';

	return grade;
}

int check_id(int id) {
	int find_id = 0;
	STUDENT_t* p = head;

	//next NULL �� ������ ���� �̵�
	while (p->next != NULL) {
		p = p->next;
		if (p->id == id) {
			find_id = p->id;
			break;
		}
	}

	return find_id;
}