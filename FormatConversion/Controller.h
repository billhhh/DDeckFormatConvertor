/* 
* 
* funtion: 逻辑控制器
* 
* Date:2015-6-5
* 
*    Author: Bill Wang
*/

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <iostream>
#include <vector>
#include "EdgeObj.h"
#include "RoadObj.h"

class Controller
{
public:
	//文件转换器
	//type=1 格式1->2
	//type=2 格式2->1
	bool startConverter(std::string path_in, std::string path_out,std::string type);
	Controller(void); //构造函数

private:
	std::string txtContent;
	std::vector <EdgeObj> JsonMap;
	std::vector <RoadObj > Layer1_RoundMap; //TypeA中的一圈的所有集合
	std::vector <RoadObj > Layer2_RoundMap;

	bool init();
	bool ConvertTypeA(std::string path_in, std::string path_out);//TypeA的转换
	bool ConvertTypeB(std::string path_in, std::string path_out);//TypeB的转换
	std::string storeForm1Info(); //把typeA转换成可写入的string
	double find_weight_num(int &position,std::string content);
	int find_round_lenth(int &position,std::string content);
	bool find_round_seq(int source_point,std::vector<int> &a_round ,int position ,std::string content,int n);
	bool find_round_seq(std::string source_point,std::vector<std::string> &a_round ,int position ,std::string content,int n);//重载vector<string>
	bool str_split(std::string str,std::vector<std::string> &a_round,std::string regex);
	int find_vehicle_num(int &position,std::string content);
	std::string build_typeB_str(std::vector<EdgeObj > Jmap);//生成 typeA->typeB 格式字符串
	std::string wh_int2string(int n);
	std::string wh_double2string(double n);
	std::string get_name(std::string content);

	//typeB
	bool fill_Jmap(std::string);
	bool remove_vec_nonnum(std::vector<std::string > &vec); //去掉vector里面非数值的项
	bool refresh_vehicle(std::vector<RoadObj > &vec);
	std::string build_typeA_str(std::vector<EdgeObj > Jmap);//生成 typeB->typeA 格式字符串

};

#endif
