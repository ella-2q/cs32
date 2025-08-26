#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <stack>

#ifndef TABLEINCLUDE
#define TABLEINCLUDE

class Table
    {
      public:
        Table(std::string keyColumn, const std::vector<std::string>& columns);
        /*
         Construct an empty Table whose column names are the elements of the vector second parameter. The first parameter is the name of the key field. The parameters might be such that you could not construct a valid table: the columns vector might be empty or contain empty or duplicate strings, or the keyColumn might not be any of the column names. The right way to handle such a problem in modern C++ is to throw an exception, but we haven't discussed exceptions. Instead, for this project you must set the state of the object so that it can later be tested using the good member function. The constructor itself should not call good and must not exit the program. For example, a user might write:
         */
        ~Table();
        bool good() const {
            return isGood;
        }
        bool insert(const std::string& recordString);
        void find(std::string key, std::vector<std::vector<std::string>>& records) const;
        int select(std::string query, std::vector<std::vector<std::string>>& records) const;

          // We prevent a Table object from being copied or assigned by
          // making the copy constructor and assignment operator unavailable.
        Table(const Table&) = delete;
        Table& operator=(const Table&) = delete;
      private:
        struct Node {
            std::string m_name;
            std::vector<std::string> cols;
            
            Node* left;
            Node* right;
        };
        
        
        std::string keyname;
        std::vector<std::string> cols;
        
        int treesize = 0;
        bool isGood;
        int posKey;
        Node* head = nullptr;
        
        void parse(std::string, std::vector<std::string>& results) const;
        char toUpperChar(char c) const;
        void toUpperCase(std::string& s) const;
        void traverseNumeric(Node* node, int columnIndex, float val, const std::string& operatort, std::vector<std::vector<std::string>>& records, int &fakecounter) const;
        void traverseString(Node* node, int columnIndex, const std::string& val, const std::string& op, std::vector<std::vector<std::string>>& records) const;
        void freeTree(Node* node);
        int oldselectalgorithm(std::string query, std::vector<std::vector<std::string>>& records) const;
        int precedence(const std::string& op) const{
            if (op == "!=" || op == "==" || op == "<" || op == "<=" || op == ">" || op == ">=" || op == "=" || op == "LT" || op == "LE" || op == "GT" || op == "GE" || op == "NE" || op == "EQ") {
                    return 3;
                } else if (op == "&") {
                    return 2;
                } else if (op == "|") {
                    return 1;
                } else {
                    return 0;
                }
        }
        void groupQueryTerms(const std::vector<std::string>& input, std::vector<std::string>& grouped) const;
    };


#endif // TABLEINCLUDED
