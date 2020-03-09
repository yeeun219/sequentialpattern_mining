#include <iostream>
#include "procedure.h"
#include <vector>
#include <utility>
#include <set>
#include <functional>
using namespace std;

#define MAX_NUM 500
set<int> set1;//최종 set 을 전역변수로 둠.
set<int> set2; //다른 set을 전역변수로 둠 -> 결과는 두개의 set이 나옴
string final_res[MAX_NUM][MAX_NUM]; //string 배열의 최대값 :4500
//k보다 큰 값이 있는 배열,큰값과 인덱스 쌍으로 묶음
vector <pair<double, int>> large_k;

int load(procedure * pro_ary[MAX_NUM]);
string setResult(string a, string b, int a_n, int b_n);
void setMatrix(int no_tid, procedure * pro_ary[MAX_NUM],string ary[MAX_NUM][MAX_NUM]);
void iteration(int matrix_num, int no_tid, int process_id[], string final_res[MAX_NUM][MAX_NUM], procedure * pro_ary[MAX_NUM], double k);


/**
 *        @brief main 함수
 *        @details 결과 matrix 를 초기화하고, 순서에 따라 함수에 넣어줌. 
 *        @return int 성공시 0을 리턴
 *        @throws indexException 결과 matrix 인덱스 잘못 넣으면 예외발생
 */
int main() {

	//procedure의 배열을 만들어야,,동적할당으로
	//동적할당으로 만들고 배열을 하나씩 채우는 과정을 new 로 해야,,, 
	procedure *pro_ary[MAX_NUM];
	//load에서 한라인을 인자로 주면 각각의 클래스 안의 멤버로 다 들어가게 해서 
	//다시 그 배열을 반환 여기서 참조 연산을 사용할 수도 있음
	
	int no_tid = load(pro_ary);
	cout << "id의 갯수 :" << no_tid<<endl;

	int matrix_num = 0;
	for (int i = 0; i < no_tid; i++) {
		matrix_num = matrix_num + pro_ary[i]->getAlternative_num();
	}
	for (int i = 0; i < matrix_num; i++) {
		for (int j = 0; j < matrix_num; j++) {
			final_res[i][j] = to_string(0.0);
		}
	}

	setMatrix(no_tid, pro_ary,final_res);
	for (int i = 0; i < matrix_num; ++i) {
		for (int j = 0; j < matrix_num; j++) {
			cout << final_res[i][j] << " ";
			//printf("%.1f ", final_res[i][j]);
		}
		cout << endl;
		//printf("\n");
	}

	printf("The measure values of similarity between sequences 1 complete\n");
	printf("\n");

	int* process_id = new int[matrix_num];
	int index = 0;
	for (int temp = 0; temp < no_tid; temp++) {
		int al = pro_ary[temp]->getAlternative_num();
		process_id[index] = temp * 10;
		for (int q = 0; q < al; q++) {
			if (process_id[index] != temp * 10) {
				process_id[index] = temp * 10 + q;
			}
			process_id[index]++;
			index++;
		}
	}


	double theta = 1.2; //사용자 지정값 1
	iteration(matrix_num, no_tid, process_id, final_res, pro_ary, theta);

	printf("The measure values of similarity between sequences 2 complete\n");
	printf("\n");
	for (int i = 0; i < matrix_num; ++i) {
		for (int j = 0; j < matrix_num; j++) {
			cout << final_res[i][j] << " ";
			//printf("%.1f ", final_res[i][j]);
		}
		cout << endl;
		//printf("\n");
	}
 	return 0;
}
/**
 *        @brief load 함수
 *        @details input파일을 받아 procedure클래스의 인스턴스 배열에 각각 넣는것 
 *        @param procedure * pro_ary[MAX_NUM] process class 의 인스턴스 배열
 *        @return int 성공시 0을 리턴
 *        @throws indexException 결과 matrix 인덱스 잘못 넣으면 예외발생
 */
int load(procedure * pro_ary[MAX_NUM])
{
	char filename[13];
	int i = 0;//주문 주소의 인덱스 값 
	int j = 0;//배열 가르키는 위치

	errno_t err;
	FILE* fp;

	err = fopen_s(&fp, "input7.txt", "rt");  // 전체 path 경로를 지정, 아니면 실행파일이 있는 곳에 생성됨 
	if (err == 0)
		puts("파일오픈 성공!\n");
	else {
		puts("파일 오픈 실패\n");
		return -1;
	}
	int index = 0;
	while (!feof(fp)) {
		char s[80];
		fgets(s, 80, fp);// 최대 80칸짜리 한줄 읽기
		pro_ary[index] = new procedure(s);
		index++;
	}
	fclose(fp);
	return index-1;
}
/**
 *        @brief setResult 함수
 *        @details 각각의 공정으로 measure values of similarity값을 계산
 *        @param string a 비교할 공정의 이름
 *		  @param string b 비교할 또 다른 공정의 이름
 *		  @param int a_n a공정의 프로세스 갯수 
 *		  @param int b_n b공정의 프로세스 갯수
 *        @return int 성공시 0을 리턴
 */
string setResult(string a, string b, int a_n, int b_n) {

	int intersect = 0;
	int union2 = 0;

	for (int j = 0; j < a_n; j++) {
		for (int i = 0; i < b_n; i++)
		{
			if (a[j] == b[i]) { intersect++; }
		}
	}
	union2 = a_n + b_n - intersect;
	//printf("%d", intersect);
	//printf("%d ", union2);
	string temp1[10];
	string temp2[10];
	int index1 = 0;

	for (int p = 0; p < a_n - 1; p++) {
		for (int q = 0; q < 2; q++) {
			temp1[p] += a[index1];
			index1++;
		}
		index1--;
	}

	int index2 = 0;
	for (int r = 0; r < b_n - 1; r++) {
		for (int s = 0; s < 2; s++) {
			temp2[r] += b[index2];
			index2++;
		}
		index2--;
	}
	//cout << temp1[1]<< temp2[1];

	int alpha = 0;
	int beta = 0;
	for (int j = 0; j < a_n - 1; j++) {
		for (int i = 0; i < b_n - 1; i++)
		{
			if (temp1[j].compare(temp2[i]) == 0) { alpha++; }
		}
	}
	//cout << alpha;
	beta = (a_n - 1) + (b_n - 1) - 2 * alpha;
	//cout << beta << endl;
	double result;
	result = (double)(alpha + intersect) / (double)(beta + union2);
	string str = to_string(result);
	return str;
}
/**
 *        @brief setResult 함수
 *        @details 각각의 공정으로 measure values of similarity값을 matrix에 넣음
 *        @param int no_tid 비교할 공정의 이름
 *		  @param procedure * pro_ary[MAX_NUM]  process class 의 인스턴스 배열
 *		  @param string ary[MAX_NUM][MAX_NUM] 결과 matrix
 *        @return int 성공시 0을 리턴
 *        @throws indexException 결과 matrix 인덱스 잘못 넣으면 예외발생
 */
void setMatrix(int no_tid, procedure * pro_ary[MAX_NUM], string ary[MAX_NUM][MAX_NUM] ) {

	int matrix_num = 0;

	for (int i = 0; i < no_tid; i++) {
		matrix_num = matrix_num + pro_ary[i]->getAlternative_num();
	}

	//결과 matrix 초기화

	int verti = 0;
	int hori = 0;
	int sum = 0;
	for (int temp = 0; temp < no_tid; temp++) {
		sum+= pro_ary[temp]->getAlternative_num();
		for (int i=0; i < pro_ary[temp]->getAlternative_num(); i++) {
			verti += sum;
			int ind = temp+1;
			while(true){
				if (verti == matrix_num) break;
				int al_v = pro_ary[ind]->getAlternative_num();
				for (int j = 0; j < al_v; j++) {
					ary[hori][verti] = setResult(pro_ary[temp]->getOrdername(i), pro_ary[ind]->getOrdername(j),pro_ary[temp]->getPrNumber(i), pro_ary[ind]->getPrNumber(j));
					//cout << ary[hori][verti];
					verti++;
				}
				ind++;

			}
			verti = 0;
			hori++;
			//cout << endl;
		}
	}
	
}
/**
 *        @brief int_to_ch_for_alternative함수
 *        @details matrix의 인덱스 번호를 통해 공정 인덱스로 바꾸는 함수
 *        @param int n 바꿔야하는 matrix 의 인덱스 번호
 *        @return char 성공시 바뀐 값을 리턴
 */
char int_to_ch_for_alternative(int n) {
	switch (n) {
	case 1: return 'a'; break;
	case 2: return 'b'; break;
	case 3: return 'c'; break;
	case 4: return 'd'; break;
	case 5: return 'e'; break;
	case 6: return 'f'; break;
	case 7: return 'g'; break;
	case 8: return 'h'; break;
	case 9: return 'i'; break;
	}

}
//col이나 row의 인덱스를 주면 해당 공정을 나타내는 번호로 
//int change_ind_to_id(int process_id[],int index)

set<int> in_set_make_inf(int infrow_ind, int matrix_num, int inf_row[], set<int> s, int theta, int process_id[]) {
	set<int> new_inf_col;
	int infcol_ind = 0;

	for (int i = 0; i < infrow_ind; i++) {
		for (int j = 0; j < matrix_num; j++) {
			if (stod(final_res[inf_row[i]][j]) >= theta) {
				new_inf_col.insert(j); infcol_ind++;
				s.insert(j);
				printf("set에 %d%c가 추가 \n", process_id[j] / 10 + 1, int_to_ch_for_alternative(process_id[j] % 10));
				for (int q = 0; q < matrix_num; q++) {
					if (process_id[q] / 10 == process_id[j] / 10) { if (q != j) { new_inf_col.insert(q); infcol_ind++; } }

				}
			}
		}

	}
	

	for (int i = 0; i < infrow_ind; i++) {
		for (auto j : new_inf_col) {
			int row = inf_row[i];
			final_res[row][j] = "-inf";
		}

	}

	return s;
}
set <int> push_to_set(int matrix_num, int process_id[],int ind, vector <pair<double, int>> large_k, set<int> g_s,int theta) {
	double max = large_k[0].first;
	int final_i = 0;

	for (int i = 0; i < ind; i++) {
		if (large_k[i].first > max) {
			max = large_k[i].first;
			final_i = i;
		}
	}

	printf("가장 큰 값\n");
	printf("%f         %d\n", large_k[final_i].first, large_k[final_i].second);
	large_k[final_i].first = 0;



	//index 가 변환되기 전의 집합의 요소, 집합은 전역 변수로 놓음.
	int element = large_k[final_i].second;

	//이제 그 인텍스 찾아서 무한대로 만들기
	int row = element / 10000;
	g_s.insert(row);
	int col = (element % 10000);
	g_s.insert(col);
	printf("\n");
	printf("%d%c와 %d%c가 P에 들어왔습니다.\n", row / 10 + 1, int_to_ch_for_alternative(row % 10), col / 10 + 1, int_to_ch_for_alternative(col % 10));

	int inf_row[MAX_NUM] = { 0, };
	int inf_col[MAX_NUM] = { 0, };
	int infrow_ind = 0;
	for (int i = 0; i < matrix_num; i++) {
		if (process_id[i] / 10 == row / 10) { inf_row[infrow_ind] = i; infrow_ind++; }

	}

	int infcol_ind = 0;
	for (int i = 0; i < matrix_num; i++) {
		if (process_id[i] / 10 == col / 10) { inf_col[infcol_ind] = i; infcol_ind++; }
	}
 	for (int i = 0; i < infrow_ind; i++) {
		for (int j = 0; j < infcol_ind; j++) {
			row = inf_row[i];
			col = inf_col[j];
			final_res[row][col] = "-inf";
		}

	}
	for (int j = 0; j < infcol_ind; j++) {
		inf_row[infrow_ind] = inf_col[j]; infrow_ind++;
	}
	g_s = in_set_make_inf(infrow_ind,matrix_num,inf_row, g_s, theta, process_id);
	
	return g_s;
}

/**
 *        @brief iteration함수
 *        @details matrix에서 비슷한 공정을 set 에 넣어서 최종 결과 matrix 에서 집어내는 함수
 *        @param int matrix_num matrix 인덱스의 갯수
 *		  @param int no_tid id의 갯수
 *		  @param procedure * pro_ary[MAX_NUM]  process class 의 인스턴스 배열
 *		  @param string final_res[MAX_NUM][MAX_NUM] 결과 matrix
 *		  @param int process_id[] 집합의 후보군에 들어갈 process 들 
 *		  @param double k 쎄타값
 *        @return char 성공시 바뀐 값을 리턴
 *        @throws indexException 결과 matrix 인덱스 잘못 넣으면 예외발생
 */
void iteration(int matrix_num, int no_tid, int process_id[], string final_res[MAX_NUM][MAX_NUM], procedure * pro_ary[MAX_NUM], double k) {
	int verti = 0;
	int hori = 0;

	

	int ind = 0;
	printf("\n");
	printf("theta보다 큰 값, index \n");

	for (int r = 0; r < matrix_num; r++) {
		for (int tp = 0; tp < matrix_num; tp++) {
			if (stod(final_res[r][tp]) > k) {
				pair<double, int> mid = make_pair(stod(final_res[r][tp]), process_id[r] * 10000 + process_id[tp]);
				large_k.push_back(mid);
				//printf("%.1f         %d\n", mid.first, mid.second);
				ind++;

			}

		}
	}

	//ind 값이 없으면 k보다 큰게 없다는 의미 main에서 이차원 매트릭스가 변하지 않으면 끝난것
	if (ind == 0) {
		printf("그룹이 지어지지 않습니다. theta를 줄여서 해보세요.");
		return;
	}
	
	set1=push_to_set(matrix_num, process_id, ind, large_k, set1,k);
	double max = large_k[0].first;
	int final_i = 0;
	for (int i = 0; i < ind; i++) {
		if (large_k[i].first > max) {
			max = large_k[i].first;
			final_i = i;
		}
	}
	large_k[final_i].first = 0;
	set2=push_to_set(matrix_num, process_id, ind, large_k, set2,k);
	
	return ;
}