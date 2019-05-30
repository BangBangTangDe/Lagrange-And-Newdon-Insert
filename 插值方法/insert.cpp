#include<iostream>

using namespace std;
//线性插值
void Line()
{
	double x0, y0, x1, y1,x, result;
	cout << "输入相邻两个节点的x0和x1" << endl;
	cout << "x0 y0";
	cin >> x0 >> y0;
	cout << "x1 y1->";
	cin >> x1 >> y1;
	cout << "输入目标x";
	cin >> x;
	result = y0 + ((y1 - y0)*1.0 / (x1 - x0))*(x - x0);
	cout << "结果是" << result;
}
//返回插值基函数
double Lx(double my_X, int cur, double * x0 ,int num)
{
	double  up = 1;
	double down = 1;
	double result;

	for (int i = 1; i <= num; i++)
	{
		if (i != cur)
		{
			up *= (my_X - x0[i]);
			down *= (x0[cur] - x0[i]);
		}
	}
	result = up * 1.0 / down;
	return result;
}
//返回x的平方和
double X2(double *x, int num)
{
	double temp=0;
	for (int i = 1; i <= num; i++)
	{
		temp += x[i] * x[i];
	}
	return temp;
}
//得到差分表
void getcha_table(double * x, double *y, double table[20][20] ,int num)
{
	for (int i = 1; i <= num; i++)
	{
		table[i][1] = y[i];
	}

	for (int i = 2; i <=num; i++)
	{
		for (int j = i; j <= num; j++)
		{
			table[j][i] = (table[j][i-1] - table[j-1][i - 1])*1.0 / (x[j] - x[j - i+1]);
		}
	}
}
//牛顿插值基函数
double SumX_Y(double source ,double *x,int count)
{
	double mul =1 ;
	for (int i = 1; i <= count; i++)
	{
		mul *= (source - x[i]);
	}
	return mul;
}
//返回xy的乘积的和
double XY(double *x,double * y, int num)
{
	double temp = 0;
	for (int i = 1; i <= num; i++)
	{
		temp += x[i] * y[i];
	}
	return temp;
}
//拉格朗日插值
void lagrange()
{
	int num; double result=0; double source;
	double y0[20] = { 0 }; double x0[20] = { 0 };
	cout << "输入点的个数";
	cin >> num;
	cout << "输入x" << endl;
	for (int i = 1; i <= num; i++) {
		cin >> x0[i];
	}
	cout << "输入y" << endl;
	for (int i = 1; i <= num; i++) {
		cin >> y0[i];
	}
	cout << "输入插值的数值X" << endl;
	cin >> source;
	cout << "插值的结果是" << endl;
	for (int i = 1; i <= num; i++)
	{
		result += y0[i] * Lx(source, i, x0, num);
	}
	cout << result << endl;

}
//牛顿插值的方法
void newdon()
{
	double cha_table[20][20] = {0};
	double x[20] = { 0 };
	double y[20] = { 0 };
	double source=0;
	double sum=0;
	int num;
	cout << "输入点的个数";
	cin >> num;
	cout << "输入x" << endl;
	for (int i = 1; i <= num; i++) {
		cin >> x[i];
	}
	cout << "输入y" << endl;
	for (int i = 1; i <= num; i++) {
		cin >> y[i];
	}
	getcha_table(x, y, cha_table, num);
	sum = y[1];
	cout << "输入插值的数值X" << endl;
	cin >> source;
	cout << "牛顿0次插值的结果是" << sum<< endl;
	for (int i = 2; i <= num; i++)
	{
		sum += cha_table[i][i] * SumX_Y(source, x, i - 1);
		cout << "牛顿" << i-1 << "次插值的结果是" << sum;
		cout << endl;

	}
}
//最小二乘法
void Min_Double()
{
	int num; double a, b, X_=0, Y_=0;
	double x[20] = { 0 };
	double y[20] = { 0 };
	cout << "输入点的个数";
	cin >> num;
	cout << "输入x" << endl;
	for (int i = 1; i <= num; i++) {
		cin >> x[i];
		X_ += x[i];
	}
	X_ = X_ / num;
	cout << "输入y" << endl;
	for (int i = 1; i <= num; i++) {
		cin >> y[i];
		Y_ += y[i];
	}
	Y_ = Y_ / num;
	b = (XY(x,y,num)-num*(X_*Y_))*1.0/(X2(x, num) - num * X_*X_);
	a = Y_ - X_ * b;
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "拟合的曲线是 y=" << a;
	if (b > 0)
		cout << "+";
	cout<< b << "X" << endl;
}
int main()
{
	int a;
	while (true)
	{
		cout << "输入选项" << endl;
		cout << " 1.线性插值\n 2.拉格朗日插值\n 3.牛顿插值\n 4.最小二乘法\n" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			Line();
			break;
		case 2:
			lagrange();
			break;
		case 3:
			newdon();
			break;
		case 4:
			Min_Double();
			break;
		case 0:
			cout << "Thanks!" << endl;
			break;
		}
		if (a == 0)break;
	}
	return 0;
}