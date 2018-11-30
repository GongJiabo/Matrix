#ifndef MATRIX_H_
#define MATRIX_H_
#include<iostream>
using namespace std;
class Matrix
{	
private:
	int Col;		//�������
	int Row;		//�������
	int Size;		//����Ԫ�ص���Ŀ
	double *Elem;	//����ָ�룬�洢Ԫ������
public:
	//
	Matrix();									//�޲ι��캯��
	Matrix(int c, int r, double val = 0);		//Ĭ�Ϲ���Ԫ��Ϊ0
	Matrix(int c, double val = 1);				//����ԽǷ���Ĭ�϶Խ�Ԫ��1
	Matrix(int c, int r, double *Array);		//һά���鹹��
	Matrix(int c, int r, double **Array);		//��ά���鹹��
	Matrix(const Matrix & m);					//copy����
	//
	virtual ~Matrix();						
	//
	int GetCols() const { return Col; };                //��ȡ����
	int GetRows() const { return Row; };                //��ȡ����
	int GetSize() const { return Row * Col; };          //��ȡ�����С
	//
	double GetElem(int c, int r) const;					//�鿴c��r�е�Ԫ��
	void SetElem(int c, int r, long double val);        //�޸�c��r�е�Ԫ��
	void Rerange(int c, int r);							//Ԫ�������䣬�������о����������ı䣬Ԫ��˳�򲻱䣩
	void Show();										//����Ļ�ϴ�ӡ����	
	void Trans_Col(int c1, int c2, double val);			//c1+c2*val;
	void Multi_Col(int c, double val);
	//
	void Exchange(int c1, int c2);						//��������
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
	friend Matrix  operator+(const Matrix& Matrix1, const Matrix& Matrix2);		//���������ӷ�������������
	friend Matrix  operator-(const Matrix& Matrix1, const Matrix& Matrix2);		//������������������������
	friend Matrix  operator*(const Matrix& Matrix1, const Matrix& Matrix2);		//���������˷�������������
	friend Matrix  operator+(const Matrix& Matrix1, const double val);		    //���������ӷ������������أ�1��
	friend Matrix  operator+(const double val, const Matrix& Matrix1);		    //���������ӷ������������أ�2��
	friend Matrix  operator-(const Matrix& Matrix1, const double val);		    //�����������������������أ�1��
	friend Matrix  operator-(const double val, const Matrix& Matrix1);		    //�����������������������أ�2��
	friend Matrix  operator*(const Matrix& Matrix1, const double val);		    //���������˷������������أ�1��
	friend Matrix  operator*(const double val, const Matrix& Matrix1);		    //���������˷������������أ�2��
	friend ostream & operator<<(ostream &out, Matrix& Mat);
 
};

#endif