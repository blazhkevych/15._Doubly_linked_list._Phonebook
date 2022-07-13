#include <iostream>
#include <iomanip>
#include <io.h>
#include "Phonebook.h"

using std::setw;
using std::cout;
using std::endl;
using std::cin;

// Добавление абонентов в телефонный справочник.
void Phonebook::AddAbonent()
{
	Abonent abonent{};

	cout << "\nФамилия: ";
	cin.getline(abonent.m_surname, 100);

	cout << "\nИмя: ";
	cin.getline(abonent.m_name, 100);

	cout << "\nАдрес: ";
	cin.getline(abonent.m_address, 100);

	cout << "\nТелефон: ";
	cin.getline(abonent.m_phone, 100);

	cout << "\nВозраст: ";
	cin >> abonent.m_age;

	m_lst.AddTail(abonent);
}

// Удаление абонентов из телефонного справочника по позиции.
void Phonebook::DeleteAbonent()
{
	PrintPhonebookHeader();
	PrintPhonebook();

	cout << "Введите Id для удаления абонента: ";
	int id;
	cin >> id;

	m_lst.Del(id);
}

// Модификация данных абонента.
void Phonebook::SubscriberDataModification()
{
	PrintPhonebookHeader();
	PrintPhonebook();

	cout << "\nВведите Id для модификации данных абонента: ";
	int id;
	cin >> id;
	cin.get(); // Убирает ентер из потока.

	m_lst.Del(id);

	cout << endl << "Введите новые данные выбранного абонента: ";

	Abonent abonent{};

	cout << "\nФамилия: ";
	cin.getline(abonent.m_surname, 100);

	cout << "\nИмя: ";
	cin.getline(abonent.m_name, 100);

	cout << "\nАдрес: ";
	cin.getline(abonent.m_address, 100);

	cout << "\nТелефон: ";
	cin.getline(abonent.m_phone, 100);

	cout << "\nВозраст: ";
	cin >> abonent.m_age;

	m_lst.AddTail(abonent);
}

// Поиск абонентов по телефонному номеру или фамилии.
void Phonebook::SearchSubscriberBySurnameOrPhone()
{
	char surname[100];
	char phone[100];
	cout << "Введите фамилию: ";
	cin.getline(surname, 100);

	cout << "\nВведите телефон: ";
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

// Распечатка абонентов в алфавитном порядке.
void Phonebook::PrintSubscribersInAscending()
{
	this->m_lst.Sort();
	PrintPhonebook();
}

// Вывод главного меню.
void Phonebook::PrintMainMenu()
{
	cout << "\tГлавное меню."
		"\n1. Добавление абонентов в телефонный справочник."
		"\n2. Удаление абонентов из телефонного справочника."
		"\n3. Модификация данных абонента."
		"\n4. Поиск абонентов по телефонному номеру или фамилии."
		"\n5. Распечатка абонентов в алфавитном порядке."
		"\n6. Выход."
		<< endl;
}

// Вывод "шапки" списка абонентов.
void Phonebook::PrintPhonebookHeader()
{
	cout << endl
		<< setw(5) << "ID"
		<< setw(15) << "ФАМИЛИЯ"
		<< setw(15) << "ИМЯ"
		<< setw(40) << "АДРЕС"
		<< setw(15) << "ТЕЛЕФОН"
		<< setw(8) << "ВОЗРАСТ"
		<< endl;
}

// Вывод списка абонентов.
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

// Сохранение телефонного справочника в файл.
void Phonebook::SavePhonebookIntoFile()
{
	if (m_lst.GetCount() == 0) // Если в Phonebook пусто, то ничего не сохраняем в файл и выходим.
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

// Чтение телефонного справочника из файла.
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

// Перегрузка оператора ">" для "this > object".
bool Abonent::operator>(const Abonent& abonent) const
{
	if (strcmp(this->m_surname, abonent.m_surname) == 1)
	{
		return true;
	}
	return false;
}
