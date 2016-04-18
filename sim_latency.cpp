#include<iostream>
#include<vector>
#include<climits>
#include<fstream>
#include<algorithm>

#define SERVERS 10
#define QUEUE 3000
#define SIZE 1000000
using namespace std;

main(){

	vector<vector<long> > server (SERVERS);

	ifstream trcfile ("zipf/B_1.txt");
	long s;
	long max=0, min=0;
	long count= 0, hitcount=0, miscount=0;
	long rem;

	vector<long>::iterator it;

	if(trcfile.is_open()){
		while(trcfile >> s){

			rem = s % SERVERS;
			it = find(server[rem].begin(), server[rem].end(), s);
			if(it != server[rem].end()){
				server[rem].erase(it);
				server[rem].insert(server[rem].begin(), s);

				if(count >  SIZE/2)
					hitcount++;
			} else{
				if(count >  SIZE/2)
					miscount++;

				if(server[rem].size() > QUEUE)
					server[rem].erase(server[rem].begin());
				server[rem].push_back(s);
				
			}

			count++;
		}
		trcfile.close();
	}	

	// for(long i =0; i<SERVERS; i++){
	// 	for(long j =0; j<QUEUE; j++){
	// 		cout<<server[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	cout<<miscount<<" "<<hitcount<<" "<<count<<endl;
	cout<<(float)(hitcount*2)/count<<endl;


	return 0;
}