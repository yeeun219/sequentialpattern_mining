#include "procedure.h"
#include <stdlib.h>  
#include <iostream>
using namespace std;
/**
 *
 *        @brief procedure의 공정 순서를 입력하는 코드
 *        @details id_no와 order_name을 저장하고, quantity까지 저장하는 공정인스턴스 생성자 
 *        @param char a[80] : 인풋 파일의 한 라인
 *        @return 생성자이므로 return값 존재하지 않음.
 *        @throws indexException 동적할당 했기때문에 인덱스 잘못 넣으면 예외발생
 */

procedure::procedure(char s[80]) {
	int j = 0;//배열 가르키는 위치
	//s의 id number 바꾸기
	if (int(s[1]) == 32) {
		id_no = s[0] - '0'; j = 1;
	}
	else if (int(s[2]) == 32)
	{
		id_no = (s[0] - '0') * 10 + (s[1] - '0') ; j = 2;
	}
	else if (int(s[3]) == 32)
	{
		id_no = (s[0] - '0') * 100 + (s[1] - '0') * 10 + (s[2] - '0'); j = 3;
	}
	else
	{
		id_no = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0') ; j = 4;
	}

	//order_name 들어감
	int num = 0;//temp_order_name의 index
	alternatives_num = 0;
	char temp_order_name[10] = { 0, };
	while (true) {

		int ind = 0;
		char temp_cha[4] = { "", };
		j++;
		while (s[j] != '-') {
			if (int(s[j]) == 32) break;
			temp_cha[ind] = s[j];
			ind++;
			j++;
		}
			
		int order_1_name = atoi(temp_cha);
		temp_order_name[num] = order_1_name;
		num++;
	
		if (s[j-1] == ',') {
			alternatives_num++;//대체 공정 수 증가
			order_name.append(temp_order_name);
			process_num[alternatives_num - 1] = num;
			num = 0;
			continue;
		}
		if (s[j] == ' ') {
			alternatives_num++;//대체 공정 수 증가
			order_name.append(temp_order_name);
			process_num[alternatives_num - 1] = num;
			break;
		}
	}

	int temp_j = j;
	int fin_j = 0;
	while (true) {
		if (int(s[temp_j]) == 10) {
			fin_j = temp_j;
			//printf("%d\n", fin_j);
			break;
		}
		else temp_j++;
	}
	int nn = fin_j - j - 1;
	//printf("%d\n ", nn);
	//printf("%d\n ", j);
	//printf("%d\n ", int(s[j + 3]) - 48);

	if (nn == 3) quantity = (int(s[j + 1]) - 48) * 100 + (int(s[j + 2]) - 48) * 10 + (int(s[j + 3]) - 48);
	else if (nn == 4) quantity = (int(s[j + 1]) - 48) * 1000 + (int(s[j + 2]) - 48) * 100 + (int(s[j + 3]) - 48) * 10 + (int(s[j + 4]) - 48);
	else if (nn == 2) quantity = (int(s[j + 1]) - 48) * 10 + (int(s[j + 2]) - 48) * 1;
	else if (nn == 1) quantity = (int(s[j + 1]) - 48);
	//printf("%d\n ", orders[i]->quantity);
	//printf("\n");

	// 잘 들어갔는지 확인 코드
	/*for (int i = 0; i < alternatives_num; i++) {
		cout << id_no << " : ";
		for (int j = 0; j < process_num[i]; j++) {
			cout << int(order_name[j]) << " ";
		}
		cout << " " << quantity;
		cout << endl;
		if (alternatives_num == 2) {
			for (int j = process_num[i]; j < process_num[i] + process_num[i]; j++) {
				cout << int(order_name[j]) << " ";
			}
			cout << endl;
		}
	}*/
}
/**
 *        @brief procedure의 한 공정의 프로세스 갯수를 return하는 코드
 *        @details 대체공정 순서에 따라 공정갯수를 리턴
 *        @param int index 몇번째 대체공정인지 알려주는 index 값
 *        @return int 성공시 공정의 프로세스 갯수 리턴
 *        @throws indexException 동적할당 했기때문에 인덱스 잘못 넣으면 예외발생
 */
int procedure::getPrNumber(int index) {
	char a = process_num[index];
	return int(a);
}

/**
 *        @brief procedure의 한 공정의 프로세스 이름을 return하는 코드
 *        @details 대체공정 순서에 따라 공정의 이름을 리턴
 *        @param int index 몇번째 대체공정인지 알려주는 index 값
 *        @return string 성공시 한 공정의 한 공정 이름을 리턴
 *        @throws indexException 동적할당 했기때문에 인덱스 잘못 넣으면 예외발생
 */
string procedure::getOrdername(int index) {
	int pr_index = 0;
	for (int i = 0; i < index; i++) {
		pr_index += getPrNumber(i);
	}
	int n = getPrNumber(index);
	string parorder_name;
	int ind = 0;
	parorder_name.assign(order_name,pr_index,n);
	return parorder_name;
}
/**
 *        @brief procedure의 한 공정의 프로세스 이름을 return하는 코드
 *        @details 대체공정 순서에 따라 공정의 이름을 리턴
 *        @param int index 몇번째 대체공정인지 알려주는 index 값
 *        @return string 성공시 한 공정의 한 공정 이름을 리턴
 *        @throws indexException 동적할당 했기때문에 인덱스 잘못 넣으면 예외발생
 */
int procedure::getAlternative_num() {
	return alternatives_num;
}

