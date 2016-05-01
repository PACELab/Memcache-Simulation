#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <algorithm>
#include <unordered_map>
extern "C"{
		#include <ketama.h>
}

#define SERVERS 10
#define QUEUE 1500
#define SIZE 1000000
#define latency 20000
using namespace std;

vector<string> servers = {"10.0.1.1:11211", "10.0.1.2:11211", "10.0.1.3:11211", 
	"10.0.1.4:11211", "10.0.1.5:11211", "10.0.1.6:11211", "10.0.1.7:11211", 
	"10.0.1.8:11211", "10.0.1.9:11211", "10.0.1.10:11211"};

main(){

	//cache servers
	vector<vector<unsigned int> > server (SERVERS);

	//wait queue => latency time to fetch from DB
	vector<unsigned int> wait_queue;

	//hash map for the wait queue
	std::unordered_map<long, unsigned int> wait_map;

	ifstream trcfile ("files/f_1.txt");
	string s;
	long max=0, min=0;
	unsigned int f_int;
	long count= 0, hitcount=0, miscount=0;
	long wq_count =0;
	std::hash<string> hash_fn;
	long rem;
	long index;
	int flag =0;

	//init all servers
	ketama_continuum c;
	ketama_roll( &c, "ketama.servers" );

	vector<unsigned int>::iterator it;
	vector<unsigned int>::iterator wq;

	if(trcfile.is_open()){
		while(trcfile >> s){

			char fname[20], fname2[20];

			f_int = hash_fn(s);

			//see if anything in wait queue is up for replacement 
			if(wait_map.count(count) > 0){
				//cout<<count<<"\t";
				long f = wait_map[count];

				//ketama hash file
				sprintf( fname, "%d", f );
   				//unsigned int kh = ketama_hashi( fname );
    			mcs* m1 = ketama_get_server( fname, c );

    			//find server index
	    		for(int i =0; i<SERVERS; i++){
	    			if(servers[i] == m1->ip){
	    				index =i;
	    				// if(count > SIZE/2)
	    				// 	cout<<index<<endl;
	    				break;
	    			}
	    		}

				//insert the item from wait queue
				if(server[index].size() > QUEUE)
					server[index].erase(server[index].begin());
				server[index].push_back(f);

				//delete the entry from hashmap
				wait_map.erase(count);
				wq = find(wait_queue.begin(), wait_queue.end(), f);
				if(wq != wait_queue.end()){
					wait_queue.erase(wq);
				} else {
					cout<<"whaaaa";
				}

			}

			//ketama hash file
			sprintf( fname2, "%d", f_int);
   			//unsigned int kh = ketama_hashi( fname );
    		mcs* m2 = ketama_get_server( fname2, c );

    		//find server index
	    	for(int i =0; i<SERVERS; i++){
	    		if(servers[i] == m2->ip){
	    			rem =i;
	    			// if(count > SIZE/2)
	    			// 	cout<<index<<endl;
	    			break;
	    			}
	    		}



			it = find(server[rem].begin(), server[rem].end(), f_int);
			if(it != server[rem].end()){
				server[rem].erase(it);				
				server[rem].push_back(f_int);

				if(count >  SIZE/2)
					hitcount++;
			} else{
				if(count >  SIZE/2)
					miscount++;

				//find/insert the item in the wait queue
				wq = find(wait_queue.begin(), wait_queue.end(), f_int);
				if(wq != wait_queue.end()){
					wq_count++;
				} else{
					wait_queue.push_back(f_int);
					wait_map.emplace(count+latency, f_int);
				}


				/*if(server[rem].size() > QUEUE)
					server[rem].erase(server[rem].begin());
				server[rem].push_back(s);*/
				
			}

			count++;

			//re hash servers when half file is done
			if(count > SIZE/2 && flag ==0){
				ketama_roll( &c, "ketama.two.servers" );
				flag =1;
			}

		}
		trcfile.close();
	}	

	// for(int i =0; i<SERVERS; i++){
	// 	for(int j =0; j<QUEUE; j++){
	// 		cout<<server[i][j]<<" ";
	// 	}
	// 	cout<<i<<endl;
	// }
	cout<<miscount<<" "<<hitcount<<" "<<count<<" "<<wq_count<<endl;
	cout<<(float)(hitcount*2)/count<<endl;


	return 0;
}