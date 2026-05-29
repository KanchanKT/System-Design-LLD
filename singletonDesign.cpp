#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Singleton{
    //private:
        Singleton(){
            cout<<"Instance Created"<<endl;
        }
        Singleton(const Singleton &) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton(const Singleton &&) = delete;
        Singleton& operator=(const Singleton&&) = delete;
        static Singleton *instance;
        static mutex mtx;
        ~Singleton(){
            cout<<"Instance Destroyed"<<endl;
        }
    public:
    static Singleton* GetInstance(){
        lock_guard<mutex> lock(mtx);
        if(instance == nullptr){
            instance = new Singleton;
        }
        return instance;
    }
    static void Destroy(){
        lock_guard<mutex> lock(mtx);
        if(instance !=nullptr ){
            delete instance;
            instance  = nullptr;
        }
    }
    
};

Singleton* Singleton::instance = NULL;
mutex Singleton::mtx;
int main(){
   Singleton *s1 = Singleton::GetInstance();
   Singleton::Destroy();//We are destroying the object after creation then we make new instance
   Singleton *s2 = Singleton::GetInstance();
   Singleton::Destroy();
   
   
//   if(s1 == s2){
//       cout<<"\nSame";
//   }else{
//       cout<<"\nnot same";
//   }
}
