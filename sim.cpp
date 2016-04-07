#include<iostream>
#include<vector>
#include<climits>
#include<fstream>
#include<algorithm>

#define SERVERS 20
#define QUEUE 100
#define SIZE 133996
using namespace std;

main(){

	vector<vector<int> > server (SERVERS);

	ifstream trcfile ("sprite.trc");
	int s;
	int max=0, min=0;
	int count= 0, hitcount=0, miscount=0;
	int rem;

	vector<int>::iterator it;

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

	// for(int i =0; i<SERVERS; i++){
	// 	for(int j =0; j<QUEUE; j++){
	// 		cout<<server[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	cout<<miscount<<" "<<hitcount<<" "<<count<<endl;
	cout<<(float)(hitcount*2)/count<<endl;


	return 0;
}