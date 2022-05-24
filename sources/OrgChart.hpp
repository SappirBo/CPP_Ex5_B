#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Node.hpp"

namespace ariel{

    class OrgChart
    {
        /**
         * @brief Implementation for Level Order Iterator.
         */
        class level_iterator{
            public:
                Node<string> *curr_Node; // Current Node in the tree.
                size_t _curr; // current index in the vector.
                vector<Node<string> *> level_list; // vector with all the pointers of the tree - listed in level order.
                level_iterator(Node<string> * root);
                ~level_iterator(){}
                int size() const;
                friend bool operator!=(const level_iterator& it1,const level_iterator& it2){
                     return (it1.curr_Node->getData() != it2.curr_Node->getData());
                }
                bool operator==(level_iterator& it) const;
                level_iterator operator++();
                level_iterator* operator->();
                string operator*() const;
                int length() const;
                char at(int index) const;
        };
        /**
         * @brief Implementation for Pre Order Iterator.
         */
        class pre_iterator{
            public:
                Node<string> *curr_Node; // Current Node in the tree.
                size_t _curr; // current index in the vector.
                vector<Node<string> *> pre_list; // vector with all the pointers of the tree - listed in pre order.
                pre_iterator(Node<string> * root);
                ~pre_iterator(){}
                int size() const;
                friend bool operator!=(const pre_iterator& it1,const pre_iterator& it2){
                    return (it1.curr_Node->getData() != it2.curr_Node->getData());
                }
                bool operator==(pre_iterator& it) const;
                pre_iterator operator++();
                pre_iterator* operator->();
                string operator*() const;
                int length() const;
                char at(int index) const;
        };

        class rev_iterator{
            public:
                Node<string> *curr_Node; // Current Node in the tree.
                size_t _curr; // current index in the vector.
                vector<Node<string> *> rev_list; // vector with all the pointers of the tree - listed in rev order.
                rev_iterator(Node<string> * root);
                ~rev_iterator(){}
                int size() const;
                friend bool operator!=(const rev_iterator& it1,const rev_iterator& it2){
                    return (it1.curr_Node->getData() != it2.curr_Node->getData());
                }
                bool operator==(rev_iterator& it) const;
                rev_iterator operator++();
                rev_iterator* operator->();
                string operator*() const;
                int length() const;
                char at(int index) const;
        };

        private:
        // Root is the root node of the tree represnting the organization.
        Node<string> *root;

        public:
        // Constructor / Deconstructor
        OrgChart();
        ~OrgChart();

        /**
         * @brief adding new root for the OrgChart, if the root is NULL we create new Node (with the data) and setting up the root to point to the Node.
         *                                          if it's not NULL, we just changing the data inside the root Node to the new one.
         * 
         * @param str - the name of the root.
         * @return OrgChart& = reference to this OrgChart. 
         */
        OrgChart& add_root(const string& str);
        /**
         * @brief Adding employee to a manager Node.
         *        first check if there main root is even exists, then if that menager is exists (throw invalid_argument if they dont).
         *        then we create new Node to the employee and add it as a child of the menager.
         * @param manager = name of the father Node (as String -> thats how we check if this name exists in the Tree).
         * @param employee = name of the employee we want to add (create new node with the employee data and add it to the manager's Node sons).
         * @return OrgChart& = reference to this OrgChart. 
         */
        OrgChart& add_sub(string const& manager,string employee);

        Node<string> *getRoot() const;
        size_t getSize(){return this->getRoot()->getSize();}

        Node<string> *getEnd() const;
        
        // Iterators calls : level_iterator, pre_iterator, rev_iterator.
        level_iterator begin();
        level_iterator end();
        level_iterator begin_level_order();
        level_iterator end_level_order();
        rev_iterator begin_reverse_order();
        rev_iterator reverse_order();
        pre_iterator begin_preorder();
        pre_iterator end_preorder();

        string to_string();
        
        // operator << for OrgChart and for Iterators.
        friend ostream& operator<<(std::ostream &o, OrgChart &chart);
        friend ostream& operator<<(std::ostream &o,const level_iterator &it){
            o << it.curr_Node->getData();
            return o;
        }
        friend ostream& operator<<(std::ostream &o,const pre_iterator &it){
            o << it.curr_Node->getData();
            return o;
        }
        friend ostream& operator<<(std::ostream &o,const rev_iterator &it){
            o << it.curr_Node->getData();
            return o;
        }
    
    };
};