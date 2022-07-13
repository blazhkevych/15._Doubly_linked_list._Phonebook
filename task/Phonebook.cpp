#include <iostream>
#include <iomanip>
#include <io.h>
#include "Phonebook.h"

using std::setw;
using std::cout;
using std::endl;
using std::cin;

// ���������� ��������� � ���������� ����������.
void Phonebook::AddAbonent()
{
	Abonent abonent{};

	cout << "\n�������: ";
	cin.getline(abonent.m_surname, 100);

	cout << "\n���: ";
	cin.getline(abonent.m_name, 100);

	cout << "\n�����: ";
	cin.getline(abonent.m_address, 100);

	cout << "\n�������: ";
	cin.getline(abonent.m_phone, 100);

	cout << "\n�������: ";
	cin >> abonent.m_age;

	m_lst.AddTail(abonent);
}

// �������� ��������� �� ����������� ����������� �� �������.
void Phonebook::DeleteAbonent()
{
	PrintPhonebookHeader();
	PrintPhonebook();

	cout << "������� Id ��� �������� ��������: ";
	int id;
	cin >> id;

	m_lst.Del(id);
}

// ����������� ������ ��������.
void Phonebook::SubscriberDataModification()
{
	PrintPhonebookHeader();
	PrintPhonebook();

	cout << "\n������� Id ��� ����������� ������ ��������: ";
	int id;
	cin >> id;
	cin.get(); // ������� ����� �� ������.

	m_lst.Del(id);

	cout << endl << "������� ����� ������ ���������� ��������: ";

	Abonent abonent{};

	cout << "\n�������: ";
	cin.getline(abonent.m_surname, 100);

	cout << "\n���: ";
	cin.getline(abonent.m_name, 100);

	cout << "\n�����: ";
	cin.getline(abonent.m_address, 100);

	cout << "\n�������: ";
	cin.getline(abonent.m_phone, 100);

	cout << "\n�������: ";
	cin >> abonent.m_age;

	m_lst.AddTail(abonent);
}

// ����� ��������� �� ����������� ������ ��� �������.
void Phonebook::SearchSubscriberBySurnameOrPhone()
{
	char surname[100];
	char phone[100];
	cout << "������� �������: ";
	cin.getline(surname, 100);

	cout << "\n������� �������: ";
	cin.getline(phone, 100);

	const int count = m_lst.GetCount();
	for (int i = 0; i < count; i++)
	{
		if (!strcmp(phone, m_lst.GetElem(i)->m_data.m_phone) || !strcmp(surname, m_lst.GetElem(i)->m_data.m_surname))
		{
			PrintPhonebookHeader();
			cout << setw(5) << i
				<< setw(15) << m_lst.GetElem(i)->m_data.m_surname
				<< setw(15) << m_lst.GetElem(i)->m_data.m_name
				<< setw(40) << m_lst.GetElem(i)->m_data.m_address
				<< setw(15) << m_lst.GetElem(i)->m_data.m_phone
				<< setw(8) << m_lst.GetElem(i)->m_data.m_age
				<< endl;
		}
	}
}

// ���������� ��������� � ���������� �������.
void Phonebook::PrintSubscribersInAscending()
{
	this->m_lst.Sort();
	PrintPhonebook();
}

// ����� �������� ����.
void Phonebook::PrintMainMenu()
{
	cout << "\t������� ����."
		"\n1. ���������� ��������� � ���������� ����������."
		"\n2. �������� ��������� �� ����������� �����������."
		"\n3. ����������� ������ ��������."
		"\n4. ����� ��������� �� ����������� ������ ��� �������."
		"\n5. ���������� ��������� � ���������� �������."
		"\n6. ���������� ����������� ����������� � ����."
		"\n7. �������� ����������� ����������� �� �����."
		"\n8. �����."
		<< endl;
}

// ����� "�����" ������ ���������.
void Phonebook::PrintPhonebookHeader()
{
	cout << endl
		<< setw(5) << "ID"
		<< setw(15) << "�������"
		<< setw(15) << "���"
		<< setw(40) << "�����"
		<< setw(15) << "�������"
		<< setw(8) << "�������"
		<< endl;
}

// ����� ������ ���������.
void Phonebook::PrintPhonebook()
{
	const int count = m_lst.GetCount();
	for (int i = 0; i < count; i++)
	{
		cout << setw(5) << i
			<< setw(15) << m_lst.GetElem(i)->m_data.m_surname
			<< setw(15) << m_lst.GetElem(i)->m_data.m_name
			<< setw(40) << m_lst.GetElem(i)->m_data.m_address
			<< setw(15) << m_lst.GetElem(i)->m_data.m_phone
			<< setw(8) << m_lst.GetElem(i)->m_data.m_age
			<< endl;
	}
}

// ���������� ����������� ����������� � ����.
void Phonebook::SavePhonebookIntoFile()
{
	if (m_lst.GetCount() == 0) // ���� � Phonebook �����, �� ������ �� ��������� � ���� � �������.
		return;

	char fileNameWrite[20]{ "phonebook.data" };
	FILE* f_wright{ nullptr };
	fopen_s(&f_wright, fileNameWrite, "wb");
	if (f_wright == nullptr)
	{
		perror("Error opening");
		return;
	}

	for (int i = 0; i < m_lst.GetCount(); i++)
	{
		fwrite(m_lst.GetElem(i), sizeof(Abonent), 1, f_wright);
	}
	fclose(f_wright);
}

// ������ ����������� ����������� �� �����.
void Phonebook::LoadPhonebookFromFile()
{
	char fileNameRead[20]{ "phonebook.data" };
	FILE* f_read{ nullptr };
	fopen_s(&f_read, fileNameRead, "rb");
	if (f_read == nullptr)
	{
		perror("Error opening");
		return;
	}

	if (m_lst.GetCount() > 0) // ���� Phonebook �� ������, ������.
		m_lst.DelAll();

	const int lenght = _filelength(_fileno(f_read));
	int numAbonentsInFile = lenght / sizeof(Abonent);

	for (int i = 0; i < numAbonentsInFile; i++)
	{
		Abonent abonent;
		fread(&abonent, sizeof(Abonent), 1, f_read);
		m_lst.Insert(abonent, i);
	}
	fclose(f_read);
}

// ���������� ��������� ">" ��� "this > object".
bool Abonent::operator>(const Abonent& abonent) const
{
	if (strcmp(this->m_surname, abonent.m_surname) == 1)
	{
		return true;
	}
	return false;
}
