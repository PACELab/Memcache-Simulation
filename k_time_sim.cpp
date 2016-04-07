#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <algorithm>
#include <string>
#include <ctime>
#include <sstream>
extern "C"{
		#include <ketama.h>
}

#define SERVERS 10
#define QUEUE 83
#define SIZE 568025
using namespace std;

vector<string> servers = {"10.0.1.1:11211", "10.0.1.2:11211", "10.0.1.3:11211", 
	"10.0.1.4:11211", "10.0.1.5:11211", "10.0.1.6:11211", "10.0.1.7:11211", 
	"10.0.1.8:11211", "10.0.1.9:11211", "10.0.1.10:11211"};

main(){

	vector<vector<unsigned int> > server (SERVERS);

	ifstream trcfile ("../trace/new_read_file.trc");
	string s;
	int count= 0, hitcount=0, miscount=0;
	unsigned int rem;
	std::hash<string> hash_fn;
	char fname[20];
	int index;
	int flag =0;
	int time_flag =0, time_count=0;
	double seconds;
	string filename;

	//vector to keep per time unit data
	vector<int> rate;

	//init all servers
	ketama_continuum c;
	ketama_roll( &c, "ketama.servers" );

	//base time struct
	struct tm now;


	vector<unsigned int>::iterator it;

	if(trcfile.is_open()){
		while(getline(trcfile, s)){

			//timeval struct
			struct tm timeinfo;
			int date, hours, mins, secs, micsecs;
			char month[4];

			//parse input string
			std::stringstream conv(s);
			conv>>month>>date>>hours>>mins>>secs>>micsecs>>filename;
			//cout<<month<<date<<hours<<mins<<secs<<micsecs<<filename<<endl;

			//assign timestmap values
			timeinfo.tm_mon = 1;
			timeinfo.tm_mday = date;
			timeinfo.tm_hour = hours;
			timeinfo.tm_min = mins;
			timeinfo.tm_sec = secs;
			timeinfo.tm_year = 116;

			time_count++;
			if(time_flag == 0){
				now = timeinfo;
				time_flag =1;
			} else{
				seconds = difftime(mktime(&timeinfo), mktime(&now));
				//cout<<seconds<<time_count;
				if(seconds >= 1){
					rate.push_back(time_count);
					time_count =0;
					now = timeinfo;
				}
			}


			//hash file name to unsigned int
			rem = hash_fn(filename);

			//ketama hash file
			sprintf( fname, "%d", rem );
   			//unsigned int kh = ketama_hashi( fname );
    		mcs* m = ketama_get_server( fname, c );


    		//find server index
    		for(int i =0; i<SERVERS; i++){
    			if(servers[i] == m->ip){
    				index =i;
    				if(count > SIZE/2)
    					//cout<<index<<endl;
    				break;
    			}
    		}


			it = find(server[index].begin(), server[index].end(), rem);
			if(it != server[index].end()){
				server[index].erase(it);
				server[index].push_back(rem);

				if(count >  SIZE/2){
					hitcount++;
					//cout<<servers[index]<<endl;
				}
			} else{
				if(count >  SIZE/2){
					miscount++;
					//cout<<servers[index]<<endl;
				}

				if(server[index].size() > QUEUE)
					server[index].erase(server[index].begin());
				server[index].push_back(rem);
				
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

	for(int i =0; i < rate.size(); i++){
		cout<<rate[i]<<"\n";
	}
	cout<<endl;

	//cout<<miscount<<" "<<hitcount<<" "<<count<<endl;
	cout<<(float)(hitcount*2)/count<<endl;


	return 0;
}