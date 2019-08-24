
#include<iostream>
#include<queue>
#include<stack>
const int MAX_GRAPH_NODES=100;


/* using Graph
edges: node0 node1 val
1 2 10
1 4 5
2 3 5
4 3 8
2 5 5

-->1,2,10,1,4,5,2,3,5,4,3,8,2,5,5,2,7,6

https://www.jianshu.com/p/11e3db610c4b
0,1,1,
0,2,2,
1,2,4,
2,0,3,
2,3,6,
3,3,2

--> 0,1,1,0,2,2,1,2,4,2,0,3,2,3,6,3,3,2

*/
class Edge{
    public:
        int val;
        int vexid_linked_to;
        Edge* next_edge;

        Edge(int v,int vexid){
            val = v;
            vexid_linked_to=vexid;
            next_edge=NULL;
        }
};
class Graph{
    private:
        Edge* edgeList[MAX_GRAPH_NODES];
    public:
        void addNodeAtTail(int source_node,Edge* edge_tobeadded){
            Edge* node_ptr = edgeList[source_node];// get the header ptr 
            if(node_ptr==NULL){
                edgeList[source_node]=edge_tobeadded;
            }else{
                while(node_ptr->next_edge!=NULL){// move to the end of the list 
                    node_ptr=node_ptr->next_edge;
                }
                node_ptr->next_edge=edge_tobeadded;// add the new node as next 
            }
        }
        void build_graph_from_array(int* array,int size);
        void showListedGraph();
        void dfs(int begin_vexid);
        void bfs(int begin_vexid);
        void static_standerd_test(){
            int arr[]={0,1,1,0,2,2,1,2,4,2,0,3,2,3,6,3,3,2};
            Graph* g=new Graph();
            g->build_graph_from_array(arr,sizeof(arr)/sizeof(arr[0]));
            g->showListedGraph();
            g->bfs(2);
            g->dfs(2);
        }

};

void Graph::build_graph_from_array(int* array,int size){
    for(int i=0;i<size;i+=3){
        this->addNodeAtTail(array[i],new Edge(array[i+2],array[i+1]));
    }
}

void Graph::showListedGraph(){
    for(int i=0;i<10;i++){// as an example, just show 10 lines 
        Edge* tmpEdge = this->edgeList[i];
        if(tmpEdge!=NULL){
            std::cout<<"("<<i<<")";
            while(tmpEdge){
                std::cout<<"->(f:"<<i<<",t:"<<tmpEdge->vexid_linked_to
                    <<",val:"<<tmpEdge->val<<")";
                tmpEdge=tmpEdge->next_edge;
            }
            std::cout<<"\n";
        }
    }
}

//operations to graph
/*
    push the beginning item to queue
    while queue not empty:
        visit item by pop() and set to visited
        push the not visited adjacent items of it 
    
    f::use queue as an interface to accessing the items 
    f::do not forget to use the array: visited to control the workflow
        otherweise, just think about two lists, will loop forever 
    f::do not have recur. version!
*/
void Graph::bfs(int begin_vexid){
    bool* visited=new bool[MAX_GRAPH_NODES];
    for(int i=0;i<MAX_GRAPH_NODES;i++)
        visited[i]=false;
    
    std::queue<int> q;
    q.push(begin_vexid);
    //visited[begin_vexid]=true;
    while(!q.empty()){
        //visiting item i and dequeue
        int item=q.front();
        q.pop();
        visited[item]=true;
        std::cout<<item<<"->";//<<std::endl;

        //push the adjcent items to the queue
        Edge* curEdge = this->edgeList[item];
        while(curEdge!=NULL){
            if(visited[curEdge->vexid_linked_to]==false)
                q.push(curEdge->vexid_linked_to);
            curEdge=curEdge->next_edge;
        }
    }std::cout<<"\n";
}
/*
    non-recur. 
*/
void Graph::dfs(int begin_vexid){
    bool* visited=new bool[MAX_GRAPH_NODES];
    for(int i=0;i<MAX_GRAPH_NODES;i++)
        visited[i]=false;
    
    std::stack<int> s;
    s.push(begin_vexid);
    //visited[begin_vexid]=true;
    while(!s.empty()){
        //visiting item i and dequeue
        int item=s.top();
        s.pop();
        visited[item]=true;
        std::cout<<item<<"->";//<<std::endl;

        /*
            push the adjcent items to the queue - last item first

        */
        // Edge* curEdge = this->edgeList[item];
        // while(curEdge!=NULL){
        //     if(visited[curEdge->vexid_linked_to]==false)
        //         s.push(curEdge->vexid_linked_to);
        //     curEdge=curEdge->next_edge;
        // }

        /*
            push the adjcent items to the queue - last item last
                push in another direction, still not the same as queue
                f::inverse visit of a linked list item use stack
        */
        std::stack<int> helperstack;
        int helperval;
        Edge* curEdge = this->edgeList[item];
        while(curEdge!=NULL){
            if(visited[curEdge->vexid_linked_to]==false)
                helperstack.push(curEdge->vexid_linked_to);
            curEdge=curEdge->next_edge;
        }
        while(!helperstack.empty()){
            helperval=helperstack.top();
            helperstack.pop();
            s.push(helperval);
        }
        
    }std::cout<<"\n";
}
