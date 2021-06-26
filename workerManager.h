#pragma once
#include<iostream>
#include"worker.h"
#include<fstream>
#define FILENAME "empFile.txt"

using namespace std;

class WorkManager
{
public:
	//构造函数
	WorkManager();

	//展示菜单
	void showMenu();

	//退出系统
	void exitSystem();

	//增加职工
	void addEmp();

	//保存文件
	void save();

	//析构函数
	~WorkManager();

	//统计人数
	int get_EmpNum();
	
	//初始化员工
	void init_Emp();

	//显示职工信息
	void Show_Emp();

	//职工是否存在
	int IsExist(int id);

	//删除员工
	void Del_Emp();

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//排序职工
	void Sort_Emp();

	//清空文件
	void Clean_File();
public:
	//记录文件中的人数个数
	int m_EmpNum;
	
	//职工数组指针
	Worker** m_EmpArray;

	//判断文件是否为空的标志
	bool m_FileIsEmpty;
};

