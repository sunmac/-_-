// adaBoost.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<vector>
#include<string>
#include<math.h>
#include<iostream>
using namespace std;
#define G1(x) x>2.5?-1:1
#define G2(x) x>8.5?-1:1
#define G3(x) x<5.5?-1:1
#define sign(x) x>0?1:-1
int index = 0;
vector<double> zm(double x,const vector<int>& dataresult, vector<double>& D, const vector<int> &data);
vector<int> classification(const vector<int>& data, double &error, const vector<double>& D);
double G(double e);
void test(const vector<double>& list, const vector<int>&data);
int main()
{
	vector<double> list;
	vector<int> data = { 1,1,1,-1,-1,-1,1,1,1,-1 };
	vector<double> D = { 0.1,0.1,0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 };
	for (int i = 0; i < 3; i++)
	{
		double error=0;
		vector<int> re = classification(data, error,D);
		double x = G(error);
		D = zm(x, re, D, data);
		list.push_back(x);
		test(list, data);
	}
    return 0;
}
vector<double> zm(double x, const vector<int>& dataresult,vector<double>& D,const vector<int> &data)
{
	vector<double> re;
	double sum1 = 0;
	for (int i = 0; i < D.size(); i++)
	{
		double w = D[i] * exp(-x*data[i] * dataresult[i]);
		re.push_back(w);
		sum1 += w;
	}
	for (int i = 0; i < D.size(); i++)
	{
		re[i] = re[i] / sum1;
	}
	return re;
}
double G(double e)
{
	double a = (1 - e) / e;
	return 0.5*(log(a));
}
void test(const vector<double>& list,const vector<int>&data )
{
	double error=0;
	switch (index)
	{
	case 1:
		for (int i = 0; i < data.size(); i++)
		{
			int c = (G1(i));
			int output=sign(list[0]*c);
			if (output != data[i])
				error++;
		}
		break;
	case 2:
		for (int i = 0; i < data.size(); i++)
		{
			int output = sign(list[0] * (G1(i))+ list[1] * (G2(i)));
			if (output != data[i])
				error++;
		}
		break;
	case 3:
		for (int i = 0; i < data.size(); i++)
		{
			int output = sign(list[0] * (G1(i)) + list[1] * (G2(i)) + list[2] * (G3(i)));
			if (output != data[i])
				error++;
		}
		break;
	}
	cout << error << endl;

}
vector<int> classification(const vector<int>& data, double &error,const vector<double>& D)
{
	vector<int> re;
	switch (index)
	{
	case 1:
		for (int i = 0; i < data.size(); i++)
		{
			int re1 = G2(i);
			re.push_back(re1);
		}
		break;
	case 2:
		for (int i = 0; i < data.size(); i++)
		{
			int re1 = G3(i);
			re.push_back(re1);
		}
		break;
	case 0:
		for (int i = 0; i < data.size(); i++)
		{
			int re1 = G1(i);
			re.push_back(re1);
		}
		break;
	}
	double e=0, r=0;
	for (int i = 0; i < data.size(); i++)
	{
		if (re[i] == data[i])
			r++;
		else
			e+=1*D[i];
	}

	error = e ;
	index++;
	return re;
}
