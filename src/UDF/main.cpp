#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdint>
#include <map>

enum class DataTypes{ Int, Double, String, Undefined };

std::map<DataTypes, std::string> TypesMap = {{DataTypes::Int, "Int"}, {DataTypes::Double, "Double"}, {DataTypes::String, "String"}, {DataTypes::Undefined, "Undefined"}};

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
	void GetData(int data);
	void GetData(std::string data);
	void PrintData();
	void PrintBytes();
	DataReturn ReturnData();
};

void DataNode::GetData(int value){
	bytes.resize(sizeof(value));
	std::memcpy(bytes.data(), &value, sizeof(value));
	dataType = DataTypes::Int;
}
void DataNode::GetData(std::string value){
	bytes.resize(value.size());
	std::memcpy(bytes.data(), value.data(), sizeof(value));
	dataType = DataTypes::String;
}

void DataNode::PrintData(){
	if(dataType == DataTypes::Int){
		int value;
		std::memcpy(&value, this->bytes.data(), sizeof(value));
		std::cout<<value<<std::endl;
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
	else if(this->dataType == DataTypes::String){
		std::string value(this->bytes.begin(), this->bytes.end());
		return DataReturn(value, this->dataType);
	}
	return DataReturn();
}

int main(){
	
	DataNode node;
	node.GetData(19482);
	node.PrintBytes();
	node.PrintData();
	node.GetData("test textą");
	node.PrintBytes();
	node.PrintData();
	node.ReturnData().PrintData();
	return 0;
}

