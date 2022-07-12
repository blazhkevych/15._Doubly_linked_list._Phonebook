#pragma once
using namespace std;

template <typename T>
struct Elem
{
	T m_data;
	Elem* m_next, * m_prev;
};

template <typename T>
class List
{
	// Голова хвост
	Elem<T>* m_head, * m_tail;
	int m_count;

public:

	// Конструктор
	List();

	// Конструктор копирования
	List(const List&);

	// Деструктор
	~List();

	// Получить количество элементов
	int GetCount();

	// Получить элемент списка
	Elem<T>* GetElem(int);

	// Удалить весь список
	void DelAll();

	// Удаление элемента по индексу
	void Del(int pos);

	// Вставка элемента в заданную позицию
	void Insert(T data, int pos);

	// Добавление в конец списка
	void AddTail(T data);

	// Добавление в начало списка
	void AddHead(T data);

	//Удаление головного элемента
	void DelHead();

	//Удаление хвостового элемента
	void DelTail();

	// Печать списка, начиная с головы
	void PrintHead();

	//Печать списка, начиная с хвоста
	void PrintTail();

	//перегрузка оператора =
	List& operator = (const List&);

	//##################################################################### Проверить нижележащие методы и перевести в шаблонные.
	// Метод поиска заданного элемента по ключу. Ключ
	// передаётся методу в качестве параметра. Метод
	// возвращает позицию найденного элемента в случае
	// успеха или - 1 в противном случае.
	int Find(char key) const;

	// Метод замены значения указанного элемента на другое
	// значение, передаваемое методу в качестве параметра.
	void Replace(char value, int position) const;

};

template <typename T>
List<T>::List()
{
	m_head = m_tail = nullptr;
	m_count = 0;
}

template <typename T>
List<T>::List(const List<T>& L)
{
	m_head = m_tail = nullptr;
	m_count = 0;
	Elem<T>* temp = L.m_head;
	while (temp != nullptr)
	{
		AddTail(temp->m_data);
		temp = temp->m_next;
	}
}

template <typename T>
List<T>::~List()
{
	DelAll();
}

template <typename T>
void List<T>::AddHead(T data)
{
	Elem<T>* temp = new Elem < T >;
	temp->m_prev = nullptr;
	temp->m_data = data;
	temp->m_next = m_head;
	if (m_head != nullptr)
		m_head->m_prev = temp;
	m_head = temp;
	if (m_tail == nullptr)
		m_tail = temp;
	m_count++;
}

template <typename T>
void List<T>::AddTail(T data)
{
	Elem<T>* temp = new Elem < T >;
	temp->m_next = nullptr;
	temp->m_data = data;
	temp->m_prev = m_tail;
	if (m_tail != nullptr)
		m_tail->m_next = temp;
	m_tail = temp;
	if (m_head == nullptr)
		m_head = temp;
	m_count++;
}

template <typename T>
void List<T>::DelHead()
{
	if (m_head != nullptr)
	{
		Elem<T>* temp = m_head;
		m_head = m_head->m_next;
		if (m_head != nullptr)
			m_head->m_prev = nullptr;
		else
			m_tail = nullptr;
		delete temp;
		m_count--;
	}
}

template <typename T>
void List<T>::DelTail()
{
	if (m_tail != nullptr)
	{
		Elem<T>* temp = m_tail;
		m_tail = m_tail->m_prev;
		if (m_tail != nullptr)
			m_tail->m_next = nullptr;
		else
			m_head = nullptr;
		delete temp;
		m_count--;
	}
}

template <typename T>
void List<T>::Insert(T data, int pos)
{
	if (pos < 0 || pos > m_count)
		return;
	if (pos == 0)
	{
		AddHead(data);
		return;
	}
	if (pos == m_count)
	{
		AddTail(data);
		return;
	}
	Elem<T>* current = nullptr;
	if (pos < m_count / 2)
	{
		current = m_head;
		int i = 0;
		while (i < pos)
		{
			current = current->m_next;
			i++;
		}
	}
	else
	{
		current = m_tail;
		int i = m_count - 1;
		while (i > pos)
		{
			current = current->m_prev;
			i--;
		}
	}
	Elem<T>* temp = new Elem < T >;
	temp->m_data = data;
	temp->m_prev = current->m_prev;
	temp->m_next = current;
	current->m_prev->m_next = temp;
	current->m_prev = temp;
	m_count++;
}

template <typename T>
void List<T>::Del(int pos)
{
	if (pos < 0 || pos >= m_count)
		return;
	if (pos == 0)
	{
		DelHead();
		return;
	}
	if (pos == m_count - 1)
	{
		DelTail();
		return;
	}
	Elem<T>* delElement = nullptr;
	if (pos < m_count / 2)
	{
		delElement = m_head;
		int i = 0;
		while (i < pos)
		{
			delElement = delElement->m_next;
			i++;
		}
	}
	else
	{
		delElement = m_tail;
		int i = m_count - 1;
		while (i > pos)
		{
			delElement = delElement->m_prev;
			i--;
		}
	}
	delElement->m_prev->m_next = delElement->m_next;
	delElement->m_next->m_prev = delElement->m_prev;
	delete delElement;
	m_count--;
}

template <typename T>
void List<T>::PrintHead()
{
	Elem<T>* current = m_head;
	while (current != nullptr)
	{
		cout << current->m_data;
		current = current->m_next;
	}
	cout << endl;
}

template <typename T>
void List<T>::PrintTail()
{
	Elem<T>* current = m_tail;
	while (current != nullptr)
	{
		cout << current->m_data;
		current = current->m_prev;
	}
	cout << endl;
}

template <typename T>
void List<T>::DelAll()
{
	while (m_head != nullptr)
		DelHead();
}

template <typename T>
int List<T>::GetCount()
{
	return m_count;
}

template <typename T>
Elem<T>* List<T>::GetElem(int pos)
{
	Elem<T>* temp = m_head;
	if (pos < 0 || pos >= m_count)
		return nullptr;
	int i = 0;
	while (i < pos)
	{
		temp = temp->m_next;
		i++;
	}
	return temp;
}

template <typename T>
List<T>& List<T>::operator = (const List<T>& L)
{
	if (this == &L)
		return *this;
	DelAll();
	Elem<T>* temp = L.m_head;
	while (temp != nullptr)
	{
		AddTail(temp->m_data);
		temp = temp->m_next;
	}
	return *this;
}

// Метод поиска заданного элемента по ключу. Ключ
// передаётся методу в качестве параметра. Метод
// возвращает позицию найденного элемента в случае
// успеха или - 1 в противном случае.
template<typename T>
inline int List<T>::Find(char key) const
{
	int position{ 0 };
	// Запоминаем адрес головного элемента.
	const Elem<T>* temp = m_head;
	// Пока еще есть элементы.
	while (temp != nullptr)
	{
		if (key == temp->m_data)
		{
			return position;
		}
		// Переходим на следующий элемент.
		temp = temp->m_next;
		position++;
	}

	return -1;
}