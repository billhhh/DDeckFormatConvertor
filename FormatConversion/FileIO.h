/* 
* 
* funtion: �ļ�IO ������
* 
* Date:2015-6-4
* 
*    Author: Bill Wang
*/

#ifndef _FILEIO_H_
#define _FILEIO_H_

#include <iostream>

class FileIO
{
public:
	bool FileReader(std::string path,std::string & content); //���سɹ���񣬴���path������content
	bool FileWriter(std::string path,std::string content); //���سɹ���񣬴���path��д��content

private:


};


#endif // !_FILEIO_H_
