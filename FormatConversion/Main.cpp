/* 
* 
* funtion: main func
* 
* Date:2015-6-4
* 
*    Author: Bill Wang
*/

#include <iostream>
#include "FileIO.h"
#include "Controller.h"

using namespace std;

void testIO()
{
	FileIO fio;
	string con;
	fio.FileReader("D:\\TESTCASE\\格式2.txt",con);
	con.append("asdfasdfasdfdddd");
	fio.FileWriter("D:\\TESTCASE\\格式2out.txt",con);
}

int main()
{
	//testIO(); //ok
	Controller ctrl; //控制器
	ctrl.startConverter("D:\\TESTCASE\\out.txt","D:\\TESTCASE\\out2.txt","2");

	return 0;
}
