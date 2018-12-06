#include<iostream>
#include<fstream>
#include<sstream>
#include"BayesianClassifier.h"
using namespace std;
const int Shuxing=13;//shuxing zongshu 
ifstream f;
vector<OriginalData> trainData;
vertor<OriginalData> testData;
double A[3];
int m;//gailu

map<double,double>C1_map[Shuxing];
map<double,double>C2_map[Shuxing];
map<double,double>C3_map[shuxing];
//从文件中读取数值
void DataRead(vector<OriginalData> &data,const char* fileName)
{
	f.open(fileName);
	int ZHjiang;
	if {fileName[0] == 'w'}
		ZHjiang = TrainNum;
	else 
		ZHjiang = TestNum;
	string line;
	OriginalData wine;
	for(int i = 0; i < ZHjiang; i++)
	{
		f >> line;//一行字符
		while（line.find(',') > 0 && line.find(',') < line.length() )
        {
        	line[line.find(',')] = ' ';
        }
        istringstream stream(line);//将stream绑定到指定的行
        stream >> wine.A1 >> wine.A2 >>wine.A3 >> wine.A4 >> wine.A5 >> wine.A6 >> wine.A7 >> wine.A8 >> wine.A9 >> wine.A10 >> wine.A11 >> wine.A12 >> wine.A13 >> wine.A14;
        //将数据传给wine
        data.push_back(wine);
	}
	f.close();
}

void bayes()
{
	int count1 = 0,count2 = 0,count3 = 0;
	int i;
	for(i = 0;i < TrainNum ; i++)
	{
		if(trainData[i].A1 == 1)
		{
			count1 ++;
		}
		if(trainData[i].A1 == 2)
		{
			count2 ++;
		}
		if(trainData[i].A1 == 3)
		{
			count3 ++;
		}//统计各类，各自求和
	}
	A[0] = (double)count1/(double)TrainNum;
	A[1] = (double)count2/(double)TrainNum;
	A[2] = (double)count3/(double)TrainNum;   //计算先验概率
	map<double,double>::iterator pipei;
	for(i = 0; i < TrainNum; i++)
	{
		if(trainData[i].A1 == 1)   //求p(xk/c1)中xk的个数
		{
			int j=0;
			for(;j<13 ;j++)
			{
				double temp = *(&trainData[i].A2+j);
				pipei = C1_map[j].find(temp);
				if(pipei == C1_map[j].end())
				{
					C1_map[j].insert(map<double,double>::value_type(temp,1));
				}
				else
				{
					double j = pipei->second;
					pipei->second = j + 1;
				}
			}
		}
		if(trainData[i].A1 ==2)   //求p(xk/c2)中xk的个数
		{
			int j = 0;
			for(;j<13 ;j++)
			{
				double temp = *(&trainData[i].A2+j);

				pipei = C2_map[j].find(temp);
				if(pipei == C2_map[j].end())
				{
					C2_map[j].insert(map<double,double>::value_type(temp,1));
				}
				else
				{
					double j = pipei->second;
					pipei->second = j + 1;
				}
			}
		}
		if(trainData[i].A1 == 3)
		{
			int j = 0;
			for(;j<13; j++)
			{
				double temp = *(&trainData[i].A2+j);
				pipei = C3_map[j].find(temp);
				if(pipei == C3_map[j].end())
				{
					C3_map[j].insert(map<double,double>::value_type(temp,1));
				}
				else
				{
					double j = pipei->second;
					pipei->second = j + 1;
				}
			}
		}
	}
//算概率
	for(i = 0;i < Shuxing; i++)
	{
		for(pipei=C1_map[i].begin(); pipei!=C1_map[i].end(); ++pipei)
		{
			double num = pipei->second;
			pipei->second = (double)num/(double)count1;
		}

		for(pipei=C2_map[i].begin(); pipei!=C2_map[i].end(); ++pipei)
		{
			double num = pipei->second;
			pipei->second = (double)num/(double)count2;
		}

		for(pipei=C3_map[i].begin(); pipei!=C3_map[i].end(); ++pipei)
		{
			double num = pipei->second;
			pipei->second = (double)num/(double)count3;
		}
	}
}

void houyan()//计算后验分布，找出最大值
{
	int i,j,k;
	double p[3];
	for(i = 0; i<TestNum; i++)
	{
		double pXC[3]={0,0,0};
		for(j=0;j<3;j++)
		{
			map<double,double>::iterator pipei;
			//计算p(x/c1)
			for(k = 0;k<Shuxing;k++)
			{
				pipei = C1_map[k].find(*(&testData[i].A2+k));
				if(pipei != C1_map[k].end())
				{
					pXC[0] = pXC[0] + pipei->second;
				}
			}
			p[0] = A[0] * pXC[0];
			//计算p(x/c2)
			for(k = 0;k<Shuxing;k++)
			{
				pipei = C2_map[k].find(*(&testData[i].A2+k));
				if(pipei != C2_map[k].end())
				{
					pXC[1] = pXC[1] + pipei->second;
				}
			}
			p[1] = A[1] * pXC[1];
			//计算p(x/c3)
			for(k = 0;k<Shuxing;k++)
			{
				pipei = C3_map[k].find(*(&testData[i].A2+k));
				if(pipei != C3_map[k].end())
				{
					pXC[2] = pXC[2] + pipei->second;
				}
			}
			p[2] = A[2] * pXC[2];
		}
		//找出最大值
		if(p[0] > p[1] && p[0] > p[2])
		{
			cout<<p[0]<<"     "<<1<<end1;
			if(testData[i].A1==1)
			m++;
		}
		else
		{
			if(p[1] > p[2])
			{
				cout<<p[1]<<"     "<<2<<end1;
				if(testData[i].A1==2)
				m++;
			}
			else
			{
				cout<<p[2]<<"     "<<3<<end1;
				if(testData[1].A1==3)
					m++;
			}
		}
	}
}
