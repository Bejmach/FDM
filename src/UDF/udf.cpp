#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdint>
#include <map>

enum class DataTypes{ Int, Double, Float, String, Undefined };

std::map<DataTypes, std::string> TypesMap = {{DataTypes::Int, "Int"}, {DataTypes::Double, "Double"}, {DataTypes::Float, "Float"}, {DataTypes::String, "String"}, {DataTypes::Undefined, "Undefined"}};

struct DataReturn{
	std::string value;
	DataTypes dataType;
	DataReturn(std::string _value, DataTypes _dataType);
	DataReturn();
	void PrintData();
};
DataReturn::DataReturn(){
	this->value = "null";
	this->dataType = DataTypes::Undefined;
}
DataReturn::DataReturn(std::string _value, DataTypes _dataType){
	this->value = _value;
	this->dataType = _dataType;
}
void DataReturn::PrintData(){
	std::cout<<"Value \""<<this->value<<"\" of type \""<<TypesMap[this->dataType]<<"\""<<std::endl;
}


struct DataNode{
	std::string id;
	std::vector<uint8_t> bytes;
	DataTypes dataType;
	void GetData(int value);
	void GetData(std::string value);
	void GetData(double value);
	void GetData(float value);
	void PrintData();
	void PrintBytes();
	DataReturn ReturnData();
	std::string DataString();
	void SaveData(std::string path);
	void LoadData(std::string path);
};

void DataNode::GetData(int value){
	bytes.resize(sizeof(value));
	std::memcpy(bytes.data(), &value, sizeof(value));
	dataType = DataTypes::Int;
}
void DataNode::GetData(double value){
	bytes.resize(sizeof(value));
	std::memcpy(bytes.data(), &value, sizeof(value));
	dataType = DataTypes::Double;
}
void DataNode::GetData(float value){
	bytes.resize(sizeof(value));
	std::memcpy(bytes.data(), &value, sizeof(value));
	dataType = DataTypes::Float;
}
void DataNode::GetData(std::string value){
	bytes.resize(value.size());
	std::memcpy(bytes.data(), value.data(), value.size());
	dataType = DataTypes::String;
}

void DataNode::PrintData(){
	if(dataType == DataTypes::Int){
		int value;
		std::memcpy(&value, this->bytes.data(), sizeof(value));
		std::cout<<std::to_string(value)<<std::endl;
	}
	if(dataType == DataTypes::Double){
		double value;
		std::memcpy(&value, this->bytes.data(), sizeof(value));
		std::cout<<std::to_string(value)<<std::endl;
	}
	if(dataType == DataTypes::Float){
		float value;
		std::memcpy(&value, this->bytes.data(), sizeof(value));
		std::cout<<std::to_string(value)<<std::endl;
	}
	else if(dataType == DataTypes::String){
		std::string value(this->bytes.begin(), this->bytes.end());
		std::cout<<value<<std::endl;
	}
}
void DataNode::PrintBytes(){
	for(int i=0; i<bytes.size(); i++){
		std::cout<<static_cast<int>(this->bytes[i])<<" ";
	}
	std::cout<<std::endl;
}
DataReturn DataNode::ReturnData(){
	if(this->dataType == DataTypes::Int){
		int value;
		std::memcpy(&value, this->bytes.data(), sizeof(value));
		return DataReturn(std::to_string(value), this->dataType);
	}
	else if(this->dataType == DataTypes::Double){
		double value;
		std::memcpy(&value, this->bytes.data(), sizeof(value));
		return DataReturn(std::to_string(value), this->dataType);
	}
	else if(this->dataType == DataTypes::Float){
		float value;
		std::memcpy(&value, this->bytes.data(), sizeof(value));
		return DataReturn(std::to_string(value), this->dataType);
	}
	else if(this->dataType == DataTypes::String){
		std::string value(this->bytes.begin(), this->bytes.end());
		return DataReturn(value, this->dataType);
	}
	return DataReturn();
}
std::string DataNode::DataString(){
	std::string dataString;
	for(int i=0; i<this->bytes.size(); i++){
		dataString+=char(this->bytes[i]);
	}
	return dataString;
}
void DataNode::SaveData(std::string path){
	std::ofstream file(path+this->id+".asc");
	file<<this->DataString()<<std::endl;
	file<<static_cast<char>(this->dataType)<<std::endl;
	file.close();
}
void DataNode::LoadData(std::string path){
	std::ifstream file(path+this->id+".asc");
	std::string value;
	int i = 0;
	while(getline(file, value)){
		if(i==0){
			bytes.resize(value.size());
			std::memcpy(bytes.data(), value.data(), value.size());
			i+=1;
			for(int j=0; j<bytes.size(); j++){
				std::cout<<static_cast<int>(bytes[j])<<" ";
			}
		}
		else{
			std::cout<<TypesMap[static_cast<DataTypes>(int(value[0]))]<<std::endl;
			this->dataType = static_cast<DataTypes>(int(value[0]));
		}
	}
}

