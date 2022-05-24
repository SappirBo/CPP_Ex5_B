#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Node.hpp"
#include "OrgChart.hpp"

using namespace std;

using namespace ariel;

/**
 * @brief Construct a new OrgChart 
 *  Setting up the root pointer as NULL -> so as long it is NULL, we wont be able to do operations on the object, exept "add root()".
 */
OrgChart::OrgChart(){
    this->root = NULL;
}

/**
 * @brief Destroy the Org Chart:: Org Chart object
 *        get Vector list with all the pointers to a Nodes, then delete them one by one. 
 * @param getAllNodes - function in Node.hpp, it returns a vetor of pointers to all the sub tree nodes.
 */
OrgChart::~OrgChart(){
    if(this->root != NULL){
        vector<Node<string> *>  tmp =  this->getRoot()->getAllNodes();
        for(auto i = tmp.begin();i!=tmp.end();i++){
            delete *i;
        }
    } 
}

/**
 * @brief adding new root for the OrgChart, if the root is NULL we create new Node (with the data) and setting up the root to point to the Node.
 *                                          if it's not NULL, we just changing the data inside the root Node to the new one.
 * 
 * @param str - the name of the root.
 * @return OrgChart& = reference to this OrgChart. 
 */
OrgChart& OrgChart::add_root(const string& str){
    if(this->root == NULL){
        Node<string>* tmp = new Node<string>(str);
        this->root = tmp;
    }
    else{
        this->root->setData(str);
    }
    return *this;
}

/**
 * @brief Adding employee to a manager Node.
 *        first check if there main root is even exists, then if that menager is exists (throw invalid_argument if they dont).
 *        then we create new Node to the employee and add it as a child of the menager.
 * @param manager = name of the father Node (as String -> thats how we check if this name exists in the Tree).
 * @param employee = name of the employee we want to add (create new node with the employee data and add it to the manager's Node sons).
 * @return OrgChart& = reference to this OrgChart. 
 */
OrgChart& OrgChart::add_sub(string const & manager,string employee){
    // Check if this OrgChart exists -> if the root is not NULL.
    if(this->root == NULL){
        throw invalid_argument("can't add sub before root");
    }
    // Check if this root have a descendant with the name manager (as string).
    // contains = boolean function in Node.hpp (check if the sub Tree contain Node with this data).
    if(! this->root->contains(manager)){
        string str = "The name" + manager + " doesn't exist!";
        throw invalid_argument(str);
    }
    Node<string> *ptr = this->root->get(manager);
    Node<string> *emp = new Node<string>(move(employee));
    ptr->addSon( emp);
    return *this;
}

Node<string> *OrgChart::getRoot() const{
    return this->root;
}

// Calling for Iterators

OrgChart::level_iterator OrgChart::begin(){
    if(this->root == NULL){
        throw invalid_argument("chart is empty!");
    }
    return OrgChart::level_iterator(this->getRoot());
}

OrgChart::level_iterator OrgChart::end(){
    if(this->root == NULL){
        throw invalid_argument("chart is empty!");
    }
    return OrgChart::level_iterator(this->getEnd());
}

OrgChart::level_iterator OrgChart::begin_level_order(){
    if(this->root == NULL){
        throw invalid_argument("chart is empty!");
    }
    return OrgChart::level_iterator(this->getRoot());
}

OrgChart::level_iterator OrgChart::end_level_order(){
    if(this->root == NULL){
        throw invalid_argument("chart is empty!");
    }
    return OrgChart::level_iterator(this->getEnd());
}

OrgChart::rev_iterator OrgChart::begin_reverse_order(){
    if(this->root == NULL){
        throw invalid_argument("chart is empty!");
    }
    return OrgChart::rev_iterator(this->getRoot());
}

OrgChart::rev_iterator OrgChart::reverse_order(){
    if(this->root == NULL){
        throw invalid_argument("chart is empty!");
    }
    return OrgChart::rev_iterator(this->getEnd());
}

OrgChart::pre_iterator OrgChart::begin_preorder(){
    if(this->root == NULL){
        throw invalid_argument("chart is empty!");
    }
    return OrgChart::pre_iterator(this->getRoot());
}

OrgChart::pre_iterator OrgChart::end_preorder(){
    if(this->root == NULL){
        throw invalid_argument("chart is empty!");
    }
    return OrgChart::pre_iterator(this->getEnd());
}


ostream& ariel::operator<<(ostream &o, OrgChart &chart){

    o << (*chart.getRoot()).to_string();
    return o;
}

/**
 * @brief return End Node<string> for the iteators. Marked as END.
 * @return Node<string>* - pointer to the  last Node (that is not included).
 */
Node<string> *OrgChart::getEnd() const{
    size_t endIndex = this->getRoot()->getSize();
    vector<Node<string> *> tmp = this->getRoot()->getAllNodes();
    return tmp[endIndex];
}

//////////////////////////////////////////////////////////////////
//      Implementing Level Order Iterator. 
//////////////////////////////////////////////////////////////////

/**
 * @brief Construct a new level_iterator (Level Order Iterator).
 *        setting up the vector list, the current index and the current node.
 * @param root  - pointer to the head of the tree.
 */
OrgChart::level_iterator::level_iterator(Node<string> *root){ 
    this->level_list = root->getAllNodes_BFS();
    this->_curr = 0;
    this->curr_Node = level_list[_curr];
}

bool OrgChart::level_iterator::operator==(level_iterator& it) const{
    return (this->curr_Node->getData() == *it);
}

OrgChart::level_iterator OrgChart::level_iterator::operator++(){
    (this->_curr)++;
    this->curr_Node = this->level_list[this->_curr];
    return *this;
}

OrgChart::level_iterator * OrgChart::level_iterator::operator->(){
    return this;
}

string OrgChart::level_iterator::operator*() const{
    return this->curr_Node->getData();
}

int OrgChart::level_iterator::length() const{
    return this->curr_Node->getData().length();
}

int OrgChart::level_iterator::size() const{
    return this->curr_Node->getData().length();
}

char OrgChart::level_iterator::at(int index) const{
    return this->curr_Node->getData().at((size_t)index);
}

//////////////////////////////////////////////////////////////////
//      Implementing Pre Order Iterator. 
//////////////////////////////////////////////////////////////////

/**
 * @brief Construct a new pre_iterator (Pre Order Iterator).
 *        setting up the vector list, the current index and the current node.
 * @param root  - pointer to the head of the tree.
 */
OrgChart::pre_iterator::pre_iterator(Node<string> *root){ 
    this->pre_list = root->getAllNodes_DFS();
    this->_curr = 0;
    this->curr_Node = pre_list[_curr];
}

bool OrgChart::pre_iterator::operator==(pre_iterator& it) const{
    return (this->curr_Node->getData() == it->curr_Node->getData());
}

OrgChart::pre_iterator OrgChart::pre_iterator::operator++(){
    if(this->_curr==this->pre_list.size()){return *this;}
    (this->_curr)++;
    this->curr_Node = this->pre_list[this->_curr];
    return *this;
}

OrgChart::pre_iterator * OrgChart::pre_iterator::operator->(){
    return this;
}

string OrgChart::pre_iterator::operator*() const{
    return this->curr_Node->getData();
}

int OrgChart::pre_iterator::size() const{
    return this->curr_Node->getData().length();
}

int OrgChart::pre_iterator::length() const{
    return this->curr_Node->getData().length();
}

char OrgChart::pre_iterator::at(int index) const{
    return this->curr_Node->getData().at((size_t)index);
}

//////////////////////////////////////////////////////////////////
//      Implementing Reverse Order Iterator. 
//////////////////////////////////////////////////////////////////


/**
 * @brief Construct a new rev_iterator (Pre Order Iterator).
 *        setting up the vector list, the current index and the current node.
 * @param root  - pointer to the head of the tree.
 */
OrgChart::rev_iterator::rev_iterator(Node<string> *root){ 
    this->rev_list = root->getAllNodes_REV();
    this->_curr = 0;
    this->curr_Node = rev_list[_curr];
}

bool OrgChart::rev_iterator::operator==(rev_iterator& it) const{
    return (this->curr_Node->getData() == it->curr_Node->getData());
}

OrgChart::rev_iterator OrgChart::rev_iterator::operator++(){
    (this->_curr)++;
    this->curr_Node = this->rev_list[this->_curr];
    return *this;
}

OrgChart::rev_iterator * OrgChart::rev_iterator::operator->(){
    return this;
}

string OrgChart::rev_iterator::operator*() const{
    return this->curr_Node->getData();
}

int OrgChart::rev_iterator::size() const{
    return this->curr_Node->getData().length();
}

int OrgChart::rev_iterator::length() const{
    return this->curr_Node->getData().length();
}

char OrgChart::rev_iterator::at(int index) const{
    char ans = this->curr_Node->getData().at((size_t)index);
    return ans;
}
