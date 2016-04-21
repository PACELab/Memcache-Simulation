#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <algorithm>
#include <unordered_map>

#define SERVERS 10
#define QUEUE 3000
#define SIZE 1000000
#define latency 1000
using namespace std;

main(){

	//cache servers
	vector<vector<long> > server (SERVERS);

	//wait queue => latency time to fetch from DB
	vector<long> wait_queue;

	//hash map for the wait queue
	std::unordered_map<long, long> wait_map;

	ifstream trcfile ("zipf/B_1.txt");
	long s;
	long max=0, min=0;
	long count= 0, hitcount=0, miscount=0;
	long rem;

	vector<long>::iterator it;
	vector<long>::iterator wq;

	if(trcfile.is_open()){
		while(trcfile >> s){

			//see if anything in wait queue is up for replacement 
			if(wait_map.count(count) > 0){
				//cout<<count<<"\t";
				long f = wait_map[count];
				long index = f % SERVERS;

				//insert the item from wait queue
				if(server[index].size() > QUEUE)
					server[index].erase(server[index].begin());
				server[index].push_back(f);

				//delete the entry from hashmap
				wait_map.erase(f);
				wait_queue.erase(wait_queue.begin());

			}

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

				//find/insert the item in the 
				wq = find(wait_queue.begin(), wait_queue.end(), s);
				if(wq != wait_queue.end()){
					;
				} else{
					wait_queue.push_back(s);
					wait_map.emplace(count+latency, s);
				}


				/*if(server[rem].size() > QUEUE)
					server[rem].erase(server[rem].begin());
				server[rem].push_back(s);*/
				
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