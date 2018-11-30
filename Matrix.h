#ifndef MATRIX_H_
#define MATRIX_H_
#include<iostream>
using namespace std;
class Matrix
{	
private:
	int Col;		//矩阵的行
	int Row;		//矩阵的列
	int Size;		//矩阵元素的数目
	double *Elem;	//矩阵指针，存储元素数据
public:
	//
	Matrix();									//无参构造函数
	Matrix(int c, int r, double val = 0);		//默认构造元素为0
	Matrix(int c, double val = 1);				//构造对角方阵，默认对角元素1
	Matrix(int c, int r, double *Array);		//一维数组构造
	Matrix(int c, int r, double **Array);		//二维数组构造
	Matrix(const Matrix & m);					//copy构造
	//
	virtual ~Matrix();						
	//
	int GetCols() const { return Col; };                //获取行数
	int GetRows() const { return Row; };                //获取列数
	int GetSize() const { return Row * Col; };          //获取数组大小
	//
	double GetElem(int c, int r) const;					//查看c行r列的元素
	void SetElem(int c, int r, long double val);        //修改c行r列的元素
	void Rerange(int c, int r);							//元素数不变，重新排列矩阵（行列数改变，元素顺序不变）
	void Show();										//在屏幕上打印矩阵	
	void Trans_Col(int c1, int c2, double val);			//c1+c2*val;
	void Multi_Col(int c, double val);
	//
	void Exchange(int c1, int c2);						//交换两行
	//
	double & operator()(int c, int r);					
	Matrix & operator=(const Matrix & m);
	Matrix & operator +=(const Matrix & m);
	Matrix & operator +=(double val);
	Matrix & operator -=(const Matrix & m);
	Matrix & operator -=(double val);
	Matrix & operator *=(const Matrix & m);
	Matrix & operator *=(double val);
	Matrix operator /(double val) const;
	//
	Matrix Trans();
	Matrix Inv();

	//
	friend double Det(const Matrix&Mat);
	friend Matrix  operator+(const Matrix& Matrix1, const Matrix& Matrix2);		//矩阵与矩阵加法－操作符重载
	friend Matrix  operator-(const Matrix& Matrix1, const Matrix& Matrix2);		//矩阵与矩阵减法－操作符重载
	friend Matrix  operator*(const Matrix& Matrix1, const Matrix& Matrix2);		//矩阵与矩阵乘法－操作符重载
	friend Matrix  operator+(const Matrix& Matrix1, const double val);		    //矩阵与数加法－操作符重载（1）
	friend Matrix  operator+(const double val, const Matrix& Matrix1);		    //矩阵与数加法－操作符重载（2）
	friend Matrix  operator-(const Matrix& Matrix1, const double val);		    //矩阵与数减法－操作符重载（1）
	friend Matrix  operator-(const double val, const Matrix& Matrix1);		    //矩阵与数减法－操作符重载（2）
	friend Matrix  operator*(const Matrix& Matrix1, const double val);		    //矩阵与数乘法－操作符重载（1）
	friend Matrix  operator*(const double val, const Matrix& Matrix1);		    //矩阵与数乘法－操作符重载（2）
	friend ostream & operator<<(ostream &out, Matrix& Mat);
 
};

#endif