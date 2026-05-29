#include<iostream>
#include<vector>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<thread>
#include<functional>
//#include<bits/stdc++.h>
using namespace std;

class threadpool{
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    bool stop = false;
    
    public:
    threadpool(int n){
        for(int i =0 ;i<n;i++){
            workers.emplace_back([this](){
                while(true){
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(mtx);
                        cv.wait(lock, [this](){return stop || !tasks.empty();});
                        if(stop && tasks.empty()) return; //exit 
                        
                        task = tasks.front();
                        tasks.pop();
                        //lock.unlock();
                    }
                    
                    task();
                    
                }
            });
        }
    }
    void submit(function<void()> task){
        {
            lock_guard<mutex> lock(mtx);
            tasks.push(task);
        }
        cv.notify_one();
    }
    ~threadpool(){
         cout << "Destructor called, stopping threads..." << endl;
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        
        for(thread &t: workers){
            if(t.joinable()){
                t.join();
            }
        }
        cout << "All threads joined." << endl;
    }
    
};

int main(){
    threadpool pool(4);
    for(int i = 0;i<8;i++){
        pool.submit([i](){
            cout<<"\nTask "<<i<<" Thread id "<<this_thread::get_id()<<endl;
            this_thread::sleep_for(std::chrono::milliseconds(500));
        });
    }
    
    return 0;
    
}









