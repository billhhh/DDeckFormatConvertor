/* 
* 
* funtion: 
* 
* Date:2015-6-6
* 
*    Author: Bill Wang
*/


#include "EdgeObj.h"

//构造函数，init
EdgeObj::EdgeObj(void){
	this->Start_Type = -1;
	this->Start_Num = -1;
	this->End_Type = -1;
	this->End_Num = -1;
	this->Weight = 0;
}

//析构函数
EdgeObj::~EdgeObj(void){

}
