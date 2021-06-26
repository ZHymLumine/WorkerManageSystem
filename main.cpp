#include<iostream>
#include<fstream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;




int main()
{	
	/*Worker *worker1 = new Employee(1, "张三", 1);
	worker1->showInfo();
	delete worker1;

	Worker* worker2 = new Manager(2, "李四", 2);
	worker2->showInfo();
	delete worker2;

	Worker* worker3 = new Boss(3, "王五", 3);
	worker3->showInfo();
	delete worker3;*/

	WorkManager wm;
	int choice = 0;
	while (true)
	{
		wm.showMenu();
		cout << "请输入您的选择"<<endl;
		cin >> choice;

		switch(choice)
		{
		case 0: //退出系统
			wm.exitSystem();
			break;
		case 1:
			wm.addEmp();
			break;
		case 2:
			wm.Show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");

	return 0;
}