#pragma once
#include<vector>
#include<string>
#include<algorithm>
#include<iostream>
class fp
{
public:
	fp();
	fp(std::vector<std::vector <std::string >> outdata, std::string outtreenode="" ,int thresholdout=1) :data(outdata),threshold(thresholdout) {
		tree.nodename = outtreenode;
		statistic();
		find();
		swap();
		builtree();
		std::vector<std::string> a;
		iter();
		//dfst(tree,a);
		//iter();
	}
	std::vector<std::vector<std::vector<std::string>>> findSuffix();
	std::vector<std::string> list;
	~fp();
	struct map {
		std::string name;
		int counter;
		bool operator>(const struct map &b)const;
		bool operator<(const struct map &b)const;
	};
	typedef struct node
	{
		int count;
		std::string nodename;
		std::vector<struct node> next;
	}fpnode;
private:
	std::vector<std::vector <std::string >> data;
	std::vector<struct map> lists;
	//std::vector<std::vector<std::string>> re;
	fpnode tree;
	int threshold;
	void statistic();
	void find();
	void swap();
	void builtree();
	void dfst(fpnode tree, std::vector<std::string>& record, std::vector<std::string>& record2);
	void findsametree(std::vector<std::string>& l,int count, fpnode& tree);
	void dfsfindSuffix(std::string namenode, fpnode tree,int index, std::vector<std::string> part, std::vector<std::vector<std::string>>& re);
	void iter();
	void outputvector(std::vector<std::string>);
};

