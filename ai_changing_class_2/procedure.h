#pragma once
#include <string>
using namespace std;


/**
 *
 * @brief 공정 정보에 대한 클래스이다. 이 클래스가 다 쓰일때에는 메모리 보존을 위해 소멸된다.
 * @details 공정 정보를 데이터 구조에 맞게 받는다.
 * @author 이예은
 * @date 2019-10-14
 * @version 0.0.1
 */

class procedure
{
private:
	int id_no;
	int alternatives_num;//대안 프로세스의 갯수는 3개까지
	char process_num[3]; //프로세스 과정 123, 2314이면 3,4 저장 
	string order_name; //123, 2314이면 1232314 저장
	int quantity;
public:
	procedure(char s[80]);
	string getOrdername(int index);
	int getPrNumber(int index); // 여기서 index는 몇번째 인건지
	int getAlternative_num();
	virtual ~procedure() {}
};

