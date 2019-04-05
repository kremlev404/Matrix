#pragma once
/****************************************************************************/
/*                                                                          */
/*       Библиотека для работы с квадратными матрицами                      */
/*                                                                          */
/****************************************************************************/

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

// Блок определения функций:

matrix::matrix(void) {
	this->size = 0;
	this->arr = nullptr;
	cout << "Сработал конструтор\n";
	return;
}

matrix::matrix(int& _size) {
	this->size = _size;
	this->arr = new double*[this->size];
	for (int i = 0; i < this->size; i++)
		this->arr[i] = new double[this->size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			this->arr[i][j] = 0;
	cout << "Сработал конструтор\n";
	return;
}

matrix::matrix(matrix& exist) {
	this->size = exist.size;
	this->arr = new double*[this->size];
	for (int i = 0; i < this->size; i++)
		this->arr[i] = new double[this->size];
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			this->arr[i][j] = exist.arr[i][j];
	cout << "Сработал конструтор\n";
	return;
}

matrix::~matrix(void) {
	if (this->arr != nullptr) {
		for (int i = 0; i < this->size; i++)
			delete[] this->arr[i];
		delete[] this->arr;
		this->size = 0;
		this->arr = nullptr;
		cout << "Сработал деструктор\n";
	}
	return;
}

void matrix::setSize(int _size) {

	if (this->arr == nullptr) {
		this->size = _size;
		this->arr = new double*[this->size];
		for (int i = 0; i < this->size; i++)
			this->arr[i] = new double[this->size];
		for (int i = 0; i < this->size; i++)
			for (int j = 0; j < this->size; j++)
				this->arr[i][j] = 0;
	}
	else {
		for (int i = 0; i < this->size; i++)
			delete[] this->arr[i];
		delete[] this->arr;
		this->size = _size;

		this->arr = new double*[this->size];
		for (int i = 0; i < this->size; i++)
			this->arr[i] = new double[this->size];
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				this->arr[i][j] = 0;
	}
	return;
}

int matrix::getSize(void) {
	int _size = this->size;
	return _size;
}

void matrix::setArr(double* _arr, int n) {
	if (this->size*this->size < n) {
		cout << "Error, size < size(arr)\n";
		exit(-1);
	}
	for (int i = 0; i < this->size; i++)
		for (int j = 0, k = 0; j < this->size; j++, k++)
			this->arr[i][j] = _arr[k];
	return;
}

double* matrix::getArr(int& len) {
	int n = size;
	len = n * n;
	double* resArr = new double[n];
	for (int i = 0; i < n; i++)
		for (int j = 0, k = 0; j < n; j++, k++)
			resArr[k] = arr[i][j];
	return resArr;
}

matrix& matrix::operator= (matrix& other) {
	if (this->arr != nullptr) {
		for (int i = 0; i < this->size; i++)
			delete[] this->arr[i];
		delete[] this->arr;
		this->size = 0;
		this->arr = nullptr;
	}
	this->size = other.size;
	this->arr = new double*[this->size];
	for (int i = 0; i < this->size; i++)
		this->arr[i] = new double[this->size];
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			this->arr[i][j] = other.arr[i][j];
	return *this;
}

matrix matrix::operator+ (matrix& other) {
	if (this->size != other.size) {
		cerr << "Попытка сложить две матрицы не совподающего размера\n";
		exit(-1);
	}
	matrix res(this->size);
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			res.arr[i][j] = this->arr[i][j] + other.arr[i][j];
		}
	}
	return res;
}

matrix& matrix::operator++(void) {
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			this->arr[i][j]++;
	return *this;
}

matrix matrix::operator- (matrix& other) {
	if (this->size != other.size) {
		cerr << "Попытка вычесть две матрицы не совподающего размера\n";
		exit(-1);
	}
	matrix res(this->size);
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			res.arr[i][j] = this->arr[i][j] - other.arr[i][j];
		}
	}
	return res;
}

template <typename T>
matrix matrix::operator+(T& other) {
	matrix res(this->size);
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			res.arr[i][j] = this->arr[i][j] + other;
		}
	}
	return res;
}

void matrix::clear(void) {
	if (this->arr == nullptr) {
		cerr << "Попытка очистить несуществующую матрицу\n";
		exit(-1);
	}
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			this->arr[i][j] = 0;
	return;
}

void matrix::destroy(void) {
	if (this->arr == nullptr) {
		cerr << "Попытка удалить несуществующую матрицу\n";
		exit(-1);
	}
	for (int i = 0; i < this->size; i++)
		delete[] this->arr[i];
	delete[] this->arr;
	this->size = 0;
	this->arr = nullptr;
	cout << "Сработал принудительный деструктор\n";
	return;
}

matrix& matrix::operator--(void) {
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			this->arr[i][j]--;
	return *this;
}

template <typename T>
matrix matrix::operator*(T& other) {
	matrix res(this->size);
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			res.arr[i][j] = this->arr[i][j] * other;
		}
	}
	return res;
}

template <typename T>
matrix matrix::operator/(T& other) {
	matrix res(this->size);
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			res.arr[i][j] = this->arr[i][j] / other;
		}
	}
	return res;
}

bool matrix::operator==(matrix& other) {
	bool res = true;
	if (this->size == other.size) {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				if (this->arr[i][j] != other.arr[i][j]) { res = false; break; }
			}
			if (!res) break;
		}
	}
	else {
		res = false;
	}
	return res;
}

bool matrix::operator!=(matrix& other) {
	bool res = true;
	if (this->size == other.size) {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				if (this->arr[i][j] != other.arr[i][j]) { res = false; break; }
			}
			if (!res) break;
		}
	}
	else {
		res = false;
	}
	return (!res);
}

matrix matrix::minorom(const int& index1, const int& index2) {
	matrix resArr;
	if (this->size - 1 > 0) {
		int _size = this->size - 1;
		resArr.setSize(_size);
		double* arr = new double[_size*_size];
		int iRes = 0;
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				if ((i == index1) || (j == index2))
					continue;
				arr[iRes] = this->arr[i][j];
				iRes++;
			}
		}
		resArr.setArr(arr, _size*_size);
		delete[] arr;
	}
	else {
		cerr << "Ошибка взятия минорома\n";
		exit(-1);
	}
	return resArr;
}

void matrix::print(void) {
	if (this->arr == nullptr)
		cout << "Матрицы не существует\n";
	else {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < size; j++) {
				cout << this->arr[i][j] << " ";
			}
			cout << "\n";
		}
	}
	return;
}

void matrix::printStr(const int& indexStr) {
	if (this->arr == nullptr)
		cout << "Матрицы не существует\n";
	else {
		for (int i = 0; i < this->size; i++) {
			cout << this->arr[indexStr][i] << "\t";
		}
		cout << "\n";
	}
	return;
}

void matrix::printStolb(const int& indexStolb) {
	if (this->arr == nullptr)
		cout << "Матрицы не существует\n";
	else {
		for (int i = 0; i < this->size; i++)
			cout << this->arr[i][indexStolb] << "\n";
	}
	return;
}

double matrix::det2D(void) {
	return(this->arr[0][0] + this->arr[1][1] - this->arr[0][1] - this->arr[1][0]);
}

double matrix::det1D(void) {
	return this->arr[0][0];
}

double matrix::det3D(void) {
	double sum1 = this->arr[0][0] + this->arr[1][1] + this->arr[2][2];
	double sum2 = this->arr[0][1] + this->arr[1][2] + this->arr[2][0];
	double sum3 = this->arr[1][0] + this->arr[2][1] + this->arr[0][2];
	double sum4 = -this->arr[0][2] - this->arr[1][1] - this->arr[2][0];
	double sum5 = -this->arr[1][0] - this->arr[0][1] - this->arr[2][2];
	double sum6 = -this->arr[2][1] - this->arr[1][2] - this->arr[0][0];
	return sum1 + sum2 + sum3 + sum4 + sum5 + sum6;
}

double matrix::aldop(const int& index1, const int& index2) {
	int temp;
	if ((index1 + index2) % 2)
		temp = -1;
	else
		temp = 1;
	return (double)(this->arr[index1][index2] * temp);
}

double matrix::det(void) {
	switch (this->size) {
	case 1:
		return(this->det1D());
	case 2:
		return(this->det2D());
	case 3:
		return(this->det3D());
	}
	double sum = 0;
	for (int i = 0; i < this->size; i++) {
		sum += this->aldop(i, 0)*minorom(i, 0).det();
	}
	return sum;
}

bool matrix::isExist(void) {
	return(this->arr != nullptr);
}

void matrix::setStolb(double* _arr, const int& numStolb) {
	for (int i = 0; i < this->size; i++)
		this->arr[i][numStolb] = _arr[i];
	return;
}

double* matrix::getStolb(const int& index) {
	double* res = new double[this->size];
	for (int i = 0; i < this->size; i++)
		res[i] = this->arr[i][index];
	return res;
}

void matrix::random(void) {
	srand(time(nullptr));
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			arr[i][j] = rand() % 20;
	return;
}

void matrix::save(std::ofstream& file) {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < size; j++) {
			file << this->arr[i][j] << " ";
		}
		file << "\n";
	}
}

void matrix::load(std::ifstream& file) {
	double buf[1024];
	int i = 0;
	while (file>>buf[i]) {
		i++;
	}
	this->setSize((i + 1) / 2);
	this->setArr(buf, i + 1);
	return;
}

void matrix::setStr(double* _arr, const int& numStr) {
	for (int i = 0; i < this->size; i++)
		this->arr[numStr][i] = _arr[i];
	return;
}

double* matrix::getStr(const int& index) {
	double* res = new double[this->size];
	for (int i = 0; i < this->size; i++)
		res[i] = this->arr[index][i];
	return res;
}

matrix& matrix::transp(void) {
	double* buf;
	for (int i = 0; i < size; i++) {
		buf = this->getStr(i);
		this->setStolb(buf, i);
	}
	return *this;
}

matrix& matrix::revers(void) {
	if (this->det() == 0) {
		cerr << "Ошиебка взятия обратной матрицы\n";
		exit(-1);
	}
	double tmp = this->det();
	tmp = 1 / tmp;
	this->transp() * tmp;
	return *this;
}

matrix matrix::operator*(matrix& other) {
	if (size != other.size) {
		cerr << "Попытка перемножить две не совпадающие матрицы\n";
		exit(-1);
	}
	matrix res(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				res.arr[i][j] += arr[i][k] * other.arr[k][j];
			}
		}
	}
	return res;
}
