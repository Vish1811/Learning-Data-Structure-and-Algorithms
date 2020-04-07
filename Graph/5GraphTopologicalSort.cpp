//simple algorithm that outputs linear ordering of vertices of the graph
///such that (u->v) then u comes before v
//works only of DAG directed acyclic graphs
//it tells the pre-requisite
//it can be used in package installing, to check which should come first.
#include <iostream>
#include<list>
#include<map>
using namespace std;
//in this algo we use dfs to rreach the last node and while returning we push
//the node to linked list, because we know that the all children of this node
//are traversed and pushed in list
//hindi : wpas aate time list me dalte rho ;

template<typename T>
class Graph{
        map<T, list<T>> adjList;
    public:
        Graph(){

        }
        void addEdge(T u, T v, bool bidir= true){
            adjList[u].push_back(v);
            if (bidir) adjList[v].push_back(u);
        }

        void print(){
            for(auto i: adjList){
                cout<<i.first<<"-> ";
                for(auto j: i.second)
                    cout<<j<<", ";
                cout<<endl;
            }
        }
        void dfsHelper(T node, map<T,bool> &visited, list<T> &ordering){
            visited[node]=true;
            //cout<<node<<" ";
            for(auto neighbour: adjList[node]){
                if (!visited[neighbour]){
                    dfsHelper(neighbour, visited, ordering);
                }
            }
            //at this ponit all the neighbour(children and grandchildren and we cant move ahead ) of current node are visited
            //so will push back that to front of list(recursively come back and check for its previous 
            ordering.push_front(node);//it will add to head of list
                //here we can also use stack for odering
        }

        void dfsTopologicalSort(){
            map<T,bool> visited;
            list<T> ordering;
            for (auto i: adjList){//loop is used to make this code to run for
            //all components of a graph.
                T node=i.first;
                if(!visited[node])
                    dfsHelper(node, visited,ordering);
            }
            for(auto e: ordering){
                cout<<e<<" ";
            }
        }


};

int main(){
    Graph<string> g;
    g.addEdge("English","Programming Logic", false);
    g.addEdge("Math","Programming Logic", false);
    g.addEdge("Programming Logic","HTML", false);
    g.addEdge("English","Programming Logic", false);
    g.addEdge("Programming Logic","Python", false);
    g.addEdge("Programming Logic","Java", false);
    g.addEdge("Python"," Web Dev", false);
    g.addEdge("HTML","CSS", false);
    g.addEdge("CSS","JS", false);
    g.addEdge("JS","Web Dev", false);
    g.dfsTopologicalSort();



}
//HINDI
//src ke ek neighbour pe gye fir uske neighbour pe fir uske finally ab aaage nhi ja sakte to jha h use push kr diya aur 
//uske just pichle wale me aa gye (reusrsion start previous process  repeat hoga) 
//  ::::  fir iske neighbour(agr nhi hai to ise bhi store krke waps laut gye) neighbour.. jha se aage mhi ja skte use store kr waps
//aa gye sare pe aise hi bari bari se krna hai

