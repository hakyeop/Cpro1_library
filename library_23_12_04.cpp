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
void printIDList(int* e_num, char(*e_pwd)[11], int e_cnt); // 현재 등록된 회원번호 확인

// 회원번호 및 비밀번호 배열의 dno 번째 요소를 삭제하는 함수, 변경된 요소의 수 반환

int deleteFromIDList(int dno, int* e_num, char(*e_pwd)[11], int e_cnt); //e_cnt 반환


// 회원번호 및 비밀번호 배열에 새로운 id, pwd를 삽입하는 함수, 변경된 요소의 수 반환

int insertToIDList(int id, char* pwd, int* e_num, char(*e_pwd)[11], int e_cnt); // e_cnt 반환

//-----------------------------------------------------------------
// 비밀번호 입력과 문자열 처리 함수

void input_password(char* pwd);
int verify_pwd(char* sp);
int my_strlen(char* sp);
void my_strcpy(char* dp, char* sp);
void my_gets(char* sp, int size);

//-----------------------------------------------------------------
// 도서 관련 함수

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

	strcpy_s(e_pwd[0], "123456789");

	e_cnt = 1;

	login_num = 1;




	while (1)
	{

		num = disp_menu();

		if (num == 0)

			break;



		switch (num)
		{
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



	printf("\n\n===[ 도서관 시스템 ]===\n");

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

	if (login_num != 1) //관리자가 아니라면 반환
	{
		printf("@ 관리자만 사용하실 수 있습니다!\n");
		return;
	}

	printf("\n[ 회원 등록/삭제 ]\n\n");

	num = get_checkRange(1, 9999);
	if (num == 0)
	{
		return;
	}
	else if (num == 1)
	{
		printf("관리자는 삭제할 수 없습니다!\n");
		return;
	}

	index = is_enroll_num(num, e_num, *e_cnt); // 등록된 번호인지 확인


	if (index >= 0) { // 등록된 번호가 있으면 회원 삭제

		*e_cnt = deleteID(index, e_num, e_pwd, *e_cnt);

	}

	else { // 없으면 회원 등록 진행

		*e_cnt = insertID(num, e_num, e_pwd, *e_cnt);

	}

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
	e_num[e_cnt] = id;
	strcpy(e_pwd[e_cnt], pwd);
	e_cnt++;
	printf("# %d번이 등록되었습니다!\n", id);
	return e_cnt;
}


void printIDList(int* e_num, char(*e_pwd)[11], int e_cnt)

{

	int i = 0;



	printf("\n>> 현재 등록된 번호 (비밀번호) : ");

	for (i = 0; i < e_cnt; i++) {

		printf("%5d(%s)", e_num[i], e_pwd[i]);

	}

	printf("\n\n");

}


int deleteID(int dno, int* e_num, char(*e_pwd)[11], int e_cnt)
{
	char yn;
	char pwd[11] = "";

	printf("@ 이미 등록되었습니다!\n");
	printf("@ 삭제하시겠습니까(Y/N)? : ");

	yn = getchar();
	scanf_s("%c", &yn);

	if ((yn == 'Y') || (yn == 'y'))
	{
		//비밀번호를 입력받아 회원번호에 맞는 비밀번호인 경우 삭제 처리
		printf("> 비밀번호 입력 : ");
		my_gets(pwd, 11); // 배열의 크기까지만 입력
		if (strcmp(pwd, e_pwd[dno]) != 0)
		{
			printf("@ 비밀번호가 다릅니다. 삭제할 수 없습니다.\n");
			return e_cnt;
		}
		printf("@ %d번이 삭제되었습니다!\n", e_num[dno]);
		e_cnt = deleteFromIDList(dno, e_num, e_pwd, e_cnt);
		printIDList(e_num, e_pwd, e_cnt);
	}
	else
	{
		printf("@ 취소되었습니다!\n");
	}
		return e_cnt;
}


int insertID(int id, int* e_num, char(*e_pwd)[11], int e_cnt)
{
	// 등록인원이 추가되지 않았다면 인원 추가
	char pwd[11] = "";



	if (e_cnt == MAX_ARY) { // 등록 인원 수가 최대 인원 수와 같으면 반환

		printf("@ 등록 인원이 초과되었습니다!");

		return e_cnt;

	}

	input_password(pwd);



	e_cnt = insertToIDList(id, pwd, e_num, e_pwd, e_cnt);

	printIDList(e_num, e_pwd, e_cnt); // 등록되었는지 확인하는 함수

	return e_cnt;
}


int is_enroll_num(int num, int* e_num, int e_cnt) // 등록된 번호인지 확인
{
	int i;

	for (i = 0; i < e_cnt; i++) 
	{
		if (num == e_num[i])
			return i;
	}

	return -1;
}


int verify_pwd(char* sp) //비밀번호 형식 검사
{
	if (my_strlen(sp) < 5) {

		return 1; //오류가 있다면 1 반환

	}

	return 0; //오류가 없으면 0 반환
}


void input_password(char* pwd) // 비밀번호 입력

{

	char first[11]; // 첫 번째 입력한 비밀번호 저장

	char second[11]; // 비밀번호 문자열 입력할 임시 배열

	int err;

	do {

		
		while (1) {
			gets_s(first); // 배열의 크기까지만 입력
			err = verify_pwd(first); // 문자열 형식 검사 
			if (err == 0) // 비밀번호 양식에 맞지 않다면 다시
				break; 
			printf("@ 비밀번호는 5글자 이상, 10글자 이하로 정해야 합니다!\n");
			printf("> 비밀번호(5-10자) : ");
		}



		printf("> 한번 더 입력하세요 : ");

		gets_s(second); // 배열 크기 전달

		if (strcmp(first, second) == 0)

			break; // 첫 번째와 두번째 입력 문자열이 같은지 비교



		printf("@ 비밀번호가 일치하지 않습니다!\n");

	} while (1);

	my_strcpy(pwd, first);

}


void my_gets(char* sp, int size) //배열의 크기까지만 문자열 입력

{

	char ch;

	int i = 0;



	getchar();

	ch = getchar();

	while ((i < (size - 1)) && (ch != '\n')) {

		sp[i] = ch;

		i++;

		ch = getchar();

	}

	sp[i] = '\0';

}




int my_strlen(char* sp) // 배열에 저장된 문자열의 길이 반환

{

	int cnt = 0;



	while (*sp++ != '\0') {

		cnt++;

	}

	return cnt;

}


void login_out(int* e_num, char(*e_pwd)[11], int e_cnt, int* login_num)
{
	//비밀번호를 확인하여 로그인, 로그인된 경우 로그아웃.
	int num;

	char pwd[11] = "";

	int index;



	if (*login_num != 0) {

		*login_num = 0;

		printf("# 로그아웃되었습니다!\n");

		return;

	}



	printf("\n[ 로그인 ]\n\n");



	printf("> 회원번호 : ");

	scanf("%d", &num);

	index = is_enroll_num(num, e_num, e_cnt); // 등록된 번호이면 배열의 등록 위치 반환, 아니면 -1 반환



	if (index == -1) {

		printf("@ %d번은 등록되지 않은 번호입니다!\n", num);

		return;

	}



	printf("> 비밀번호 : ");

	fflush(stdin);

	my_gets(pwd, 11);

	if (strcmp(pwd, e_pwd[index]) != 0) {

		printf("@ 비밀번호가 틀렸습니다!\n");

		return;

	}

	*login_num = num; // 로그인 사번 저장

	printf("# 로그인되었습니다!\n");

}

void my_strcpy(char* dp, char* sp)
{
	while ((*dp++ = *sp++) != '\0');
}