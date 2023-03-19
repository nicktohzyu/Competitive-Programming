#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
/*
input:

#job_id,runtime_in_seconds,next_job_id
1,60,23
2,23,3
3,12,1
23,30,0
 */
using namespace std;
struct Job{
    int id, runtime, next_job_id;
};

Job parse_line(const string& line){
    stringstream line_stream(line);
    string int_buf;
    int id, runtime, next_job_id;
    getline(line_stream, int_buf, ',');
    id = stoi(int_buf);
    // if(line_stream.peek() != ','){
    //     throw 0;
    // }
    getline(line_stream, int_buf, ',');
    runtime = stoi(int_buf);
    // if(line_stream.peek() != ','){
    //     throw 0;
    // }
    getline(line_stream, int_buf, ',');
    next_job_id = stoi(int_buf);
    // if(line_stream.peek() != EOF){
    //     throw 0;
    // }
    return {id, runtime, next_job_id};
}

vector<Job> read_jobs(){
    vector<Job> jobs;
    //not clear on whether we can assume consistent csv format
    string header;
    cin >> header;
    if(header != "#job_id,runtime_in_seconds,next_job_id"){
        throw 0;
    }
    string line;
    while(cin >> line){
        jobs.push_back(parse_line(line));
    }
    return jobs;
}
class Job_toposorter{ //doesn't check for loops
    vector<int> job_ids;
    set<int> seen; //would usually use unordered_set but it wasn't included in the skeleton; minimal performance gain
    const unordered_map<int, Job>& jobs_by_id;
    Job_toposorter(const unordered_map<int, Job>& jobs_by_id) : jobs_by_id(jobs_by_id) {
        for(const auto& id_job_pair : jobs_by_id){
            int id{id_job_pair.first}; //hackerrank complains about structured bindings
            //it's ok if this one is seen
            if(seen.count(id)){
                continue;
            }
            dfs(id);
        }
        reverse(job_ids.begin(), job_ids.end());
    }
    void dfs(int id){ //assumes id always valid
        seen.insert(id);
        int next_id = jobs_by_id.at(id).next_job_id; //expect throw upon invalid input
        if(next_id == 0){
            job_ids.push_back(id);
            return;
        }
        if(seen.count(next_id)){
            job_ids.push_back(id);
            return;
        }
        dfs(next_id);
        job_ids.push_back(id);
    }

    vector<int> get() const {
        return job_ids;
    }
public:
    static vector<int> sort_jobs(const unordered_map<int, Job>& jobs_by_id){
        return Job_toposorter(jobs_by_id).get();
    }
};



class Chain{
public:
    int start_job, last_job, number_of_jobs, total_runtime;

    bool operator > (const Chain& other) const {
        return total_runtime > other.total_runtime;
    }
};

class Job_processor{
    vector<Chain> chains;
    unordered_map<int, Job> jobs_by_id;
    set<int> seen;

    Job_processor(const vector<Job>& jobs){
        //TODO: check for repeated ids
        for(Job job : jobs){
            jobs_by_id.emplace(job.id, job);
        }
        vector<int> ordered_job_ids{Job_toposorter::sort_jobs(jobs_by_id)};
        for(int id : ordered_job_ids){

            if(seen.count(id)){
                continue;
            }
            Chain chain{id, id, 0, 0};
            while(id != 0){
                //toposort ignored loops; check for loops here
                if(seen.count(id)){
                    throw 0;
                }
                seen.insert(id);
                chain.last_job = id;
                chain.number_of_jobs++;
                chain.total_runtime += jobs_by_id[id].runtime;
                id = jobs_by_id[id].next_job_id;
            }
            chains.push_back(chain);
        }
        sort(chains.begin(), chains.end(), greater<Chain>());
    }

    vector<Chain> get(){
        return chains;
    }
public:
    static vector<Chain> get_job_chains(const vector<Job>& jobs){
        return Job_processor(jobs).get();
    }
};

//returns time formatted in HH:MM:SS
string format_time(int seconds){
    int hours{seconds/3600}, minutes{(seconds/60)%60};
    seconds %= 60;
    //std::format not available
    char buffer[10];
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
    string s(buffer);
    return s;
}

void print_chain(Chain chain){
    cout << "start_job: " << chain.start_job << "\n";
    cout << "last_job: " << chain.last_job << "\n";
    cout << "number_of_jobs: " << chain.number_of_jobs << "\n";
    cout << "job_chain_runtime: " << format_time(chain.total_runtime) << "\n";
    cout << "average_job_time: " << format_time(chain.total_runtime / chain.number_of_jobs) << "\n";
    cout << "-\n";
}

void print_summary(const vector<Chain>& chains){
    cout << "-\n";
    for(Chain chain : chains){
        print_chain(chain);
    }
}

int main() {
    try{
        //to my knowledge C++ stdlib has no csv readers
        vector<Job> jobs{read_jobs()};
        vector<Chain> chains{Job_processor::get_job_chains(jobs)};
        //from this point on our code should not throw; no need to print atomically
        print_summary(chains);
    } catch (...){
        //we don't care how the input is malformed, so print malformed if anything throws
        cout << "Malformed Input";
    }
    return 0;
}


