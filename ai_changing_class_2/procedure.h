#pragma once
#include <string>
using namespace std;


/**
 *
 * @brief ���� ������ ���� Ŭ�����̴�. �� Ŭ������ �� ���϶����� �޸� ������ ���� �Ҹ�ȴ�.
 * @details ���� ������ ������ ������ �°� �޴´�.
 * @author �̿���
 * @date 2019-10-14
 * @version 0.0.1
 */

class procedure
{
private:
	int id_no;
	int alternatives_num;//��� ���μ����� ������ 3������
	char process_num[3]; //���μ��� ���� 123, 2314�̸� 3,4 ���� 
	string order_name; //123, 2314�̸� 1232314 ����
	int quantity;
public:
	procedure(char s[80]);
	string getOrdername(int index);
	int getPrNumber(int index); // ���⼭ index�� ���° �ΰ���
	int getAlternative_num();
	virtual ~procedure() {}
};

