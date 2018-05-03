// gp-grown.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<vector>
#include<string>
#include<iostream>
#include"fp.h"
int main()
{
	std::vector<std::vector <std::string >> y = { {"I1","I2","I5"},{"I2","I4"},{"I2","I3"},{"I1","I2","I4"},{"I1","I3"} ,{"I2","I3"},{"I1","I3"} ,{ "I1","I2","I3" ,"I5"} ,{ "I1","I2","I3" } };
	fp a(y);
    return 0;
}

