# FDM -> Filesystem_database_manager
A database working on files and folders. Project is supposed to be made with 3 crucial elements

## Table of contents
* [FDM - Filesystem database manager](#FMD)
* [UDF - Unified data format](#UDF)
* [FDC - Filesystem database comunicator](#FDC)

## FDM
all functions to controll the database and manage files
### Database - database struct
* Constructor - Database db = Database(string name, string path);
* CreateTable - db.CreateTable(string TableName, {{string ValueName, [DataTypes](#DataTypes)}, {...}, ...});

### Work overview
while constructing Database struct, program creates a folder on path with name(path = ./a, name = b, folder ./a/b created). While creating table, program maked another folder on database path + table name, and creates .sln file to store informations about collumn names and types.

## UDF
Data format to store any data type in one type using conversion to bytes and storing the data type name separately

### DataTypes
enum with possible types
* DataTypes::Int/Float/Double/String/Undefined;

### overwiew and all functionality will be later

## FDC
Cli to send commands to FDM and return a certain data

### Currently made
* UDF, and partialy FDM

### To do
* basicly whole project
