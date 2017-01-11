/* 
* 
* funtion: 文件IO 工具类
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
	bool FileReader(std::string path,std::string & content); //返回成功与否，传入path，返回content
	bool FileWriter(std::string path,std::string content); //返回成功与否，传入path，写入content

private:


};


#endif // !_FILEIO_H_
