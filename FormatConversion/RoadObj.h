/* 
* 
* funtion: ������һ��·ʵ����
* 
* Date:2015-6-5
* 
*    Author: Bill Wang
*/

#pragma once
#include <vector>

class RoadObj
{
public:
	std::vector <int > station_seq; //��·���У��������
	double Weight;
	int Vehicles;
	int belong; //���������ĸ����

	RoadObj(void); //���캯��
	~RoadObj(void);

protected:
private:
};