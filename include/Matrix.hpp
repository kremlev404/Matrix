#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using std::cout;
using std::cin;
using std::cerr;

template <typename T>
T myAbs(T num) { // Модуль числа.
	return num > 0 ? num : -num;
}

template <typename T>
void chek_in(T& a) { // Функция проверки ввода.
	while (!(cin >> a)) {
		cerr << "Error\n";
		cin.clear();
		cin.ignore(132, '\n');
	}
}

class matrix {

private:

	int size; // Размер матрицы.
	double** arr; // Указатель на двумерный динамический массив.
	matrix minorom(const int& index1, const int& index2); // Взятие минорома.
	double det1D(void); // Определитель одинарной матрицы.
	double det2D(void); // Определитель двойной матрицы.
	double det3D(void); // Определитель тройной матрицы.
	double aldop(const int& index1, const int& index2); // Алгебраическое дополнение.
	void setSize(int _size); // Установка нового размера.

public:

	/*=====================================================================================================================================================*/

	matrix(void); // Конструктор по умолчанию.
	matrix(int& _size); // Конструктор с параметром размера.
	matrix(matrix& exist); // Конструктор с параметром существующей матрицы.
	~matrix(void); // Деструктор по умолчанию.
	int getSize(void); // Взятие размера.
	void setArr(double* _arr, int n); // Установка матрицы через одномерный массив.
	double* getArr(int& len); // Взятие массива, первым параметром идет переменная в которую будет производиться запись размера.
	void clear(void); // Заполнение нулями.
	void random(void); // Заполнение случайно сгенерированными числами.
	void destroy(void); // Принудительный деструктор.
	void setStr(double* _arr, const int& numStr); // Установка строки вместо numStr.
	double* getStr(const int& index); // Взятие строки с индексом index.
	void setStolb(double* _arr, const int& numStolb); // Установка столбца _arr вместо numStolb.
	double* getStolb(const int& index); // Взятие столбца с индексом index.

	/*=====================================================================================================================================================*/

	// Блок перегрузки математических операторов:

	matrix& operator= (matrix& other);
	matrix operator+ (matrix& a);
	matrix& operator++(void);
	matrix operator- (matrix& other);
	template <typename T>
	matrix operator+(T& other);
	matrix& operator--(void);
	matrix operator*(matrix& other);
	template <typename T>
	matrix operator*(T& other);
	template <typename T>
	matrix operator/(T& other);
	bool operator==(matrix& other);
	bool operator!=(matrix& other);

	/*=====================================================================================================================================================*/

	// Блок сложных операций:

	void print(void); // Печать матрицы.
	void save(std::ofstream& file); // Сохранение матрицы в файле.
	void load(std::ifstream& file); // Загрузка значений из файла.
	void printStr(const int& indexStr); // Печать строки.
	void printStolb(const int& indexStolb); // Печать столбца.
	double det(void); // Общий определитель.
	matrix& transp(void); // Транспонированная матрица.
	matrix& revers(void); // Обратная матрица
	bool isExist(void); // Проверка существования.

	/*=====================================================================================================================================================*/
};