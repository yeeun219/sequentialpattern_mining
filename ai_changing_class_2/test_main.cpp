#include <iostream>
#include "procedure.h"
#include <vector>
#include <utility>
#include <set>
#include <functional>
using namespace std;

#define MAX_NUM 500
set<int> set1;//���� set �� ���������� ��.
set<int> set2; //�ٸ� set�� ���������� �� -> ����� �ΰ��� set�� ����
string final_res[MAX_NUM][MAX_NUM]; //string �迭�� �ִ밪 :4500
//k���� ū ���� �ִ� �迭,ū���� �ε��� ������ ����
vector <pair<double, int>> large_k;

int load(procedure * pro_ary[MAX_NUM]);
string setResult(string a, string b, int a_n, int b_n);
void setMatrix(int no_tid, procedure * pro_ary[MAX_NUM],string ary[MAX_NUM][MAX_NUM]);
void iteration(int matrix_num, int no_tid, int process_id[], string final_res[MAX_NUM][MAX_NUM], procedure * pro_ary[MAX_NUM], double k);


/**
 *        @brief main �Լ�
 *        @details ��� matrix �� �ʱ�ȭ�ϰ�, ������ ���� �Լ��� �־���. 
 *        @return int ������ 0�� ����
 *        @throws indexException ��� matrix �ε��� �߸� ������ ���ܹ߻�
 */
int main() {

	//procedure�� �迭�� ������,,�����Ҵ�����
	//�����Ҵ����� ����� �迭�� �ϳ��� ä��� ������ new �� �ؾ�,,, 
	procedure *pro_ary[MAX_NUM];
	//load���� �Ѷ����� ���ڷ� �ָ� ������ Ŭ���� ���� ����� �� ���� �ؼ� 
	//�ٽ� �� �迭�� ��ȯ ���⼭ ���� ������ ����� ���� ����
	
	int no_tid = load(pro_ary);
	cout << "id�� ���� :" << no_tid<<endl;

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


	double theta = 1.2; //����� ������ 1
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
 *        @brief load �Լ�
 *        @details input������ �޾� procedureŬ������ �ν��Ͻ� �迭�� ���� �ִ°� 
 *        @param procedure * pro_ary[MAX_NUM] process class �� �ν��Ͻ� �迭
 *        @return int ������ 0�� ����
 *        @throws indexException ��� matrix �ε��� �߸� ������ ���ܹ߻�
 */
int load(procedure * pro_ary[MAX_NUM])
{
	char filename[13];
	int i = 0;//�ֹ� �ּ��� �ε��� �� 
	int j = 0;//�迭 ����Ű�� ��ġ

	errno_t err;
	FILE* fp;

	err = fopen_s(&fp, "input7.txt", "rt");  // ��ü path ��θ� ����, �ƴϸ� ���������� �ִ� ���� ������ 
	if (err == 0)
		puts("���Ͽ��� ����!\n");
	else {
		puts("���� ���� ����\n");
		return -1;
	}
	int index = 0;
	while (!feof(fp)) {
		char s[80];
		fgets(s, 80, fp);// �ִ� 80ĭ¥�� ���� �б�
		pro_ary[index] = new procedure(s);
		index++;
	}
	fclose(fp);
	return index-1;
}
/**
 *        @brief setResult �Լ�
 *        @details ������ �������� measure values of similarity���� ���
 *        @param string a ���� ������ �̸�
 *		  @param string b ���� �� �ٸ� ������ �̸�
 *		  @param int a_n a������ ���μ��� ���� 
 *		  @param int b_n b������ ���μ��� ����
 *        @return int ������ 0�� ����
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
 *        @brief setResult �Լ�
 *        @details ������ �������� measure values of similarity���� matrix�� ����
 *        @param int no_tid ���� ������ �̸�
 *		  @param procedure * pro_ary[MAX_NUM]  process class �� �ν��Ͻ� �迭
 *		  @param string ary[MAX_NUM][MAX_NUM] ��� matrix
 *        @return int ������ 0�� ����
 *        @throws indexException ��� matrix �ε��� �߸� ������ ���ܹ߻�
 */
void setMatrix(int no_tid, procedure * pro_ary[MAX_NUM], string ary[MAX_NUM][MAX_NUM] ) {

	int matrix_num = 0;

	for (int i = 0; i < no_tid; i++) {
		matrix_num = matrix_num + pro_ary[i]->getAlternative_num();
	}

	//��� matrix �ʱ�ȭ

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
 *        @brief int_to_ch_for_alternative�Լ�
 *        @details matrix�� �ε��� ��ȣ�� ���� ���� �ε����� �ٲٴ� �Լ�
 *        @param int n �ٲ���ϴ� matrix �� �ε��� ��ȣ
 *        @return char ������ �ٲ� ���� ����
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
//col�̳� row�� �ε����� �ָ� �ش� ������ ��Ÿ���� ��ȣ�� 
//int change_ind_to_id(int process_id[],int index)

set<int> in_set_make_inf(int infrow_ind, int matrix_num, int inf_row[], set<int> s, int theta, int process_id[]) {
	set<int> new_inf_col;
	int infcol_ind = 0;

	for (int i = 0; i < infrow_ind; i++) {
		for (int j = 0; j < matrix_num; j++) {
			if (stod(final_res[inf_row[i]][j]) >= theta) {
				new_inf_col.insert(j); infcol_ind++;
				s.insert(j);
				printf("set�� %d%c�� �߰� \n", process_id[j] / 10 + 1, int_to_ch_for_alternative(process_id[j] % 10));
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

	printf("���� ū ��\n");
	printf("%f         %d\n", large_k[final_i].first, large_k[final_i].second);
	large_k[final_i].first = 0;



	//index �� ��ȯ�Ǳ� ���� ������ ���, ������ ���� ������ ����.
	int element = large_k[final_i].second;

	//���� �� ���ؽ� ã�Ƽ� ���Ѵ�� �����
	int row = element / 10000;
	g_s.insert(row);
	int col = (element % 10000);
	g_s.insert(col);
	printf("\n");
	printf("%d%c�� %d%c�� P�� ���Խ��ϴ�.\n", row / 10 + 1, int_to_ch_for_alternative(row % 10), col / 10 + 1, int_to_ch_for_alternative(col % 10));

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
 *        @brief iteration�Լ�
 *        @details matrix���� ����� ������ set �� �־ ���� ��� matrix ���� ����� �Լ�
 *        @param int matrix_num matrix �ε����� ����
 *		  @param int no_tid id�� ����
 *		  @param procedure * pro_ary[MAX_NUM]  process class �� �ν��Ͻ� �迭
 *		  @param string final_res[MAX_NUM][MAX_NUM] ��� matrix
 *		  @param int process_id[] ������ �ĺ����� �� process �� 
 *		  @param double k ��Ÿ��
 *        @return char ������ �ٲ� ���� ����
 *        @throws indexException ��� matrix �ε��� �߸� ������ ���ܹ߻�
 */
void iteration(int matrix_num, int no_tid, int process_id[], string final_res[MAX_NUM][MAX_NUM], procedure * pro_ary[MAX_NUM], double k) {
	int verti = 0;
	int hori = 0;

	

	int ind = 0;
	printf("\n");
	printf("theta���� ū ��, index \n");

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

	//ind ���� ������ k���� ū�� ���ٴ� �ǹ� main���� ������ ��Ʈ������ ������ ������ ������
	if (ind == 0) {
		printf("�׷��� �������� �ʽ��ϴ�. theta�� �ٿ��� �غ�����.");
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