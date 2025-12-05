#include <iostream>

using namespace std;

class Container{
private:
        double w;
        vector<Container*> connections;
public:
    Container(int level){
        w = level;
    }

    int getAmount(){
        return w;
    }

    void connectTo(Container* c){
        connections.emplace_back(c);
        c->connectTo(this);
        double sum = 0;

        for(int i = 0; i < connections.size(); i++){
            sum += connections[i]->getAmount();
        }

        sum /= connections.size();

        for(int i = 0; i < connections.size(); i++){
            connections[i]->setWater(sum);
        }
    }

    void disconnectFrom(Container* c){
        int i;
        for( i = 0; i < connections.size(); i++){
            if(connections[i] == c) break;
        }

        connections.erase(connections.begin() + i);
        c->disconnectFrom(this);
    }

    void addWater(double amt){
        w += amt;
    }

    void setWater(double amt){
        w = amt;
        double sum = 0;

        for(int i = 0; i < connections.size(); i++){
            sum += connections[i]->getAmount();
        }

        sum /= connections.size();

        for(int i = 0; i < connections.size(); i++){
            connections[i]->setWater(sum);
        }
    }
};


int main(){

    Container* c = new Container(5);
    Container* c1 = new Container(1);

    c->connectTo(c1);

    cout << c->getAmount
}