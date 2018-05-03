// CART.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<iostream>
#include <deque>
using namespace std;
struct node* init(const vector<vector<string>>& data,const vector<string>& list, vector<string> del, const string& n);
std::vector<int> statistic(const std::vector<std::vector<std::string>> &data, std::vector<std::string> list, int index, std::vector<std::string>& sta);
std::vector<int> findname(const std::vector<std::vector<std::string>> &data, const int index, const std::string name);
bool pickupset(const vector<string>& set1, const vector<string>& set2);
vector<vector<int>> pickup(vector<vector<string>>& set, int sum);
float Gini(const vector<int> s, const vector<vector<string>>& list, const vector<int>& statictis,const vector<string>& name, const vector<vector<string>>& data, const int& index);
void dfs(struct node *a);
void layer(struct node *a);
struct node
{
	std::vector<node*> next;
	std::string nodename;
};
int main()
{
	std::vector<std::string> r = { "age","income","student","credit_rating","class" };
	std::vector<vector<string>> a = { { "youth","high","no1","fair","no" },{ "youth","high","no1","excellent","no" },{ "middle_aged","high","no1","fair","yes" }
		,{ "senior","medium","no1","fair","yes" } ,{ "senior","low","yes1","fair","yes" },{ "senior","low","yes1","excellent","no" } ,{ "middle_aged","low","yes1","excellent","yes" },
		{ "youth","medium","no1","fair","no" },{ "youth","low","yes1","fair","yes" },{ "senior","medium","yes1","fair","yes" },{ "youth","medium","yes1","fair","yes" },
		{ "middle_aged","medium","no1","excellent","yes" } ,{ "middle_aged","high","yes1","fair","yes" }
	,{ "senior","medium","no1","fair","no" } };
	vector<string>d;
	struct node *cc=init(a, r,d,"");
	dfs(cc);
	layer(cc);
    return 0;
}
vector<vector<vector<string>>> findset(const vector<vector<string>>&name)
{
	vector<vector<vector<string>>> set;

	for (int i = 0; i < name.size(); i++)
	{
		int z = 1;
		vector<vector<string>> set1;

		while (z < name[i].size())
		{
			for (int j = 0; j < name[i].size(); j++)
			{
				vector<string> re;
				int count = z;
				for (int k = j; k < name[i].size(); k++)
				{
					if (std::find(re.begin(), re.end(), name[i][k]) == re.end() && count>0)
					{
						re.push_back(name[i][k]);
						if (re.size() == z)
						{
							if (std::find(set1.begin(), set1.end(), re) == set1.end())
								set1.push_back(re);
							re.erase(re.end() - 1);
							count++;
						}
						count--;
					}
				}


			}
			z++;
		}
		set.push_back(set1);
	}
	return set;
}
struct node* init(const vector<vector<string>>& data,const vector<string>& list,vector<string> del,const string& n)
{
	struct node* re = new struct node();
	re->nodename = n;

	if (del.size() == 10)
	{
		return re;

	}
	vector<vector<string>>name;
	vector<vector<int>> statictis;
	for (int j = 0; j < list.size() - 1; j++)
	{
		std::vector<std::string> name1;
		std::vector<int> list2 = statistic(data, list, j, name1);
		for (int i = 0; i < del.size(); i++)
		{
			auto f = std::find(name1.begin(), name1.end(), del[i]);
			int cc = f - name1.begin();

			if ( f!= name1.end())
			{
				name1.erase(f);
				list2.erase(list2.begin()+cc);
			}
		}
		name.push_back(name1);
		statictis.push_back(list2);
	}
	vector<vector<vector<string>>> set=findset(name);
	float max = 0;
	vector<int> maxr;
	int maxindex=-1;
	for (int i = 0; i < set.size(); i++)
	{
		for (int j = 0; j < set[i].size(); j++)
		{
			vector<vector<int>> r;
			r=pickup(set[i], statictis[i].size());
			for (int k = 0; k < r.size(); k++)
			{
				//G.push_back(Gini(r[k],set[i], statictis[i],name[i],data,i));
				double ccc = Gini(r[k], set[i], statictis[i], name[i], data, i);
				if (max < ccc)
				{
					max = ccc;
					maxr.swap(r[k]);
					maxindex = i;
				}
			}
		}
	}
	if (max == 0)
		return re;
	vector<string>del1=del, del2=del;
	string d1="", d2="";
	for (int i = 0; i < set[maxindex][maxr[0]].size(); i++)
	{
		d1 += set[maxindex][maxr[0]][i];
		del1.push_back(set[maxindex][maxr[0]][i]);
	}
	for (int i = 0; i < set[maxindex][maxr[1]].size(); i++)
	{
		d2 += set[maxindex][maxr[1]][i];

		del2.push_back(set[maxindex][maxr[1]][i]);
	}
	re->next.push_back(init(data, list, del1,d1));
	re->next.push_back(init(data, list, del2,d2));
	return re;
	
	
}
std::vector<int> statistic(const std::vector<std::vector<std::string>> &data, std::vector<std::string> list, int index, std::vector<std::string>& sta)
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
std::vector<int> findname(const std::vector<std::vector<std::string>> &data, const int index, const std::string name)
{
	std::vector<int> l;
	int a = 0, b = 0;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i][index] == name&&data[i][data[i].size() - 1] == "yes")
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
vector<vector<int>> pickup(vector<vector<string>>& set,int sum)
{
	vector<vector<int>> re;
	
	for (int i = 0; i < set.size(); i++)
	{
		for (int j = i+1; j < set.size(); j++)
		{
			if (set[i].size() + set[j].size() == sum)
			{
				bool p =pickupset(set[i], set[j]);
				if (p)
				{
					vector<int> a;
					a.push_back(i);
					a.push_back(j);
					re.push_back(a);
				}
			}
		}
	}

	return re;
}
bool pickupset(const vector<string>& set1, const vector<string>& set2)
{
	vector<string> re;
	bool flag = true;
	for (int i = 0; i < set1.size(); i++)
	{
		vector<string> repart;
		for (int j = 0; j < set2.size(); j++)
		{
			if (std::find(set1.begin(), set1.end(), set2[j]) != set1.end())
			{
				flag = false;
			}
		}
	}

	return flag;
}
float Gini(const vector<int> s,const vector<vector<string>>& list,const vector<int>& statictis, const vector<string>& name,const vector<vector<string>>& data,const int& index1)
{
	vector<string>set1=list[s[0]];
	vector<string>set2 = list[s[1]];
	vector<int> set1int;
	vector<int> set2int;
	vector<vector<int>> ss;
	vector<int> a1sum, a2sum;
	a1sum.push_back(0);
	a1sum.push_back(0);
	a2sum.push_back(0);
	a2sum.push_back(0);
	vector<string> a = { "age","income","student","credit_rating","class" };
	std::vector<std::string> name1;

	std::vector<int> list1 = statistic(data,a,a.size()-1,name1);
	for (int i = 0; i < set1.size(); i++)
	{
		auto index = std::find(name.begin(), name.end(), set1[i]);
		if (index != name.end())
		{
			int indexint = index - name.begin();
			set1int.push_back(statictis[indexint]);
			vector<int> a1 = findname(data, index1, set1[i]);
			a1sum[0] += a1[0];
			a1sum[1] += a1[1];

		}
	}
	ss.push_back(a1sum);
	for (int i = 0; i < set2.size(); i++)
	{
		auto index = std::find(name.begin(), name.end(), set2[i]);
		if (index != name.end())
		{
			int indexint = index - name.begin();
			set2int.push_back(statictis[indexint]);
			vector<int> a1 = findname(data, index1, set2[i]);
			a2sum[0] += a1[0];
			a2sum[1] += a1[1];
		}
	}
	ss.push_back(a2sum);

	int sum = 0;
	for (int i = 0; i < statictis.size(); i++)
	{
		sum += statictis[i];
	}
	//int re;
	float sum1=0,sum2=0;
	for (int i = 0; i < set1.size(); i++)
	{
		sum1 += set1int[i];
	}
	for (int i = 0; i < set2.size(); i++)
	{
		sum2 += set2int[i];
	}
	float re = float(1) - ((float)list1[0] / sum)*((float)list1[0] / sum) - ((float)list1[1] / sum)*((float)list1[1] / sum);
	float D1 = sum1 / sum*(1 - (ss[0][0] / sum1)*(ss[0][0] / sum1) - (ss[0][1] / sum1)*(ss[0][1] / sum1)) + sum2 / sum*(1 - (ss[1][0] / sum2)*(ss[1][0] / sum2) - (ss[1][1] / sum2)*(ss[1][1] / sum2));
	return re-D1;
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
		struct node cc = *c[0];
		c.pop_front();
		std::cout << "节点名称：" << cc.nodename << " 下一个节点数量：" << cc.next.size() << std::endl;
		for (int i = 0; i < cc.next.size(); i++)
		{
			c.push_back(cc.next[i]);
		}
	}
}
