//열거형 상수 : 성적주 메뉴 선택 사용
enum MAIN_MENU { END, READ, PRINT, EDIT, WRITE };
enum MAIN_MENU main_select;

//열거형 상수 : 성적관리 부 메뉴 선택 사용
enum EDIT_MENU { EXIT, PREV, NEXT, INSERT, MODIFY, DELETE, SEARCH };
enum EDIT_MENU edit_select;

#include "cwstdio.h"

void read_student_data();   //student_data.txt 데이터 읽어오기
void write_student_data();  //student_data.txt 데이터 저장하기

char student_file_name[] = "student_data.txt";

int main()
{
	int flag = 0;
	initialize_student();   //연결리스트 head 생성

	while (!flag && head != NULL) {
		system("cls");
		puts("================================");
		puts("\t 성적 관리 프로그램 \t");
		puts("================================");
		puts("1.성적프로그램 파일에서 가져오기");
		puts("2.성적프로그램 현황보기");
		puts("3.성적프로그램 관리하기");
		puts("4.성적프로그램 파일에 저장하기");
		puts("0.종료");
		printf(">> ");
		scanf_s("%d", &main_select);
		getchar();

		switch (main_select) {
		case READ:
			read_student_data();
			getchar();
			break;
		case PRINT:
			print_student_data();
			getchar();
			break;
		case EDIT:
			edit_student_data();
			break;
		case WRITE:
			write_student_data();
			getchar();
			break;
		case END:
			flag = 1;
			break;
		default:
			puts("다시선택 하세요.~");
			getchar();
			break;
		}//end of switch

	}//end of while

	return 0;
}

void read_student_data() {
	STUDENT_t* data = NULL;
	FILE* file = NULL;
	int flag = 0;
	int count = 0;

	printf("읽어올 학생 정보 파일이름 입력 >> ");
	scanf_s("%s", student_file_name, sizeof(student_file_name));
	getchar();

	file = fopen(student_file_name, "rt");

	if (file == NULL) {
		printf("%s 파일을 읽지 못했습니다. \n", student_file_name);
		return;
	}

	while (!flag) {
		data = (STUDENT_t*)calloc(1, sizeof(STUDENT_t));
		int result = fscanf(file, "%s %d %s %d %d %d %d %d %d %lf %c",
			data->name, &data->id, data->gender, &data->java, &data->android,
			&data->kotlin, &data->react_native, &data->javascript, &data->total,
			&data->avr, &data->grade);

		if (result == EOF) {
			flag = 1;
			continue;
		}

		append_node(data);  //이중연결리스트 data 구조체 추가연결
		count++;

		printf("%s %d %s %d %d %d %d %d %d %5.2lf %c\n",
			data->name, data->id, data->gender, data->java, data->android,
			data->kotlin, data->react_native, data->javascript, data->total,
			data->avr, data->grade);
	}

	printf("%d 개의 데이터를 읽었습니다. ", count);
	fclose(file);
	getchar();

	return;
}


void write_student_data() {
	STUDENT_t* p = head;
	FILE* file = NULL;
	int count = 0;

	file = fopen(student_file_name, "wt");

	if (file == NULL) {
		printf("%s 파일을 저장하지 못했습니다. \n", student_file_name);
		return;
	}

	while (p->next != NULL) {
		p = p->next;
		int result = fprintf(file, "%s %d %s %d %d %d %d %d %d %lf %c\n",
			p->name, p->id, p->gender, p->java, p->android,
			p->kotlin, p->react_native, p->javascript, p->total,
			p->avr, p->grade);

		if (result == EOF) {
			printf("%s 파일을 저장도중에 문제가 발생했습니다. ", student_file_name);
			break;
		}
		count++;
	}

	printf("%d 개의 데이터를 저장했습니다. ", count);
	fclose(file);
	getchar();

	return;
}

//이전성적,다음성적,성적등록,성적수정,성적삭제,성적검색
void edit_student_data() {
	STUDENT_t* data = NULL;
	current = head->next;     //실제 데이타가 저장된 노드위치 저장
	int flag = 0;

	while (!flag && head != NULL) {
		system("cls");
		puts("================================");
		puts("\t 성적 관리 \t");
		puts("================================");

		if (current != NULL) {
			print_one_student_data(current);
		}

		puts("1.이전성적");
		puts("2.다음성적");
		puts("3.성적등록");
		puts("4.성적수정");
		puts("5.성적삭제");
		puts("6.성적검색");
		puts("0.돌아가기");
		printf(">> ");
		scanf_s("%d", &edit_select);
		getchar();

		//보여줄 node가 없어서, 이전, 다음, 수정, 삭제, 검색기능 불허가
		//등록, 돌아가기 기능 허가
		if (current == NULL) {
			switch (edit_select) {
			case PREV:
			case NEXT:
			case MODIFY:
			case DELETE:
			case SEARCH:
				continue;
			}
		}

		switch (edit_select) {
		case PREV:
			if (current->prev != NULL) {
				current = current->prev;
			}
			break;
		case NEXT:
			if (current->next != NULL) {
				current = current->next;
			}
			break;
		case INSERT:
			data = new_student_data();
			getchar();
			break;
		case MODIFY:
			update_student_data(current);
			getchar();
			break;
		case DELETE:

			break;
		case SEARCH:
			data = search_student_data();
			if (data != NULL) {
				current = data;
			}
			break;
		case EXIT:
			flag = 1;
			break;
		default:
			puts("다시선택 하세요.~");
			getchar();
			break;
		}//end of switch

	}//end of while

	return;
}





