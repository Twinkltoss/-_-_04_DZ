#include <iostream>
#include <cassert>

using namespace std;

//Задание 1
//Реализуйте в классе MedalsTable из примера 18 возможность динамически задавать размер таблицы медалей.
//Текущая реализация для упрощения использует статический массив на 10 элементов.Замените его на динамически
//выделяемый массив.Для класса MedalsTable реализуйте
//семантику копирования и семантику перемещния(две пары конструктор / оператор присваивания).

class MedalRow
{
	char country[4];
	int medals[3];
public:
	static const int GOLD{ 0 };
	static const int SILVER{ 1 };
	static const int BRONZE{ 2 };
	MedalRow(const char* countryP, const int* medalsP)
	{
		strcpy_s(country, 4, countryP ? countryP : "NON");
		for (int i{ 0 }; i < 3; ++i)
		{
			medals[i] = medalsP ? medalsP[i] : 0;
		}
	}
	MedalRow() : MedalRow(nullptr, nullptr) {}
	MedalRow& setCountry(const char* countryP)
	{
		if (countryP)
		{
			strcpy_s(country, 4, countryP);
		}
		return *this;
	}
	const char* getCountry()const { return country; }
	71
		4. Специальные перегрузки — перегрузка[]
		int& operator[](int idx)
	{
		assert((idx >= 0 and idx < 3) and "Index out "
			"of range!");
		return medals[idx];
	}
	int operator[](int idx)const
	{
		assert((idx >= 0 and idx < 3) and "Index out "
			"of range!");
		return medals[idx];
	}
	void print()const
	{
		std::cout << '[' << country << "]-( ";
		for (int i{ 0 }; i < 3; ++i)
		{
			std::cout << medals[i];
			if (i < 2) { std::cout << '\t'; }
		}
		std::cout << " )\n";
	}
};
class MedalsTable
{
public:
	static const int maxSize{ 10 };
private:
	MedalRow medalRows[MedalsTable::maxSize];
	int size;
	int findCountry(const char* country)const
	{
		for (int i{ 0 }; i < size; ++i)
		{
			72
				Урок 4
				if (strcmp(medalRows[i].getCountry(),
					country) == 0)
				{
					return i;
				}
		}
		return -1;
	}
public:
	MedalsTable() : size{ 0 } {};
	MedalRow& operator[](const char* country)
	{
		int idx{ findCountry(country) };
		if (idx == -1)
		{
			assert(size < MedalsTable::maxSize and
				"Table is FULL!");
			idx = size++;
			medalRows[idx].setCountry(country);
		}
		return medalRows[idx];
	}
	const MedalRow& operator[](const char* country)const
	{
		int idx{ findCountry(country) };
		assert(idx != -1 and "Country not found on const "
			"table");
		return medalRows[idx];
	}
	void print()const
	{
		73
			4. Специальные перегрузки — перегрузка[]
			for (int i{ 0 }; i < size; ++i)
			{
				medalRows[i].print();
			}
	}
};

//	Задание 2
//	Дополните решение из задания 1 перегрузкой оператора помещения в поток(operator<<) для классов MedalRow и MedalsTable, заменив тем самым соответствующие
//	функции - члены print() в них.

 
//	Задание 3
//	Дополните решение из задания 2 реализацией оператора вызова функции для класса MedalsTable.
// Перегрузка должна принимать в качестве аргумента идентификатор
//	страны и возвращать одну из констант MedalRow::GOLD,
//	MedalRow::SILVER, MedalRow::BRONZE как константу
//	соответствующую максимальному количеству медалей
//	для заданной страны.То есть если, к примеру, у Польши
//	2 золотые, 4 серебрянных и одна бронзовая медаль, то
//	перегрузка оператора вызов функции с параметром POL
//	вернет MedalRow::SILVER.
 
 
//	Задание 4
//	Модифицируйте функтор NoSequence из задания 26,
//	чтоб он игнорировал не менее N подряд значений, где
//	N — параметр конструктора данного функтора.

template <typename T>
void print(T* begin, T* end, char delimiter = ' ')
{
	while (begin != end)
	{
		std::cout << *begin++ << delimiter;
	}
	std::cout << '\n';
}
template <typename T, typename Predicate>
int copy_if(T* srcB, T* srcE, T* destB, T* destE,
	Predicate pred)
{
	int copyCount{ 0 };
	while (destB != destE and srcB != srcE)
	{
		if (pred(*srcB))
		{
			*destB++ = *srcB;
			++copyCount;
		}
		++srcB;
	}
	return copyCount;
}
class NoSequence
{
	bool init;
	106
		Урок 4
		int prevEl;
public:
	NoSequence() : init{ false }, prevEl{ 0 } {}
	bool operator()(int el)
	{
		if (init)
		{
			bool result{ prevEl != el };
			if (result)
			{
				prevEl = el;
			}
			return result;
		}
		init = true;
		prevEl = el;
		return true;
	}
};


int main()
{
	MedalsTable mt1;
	std::cout << "Medals table #1:\n";
	mt1["UKR"][MedalRow::GOLD] = 14;
	mt1["UKR"][MedalRow::SILVER] = 5;
	mt1["HUN"][MedalRow::BRONZE] = 9;
	mt1["HUN"][MedalRow::GOLD] = 7;
	mt1["POL"][MedalRow::GOLD] = 4;
	mt1["POL"][MedalRow::SILVER] = 2;
	mt1.print();
	// создаем константную копию таблицы №1
	std::cout << "\nMedals table #2:\n";
	const MedalsTable mt2{ mt1 };
	mt2.print();
	// раскомментировав следующую строку можно протестировать
	// проверку отсутствия страны в константной таблице
	// медалей
	// программа аварийно завершиться, что нормально!
	// mt2["SLO"]

	//-----------------------------------------------------------------

	const int size{ 10 };
	int arr1[size]{ 1,1,1,4,5,5,7,8,9,9 };
	int arr2[size]{};
	int* const arr1Begin{ arr1 };
	int* const arr1End{ arr1 + size };
	int* const arr2Begin{ arr2 };
	int* const arr2End{ arr2 + size };
	int* arr2NewEnd{};
	std::cout << "Original arr1:\n";
	107
	std::cout << "Original arr2:\n";
	print(arr2, arr2 + size);
	std::cout << '\n';
	std::cout << "arr2 copy of arr1 without sequencing "
		"duplicates:\n";
	arr2NewEnd = arr2Begin + copy_if(arr1Begin, arr1End,
		arr2Begin, arr2End, NoSequence{});
	print(arr2, arr2NewEnd);
	std::cout << '\

}
