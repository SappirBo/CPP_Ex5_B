#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/**
 * @brief  This is my implementation for Node (that can be used in a Tree or as Tree on it's on).
 *         The class is template so it will work for every type.
 * @tparam T - type of the object that this node will contain.
 */
template<typename T>
class Node{
    private:
    
    T n_data;
    Node * pFather;
    vector<Node<T> *> n_childrens; // This Vector contains Pointers to all the childrens
    size_t size{};
    int color{}; // For the DFS: 0 is White, 1 is black (No need for gray couse it's a Tree).  

    public:
    /**
     * @brief Construct a new Node object
     *       1. defult Constructor.
     *       2. argument Constructor - data (type T)
     */
    Node(): pFather(NULL),size(0),color(1){}
    // {
    //     this->pFather = NULL;
    //     this->size = 0;
    //     this->color = 1;
    // }
    Node(T data)//: pFather(NULL), n_data(data), size(0), color(1) {}
    {
        this->pFather = NULL;
        this->n_data = data;
        this->size = 1;
        this->color = 0;
    }
    // Node(Node<T> &n_copy): pFather(n_copy.getFather()),n_data(n_copy.getData()),size(n_copy.getSize()),color(n_copy.getColor()){}
    // {
    //     this->pFather = n_copy.getFather();
    //     this->n_data = n_copy.getData();
    //     this->size = n_copy.getSize();
    //     this->color = n_copy.getColor();
    // }
    ~Node(){}

    // Node(Node &org) = default;
    // Node(Node &&org) = default;
    // Node &Node =(Node &&) = default;
    // Node &Node=(const Node &org) = default;

    /**
     * @brief Get the Data object
     * @return T - The data stored in the Node (Type T).
     */
    T getData(){ return this->n_data;}
    /**
     * @brief Set the Data object
     * @param data 
     */
    void setData(T data){this->n_data = data;}
    /**
     * @brief Get the Size Of the Tree Starting from this Node.
     * @return size_t  - size;
     */
    size_t getSize(){
        return this->size;
    }
    /**
     * @brief Add children to the Node, the children father (A.K.A pFather) set to be this Node.
     * @param pchild - (type Node<T>) Children Node adding to this vector array (By reffrence); 
     */
    void addSon(Node *pchild){
        pchild->setFather(this);
        this->n_childrens.push_back(pchild);
        Node *ptr = this;
        while(ptr != NULL){
            ptr->size += 1;
            ptr = ptr->pFather;
        }
    }
    /**
     * @brief Get the Color of Node (For the DFS).
     * 
     * @return int = 0 is White, int = 1 is black. (No need for gray couse it's a Tree).  
     */
    int getColor(){return this->color;}
    /**
     * @brief Set the Color of Node.
     * 
     * @param c - = 0 is White, = 1 is black. (No need for gray couse it's a Tree). 
     */
    void setColor(int c){this->color = c;}
    /**
     * @brief Get the Father object
     * @return Node* - pointer to the father.
     */
    Node *getFather(){
        return this->pFather;
    }
    /**
     * @brief Set the Father object
     * @param pNode - Pointer to the father
     */
    void setFather(Node *pNode){
        this->pFather = pNode;
    }
    /**
     * @brief  Get  pointer to the node contains that data. 
     * @param data - The data we want to receive --> if the data doesn't exist, Return NULL.
     * @return Node<T>*  - Pointer to Node;
     */
    Node<T> *get(T data){
        Node<T> * ans = NULL;
        Node<T> * ptr = this;
        queue< Node<T>* > node_q;
        node_q.emplace(ptr);
        while(!node_q.empty()){
            ptr = node_q.front();
            node_q.pop();
            if(ptr->getData() == data){
                ans = ptr;
                break;
            }
            vector<Node<T> *> tmp = ptr->getSons();
            for(size_t i=0; i<tmp.size(); i++){
                node_q.emplace(tmp[i]);
            }
        }
        return ans;
    }
    /**
     * @brief Checks if there is a Node in the Tree that contains this data.
     * 
     * @param data - The data we look for.
     * @return true - there is a node in this sub tree that contains this data (Get it with the get(T data)).
     * @return false - there is no node in this Sub-Tree that contains this data.
     */
    bool contains(T data){
        Node<T> *ptr = this->get(data); 
        bool ans = true;
        if(ptr == NULL){
            ans = false;
        }
        return ans;
    }
    /**
     * @brief This Function returns the level of this node. 
     *          Root level equals 0, his childrens are 1 and move on.
     * @return int  - the level number.
     */
    int level(){
        int count = 0;
        Node<T> *ptr = (this);
        while(ptr->pFather != NULL){
            ptr = ptr->pFather;
            count++;
        }
        return count;
    }

    /**
     * @brief Get all of this Nodes sons
     * 
     * @return vector<Node<T> *> - list of pointers to all the Sons of this Node.
     */
    vector<Node<T> *> getSons(){return this->n_childrens;}
    
    /**
     * @brief string representaion of this Sub Tree.
     * 
     * @return string - the Sub Tree.
     */
    string to_string(){
        int last_level = this->level();
        queue<Node<T> *> node_q;
        string str;
        str += (char) last_level;
        str =  "| ";
        Node<T> *ptr = this;
        node_q.emplace(ptr);
        while(! node_q.empty()){
            ptr = node_q.front();
            node_q.pop();
            vector<Node<T> *> tmp = ptr->getSons();
            for(size_t i=0; i<tmp.size(); i++){
                node_q.emplace(tmp[i]);
            }
            if(ptr->level() != last_level){
                last_level = ptr->level();
                str += "\n";
                str += (char) last_level;
                str += "|";
            }
            str += ptr->getData();
            str += " | ";
        }
        return str;
    }

    /**
     * @brief Get All the Nodes that are in this sub tree (including this).
     * 
     * @return vector<Node<T> *> - list of pointers to all th Sub Tree Nodes.  
     */
    vector<Node<T> *> getAllNodes(){
        queue<Node<T> *> node_q;
        vector<Node<string> *> *allNodes = new vector<Node<string> *>; 
        Node<T> *ptr = this;
        node_q.emplace(ptr);
        while(! node_q.empty()){
            ptr = node_q.front();
            node_q.pop();
            vector<Node<T> *> tmp = ptr->getSons();
            for(size_t i=0; i<tmp.size(); i++){
                node_q.emplace(tmp[i]);
            }
            (*allNodes).push_back(ptr);
        }
        ptr = new Node<string>("END"); 
        (*allNodes).push_back(ptr);
        return *allNodes;
    }

    /**
     * @brief Get the All Nodes with a BFS Order (becouse it's a Tree that means Level Order).
     * 
     * @return vector<Node<T> *> - list of pointers to all the Nodes level Ordered. 
     */
    vector<Node<T> *> getAllNodes_BFS(){
        return this->getAllNodes();
    }

    /**
     * @brief Get the All Nodes with a DFS Order (becouse it's a Tree that means Pre Order).
     * 
     * @return vector<Node<T> *> - list of pointers to all the Nodes Pre Ordered. 
     */
    vector<Node<T> *> getAllNodes_DFS(){
        this->paintWhite();
        vector<Node<T> *> *_vec = new vector<Node<T> *>;
        vector<Node<T> *> tmp = this->getSons();
        this->setColor(1);
        (*_vec).push_back(this);
        for(size_t i=0; i<tmp.size(); i++){
            if( tmp[i]->getColor() == 0){
                DFS_VISIT(tmp[i],_vec);
            } 
        }
        Node<string> *ptr = new Node<string>("END"); 
        (*_vec).push_back(ptr);
        return (*_vec);
    }

    void DFS_VISIT(Node<T> *s, vector<Node<T> *> *_vec){
        if(s->getColor() == 0){
            s->setColor(1);
            _vec->push_back(s);
        }
        vector<Node<T> *> tmp = s->getSons();
        for(size_t i=0; i<tmp.size(); i++){
            if( tmp[i]->getColor() == 0){
                DFS_VISIT(tmp[i],_vec);
            } 
        }
    }

    void paintWhite(){
        vector<Node<string> *> _vec = this->getAllNodes();
        for(size_t i=0; i<_vec.size(); i++){
            _vec[i]->setColor(0);
        }
    }
    
    /**
     * @brief Get the All Nodes with a Reverse Order.
     * @return vector<Node<T> *> - list of pointers to all the Nodes Pre Ordered. 
     */
    vector<Node<T> *> getAllNodes_REV(){
        int max_Level = this->maxLevel();
        vector<Node<string> *> *_vec = new vector<Node<string> *>;
        vector<Node<string> *> tmp = this->getAllNodes();
        for(int k=0; k<tmp.size(); k++){
            for(size_t i=0; i<tmp.size() && max_Level>=0; i++){
                if(tmp[i]->level() == max_Level){
                    (*_vec).push_back(tmp[i]);
                }
            }
            max_Level--;
        }
        return *_vec;
    }

    int maxLevel(){
        int ans = 0;
        vector<Node<T> *> tmp = this->getAllNodes();
        for(Node<T> * ptr : tmp){
            if(ptr->level() > ans){
                ans = ptr->level();
            }
        }
        return ans;
    }

    Node(Node<T> &n_copy) = default;
    Node<T> &operator=(Node<T> const &n_new) = default;
    Node<T> &operator=(Node<T> &&n_new) noexcept = default;
    Node<T> (Node &&n) noexcept = default;

    friend ostream& operator<<(ostream& os, Node& N){
        auto data = N.getData();
        os << data;
        return os;
    }
    
};