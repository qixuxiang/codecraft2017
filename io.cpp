#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <queue>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>
using namespace std;
int main(int argc, char **argv)
{
    int Nodenum,Linknum,Consumernum,Serverprime;
    unordered_map<int, int> Serverto;
    ifstream ifs("/home/zte/rep001/data/easy_example/case00.txt");  //改成你自己的文件路径
    streambuf* old_buffer = cin.rdbuf(ifs.rdbuf());
    string read;
    //from http://blog.csdn.net/sibo626/article/details/6781036
    cin >> read;
    Nodenum = atoi(read.c_str());
    //cout<<Nodenum<<endl;
    cin >> read;
    Linknum = atoi(read.c_str());
    cin >> read;
    Consumernum = atoi(read.c_str());
    cin >> read;
    Serverprime =atoi(read.c_str());

    vector<vector<int>> network;//linkway
    network.resize(Linknum,vector<int>(4));
    vector<vector<int>> consumer;//consumerway
    consumer.resize(Linknum,vector<int>(3));
    for(int i = 0;i < Linknum;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            cin >> read;
            network[i][j] = atoi(read.c_str());
        }
    }

    for(int i = 0;i < Consumernum;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            cin >> read;
            consumer[i][j] = atoi(read.c_str());
        }
    }

    cin.rdbuf(old_buffer);
    ifs.close();

    cout<<"Nodenum is :"<<Nodenum<<" Linknum is :"<<Linknum<<" Consumernum is: "
    <<Consumernum<<" Server_prime is: "<<Serverprime<<endl;

    for(int i = 0;i < Linknum;i++)
    {

        for(int j = 0;j < 4;j++)
        {
           cout<< network[i][j] <<",";

        }
        cout<<"\n";

    }
    cout<<"----------------"<<endl;
    int demand=0;
    for(int i = 0;i < Consumernum;i++)
    {
        Serverto.insert(make_pair(i,consumer[i][1]+2));//key is server location
        //insert method can ensure the key is unique!
        //intial Serverto is directive method
        demand+=consumer[i][2];
        for(int j = 0;j < 3;j++)
        {
            cout<<consumer[i][j] <<",";
        }
        cout<<"\n";
    }
    cout<<"demand is: "<<demand<<endl;
    /*
    cout<<"................................"<<endl;
    //int m = 2*Consumernum+2*Linknum+Serverto.size();
    int m = 3*Consumernum;
    //int n = Nodenum + Consumernum+2;
    int n = 2*Consumernum+2;
    G.init(n);
    vector<vector<int>> FlowLink(network);
    FlowLink.resize(Linknum,vector<int>(3));
    vector<int> start;
    vector<int> end;
    vector<int> flow;

    for(int i=0;i!=Serverto.size();i++)
    {
        start.push_back(1);
        end.push_back(Serverto[i]);
        flow.push_back(oo);
    }
    /*
    for(int i = 0;i < Linknum;i++)
    {
        start.push_back(FlowLink[i][0]+2);
        end.push_back(FlowLink[i][1]+2);
        flow.push_back(FlowLink[i][2]);
    }
    for(int i = 0;i < Linknum;i++)
    {
        start.push_back(FlowLink[i][1]+2);
        end.push_back(FlowLink[i][0]+2);
        flow.push_back(FlowLink[i][2]);
    }
     */
    /*
    for(int i = 0;i<Consumernum;i++)
    {
        start.push_back(consumer[i][1]+2);

        end.push_back(consumer[i][0]+2+Nodenum);

        flow.push_back(consumer[i][2]);
    }

    for(int i = 0;i<Consumernum;i++)
    {
        start.push_back(consumer[i][0]+2+Nodenum);
        end.push_back(Nodenum+Consumernum+2);
        flow.push_back(oo);
    }
    cout<<"......................."<<endl;

    for(int i=0;i!=start.size();i++)
    {
        cout<<start[i]<<",";
        cout<<end[i]<<",";
        cout<<flow[i]<<",";
        G.add(start[i],end[i],flow[i]);

    }
    cout<<"maxflow of 1 and Nodenum + Consumernum+2 is: "<<G.ans(1,Nodenum + Consumernum+2)<<endl;

    /*
    int m,n,u,v,w;//m是边数目，n是点数目，u是起点，v是终点，w是流量

	while(cin>>m>>n)
	{
		G.init(n);
		while(m--)
		{
			cin>>u>>v>>w;
			G.add(u,v,w);
		}
		cout<<G.ans(1,n)<<endl;
	}
    */
	return 0;
}
