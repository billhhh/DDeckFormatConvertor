/* 
* 
* funtion: 完整的一条路实体类
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
	std::vector <int > station_seq; //道路序列，方便输出
	double Weight;
	int Vehicles;
	int belong; //代表属于哪个起点

	RoadObj(void); //构造函数
	~RoadObj(void);

protected:
private:
};