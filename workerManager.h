#pragma once
#include<iostream>
#include"worker.h"
#include<fstream>
#define FILENAME "empFile.txt"

using namespace std;

class WorkManager
{
public:
	//���캯��
	WorkManager();

	//չʾ�˵�
	void showMenu();

	//�˳�ϵͳ
	void exitSystem();

	//����ְ��
	void addEmp();

	//�����ļ�
	void save();

	//��������
	~WorkManager();

	//ͳ������
	int get_EmpNum();
	
	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ����Ϣ
	void Show_Emp();

	//ְ���Ƿ����
	int IsExist(int id);

	//ɾ��Ա��
	void Del_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����ְ��
	void Sort_Emp();

	//����ļ�
	void Clean_File();
public:
	//��¼�ļ��е���������
	int m_EmpNum;
	
	//ְ������ָ��
	Worker** m_EmpArray;

	//�ж��ļ��Ƿ�Ϊ�յı�־
	bool m_FileIsEmpty;
};

