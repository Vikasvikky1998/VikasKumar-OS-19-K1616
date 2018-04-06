#include<iostream>
#include<string.h>
#include<vector>
#define p 5         //declaration of number of processes
#define r 3         //declaration of number of resources
int tot = 0;
using namespace std;
bool is_avail(int p_id, int allocated[][r],int max[][r],int need[][r],int avail[])
{
	bool flag = true;
	for (int i=0;i<r;i++)
	{
		if(need[p_id][i]>avail[i])
		   flag = false;
	}
	return flag;
}
//printing safe sequences
void ss(bool marked[],int alloc[][r],int max[][r],int need[][r],int avail[],vector<int> safe)
{
	for(int i=0;i<p;i++){
		if(!marked[i] && is_avail(i,alloc,max,need,avail)){
			marked[i] = true;
			for(int j=0;j<r;j++)
			    avail[j] += alloc[i][j];
			safe.push_back(i);  
			ss(marked,alloc,max,need,avail,safe);
			safe.pop_back();
			marked[i] = false;
			for(int j=0;j<r;j++)
			    avail[j] -= alloc[i][j];
		}
	}
	if(safe.size()==p){
		tot++;
		for(int i=0;i<p;i++){
			cout<<"p"<<safe[i]+1;
			if(i!=(p-1))
			   cout<< "-->";
		}
		cout<<endl;
	}
}
int main()
{
	int allocated[p][r]={{0,1,0},
	                     {2,0,0},
						 {3,0,2},
						 {2,1,1},
						 {0,0,2}};
	int max[p][r]={{7,5,3},
	               {3,2,2},
				   {9,0,2},
				   {2,2,2},
				   {4,3,3}};
	int resources[r]={10,5,7};
	int avail[r];
	for(int i=0;i<r;i++){
		int sum=0;
		for(int j=0;j<p;j++)
		    sum += allocated[j][i];
		avail[i] = resources[i]-sum;
	}
	vector<int> safe;
	bool marked[p];
	memset(marked,false,sizeof(marked));
	int need[p][r];
	for(int i=0;i<p;i++)
	   for(int j=0;j<r;j++)
	      need[i][j]=max[i][j]-allocated[i][j];
	cout<<"Safe sequence are: "<<endl;
	ss(marked,allocated,max,need,avail,safe);
	cout<<"\nThere are total "<< tot <<" safe sequences "<<endl;
	return 0;
}
