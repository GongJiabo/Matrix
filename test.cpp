#include"Matrix.h"
#include<iostream>
#include<random>
#include<ctime>

int main()
{
	srand(time(NULL));
	double arr[9] = { 0, 1, 2, 3, 4, 5, 0, 6, 7 };
	Matrix A(3, 3);
	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			A(i, j) = rand()%10;
		}
	}
	A.Show();

 	A.Inv();
 
	return 0;
}