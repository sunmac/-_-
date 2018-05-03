#include "stdafx.h"
#include "fp.h"

fp::fp()
{
}
fp::~fp()
{
}

void fp::statistic()
{
	for (auto &i : data)
	{
		for (auto &j : i)
		{
			if (list.end() == std::find(list.begin(), list.end(), j))
			{
				list.push_back(j);
			}
		}
	}

}

void fp::find()
{
	for (size_t j = 0; j < list.size(); j++)
	{
		int count = 0;
		struct map s;
		s.name = list[j];
		for (auto &i : data)
		{
			

			if (i.end() != std::find(i.begin(), i.end(), list[j]))
			{
				count++;
			}
		}
		s.counter = count;
		lists.push_back(s);
		std::vector<fpnode*> a;
	}
	std::vector<std::string> out;
	for (size_t i = 0; i < lists.size();)
	{
		if (lists[i].counter > threshold)
		{
			i++;
		}
		else
		{
			out.push_back(lists[i].name);
			lists.erase(lists.begin() + i);
		}
	}
	std::sort(lists.begin(), lists.end());
	std::vector <std::string>().swap(list);
	for (size_t i = 0; i < lists.size();i++)
	{
		list.push_back(lists[i].name);
	}
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data[i].size(); j++ )
		{
			for (auto &k : out)
			{
				if (k == data[i][j])
				{
					data[i].erase(data[i].begin() + j);
					j--;
				}
				
			}
		}
	}
}

void fp::swap()
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			for (int k=0;k<lists.size();k++)
			{
				auto z = std::find(data[i].begin()+j, data[i].end(), lists[k].name);
				if (data[i].end() != z)
				{
					std::swap(data[i][j], *z);
					j++;
				}
			}
		}
	}
}

void fp::builtree()
{
	for (auto &i : data)
	{
		findsametree(i, 0, this->tree);
	}
}

void fp::dfst(fpnode tree, std::vector<std::string>& record, std::vector<std::string>& record2)
{
	if (tree.count > 0)
	{
		if (record2.end() == std::find(record2.begin(), record2.end(), tree.nodename))
		{
			std::cout << tree.nodename << " ";
			record2.push_back(tree.nodename);

		}
		record.push_back(tree.nodename);
		if(record.size()>1)
			outputvector(record);
		
	}
	for (int i = 0; i < tree.next.size();i++ )
	{
		if (i < tree.next.size())
		{

			dfst(tree.next[i],record,record2);
			record.erase(record.end()-1);
		}
	}
}

void fp::findsametree(std::vector<std::string>& l,int count, fpnode& tree)
{
	for (auto &i : tree.next)
	{
		if (i.nodename == l[count])
		{
			i.count++;
			if(count+1<l.size())
				findsametree(l, count + 1, i);
			return;
		}
	}
	if (count < l.size())
	{
		fpnode newtree;
		newtree.nodename = l[count];
		int c = std::find(list.begin(), list.end(), newtree.nodename)-list.begin();
		newtree.count = 1;
		tree.next.push_back(newtree);
		if (count + 1<l.size())
			findsametree(l, count + 1, tree.next[tree.next.size()-1]);
	}
	
}

std::vector<std::vector<std::vector<std::string>>> fp::findSuffix()
{
	std::vector<std::vector<std::vector<std::string>>> ret;
	for (int i=0;i< list.size();i++)
	{
		std::vector<std::string> part;
		std::vector<std::vector<std::string>> re;
		dfsfindSuffix(list[i],tree,i,part,re);
		ret.push_back(re);
	}
	return ret;
}

void fp::dfsfindSuffix(std::string namenode, fpnode tree,int index, std::vector<std::string> part, std::vector<std::vector<std::string>>& re)
{
	
	if (tree.nodename == namenode&&part.size()!=0)
	{
		for(int i=0;i<tree.count;i++)
			re.push_back(part);
	}
	else
	{
		for (int i = 0; i < tree.next.size(); i++)
		{
			//dfsfindSuffix();
			if(tree.nodename!="")
				part.push_back(tree.nodename);
			dfsfindSuffix(namenode, tree.next[i], index, part,re);
			if (tree.nodename != "")
				part.erase(part.end() - 1);
		}
	}
}

void fp::iter()
{
	std::vector<std::vector<std::vector<std::string>>> re = findSuffix();
	for (int i = 0; i<re.size(); i++)
	{
		if (list.size() >2)
		{
			fp a1(re[i]);
			if (a1.tree.next.size() > 0)
			{
				std::cout << list[i] << "¼¯ºÏ: ";
				std::vector<std::string> a, b;
				a1.dfst(a1.tree, a, b);
				std::cout << std::endl;
			}
		}
			
	}
}

void fp::outputvector(std::vector<std::string> out)
{
	for (auto &i : out)
	{
		std::cout << i ;
	}
	std::cout << "  ";
}

bool fp::map::operator<(const map &b)const
{
	if (counter > b.counter)
		return true;
	return false;
}

bool fp::map::operator>(const map & b) const
{
	if (counter < b.counter)
		return true;
	return false;

}
