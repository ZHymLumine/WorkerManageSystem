#include"workerManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

WorkManager::WorkManager()
{
	//1.�ļ���������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.�ļ����� ����Ϊ��
	char ch;
	ifs >> ch;;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ�գ�" << endl;

		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.�ļ����ڣ� ���Ҽ�¼����
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ�� " << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//���ļ��е����ݣ��浽������
	this->init_Emp();

	//���Դ���
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		this->m_EmpArray[i]->showInfo();
	}
	*/

}

void WorkManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ��  *********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
}
//�˳���������ʵ��
void WorkManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0); //�˳�����
}

void WorkManager::addEmp()
{
	int addsize;
	cout << "��������Ҫ��ӵ�ְ������: "<<endl;
	cin >> addsize;

	
	
	if (addsize > 0)
	{	
		//��������¿ռ��С
		int newSize = this->m_EmpNum + addsize;

		//�����¿ռ�
		Worker** newEmpArray = new Worker * [newSize];

		//��ԭ�ռ��µ����ݿ������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newEmpArray[i] = this->m_EmpArray[i];
			}
		}
		
		//�������������
		for (int i = 0; i < addsize; i++)
		{
			int id; //ְ�����
			string name; //ְ������
			int dSelect; //����ѡ��

			cout << "������� " << i + 1 << " ����ְ����ţ� " << endl;
			cin >> id;

			cout << "������� " << i + 1 << " ����ְ�������� " << endl;
			cin >> name;

			cout << "��ѡ���" << i + 1 << " ����ְ����λ�� " << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
			//������ְ�� ���浽������
			newEmpArray[this->m_EmpNum + i] = worker;

			
		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newEmpArray;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�յı�־
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ���� " << addsize << " ����ְ��";

		//�������ݵ��ļ���
		this->save();
	}
	else
	{
		cout << "��������";
	}

	system("pause");
	system("cls");
}

void WorkManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//д���ļ�
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	ofs.close();
}

//ͳ������
int WorkManager:: get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)    //��ȡ����
	{
		num++;
	}

	return num;
}



//��ʼ��Ա��
void WorkManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)    //��ȡ����
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
		//�����������
		this->m_EmpArray[index] = worker;
		index++;
	}

	ifs.close();

}

//��ʾְ����Ϣ
void WorkManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0 ; i < this->m_EmpNum; i++)
		{	
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	//�������������
	system("pause");
	system("cls");
}

//ְ���Ƿ����
int WorkManager::IsExist(int id)
{	
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//�ҵ�Ա��
			index = i;
			break;
		}
	}
	return index;
}

//ɾ��Ա��
void WorkManager::Del_Emp()
{	
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{	//���ձ��ɾ��ְ��
		cout << "����������ɾ����ְ���ı�ţ� " << endl;
		int del_id;
		
		cin >> del_id;
		int index = this->IsExist(del_id);
		if (index != -1)
		{   
			//����ǰ��
			for (index; index < this->m_EmpNum; index++)
			{
				this->m_EmpArray[index] = this->m_EmpArray[index + 1];
			}
			
			this->m_EmpNum--; //���������м�¼��Ա����

			//����ͬ�����µ��ļ���
			this->save();

			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}

	system("pause");
	system("cls");
}


//�޸�ְ��
void WorkManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�����������޸ĵ�ְ���ı�ţ� " << endl;
		int mod_id;

		cin >> mod_id;
		int index = this->IsExist(mod_id);
		if (index != -1)
		{
			
			int id; //ְ�����
			string name; //ְ������
			int dSelect; //����ѡ��

			cout << "�������޸ĺ��ְ����ţ� " << endl;
			cin >> id;

			cout << "�������޸ĺ��ְ�������� " << endl;
			cin >> name;

			cout << "��ѡ��ְ����λ�� " << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
			//���޸ĺ��ְ�����ݱ��浽������
			this->m_EmpArray[index] = worker;

		
			//����ͬ�����µ��ļ���
			this->save();

			cout << "�޸ĳɹ���" << endl;
		}
		else
		{
			cout << "�޸�ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}

	system("pause");
	system("cls");
}

//����ְ��
void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ�� " << endl;
		cout << "1.��ְ����Ų���" << endl;
		cout << "2.��ְ����������" << endl;

		int select;
		cin >> select;

		if (select == 1) 
		{
			int id;
			cout << "��������ҵ�ְ����ţ� " << endl;
			cin >> id;
			int index = this->IsExist(id);

			if (index != -1)
			{	
				cout << "���ҳɹ���ְ����Ϣ���£� " << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "���޴���" << endl;
			}
		}
		else if (select == 2)
		{	
			string name;
			cout << "��������ҵ�ְ�������� " << endl;
			cin >> name;

			bool find_flag = false; //�Ƿ�鵽 �ı��
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{	
					cout << "���ҳɹ���ְ�����Ϊ�� "<<this->m_EmpArray[i]->m_Id
						<<"��ְ����Ϣ���£� "<< endl;
					this->m_EmpArray[i]->showInfo();
					find_flag = true;
				}
			}

			if (find_flag == false)
			{
				cout << "���޴���" << endl;
			}
		}
		else
		{
			cout << "�������" << endl;
		}
	}

	system("pause");
	system("cls");
}


//����ְ��
void WorkManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ�� " << endl;
		cout << "1.��ְ���Ž�������" << endl;
		cout << "2.��ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1) //����
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else //����
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
		cout << "����ɹ��������Ľ��Ϊ�� " << endl;
		this->save(); //���������Ľ��
		this->Show_Emp();
	}

}

//����ļ�
void WorkManager::Clean_File()
{
	cout << "ȷ�������" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc); //ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpArray != NULL)
		{	
			//ɾ������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ����������ָ��
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