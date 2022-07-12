#include <iostream>
#include <iomanip>
#include <conio.h>
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

	cout << "Абонент успешно добавлен в телефонный справочник !" << endl
		<< "\nДля продолжения нажмите любую клавишу." << endl;

	_getch();
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

	cout << "Абонент успешно удален из телефонной книги !" << endl
		<< "\nДля продолжения нажмите любую клавишу." << endl;
	_getch();
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

	cout << "Абонент успешно модифицирован !" << endl
		<< "\nДля продолжения нажмите любую клавишу." << endl;
	_getch();
}

// Поиск абонентов по телефонному номеру или фамилии.
void Phonebook::SearchSubscriberBySurname()
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
	cout << "Поиск в телефонном справочнике завершен !" << endl
		<< "\nДля продолжения нажмите любую клавишу." << endl;

	_getch();
}

// Распечатка абонентов в алфавитном порядке.
void Phonebook::PrintSubscribersInAscending()
{
	this->m_lst.Sort();

	PrintPhonebook();

	cout << "Вывод абонентов из телефонного справочника в алфавитном порядке завершен !" << endl
		<< "\nДля продолжения нажмите любую клавишу." << endl;

	_getch();
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
		"\n6. Сохранение телефонного справочника в файл."
		"\n7. Загрузка телефонного справочника из файла."
		"\n8. Выход."
		<< endl;
}

// Вывод "шапки" списка абонентов.
void Phonebook::PrintPhonebookHeader()
{
	cout << endl
		<< setw(5) << "Id"
		<< setw(15) << "Фамилия"
		<< setw(15) << "Имя"
		<< setw(40) << "Адрес"
		<< setw(15) << "Телефон"
		<< setw(8) << "Возраст"
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
	cout << "Вывод абонентов из телефонного справочника завершен !" << endl
		<< "\nДля продолжения нажмите любую клавишу." << endl;

	_getch();
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



	/*





	// Пишем размер поля "m_name"
	int name_strlen = strlen(student.getName()) + 1;
	fwrite(&name_strlen, sizeof(int), 1, f_wright);

	// Пишем значение поля "m_name"
	fwrite(student.getName(), name_strlen, 1, f_wright);

	// Пишем размер поля "m_surname"
	int surname_strlen = strlen(student.getSurname()) + 1;
	fwrite(&surname_strlen, sizeof(int), 1, f_wright);

	// Пишем значение поля "m_surname"
	fwrite(student.getSurname(), surname_strlen, 1, f_wright);

	// Пишем значение поля "m_age"
	int age = student.getAge();
	fwrite(&age, sizeof(int), 1, f_wright);

	// Пишем значение поля "m_phone"
	fwrite(student.getPhone(), 15, 1, f_wright);

	// Пишем значение поля "m_average"
	double average = student.getAverage();
	fwrite(&average, sizeof(double), 1, f_wright);

	fclose(f_wright);


	*/
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

	if (m_lst.GetCount() > 0) // Если Phonebook ен пустой, чистим.
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




	// Читаем размер поля "m_name"
	int name_strlen{ 0 };
	fread(&name_strlen, sizeof(int), 1, f_read);

	// Читаем значение поля "m_name"
	char* nameBufferRead = new char[name_strlen];
	fread(nameBufferRead, name_strlen, 1, f_read);
	student.setName(nameBufferRead);

	// Читаем размер поля "m_surname"
	int surname_strlen{ 0 };
	fread(&surname_strlen, sizeof(int), 1, f_read);

	// Читаем значение поля "m_surname"
	char* surnameBufferRead = new char[surname_strlen];
	fread(surnameBufferRead, surname_strlen, 1, f_read);
	student.setSurname(surnameBufferRead);

	// Читаем значение поля "m_age"
	int age{ 0 };
	fread(&age, sizeof(int), 1, f_read);
	student.setAge(age);

	// Читаем значение поля "m_phone"
	char phone[15]{ 0 };
	fread(phone, 15, 1, f_read);
	student.setPhone(phone);

	// Читаем значение поля "m_average"
	double average{ 0.0 };
	fread(&average, sizeof(double), 1, f_read);
	student.setAverage(average);

	delete[]nameBufferRead;
	delete[]surnameBufferRead;
	fclose(f_read);



	 */
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
