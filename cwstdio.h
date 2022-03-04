#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define SUBJECT_SUM 5

// 열거형 상수 : 성적관리 주 메뉴 선택 사용
enum MAIN_MENU { END, READ, PRINT, EDIT, WRITE };
enum MAIN_MENU main_select;

//열거형 상수 : 성적관리 부 메뉴 선택 사용
enum EDIT_MENU { EXIT, PREV, NEXT, INSERT, MODIFY, DELETE, SEARCH };
enum EDIT_MENU edit_select;

void read_student_data(); // student_data.txt 파일에서 데이터 읽어오기
void write_student_data(); // student_data.txt 파일의 데이터 저장하기
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

	struct STUDENT* prev; //struct STUDENT 가르키는 포인터변수 (앞 구조체)
	struct STUDENT* next; //struct STUDENT 가르키는 포인터변수 (뒤 구조체)
}STUDENT_t;


STUDENT_t* head = NULL;     //이중연결리스트 시작노드저장
STUDENT_t* current = NULL;  //현재화면에 표시되는 노드저장

//패턴 1 head 생성하기
void initialize_student() {
	head = (STUDENT_t*)calloc(1, sizeof(STUDENT_t));
	if (head == NULL) {
		puts("힙영역에 STUDENT 구조체 생성 실패");
		getchar();
	}
	return;
}

//패턴 2 노드 추가하기(처음 추가하기 , 마지막추가하기)
void append_node(STUDENT_t* data) {
	STUDENT_t* p = head;

	//next NULL 인 마지막 노드로 이동
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = data;

	//추가된 node에서 바로 앞 node 가르킴.
	if (p != head) {
		data->prev = p;
	}
	return;
}

//패턴 3 노드 출력하기
void print_student_data() {
	STUDENT_t* p = head;

	if (p == NULL) {
		puts("출력할 데이타가 없습니다.");
		return;
	}

	puts("=====================================================================");
	puts("이름\t학번\t성별\t\t성적\t\t총점\t평균\t등급");
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
		printf("출력할 STUDENT 구조체가 없습니다.");
		getchar();
		return;
	}
	puts("================================");
	printf("%14s [%s] \n ", "이름", current->name);
	printf("%14s [%4d] \n ", "학번", current->id);
	printf("%14s [%s] \n ", "성별", current->gender);
	printf("%14s [%3d] \n ", "자바", current->java);
	printf("%14s [%3d] \n ", "안드로이드", current->android);
	printf("%14s [%3d] \n ", "코틀린", current->kotlin);
	printf("%14s [%3d] \n ", "리액트", current->react_native);
	printf("%14s [%3d] \n ", "자바스크립트", current->javascript);
	printf("%14s [%3d] \n ", "총점", current->total);
	printf("%14s [%5.2lf] \n ", "평균", current->avr);
	printf("%14s [%c] \n ", "등급", current->grade);
	puts("================================");


	return;
}

STUDENT_t* new_student_data() {
	STUDENT_t* data = (STUDENT_t*)calloc(1, sizeof(STUDENT_t));
	int flag_id = 0;

	if (data == NULL) {
		puts("힙 영역에 STUDENT 구조체 입력 실패");
		getchar();
		return NULL;
	}

	printf("================================\n");
	printf("%14s :  ", "이름");
	scanf_s("%s", data->name, sizeof(data->name));

	// id 중복 체크 기능
	while (!flag_id) {
		printf("%14s :  ", "학번(1000-9999) ");
		scanf_s("%d", &data->id, sizeof(data->id));

		if (check_id(data->id != 0)) {
			puts("기존 학번이 존재합니다.");
			continue;
		}
		flag_id = 1; // == break;
	}

	printf("%14s :  ", "성별");
	scanf_s("%s", data->gender, sizeof(data->gender));

	data->java = input_score("자바");
	data->android = input_score("안드로이드");
	data->kotlin = input_score("코틀린");
	data->react_native = input_score("리액트네이티브");
	data->javascript = input_score("자바스크립트");

	data->total = data->java + data->android + data->kotlin + data->react_native + data->javascript;
	data->avr = data->total / (double)SUBJECT_SUM;
	data->grade = make_grade(data->avr);

	return data;
}

void update_student_data(STUDENT_t* current) {

	if (current == NULL) {
		puts("수정할 STUDENT 구조체 존재 X");
		getchar();
		return NULL;
	}

	printf("================================\n");

	current->java = input_score("수정 자바");
	current->android = input_score("수정 안드로이드");
	current->kotlin = input_score("수정 코틀린");
	current->react_native = input_score("수정 리액트네이티브");
	current->javascript = input_score("수정 자바스크립트");

	current->total = current->java + current->android + current->kotlin + current->react_native + current->javascript;
	current->avr = current->total / (double)SUBJECT_SUM;
	current->grade = make_grade(current->avr);

	return;
}

STUDENT_t* search_student_data() {
	STUDENT_t* p = head;
	STUDENT_t* data = NULL;

	int id = 0;

	printf("학생 번호(1000-9999) 입력: ");
	scanf("%d", &id);

	while (p->next != NULL) {
		p = p->next;
		if (p->id == id) {
			data = p;
			break;
		}
	}

	if (data == NULL) {
		puts("해당되는 id[%4d]는 없습니다.", id);
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
			printf("%s 점수(0 -100) 입력하세요.\n", subject);
			continue;
		}
		input_flag = 1; // == break;
	} // end of while

	return score;
	//   printf("%14s :  ", "자바(0-100) ");
	//scanf_s("%d", &data->java, sizeof(data->java)); 를 함수로 만든 것
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

	//next NULL 인 마지막 노드로 이동
	while (p->next != NULL) {
		p = p->next;
		if (p->id == id) {
			find_id = p->id;
			break;
		}
	}

	return find_id;
}