#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct // 책 구조체
{
	char bookname[50];	//책 이름을 담는 배열
	char bookpublisher[50]; //책 출판사를 담는 배열
	int bookid; //책 id를 담는 변수
	int bookyear; // 출판연도를 담아두는 변수
	bool cancheckout; // 대출가능여부를 적어두는 변수
	int edition; // 책의 판본을 적어두는 변수
}book;


// 회원 등록, 로그인 메뉴 관련 함수와 변수

//-----------------------------------------------------------------

int disp_menu(void);	//메뉴 인터페이스
void enroll_num(int* e_num, char(*e_pwd)[11], int* e_cnt, int login_num); //회원등록/삭제 
int is_enroll_num(int num, int* e_num, int e_cnt); //회원이 등록되었는지 확인
void login_out(int* e_num, char(*e_pwd)[11], int e_cnt, int* login_num); //로그인 로그아웃

//-----------------------------------------------------------------
// 회원 등록 관련 처리 함수

int get_checkRange(int min, int max); //회원번호를 입력받아 반환하는 함수
void printIDList(int* e_num, char(*e_pwd)[11], int e_cnt); // 회원번호 및 비밀번호를 출력하는 함수
int deleteID(int dno, int* e_num, char(*e_pwd)[11], int e_cnt); // 회원번호 및 비밀번호 삭제
int insertID(int id, int* e_num, char(*e_pwd)[11], int e_cnt); // 회원번호 및 비밀번호 삽입

// 회원번호 및 비밀번호 배열의 dno 번째 요소를 삭제하는 함수, 변경된 요소의 수 반환

int deleteFromIDList(int dno, int* e_num, char(*e_pwd)[11], int e_cnt); //e_cnt 반환


// 회원번호 및 비밀번호 배열에 새로운 id, pwd를 삽입하는 함수, 변경된 요소의 수 반환

int insertToIDList(int id, char* pwd, int* e_num, char(*e_pwd)[11], int e_cnt); // e_cnt 반환

//-----------------------------------------------------------------
// 비밀번호 입력과 문자열 처리 함수

//-----------------------------------------------------------------


//-----------------------------------------------------------------



#define MAX_ARY 100 // 최대 등록 인원 수



int main(void)

{
	int e_num[MAX_ARY] = { 0 }; // 회원 배열

	char e_pwd[MAX_ARY][11] = { "" }; // 비밀번호 배열 (최대 100명, 최대 10자)

	int e_cnt = 0; // 등록 인원 수

	int login_num = 0; // 로그인된 회원 번호 저장

	int num;




	// 관리자 계정

	e_num[0] = 1;

	strcpy_s(e_pwd[0], "123123");

	e_cnt = 1;

	login_num = 1;




	while (1) {

		num = disp_menu();

		if (num == 0)

			break;



		switch (num) {

		case 1:

			enroll_num(e_num, e_pwd, &e_cnt, login_num);

			break;

		case 2:

			login_out(e_num, e_pwd, e_cnt, &login_num);

			break;

		case 3:

			// 도서 등록 삭제

			break;

		case 4:

			// 도서 대출 함수

			break;


		default:

			printf("@ 메뉴 번호가 아닙니다!\n\n");

			break;

		}

	}



	return 0;

}

// 메뉴 출력 후 선택 번호 반환

int disp_menu(void)

{

	int num;



	printf("\n===[ 도서관 시스템 ]===\n");

	printf("1. 회원 등록/삭제\n");

	printf("2. 로그인/로그아웃\n");

	printf("3. 도서등록\n");

	printf("4. 도서대출\n");

	printf("0. 종료\n");

	printf("---------------------------\n");



	printf("> 번호 선택 : ");

	scanf_s("%d", &num);



	return num;

}

//==========< 회원 등록/삭제, 로그인/로그아웃 관련 함수 >==========
void enroll_num(int* e_num, char(*e_pwd)[11], int* e_cnt, int login_num)
{
	int num; //회원 번호
	int index; //회원번호가 있는 배열의 위치

	if (login_num != 0) //이미 로그인된 상태라면 반환
	{
		printf("@ 로그아웃 후 사용하실 수 있습니다!\n");
		return;
	}

	printf("\n[ 회원 등록/삭제 ]\n\n");
	num = get_checkRange(1, 9999);
	return;
}

int get_checkRange(int min, int max)
{
	int input = 0;
	printf("> 회원번호(%d-%d) : ", min, max);
	scanf("%d", &input);
	if ((input < min) || (input > max)) // 허용 범위의 숫자가 아니면 반환
	{
		printf("@ 유효한 번호가 아닙니다!\n");
		return 0;
	}
	return input;
}

int deleteFromIDList(int dno, int* e_num, char(*e_pwd)[11], int e_cnt)
{
	//dno 번째 배열의 회원 정보를 삭제하고 하나씩 당기기, 감소된 e_cnt(등록된 회원 수) 반환
	int i = 0;

	for (i = dno; i < (e_cnt - 1);i++)
	{
		e_num[i] = e_num[i + 1];
		strcpy(e_pwd[i], e_pwd[i + 1]);
	}
	e_cnt--; //등록된 회원수 감소
	return e_cnt;
}

int insertToIDList(int id, char* pwd, int* e_num, char(*e_pwd)[11], int e_cnt)
{
	//회원 정보를 추가하고 증가된 e_cnt(등록된 회원 수) 반환
	return 0;
}

int deleteID(int dno, int* e_num, char(*e_pwd)[11], int e_cnt)
{
	// 맞는 비밀번호를 입력하면 deleteFromIDList 를 호출
	return 0;
}

int insertID(int id, int* e_num, char(*e_pwd)[11], int e_cnt)
{
	// 등록인원이 추가되지 않았다면 인원 추가
	return 0;
}

int is_enroll_num(int num, int* e_num, int e_cnt)
{
	// 등록된 번호인지 확인
	return 0;
}

void login_out(int* e_num, char(*e_pwd)[11], int e_cnt, int* login_num)
{
	//비밀번호를 확인하여 로그인, 로그인된 경우 로그아웃.
}
