/* 
* 
* funtion: 
* 
* Date:2015-6-6
* 
*    Author: Bill Wang
*/


#include "RoadObj.h"

//构造函数，init
RoadObj::RoadObj(void)
{
	this->station_seq.clear();
	this->Weight = 0;
	this->Vehicles = 0;
	this->belong = -1;
}

//析构函数
RoadObj::~RoadObj(void){

}
