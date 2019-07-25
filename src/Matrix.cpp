#include "Matrix.hpp"

matrix::matrix(void) { // *1
	this->size = 0;
	this->arr = nullptr;
	return;
}

matrix::matrix(int _size) { // *2
	this->size = _size;
	this->arr = new double*[size];
	for (int i = 0; i < this->size; i++)
		this->arr[i] = new double[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			this->arr[i][j] = 0;
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
	return;
}

matrix::~matrix(void) { // *3
	if (this->arr != nullptr) {
		for (int i = 0; i < this->size; i++)
			delete[] this->arr[i];
		delete[] this->arr;
		this->size = 0;
		this->arr = nullptr;
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

void matrix::setArr(double* _arr, int n) { // *4
	if (this->size*this->size != n) {
		cout << "Error, size != size(arr)\n";
		exit(-1);
	}
	int k = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			arr[i][j] = _arr[k];
			k++;
		}
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

void matrix::clear(void) {
	if (this->arr == nullptr) {
		cerr << "Ïîïûòêà î÷èñòèòü íåñóùåñòâóþùóþ ìàòðèöó\n";
		exit(-1);
	}
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			this->arr[i][j] = 0;
	return;
}

void matrix::destroy(void) {
	if (this->arr == nullptr) {
		cerr << "Ïîïûòêà óäàëèòü íåñóùåñòâóþùóþ ìàòðèöó\n";
		exit(-1);
	}
	for (int i = 0; i < this->size; i++)
		delete[] this->arr[i];
	delete[] this->arr;
	this->size = 0;
	this->arr = nullptr;
	cout << "Ñðàáîòàë ïðèíóäèòåëüíûé äåñòðóêòîð\n";
	return;
}

matrix matrix::minorom(const int index1, const int index2) { // *5
	matrix resArr(size - 1);
	int i, j;
	int di, dj;
	di = 0;
	for (i = 0; i < size - 1; i++) {
		if (i == index1) di = 1;
		dj = 0;
		for (j = 0; j < size - 1; j++) {
			if (j == index2) dj = 1;
			resArr.arr[i][j] = arr[i + di][j + dj];
		}
	}
	return resArr;
}

void matrix::print(void) { // *6
	if (this->arr == nullptr)
		cout << "Ìàòðèöû íå ñóùåñòâóåò\n";
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
		cout << "Ìàòðèöû íå ñóùåñòâóåò\n";
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
		cout << "Ìàòðèöû íå ñóùåñòâóåò\n";
	else {
		for (int i = 0; i < this->size; i++)
			cout << this->arr[i][indexStolb] << "\n";
	}
	return;
}

double matrix::det2D(void) { // *7
	return(this->arr[0][0] * this->arr[1][1] - this->arr[0][1] * this->arr[1][0]);
}

double matrix::det1D(void) { // *8
	return this->arr[0][0];
}

double matrix::det3D(void) { // *9
	double sum1 = this->arr[0][0] * this->arr[1][1] * this->arr[2][2];
	double sum2 = this->arr[0][1] * this->arr[1][2] * this->arr[2][0];
	double sum3 = this->arr[1][0] * this->arr[2][1] * this->arr[0][2];
	double sum4 = -this->arr[0][2] * this->arr[1][1] * this->arr[2][0];
	double sum5 = -this->arr[1][0] * this->arr[0][1] * this->arr[2][2];
	double sum6 = -this->arr[2][1] * this->arr[1][2] * this->arr[0][0];
	return (sum1 + sum2 + sum3 + sum4 + sum5 + sum6);
}

double matrix::aldop(const int& index1, const int& index2) { // *10
	int temp;
	if ((index1 + index2) % 2)
		temp = -1;
	else
		temp = 1;
	return (double)(this->arr[index1][index2] * temp);
}

double matrix::det(void) { // *11
	if (size == 1) return(det1D());
	if (size == 2) return(det2D());
	if (size == 3) return(det3D());
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += this->aldop(i, 0) * (this->minorom(i, 0)).det();
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