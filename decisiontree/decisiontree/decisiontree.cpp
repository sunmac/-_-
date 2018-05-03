// decisiontree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<iostream>
#include <deque> 
std::vector<int> statistic(const std::vector<std::vector<std::string>> &data, std::vector<std::string> list, int index, std::vector<std::string>& sta);
double infoD(const std::vector<double>& info, const int sum, const std::vector<int> list);
std::vector<int> findname(const std::vector<std::vector<std::string>> &data, const int index, const std::string name);
struct node* iter(const std::vector<std::vector<std::string>> &data, std::vector<std::string> list, std::string root);
std::vector<std::vector<std::string>> findname(const std::vector<std::vector<std::string>> &data, const std::string& n, int index);
void layer(struct node *a);
double entroy(const std::vector<int>& list);
int init(const std::vector<std::vector<std::string>> &data, std::vector<std::string> list);
void dfs(struct node *a);

struct node
{
	std::vector<node*> next;
	std::string nodename;
};
int main()
{
	using namespace std;
	std::vector<std::string> r = { "age","income","student","credit_rating","class" };
	std::vector<vector<string>> a={{"youth","high","no1","fair","no"},{ "youth","high","no1","excellent","no" },{"middle_aged","high","no1","fair","yes"} 
	,{ "senior","medium","no1","fair","yes" } ,{ "senior","low","yes1","fair","yes" },{ "senior","low","yes1","excellent","no" } ,{ "middle_aged","low","yes1","excellent","yes" },
	{ "youth","medium","no1","fair","no" },{ "youth","low","yes1","fair","yes" },{ "senior","medium","yes1","fair","yes" },{ "youth","medium","yes1","fair","yes" },
	{ "middle_aged","medium","no1","excellent","yes" } ,{ "middle_aged","high","yes1","fair","yes" } 
	,{ "senior","medium","no1","fair","no" } };

	auto c=(iter(a, r,""));
	std::cout << "层次遍历："<<std::endl;
	layer(c);

    return 0;
}



std::vector<int> statistic(const std::vector<std::vector<std::string>> &data, std::vector<std::string> list,int index, std::vector<std::string>& sta)
{
	
	std::vector<int> list1;
	if (index == -1)
		return list1;
	for (size_t i = 0; i < data.size(); i++)
	{
		int flag = 1;
		for (size_t j = 0; j < sta.size(); j++)
		{
			if (data[i][index] == sta[j])
			{
				list1[j] = list1[j] + 1;
				flag = 0;
				break;
			}
			
		}
		if (flag)
		{
			list1.push_back(1);
			sta.push_back(data[i][index]);
		}
	}

	return list1;
}

double entroy(const std::vector<int>& list)
{
	double sum=0,en=0;
	std::vector<double> re;
	for (size_t i = 0; i < list.size(); i++)
	{
		sum += list[i];
	}
	for (size_t i = 0; i < list.size(); i++)
	{
		en += list[i] / sum*log2(list[i] / sum);
	//	re.push_back(-list[i] / sum*log2(list[i] / sum));
	}
	return -en;
}
double infoD(const std::vector<double>& info, const int sum,const std::vector<int> list)
{
	double s = 0;
	for (size_t i = 0; i < info.size(); i++)
	{
		if(info[i]<100)
			s += info[i] / sum*list[i];
		else
			s += 0;

	}
	return s;
}
int init(const std::vector<std::vector<std::string>> &data, std::vector<std::string> list)
{
	if (list.size() <= 0)
		return 0;
	std::vector<std::string> name;
	std::vector<int> list1= statistic(data, list, list.size()-1,name);
	int sum = 0;
	for (int i = 0; i < list1.size(); i++)
		sum += list1[i];
	double en1 = entroy(list1);

	std::vector<double> sss;
	for (int j = 0; j < list.size() - 1; j++)
	{
		std::vector<std::string> name1;
		std::vector<int> list2 = statistic(data, list, j, name1);
		std::vector<double> listt;
		for (int i = 0; i < name1.size(); i++)
		{
			std::vector<int> l = findname(data, j, name1[i]);

			listt.push_back(entroy(l));
		}
		//std::vector<double> en2 = entroy(list2);
		double end = infoD(listt, sum, list2);
		sss.push_back(end);
	}
	auto min = std::min_element(sss.begin(),sss.end());
	//std::cout << *min << std::endl;
	int i = min - sss.begin();
	return i;
}
std::vector<int> findname(const std::vector<std::vector<std::string>> &data, const int index,const std::string name)
{
	std::vector<int> l;
	int a = 0, b = 0;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i][index] == name&&data[i][data[i].size()-1]=="yes")
		{
			a++;
		}
		if (data[i][index] == name&&data[i][data[i].size() - 1] == "no")
		{
			b++;
		}
	}
	l.push_back(a);
	l.push_back(b);
	return l;
}

struct node* iter(const std::vector<std::vector<std::string>> &data, std::vector<std::string> list,std::string root)
{
	struct node* re=new struct node();

	re->nodename = root;
	int index = init(data, list);
	std::cout <<"节点名称："<< root << " 节点深度：" << list.size() << std::endl;

	std::vector<std::string> name1;
	if (list.size() <= 0)
		return re;
	std::vector<int> list2 = statistic(data, list, index, name1);
	if (list2.size() != name1.size())
		std::cout << "error" << std::endl;
	/*for (int i = 0; i < name1.size(); i++)
	{
		struct node* next;

		re->next.push_back(next);
	}*/
	for (int i = 0; i < name1.size(); i++)
	{
		std::vector<std::vector<std::string>> next=findname(data, name1[i], index);
		std::vector<std::string> list1 = list;

		list1.erase(list1.begin()+index);
		re->next.push_back(iter(next, list1,name1[i]));
	}
	return re;
}
std::vector<std::vector<std::string>> findname(const std::vector<std::vector<std::string>> &data, const std::string& n,int index)
{
	std::vector<std::vector<std::string>> re;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i][index] == n)
		{
			std::vector<std::string> r = data[i];
			r.erase(r.begin() + index);
			re.push_back(r);
		}
	}
	return re;
}

void dfs(struct node *a)
{
	for (int i = 0; i < a->next.size(); i++)
	{
		std::cout << a->nodename << std::endl;
		dfs(a->next[i]);

	}
}
void layer(struct node *a)
{
	std::deque<node*> c;
	c.push_back(a);
	while (c.size() > 0)
	{
		//struct node* out = new struct node;
		struct node cc=*c[0];
		c.pop_front();
		std::cout << "节点名称：" << cc.nodename <<" 下一个节点数量：" <<cc.next.size()<<std::endl;
		for (int i = 0; i < cc.next.size(); i++)
		{
			c.push_back(cc.next[i]);
		}
	}
}
