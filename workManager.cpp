#include"workerManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

WorkManager::WorkManager()
{
	//1.文件不存在在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.文件存在 数据为空
	char ch;
	ifs >> ch;;
	if (ifs.eof())
	{
		//cout << "文件为空！" << endl;

		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.文件存在， 并且记录数据
	int num = this->get_EmpNum();
	//cout << "职工人数为： " << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//将文件中的数据，存到数组中
	this->init_Emp();

	//测试代码
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		this->m_EmpArray[i]->showInfo();
	}
	*/

}

void WorkManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！  *********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
}
//退出程序函数的实现
void WorkManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0); //退出程序
}

void WorkManager::addEmp()
{
	int addsize;
	cout << "请输入您要添加的职工人数: "<<endl;
	cin >> addsize;

	
	
	if (addsize > 0)
	{	
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addsize;

		//开辟新空间
		Worker** newEmpArray = new Worker * [newSize];

		//将原空间下的数据拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newEmpArray[i] = this->m_EmpArray[i];
			}
		}
		
		//批量添加新数据
		for (int i = 0; i < addsize; i++)
		{
			int id; //职工编号
			string name; //职工姓名
			int dSelect; //部门选择

			cout << "请输入第 " << i + 1 << " 个新职工编号： " << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << " 个新职工姓名： " << endl;
			cin >> name;

			cout << "请选择第" << i + 1 << " 个新职工岗位： " << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建职工 保存到数组中
			newEmpArray[this->m_EmpNum + i] = worker;

			
		}
		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newEmpArray;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空的标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加 " << addsize << " 名新职工";

		//保存数据到文件中
		this->save();
	}
	else
	{
		cout << "输入有误";
	}

	system("pause");
	system("cls");
}

void WorkManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//写入文件
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	ofs.close();
}

//统计人数
int WorkManager:: get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)    //读取人数
	{
		num++;
	}

	return num;
}



//初始化员工
void WorkManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)    //读取人数
	{
		Worker* worker = NULL;
		if (dId == 1)
		{
			 worker = new Employee(id, name, dId);
		}
		else if(dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)
		{
			worker = new Boss(id, name, dId);
		}
		//存放在数组中
		this->m_EmpArray[index] = worker;
		index++;
	}

	ifs.close();

}

//显示职工信息
void WorkManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0 ; i < this->m_EmpNum; i++)
		{	
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}

//职工是否存在
int WorkManager::IsExist(int id)
{	
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//找到员工
			index = i;
			break;
		}
	}
	return index;
}

//删除员工
void WorkManager::Del_Emp()
{	
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{	//按照编号删除职工
		cout << "请输入你想删除的职工的编号： " << endl;
		int del_id;
		
		cin >> del_id;
		int index = this->IsExist(del_id);
		if (index != -1)
		{   
			//数据前移
			for (index; index < this->m_EmpNum; index++)
			{
				this->m_EmpArray[index] = this->m_EmpArray[index + 1];
			}
			
			this->m_EmpNum--; //更新数组中记录人员个数

			//数据同步更新到文件中
			this->save();

			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}

	system("pause");
	system("cls");
}


//修改职工
void WorkManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入你想修改的职工的编号： " << endl;
		int mod_id;

		cin >> mod_id;
		int index = this->IsExist(mod_id);
		if (index != -1)
		{
			
			int id; //职工编号
			string name; //职工姓名
			int dSelect; //部门选择

			cout << "请输入修改后的职工编号： " << endl;
			cin >> id;

			cout << "请输入修改后的职工姓名： " << endl;
			cin >> name;

			cout << "请选择职工岗位： " << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}
			//将修改后的职工数据保存到数组中
			this->m_EmpArray[index] = worker;

		
			//数据同步更新到文件中
			this->save();

			cout << "修改成功！" << endl;
		}
		else
		{
			cout << "修改失败，未找到该职工" << endl;
		}
	}

	system("pause");
	system("cls");
}

//查找职工
void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式： " << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按职工姓名查找" << endl;

		int select;
		cin >> select;

		if (select == 1) 
		{
			int id;
			cout << "请输入查找的职工编号： " << endl;
			cin >> id;
			int index = this->IsExist(id);

			if (index != -1)
			{	
				cout << "查找成功，职工信息如下： " << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "查无此人" << endl;
			}
		}
		else if (select == 2)
		{	
			string name;
			cout << "请输入查找的职工姓名： " << endl;
			cin >> name;

			bool find_flag = false; //是否查到 的标记
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{	
					cout << "查找成功，职工编号为： "<<this->m_EmpArray[i]->m_Id
						<<"号职工信息如下： "<< endl;
					this->m_EmpArray[i]->showInfo();
					find_flag = true;
				}
			}

			if (find_flag == false)
			{
				cout << "查无此人" << endl;
			}
		}
		else
		{
			cout << "输入错误" << endl;
		}
	}

	system("pause");
	system("cls");
}


//排序职工
void WorkManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式： " << endl;
		cout << "1.按职工号进行升序" << endl;
		cout << "2.按职工号进行降序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1) //升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else //降序
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功，排序后的结果为： " << endl;
		this->save(); //保存排序后的结果
		this->Show_Emp();
	}

}

//清空文件
void WorkManager::Clean_File()
{
	cout << "确定清空吗？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc); //删除文件后重新创建
		ofs.close();

		if (this->m_EmpArray != NULL)
		{	
			//删除堆区每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;

			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;

		}
	}
}

WorkManager::~WorkManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}