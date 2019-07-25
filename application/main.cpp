#include "Matrix.hpp"

int main() {
	setlocale(LC_ALL, "rus");
	matrix a(3);
	double arr[9];
	for (int i = 0; i < 9; i++) 
		chek_in(arr[i]);
	a.setArr(arr,9);
	cout << std::endl;
	a.print();
	cout << "det = " << a.det() << std::endl;
	system("pause");
}