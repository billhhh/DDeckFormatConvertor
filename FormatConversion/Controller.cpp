/* 
* 
* funtion: �߼���������ʵ�֣�ʮ����Ҫ��
* 
* Date:2015-6-5
* 
*    Author: Bill Wang
*/

#include "Controller.h"
#include "FileIO.h"
#include "TemplateStringToNum.h"

using namespace std;

//���캯��
Controller::Controller(void)
{
	init();
}

bool Controller::init()
{
	//��ʼ��
	this->txtContent = "";
	this->JsonMap.clear();
	this->Layer1_RoundMap.clear();
	this->Layer2_RoundMap.clear();

	return true;
}

//�ļ�ת����
//type=1 ��ʽ1->2
//type=2 ��ʽ2->1
bool Controller::startConverter(string path_in, string path_out,string type)
{
	init();

	if ( type.compare("1") == 0 )
		ConvertTypeA(path_in,path_out);
	else
		ConvertTypeB(path_in,path_out);

	return true;
}

bool Controller::ConvertTypeA(string path_in, string path_out)
{
	//��ȡtxt
	FileIO fio;
	fio.FileReader(path_in,this->txtContent);

	string res = storeForm1Info();  //���ɸ�ʽ1��Ϣ
	//д���ļ�
	fio.FileWriter(path_out,res);
	cout<<"д��ɹ�!"<<endl;

	return true;
}

string Controller::storeForm1Info()
{
	string process_content = this->txtContent;	//�ı�����
	int position=process_content.find("Layer1",0);
	int L2_position=process_content.find("Layer2",position);

	//---------------Layer1---------------
	while( (position=process_content.find("Weight",position))!=string::npos 
		 && position<L2_position 
		 )
	{

		//process here
		double w = find_weight_num( position,process_content ); //�ҵ������ڵ�weight��ֵ
		EdgeObj e;
		e.Weight=w;

		if(w == 0)
			continue; //unreachable point

		position = process_content.find("Cust",position);
		int n = find_round_lenth(position,process_content); //����position�����غ�position��")"��λ��

		if(n==0)
			continue;

		vector<int > a_round;
		find_round_seq(0,a_round ,position ,process_content,n); //����һ������·�������� a_round

		e.Start_Type = 0;
		e.Start_Num = 0;
		e.End_Type = 1;
		e.End_Num = a_round.at(1);
		this->JsonMap.push_back(e);

		//�Ѿ��õ� <int >����<string >��װ����EdgeObj��Ȼ�����vector
		for (int i=1 ;i<a_round.size()-2; ++i)
		{
			EdgeObj eobj;
			eobj.Start_Type = 1;
			eobj.Start_Num = a_round.at(i);
			eobj.End_Type = 1;
			eobj.End_Num = a_round.at(i+1);
			eobj.Weight = 0;
			this->JsonMap.push_back(eobj);
		}
		e.Start_Type = 1;
		e.Start_Num = a_round.at(a_round.size()-2);
		e.End_Type = 0;
		e.End_Num = a_round.at(a_round.size()-1);
		e.Weight = 0;
		this->JsonMap.push_back(e);
	}

	//layer1 all over
	//---------------Layer2---------------
	int L2_point=0; //�������
	position = L2_position;
	while( (position=process_content.find("Vehicles",position))!=string::npos ){

		L2_point++;

		//�ҳ�Vehicles������֣����Ϊ0������
		int vn = find_vehicle_num(position,process_content);

		//process here

		for (int i=0 ; i<vn ; ++i)
		{
			double w = find_weight_num( position,process_content ); //�ҵ������ڵ�weight��ֵ
			EdgeObj e;
			e.Weight=w;

			if(w == 0)
				continue; //unreachable point

			position = process_content.find("Cust",position);
			int n = find_round_lenth(position,process_content); //����position�����غ�position��")"��λ��

			if(n==0)
				continue;

			vector<int > a_round;
			find_round_seq(L2_point,a_round ,position ,process_content,n); //����һ������·�������� a_round

			e.Start_Type = 1;
			e.Start_Num = a_round.at(0);
			e.End_Type = 2;
			e.End_Num = a_round.at(1);
			this->JsonMap.push_back(e);

			//�Ѿ��õ� <int >����<string >��װ����EdgeObj��Ȼ�����vector
			for (int i=1 ;i<a_round.size()-2; ++i)
			{
				EdgeObj eobj;
				eobj.Start_Type = 2;
				eobj.Start_Num = a_round.at(i);
				eobj.End_Type = 2;
				eobj.End_Num = a_round.at(i+1);
				eobj.Weight = 0;
				this->JsonMap.push_back(eobj);
			}
			e.Start_Type = 2;
			e.Start_Num = a_round.at(a_round.size()-2);
			e.End_Type = 1;
			e.End_Num = a_round.at(a_round.size()-1);
			e.Weight = 0;
			this->JsonMap.push_back(e);
		}

	}

	//���ˣ�JsonMap�Ѿ�ȫ��д��
	//����typeB��ʽstring
	string res = build_typeB_str(this->JsonMap);
	//cout<<res;

	return res;
}

double Controller::find_weight_num(int &position,string content){

	position = content.find("Weight",position);
	int start_pos = content.find("(",position);
	int end_pos = content.find(")",position);
	int lenth = end_pos - start_pos+1;

	string numStr = content.substr(start_pos+1,lenth);
	position = end_pos;
	return stringToNum<double> (numStr);
}

//����һȦ��·�����ȣ�ע����������position
int Controller::find_round_lenth(int &position,string content){
	int start_pos = content.find("(",position);
	int end_pos = content.find(")",position);
	int lenth = end_pos - start_pos+1;

	string numStr = content.substr(start_pos+1,lenth);
	position = end_pos;
	return stringToNum<int> (numStr);
}

bool Controller::find_round_seq(int source_point,vector<int> &a_round ,int position , string content,int n)
{
	a_round.push_back(source_point);
	int start_pos = position+2;
	int end_pos = content.find("\n",position);
	int lenth = end_pos - start_pos;

	string str = content.substr(start_pos,lenth);
	vector<string> strVec;
	str_split(str,strVec," ");

	//��strVec�е�stringת��Ϊint vector
	for (int i=0;i<strVec.size();++i)
	{
		int tmp = stringToNum<int > (strVec.at(i));
		a_round.push_back(tmp);
	}
	a_round.push_back(source_point);

	return true;
}

//���ط�����ֱ�Ӵ���vector<string> &a_round
bool Controller::find_round_seq(string source_point,vector<string> &a_round ,int position , string content,int n)
{
	a_round.push_back("0");
	int start_pos = position+2;
	int end_pos = content.find("\n",position);
	int lenth = end_pos - start_pos;

	string str = content.substr(start_pos,lenth);
	vector<string> strVec;
	str_split(str,strVec," ");

	//��strVec�е�stringת��Ϊint vector
	for (int i=0;i<strVec.size();++i)
		a_round.push_back(strVec.at(i));
	a_round.push_back("0");

	return true;
}

bool Controller::str_split(std::string str,std::vector<string> &strvec,std::string regex){
	//string test = "aa aa bbc cccd";
	string test = str;
	string strtemp;

	string::size_type pos1, pos2;
	pos2 = test.find(regex);
	pos1 = 0;        
	while (string::npos != pos2)
	{
		strvec.push_back(test.substr(pos1, pos2 - pos1));

		pos1 = pos2 + 1;
		pos2 = test.find(regex, pos1);
	}
	strvec.push_back(test.substr(pos1));

//  	vector<string>::iterator iter1 = strvec.begin(), iter2 = strvec.end();
//  	while (iter1 != iter2)
//  	{
//  		cout << *iter1 << endl;
//  		++iter1;
//  	}

	return true;
}

int Controller::find_vehicle_num(int &position,std::string content){
	position = content.find("=",position);
	int start_pos = position+1;
	int end_pos = content.find("\n",position);
	int lenth = end_pos - start_pos;

	string str = content.substr(start_pos,lenth);
	position = end_pos;
	return stringToNum<int > (str);
}

//����typeB��ʽ
string Controller::build_typeB_str(std::vector<EdgeObj > Jmap)
{
	string result("{\"steps\":[\n");

	for (int i=0 ; i<Jmap.size() ;i++)
	{
		result.append("{\"from\":[\"");
		result.append(wh_int2string(Jmap.at(i).Start_Type));
		result.append("\",\"");
		result.append(wh_int2string(Jmap.at(i).Start_Num));
		result.append("\"],\"line\":\"");
		result.append(wh_double2string(Jmap.at(i).Weight));
		result.append("\",\"to\":[\"");
		result.append(wh_int2string(Jmap.at(i).End_Type));
		result.append("\",\"");
		result.append(wh_int2string(Jmap.at(i).End_Num));
		result.append("\"]}");

		if(i!=Jmap.size()-1)
			result.append(",");
		result.append("\n");
	}

	result.append("],\n");
	result.append("\"name\":\"");
	result.append(get_name(txtContent));
	result.append("\",\n}\n");

	return result;
}

string Controller::wh_int2string(int n)
{
	std::stringstream ss;
	std::string str;
	ss<<n;
	ss>>str;

	return str;
}

string Controller::wh_double2string(double n)
{
	std::stringstream ss;
	std::string str;
	ss<<n;
	ss>>str;

	return str;
}

//����ļ���
string Controller::get_name(std::string content){

	int position = content.find("name",0);
	int start_pos = position+5;
	int end_pos = content.find("\n",position);
	int lenth = end_pos - start_pos;

	string name = content.substr(start_pos,lenth);
	return name;
}

bool Controller::ConvertTypeB(string path_in, string path_out)
{
	//��ȡtxt
	FileIO fio;
	fio.FileReader(path_in,this->txtContent);

	fill_Jmap(this->txtContent); //���Jmap

	//���������� a round ��map
	//---------------Layer1---------------
	vector <EdgeObj > process_Jmap = this->JsonMap;
	bool isNewRound = false; //�Ƿ�����һ��
	RoadObj r;
	RoadObj lastRoad;
	int Layer2_index; //��¼layer2��vector�±�
	for (int i=0;i<process_Jmap.size() ;++i)
	{
		//��������һ��
		if(process_Jmap.at(i).Weight != 0)
		{
			isNewRound = true;
			lastRoad = r;

			//��ʼ��
			r.station_seq.clear();
			r.Weight = process_Jmap.at(i).Weight;
			r.Vehicles = 1;
			r.belong = process_Jmap.at(i).Start_Num;
		}

		if(i != 0 && isNewRound == true)
			this->Layer1_RoundMap.push_back(lastRoad);

		if( isNewRound == true && process_Jmap.at(i).Start_Type != 0) //�������layer2
		{
			Layer2_index = i; //��¼һ���±�
			break;
		}

		////process here
		if(isNewRound == false)
			r.station_seq.push_back(process_Jmap.at(i).Start_Num);

		isNewRound = false;
	}

	//---------------Layer2---------------
	isNewRound == false;
	//init r
	r.station_seq.clear();
	r.Weight = 0;
	r.Vehicles = 0;
	r.belong = -1;
	for (int i=Layer2_index; i<process_Jmap.size() ;++i)
	{
		//��������һ��
		if(process_Jmap.at(i).Weight != 0)
		{
			isNewRound = true;
			lastRoad = r;

			//��ʼ��
			r.station_seq.clear();
			r.Weight = process_Jmap.at(i).Weight;

			if(r.belong == process_Jmap.at(i).Start_Num) //////����
				r.Vehicles++;
			else{
				r.belong = process_Jmap.at(i).Start_Num;
				r.Vehicles = 1;
			}
		}

		if(i != Layer2_index && isNewRound == true)
			this->Layer2_RoundMap.push_back(lastRoad);

		////process here
		if(isNewRound == false)
			r.station_seq.push_back(process_Jmap.at(i).Start_Num);

		isNewRound = false;
	}

	this->Layer2_RoundMap.push_back(r);

	//����һЩ��ֹһ������ Road �� Vehicles
	refresh_vehicle(this->Layer2_RoundMap);

	//

	return true;
}

//�ú���ֻ�ǵ����������JsonMap
bool Controller::fill_Jmap(std::string content)
{
	string process_content = this->txtContent;	//�ı�����
	int position = 0;
	int name_position = process_content.find("name",0);

	while( (position = process_content.find("from",position))!=string::npos 
		&& position<name_position 
		)
	{
		////�ҵ�һ�е�from��to
		int start_pos = ++position;
		int end_pos = process_content.find("\n",position);
		int lenth = end_pos - start_pos;
		string line_str = process_content.substr(start_pos,lenth);

		//�ָ�һ���е��ַ���
		vector<string > line_vec;
		str_split(line_str,line_vec,"\"");

		remove_vec_nonnum(line_vec);

		//�ɹ��Ƴ�vector�������з����ֳ�Ա
		EdgeObj e;
		e.Start_Type = stringToNum<int > (line_vec.at(0));
		e.Start_Num = stringToNum<int > (line_vec.at(1));
		e.Weight = stringToNum<double > (line_vec.at(2));
		e.End_Type = stringToNum<int > (line_vec.at(3));
		e.End_Num = stringToNum<int > (line_vec.at(4));

		this->JsonMap.push_back(e);
	}

	return true;
}

bool Controller::remove_vec_nonnum(std::vector<string > &vec)
{
	for (vector<string >::iterator it = vec.begin(); it != vec.end() ; )
	{
		string tmpStr = *it;
		if( tmpStr[0]>='0' && tmpStr[0]<='9' )
		{
			++it;
			continue;
		}

		it = vec.erase(it);
	}

	return true;
}

bool Controller::refresh_vehicle(std::vector<RoadObj > &vec)
{
	for (int i=vec.size()-1 ; i>=1 ;i--)
		if(vec.at(i).belong == vec.at(i-1).belong)
		{
// 			printf("vec.at(%d).Vehicles == %d\n",i,vec.at(i).Vehicles);
// 			printf("vec.at(%d).Vehicles == %d\n",i-1,vec.at(i-1).Vehicles);
			vec.at(i-1).Vehicles = vec.at(i).Vehicles;
		}

	return true;
}
