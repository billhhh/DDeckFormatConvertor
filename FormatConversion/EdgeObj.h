/* 
* 
* funtion: 边实体类
* 
* Date:2015-6-5
* 
*    Author: Bill Wang
*/

#pragma once

class EdgeObj
{
public:
	int Start_Type;
	int Start_Num;
	int End_Type;
	int End_Num;
	double Weight;
	EdgeObj(void); //构造函数
	~EdgeObj(void);

protected:
private:
};