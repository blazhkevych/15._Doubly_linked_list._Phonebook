#include <iostream>
#include <iomanip>
#include <conio.h>
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

	cout << "������� ������� �������� � ���������� ���������� !" << endl
		<< "\n��� ����������� ������� ����� �������." << endl;

	_getch();
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

	cout << "������� ������� ������ �� ���������� ����� !" << endl
		<< "\n��� ����������� ������� ����� �������." << endl;
	_getch();
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

	cout << "������� ������� ������������� !" << endl
		<< "\n��� ����������� ������� ����� �������." << endl;
	_getch();
}

// ����� ��������� �� ����������� ������ ��� �������.
void Phonebook::SearchSubscriberBySurname()
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
	cout << "����� � ���������� ����������� �������� !" << endl
		<< "\n��� ����������� ������� ����� �������." << endl;

	_getch();
}

// ���������� ��������� � ���������� �������.
void Phonebook::PrintSubscribersInAscending()
{
	this->m_lst.Sort();

	PrintPhonebook();

	cout << "����� ��������� �� ����������� ����������� � ���������� ������� �������� !" << endl
		<< "\n��� ����������� ������� ����� �������." << endl;

	_getch();
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
		<< setw(5) << "Id"
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
	cout << "����� ��������� �� ����������� ����������� �������� !" << endl
		<< "\n��� ����������� ������� ����� �������." << endl;

	_getch();
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



	/*





	// ����� ������ ���� "m_name"
	int name_strlen = strlen(student.getName()) + 1;
	fwrite(&name_strlen, sizeof(int), 1, f_wright);

	// ����� �������� ���� "m_name"
	fwrite(student.getName(), name_strlen, 1, f_wright);

	// ����� ������ ���� "m_surname"
	int surname_strlen = strlen(student.getSurname()) + 1;
	fwrite(&surname_strlen, sizeof(int), 1, f_wright);

	// ����� �������� ���� "m_surname"
	fwrite(student.getSurname(), surname_strlen, 1, f_wright);

	// ����� �������� ���� "m_age"
	int age = student.getAge();
	fwrite(&age, sizeof(int), 1, f_wright);

	// ����� �������� ���� "m_phone"
	fwrite(student.getPhone(), 15, 1, f_wright);

	// ����� �������� ���� "m_average"
	double average = student.getAverage();
	fwrite(&average, sizeof(double), 1, f_wright);

	fclose(f_wright);


	*/
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

	int lenght = _filelength(_fileno(f_read));
	int numAbonentsInFile = lenght / sizeof(Abonent);

	for (int i = 0; i < numAbonentsInFile; i++)
	{
		Abonent abonent;
		//Book* book = new Book;
		fread(&abonent, sizeof(Abonent), 1, f_read);
		//b.PtrBook[b.Count++] = book;
		m_lst.Insert(abonent, i);
	}
	fclose(f_read);

	/*




	// ������ ������ ���� "m_name"
	int name_strlen{ 0 };
	fread(&name_strlen, sizeof(int), 1, f_read);

	// ������ �������� ���� "m_name"
	char* nameBufferRead = new char[name_strlen];
	fread(nameBufferRead, name_strlen, 1, f_read);
	student.setName(nameBufferRead);

	// ������ ������ ���� "m_surname"
	int surname_strlen{ 0 };
	fread(&surname_strlen, sizeof(int), 1, f_read);

	// ������ �������� ���� "m_surname"
	char* surnameBufferRead = new char[surname_strlen];
	fread(surnameBufferRead, surname_strlen, 1, f_read);
	student.setSurname(surnameBufferRead);

	// ������ �������� ���� "m_age"
	int age{ 0 };
	fread(&age, sizeof(int), 1, f_read);
	student.setAge(age);

	// ������ �������� ���� "m_phone"
	char phone[15]{ 0 };
	fread(phone, 15, 1, f_read);
	student.setPhone(phone);

	// ������ �������� ���� "m_average"
	double average{ 0.0 };
	fread(&average, sizeof(double), 1, f_read);
	student.setAverage(average);

	delete[]nameBufferRead;
	delete[]surnameBufferRead;
	fclose(f_read);



	 */
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
