/* K-均值算法 */
#include<iostream>
#include<math.h>
 
using namespace std;
#define Number 100 //模式样本的最大维数与个数
 
struct Node //定义了一个用于存放模式样本的数据结构
{
	double element[Number] = { 0 };//模式样本
	int kinds = 0; //模式样本所属类别，0为未分类状态
} X[Number];
 
double Distance(Node X, Node Z, int n) //欧式距离计算函数
{
	double result = 0;
	for (int i = 0; i < n; i++)
	{
		result = result + (X.element[i] - Z.element[i]) * (X.element[i] - Z.element[i]);
	}
	result = sqrt(result);
	return result;
}
 
void Add(Node& result, Node X, int n) //矩阵加法
{
	for (int i = 0; i < n; i++)
	{
		result.element[i] = result.element[i] + X.element[i];
	}
}
 
void Kmeans(int k, Node X[], Node Z[], int m, int n) //K-means算法中迭代计算函数
{
	int number = 0; //用于记录迭代计算轮数
	double* D = new double[k]; //用于存放迭代计算中距离的变量
	int* N = new int[k](); //用于统计每个模式类中的模式样本数
	int(*S)[100] = new int[k][100]; //用于统计每个模式类中的模式样本
	int condition = 1; //算法结束的条件
	while (1) //迭代运算
	{
		number++;
		condition = 1;
		for (int i = 0; i < k; i++) //对Ni进行初始化
		{
			N[i] = 0;
		}
		/* 分别计算各点与聚类中心的距离 */
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < k; j++)
			{
				D[j] = Distance(X[i], Z[j], n);
			}
			int temp = 0;
			for (int j = 0; j < k; j++)
			{
				if (D[temp] > D[j])
					temp = j;
				X[i].kinds = temp + 1;
			}
		}
 
		/* 统计每个模式类中的样本数和样本 */
		for (int i = 0; i < k; i++)
		{
			cout << "第" << number << "次迭代计算后，模式类" << i + 1 << "中包括{ ";
			int temp = 0;
			for (int j = 0; j < m; j++)
			{
				if (X[j].kinds == (i + 1))
				{
					N[i]++;
					S[i][temp] = j;
					cout << "X" << S[i][temp] + 1 << " ";
					temp++;
				}
			}
			cout << "}\n";
		}
 
		/* 计算新的聚类中心 */
		Node* oldZ = new Node[k]; //保存本次计算前的聚类中心
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < n; j++)
			{
				oldZ[i].element[j] = Z[i].element[j];
			}
		}
		//计算聚类中心
		for (int i = 0; i < k; i++)
		{
			Node result;
			for (int j = 0; j < N[i]; j++)
			{
				Add(result, X[S[i][j]], n);
			}
			for (int j = 0; j < n; j++)
			{
				Z[i].element[j] = ((result.element[j]) / N[i]);
			}
		}
 
		/* 判断是否符合迭代结束条件 */
		for (int i = 0; i < k; i++)
		{
			cout << "第" << number << "次迭代计算后聚类中心Z" << i + 1 << "=( ";
			for (int j = 0; j < n; j++)
			{
				cout << Z[i].element[j] << " ";
			}
			cout << ")\n";
		}
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Z[i].element[j] != oldZ[i].element[j])
					condition = 0;
			}
		}
		
		delete[] oldZ;
 
		if (condition == 1)
			break;
	}
 
	delete[] S;
	delete[] N;
	delete[] D;
}
 
int main()
{
	/* 数据的输入与初始化 */
	int n; //模式样本的维数
	int m; //模式样本的个数
	cout << "请输入需要分类的模式样本的维数：";
	cin >> n;
	cout << "请输入需要分类的模式样本的个数：";
	cin >> m;
	cout << "请输入需要分类的模式样本：\n";
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> X[i].element[j];
		}
	}
	int k; //用于K-means算法的k值
	while (1)
	{
		cout << "请输入本次聚类分析需要将模式样本分成的类数（k值）：";
		cin >> k;
		if (k <= 1)
			cout << "k值需为大于等于1的整数";
		else
			break;
	}
		
	/* 根据用户输入的k值初始化聚类中心 */
	Node* Z = new Node[k]; //聚类中心
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Z[i].element[j] = X[i].element[j];
		}
	}
 
	/* 迭代计算聚类中心 */
	Kmeans(k,X,Z,m,n);
 
	/* 输出计算结果 */
	cout << "经过计算\n";
	for (int i = 0; i < k; i++)
	{
		cout << "聚类中心Z" << i + 1 << "=( ";
		for (int j = 0; j < n; j++)
		{
			cout << Z[i].element[j] << " ";
		}
		cout << ")\n";
	}
 
	delete[] Z;
	return 0;
}