#include"Matrix.h"
#include<cstdlib>
#include<cmath>
#include<iomanip>
Matrix::Matrix()
{
	Col = 0;
	Row = 0;
	Size = Col*Row;
	Elem = NULL;
}

Matrix::Matrix(int c, int r, double val)
{
	Col = c;
	Row = r;
	Size = Col*Row;
	Elem = new double[Size];
	for (int i = 0; i < Size; i++)
	{
		Elem[i] = val;
	}
}

Matrix::Matrix(int c, double val)
{
	Col = Row = c;
	Size = Col*Row;
	Elem = new double[Size];
	for (int i = 0; i < Col; i++)
	{
		for (int j = 0; j < Row; j++)
		{
			Elem[i * Row + j] = (j == i ? val : 0.0);
		}
	}

}

Matrix::Matrix(int c, int r, double *Array)
{
	Col = c;
	Row = r;
	Size = Col*Row;
	Elem = new double[Size];
	//未检查Array的大小是否正确
	for (int i = 0; i < Size; i++)
	{
		Elem[i] = Array[i];
	}
}

Matrix::Matrix(int c, int r, double **Array)
{
	Col = c;
	Row = r;
	Size = Col*Row;
	Elem = new double[Size];
	for (int i = 0; i < Col; i++)
		for (int j = 0; j < Row; j++)
			Elem[i * Row + j] = Array[i][j];
}

Matrix::Matrix(const Matrix & m)
{
	Col = m.Col;
	Row = m.Row;
	Size = m.Size;
	Elem = new double[Size];
	for (int i = 0; i < Size; i++)
		Elem[i] = m.Elem[i];
}

Matrix::~Matrix()
{
	delete[]Elem;
}

//////////////////////////////////////////////////

double Matrix:: GetElem(int c, int r) const
{
	return Elem[(c - 1) * Row + (r - 1)];
}

void Matrix::SetElem(int c, int r, long double val)
{
	if (c < 1 || r<1 || c>Col || r>Row)
	{
		std::cout << "请输入正确的行列数!"<< std::endl;
		return;
	}
	Elem[(c - 1)*Row + (r - 1)] = val;
}

void Matrix::Rerange(int c, int r)
{
	if (c * r != Size)
	{
		std::cout << "所要重置矩阵的行列数参数错误，请查正！(matrix::rerange)" << std::endl;
		return;
	}
	else
	{
		Col = c;
		Row = r;
	}
}

void Matrix::Show()
{
	std::cout << *this;
	std::cout << std::endl;
}

void Matrix::Exchange(int c1, int c2)
{
	double *temp = new double[Row];
	for (int i = 1; i <= Row; i++)
	{
		temp[i - 1] = GetElem(c1, i);
		SetElem(c1, i, GetElem(c2, i));
		SetElem(c2, i, temp[i - 1]);
	}
	delete[]temp;
}

//c1+c2*val
void Matrix::Trans_Col(int c1, int c2, double val)
{
	if (c1 < 1 || c2 < 1 || c1 > Col || c2 > Col)
	{
		cout << "行数不正确！" << endl;
		exit(1);
	}
	for (int i = 1; i <= Row; i++)
	{
		SetElem(c1, i, GetElem(c1, i) + val*GetElem(c2, i));
	}
}

void Matrix::Multi_Col(int c, double val)
{
	if (c < 1 || c > Col)
	{
		cout << "行数不正确！" << endl;
		exit(1);
	}
	else
	{
		for (int i = 1; i <= Row; i++)
			SetElem(c, i, GetElem(c, i)*val);
	}
}
///operator

double & Matrix::operator()(int c, int r)
{
	return Elem[(c - 1)*Row + (r - 1)];
}

Matrix & Matrix::operator=(const Matrix & m)
{
	if (this == &m) return *this;
	Col = m.Col;
	Row = m.Row;
	Size = Col*Row;
	Elem = new double[Size];
	for (int i = 0; i < Size; i++) Elem[i] = m.Elem[i];
	return *this;
}

Matrix & Matrix::operator +=(const Matrix & m)
{
	if (Col == m.Col && Row == m.Row)
	{
		for (int i = 0; i < m.Size; i++)
			Elem[i] += m.Elem[i];
		return *this;
	}
	else
	{
		std::cout << "矩阵行列不相等，无法进行加法运算！" << std::endl;
		return *this;
	}
}

Matrix & Matrix::operator +=(double val)
{
	for (int i = 0; i < Size; i++)
		Elem[i] += val;
	return *this;
}

Matrix & Matrix::operator -=(const Matrix & m)
{
	if (Col == m.Col && Row == m.Row)
	{
		for (int i = 0; i < m.Size; i++)
			Elem[i] -= m.Elem[i];
		return *this;
	}
	else
	{
		std::cout << "矩阵行列不相等，无法进行减法运算！" << std::endl;
		return *this;
	}
}

Matrix & Matrix::operator -=(double val)
{
	for (int i = 0; i < Size; i++)
		Elem[i] -= val;
	return *this;
}

Matrix & Matrix::operator *=(const Matrix & m)
{
	if (Row == m.Col)
	{
		for (int i = 0; i < Col; i++)
		{
			for (int j = 0; j < Row; j++)
			{
				double temp = 0;
				for (int k = 0; k < Row; k++)
				{
					temp += GetElem(i + 1, k + 1)*m.GetElem(k + 1, j + 1);
				}	
				SetElem(i + 1, j + 1, temp);
			}
		}
		return *this;
	}
	else
	{
		std::cout << "矩阵无法相乘！" << std::endl;
		return *this;
	}
}

Matrix & Matrix::operator *=(double val)
{
	for (int i = 0; i < Size; i++)
		Elem[i] *= val;
	return *this;
}

Matrix Matrix::operator /(double val) const
{
	Matrix temp(*this);
	if (val == 0)
	{
		cout << "不能除以0！" << endl;
		return *this;
	}
	for (int i = 0; i < Size; i++)
		temp.Elem[i] /= val;
	return temp;
}
//friend
//

Matrix operator+(const Matrix& Matrix1, const Matrix& Matrix2)				//矩阵与矩阵加法－操作符重载
{
	Matrix temp(Matrix1);
	if (Matrix1.Col == Matrix2.Col && Matrix1.Row == Matrix2.Row)
	{
		for (int i = 0; i < Matrix1.Size; i++)
			temp.Elem[i] += Matrix2.Elem[i];
		return temp;
	}
	else
	{
		std::cout << "矩阵行列数不相等，无法相加" << std::endl;
		return temp;
	}
}
Matrix  operator-(const Matrix& Matrix1, const Matrix& Matrix2)		//矩阵与矩阵减法－操作符重载
{
	Matrix temp(Matrix1);
	if (Matrix1.Col == Matrix2.Col && Matrix1.Row == Matrix2.Row)
	{
		for (int i = 0; i < Matrix1.Size; i++)
			temp.Elem[i] -= Matrix2.Elem[i];
		return temp;
	}
	else
	{
		std::cout << "矩阵行列数不相等，无法相减" << std::endl;
		return temp;
	}
}
Matrix  operator*(const Matrix& Matrix1, const Matrix& Matrix2)		//矩阵与矩阵乘法－操作符重载
{
	Matrix temp(Matrix1.Col, Matrix1.Row);
	if (Matrix1.Row == Matrix2.Col)
	{
		for (int i = 0; i < Matrix1.Col; i++)
		{
			for (int j = 0; j < Matrix1.Row; j++)
			{
				double t = 0;
				for (int k = 0; k < Matrix1.Row; k++)
				{
					t += Matrix1.GetElem(i + 1, k + 1)*Matrix2.GetElem(k + 1, j + 1);

				}
				temp.SetElem(i + 1, j + 1, t);
			}
		}
		return temp;
	}
	else
	{
		std::cout << "矩阵1列数与矩阵2行数不等，无法相乘！" << std::endl;
		return temp;
	}
}

Matrix  operator+(const Matrix& Matrix1, const double val)		    //矩阵与数加法－操作符重载（1）
{
	for (int i = 0; i < Matrix1.Size; i++)
		Matrix1.Elem[i] += val;						//const对象可以修改？？？
	return Matrix1;
}

Matrix  operator+(const double val, const Matrix& Matrix1)		    //矩阵与数加法－操作符重载（2）
{
	return Matrix1 + val;
}

Matrix  operator-(const Matrix& Matrix1, const double val)		    //矩阵与数减法－操作符重载（1）
{
	for (int i = 0; i < Matrix1.Size; i++)
		Matrix1.Elem[i] -= val;						//const对象可以修改？？？为了可以使用右值？
	return Matrix1;
}

Matrix  operator-(const double val, const Matrix& Matrix1)		    //矩阵与数减法－操作符重载（2）
{
	return Matrix1 - val;
}

Matrix  operator*(const Matrix& Matrix1, const double val)		    //矩阵与数乘法－操作符重载（1）
{
	for (int i = 0; i < Matrix1.Size; i++)
		Matrix1.Elem[i] *= val;						//const对象可以修改？？？
	return Matrix1;
}

Matrix  operator*(const double val, const Matrix& Matrix1)		    //矩阵与数乘法－操作符重载（2）
{
	return Matrix1*val;
}

ostream & operator<<(ostream &os, Matrix& Mat)
{
	for (int i = 0; i < Mat.Col; i++)
	{
		for (int j = 0; j < Mat.Row; j++)
		{
			os <<setw(10)<<Mat.GetElem(i + 1, j + 1) << "  ";
		}
		os << std::endl;
	}
	return os;
}


Matrix Matrix::Trans()
{
	Matrix temp(Row, Col);
	for (int i = 0; i < Col; i++)
	{
		for (int j = 0; j < Row; j++)
			temp.SetElem(j + 1, i + 1, GetElem(i + 1, j + 1));
	}
	return temp;
}

Matrix Matrix::Inv()
{
	//judge
	if (Col != Row)
	{
		cout << "不是方阵无法求逆！" << endl;
		exit(1);
	}
	else if (Det(*this) == 0)
	{
		cout << "奇异矩阵！无法求逆！" << endl;
		exit(1);
	}
	//
	if (Size == 1) return GetElem(1, 1);
	//
	int n = Col;	
	Matrix M(*this);
	Matrix Inv_M(n, 1.0);
	//高斯约旦法	
	for (int i = 1; i <= n; i++)
	{
		//判断每列最大的数并放在对角线上，即交换行
		double max = M(i, i);
		bool max_tag = false;
		for (int j = i + 1; j <= n; j++)   //遍历所有行，第i列
		{
			if (M(j, i) > max)
			{
				max = M(j, i);
				M.Exchange(i, j); 
				Inv_M.Exchange(i, j);
			}
		}
		//从第i列开始，消去元素
		for (int k = 1; k <= n; k++)
		{
			if (max == 0)break;
			if (k == i) continue;
			double t = M(k, i) / M(i, i);
			M.Trans_Col(k, i, -t);			//k-t*i
			Inv_M.Trans_Col(k, i, -t);
		}
	}
 
	//将M化为单位阵
	for (int i = 1; i <= n; i++)
	{
		double t = 1.0 / M(i, i);
		M.Multi_Col(i, t);
		Inv_M.Multi_Col(i, t); 
	}
	//M.Show();
	 Inv_M.Show();
	return Inv_M;
}

double Det(const Matrix&Mat)
{
	Matrix M(Mat);
	if (Mat.Col != Mat.Row)
	{
		cout << "不是方阵无法求行列式！" << endl;
		exit(1);
	}
	if (Mat.Size == 1) return  Mat.GetElem(1, 1);
	int n = Mat.Col;
	//高斯列主元消去法
	int ex = 0;			//交换次数
	for (int i = 1; i <= n; i++)
	{
		//判断每列最大的数并放在对角线上，即交换行
		double max = M(i , i);
		bool max_tag = false;
		for (int j = i + 1; j <= n; j++)   //遍历所有行，第i列
		{
			if (M(j, i) > max)
			{
				max = M(j, i);
				M.Exchange(i, j);
				ex++;
			}
		}
		//M.Show();
		//从第i列开始，消去元素
		for (int k = i+1; k <= n; k++)
		{
			if (max == 0)break;
			double t = M(k, i) / M(i, i);
			M.Trans_Col(k, i, -t);			//k-t*i
		}

	}
	//output
	double result = 1;
	for (int i = 1; i <= n; i++)
		result *= M(i, i);
	if (ex % 2 != 0) 
		return -result;
	else
		return result;
}

