/* 
* 
* funtion: 文件IO
* 
* Date:2015-6-5
* 
*    Author: Bill Wang
*/

#include "FileIO.h"
#include <fstream>
#include <string>

using namespace std;

bool FileIO::FileReader(string path,string & content)
{
	//文件读取
	//ifstream myfile ("D:\\TESTCASE\\格式1.txt");
	ifstream myfile (path);
	string buf;
	string outStr;

	if(!myfile){
		cout << "Unable to open TXT\n";
		return false; // terminate with error
	}

	while (myfile)
	{
		if( getline( myfile, buf ) ){  
			outStr.append(buf);
			outStr.append("\n");
		}
	}

	content = outStr;

	return true;
}

bool FileIO::FileWriter(string path,string content)
{
	//ofstream myfile("D:\\TESTCASE\\testout.txt",ios::out);
	cout<<"正在写入..."<<endl;
	ofstream myfile(path,ios::out);
	if(!myfile)
	{
		cout << "Unable to open TXT\n";
		return false;
	}

	else
	{
		myfile<<content;
		myfile.close();
	}

	return true;
}