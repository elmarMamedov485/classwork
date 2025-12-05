#include <iostream>

using namespace std;

//vector<vector<int>> connections;
vector<int> parent, ssize;
vector<double> weight;
int indexx = 0;

int Repr(int v)
{
  if (v == parent[v]) return v;
  return parent[v] = Repr(parent[v]);
}

void Union(int x, int y)
{
  x = Repr(x); y = Repr(y);
  if (x == y) return;
  if (ssize[x] < ssize[y]) swap(x, y);
  parent[y] = x;
  weight[x] = weight[x] * (double) ssize[x] + weight[y] * (double) ssize[y];
  ssize[x] += ssize[y];
  weight[x] /= (double) ssize[x];
}


class Container{
private:
        double w;
        int ind;
public:
    Container(int level){
        w = level;
        ind = indexx;
        indexx++;
        parent.resize(parent.size() + 1);
        parent[parent.size()-1] = parent.size()-1;
        ssize.resize(ssize.size()+1);
        ssize[ssize.size()-1] = 1;
        weight.resize(weight.size() + 1);
        weight[weight.size()-1] = w;
    }

    double getAmount(){
        return weight[Repr(ind)];
    }
     
    int getIndex(){
        return ind;
    }

    void connectTo(Container* c){
       Union(this->getIndex(), c->getIndex());
    }

    void disconnectFrom(Container* c){
        parent[ind] = ind;
    }

    void addWater(double amt){
        w += amt;
    }

    void setWater(double amt){
        w = amt;
        weight[Repr(ind)] = amt + weight[Repr(ind)] * ((double)ssize[Repr(ind)]);
        weight[Repr(ind)] /= (double)ssize[Repr(ind)];
    }
};

int main(){

    Container* c = new Container(5);
    Container* c1 = new Container(1);
    Container* c2 = new Container(4);
    Container* c3 = new Container(1);
    Container* c4 = new Container(1);

    c->connectTo(c1);
    c2->connectTo(c3);

    cout << c->getAmount() << endl << c2->getAmount() << endl;

    c->connectTo(c2);

    cout << c->getAmount() << endl << c2->getAmount();

    c2 -> connectTo(c4);

    cout << endl << c4->getAmount();
}