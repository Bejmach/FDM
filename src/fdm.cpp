#include "UDF/udf.cpp"
#include <iostream>
#include <filesystem>
#include <sys/stat.h>
#include <vector>
#include <map>

struct Database{
	std::string path;
	std::string name;
	Database(std::string name, std::string path);
	void CreateTable(std::string _name, std::vector<std::pair<std::string, DataTypes>> map);
};
Database::Database(std::string _name, std::string _path){
	if(_path!="")this->path = _path;
	else this->path = "./";
	this->name = _name;
	std::filesystem::create_directory(path+name);
}
void Database::CreateTable(std::string _name, std::vector<std::pair<std::string, DataTypes>> map){
	std::filesystem::create_directory(this->path+this->name+"/"+_name);
	std::ofstream file(this->path+this->name+"/"+_name+"/.sln");
	for(int i=0; i<map.size(); i++){
		file<<map[i].first;
		if(i!=map.size()-1){
			file<<char(0);
		}
	}
	file<<"\n";
	for(int i=0;i<map.size();i++){
		file<<char(static_cast<int>(map[i].second));
	}
}


int main(){
	Database db = Database("test", "");
	db.CreateTable("testTable", {{"name1", DataTypes::Float}, {"name2", DataTypes::Double}});
}
