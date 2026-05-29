#include<vector>
#include <iostream>
#include<memory>
#include<algorithm>
using namespace std;

class users{
    public:
    
    string username;
    users(string str){
        username = str;
    }
    
};
class INotificationService{
    public:
    
    virtual void notify(users *u) = 0;
    virtual ~INotificationService(){}
};
class emailNotification:public INotificationService{
    public:
    void notify(users *u) override{
        cout<<"Email notification sent to : "
            <<u->username<<endl;
    }
};
class smsNotification:public INotificationService{
    public:
    void notify(users *u) override{
        cout<<"SMS notification sent to : "
            <<u->username<<endl;
    }
};
class OTT{
    public:
    vector<users*> user;
    shared_ptr<INotificationService> notifier;
    
    OTT(shared_ptr<INotificationService> service):notifier(service){}
    //shared_ptr<INotificationService> publish = make_shared<smsNotification>();
    
    void subscriber(users* u){
        user.push_back(u);
    }
    void sendNotification(){
        for(auto usr:user){
            notifier->notify(usr);
        }
    }
    void unsubscribe(users *u){
        auto it = find(user.begin(),user.end(),u);
        if(it != user.end()){
            cout<<"user unsubscribed:"<<u->username<<endl;
            user.erase(it);
        }
        else{
            cout<<"User already unsubscribed:"<<endl;
        }
    }
    
};
int main()
{
    users u1("Kanchan");
    users u2("Kumar");
    
    OTT netflix(make_shared<emailNotification>());//dependency injection
    netflix.subscriber(&u1);
    netflix.subscriber(&u2);
    netflix.sendNotification();
     
    netflix.unsubscribe(&u2);
    netflix.sendNotification();
   
    

    return 0;
}