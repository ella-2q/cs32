#include "Table.h"

Table::Table(std::string keyColumn, const std::vector<std::string>& columns){
    isGood = true;
    keyname = keyColumn;
    int counter = 0;
    for (std::vector<std::string>::const_iterator p = columns.begin(); p != columns.end(); p++){
        cols.push_back(*p);
        if (*p == ""){
            std::cerr << "empty column" << std::endl;
            isGood = false;
        }
        if (*p == "&" || *p == "|" || *p == "(" || *p == ")") {
            // Invalid column name
            isGood = false;
        }
        if (*p == keyname) counter++;
    }
    
    if (counter != 1){
        std::cerr << "there is more than 1 instance of keyname" << std::endl;
        isGood = false;
    }
    
    if (cols.size() == 0){
        std::cerr << "column size = 0" << std::endl;
        isGood = false;
    }
    else {
        for (std::vector<std::string>::iterator p = cols.begin(); p != cols.end(); p++){
            for (std::vector<std::string>::iterator k = p; k != cols.end(); k++){
                if (k != p && *k == *p){
                    std::cerr << "repeated columns" << std::endl;
                    isGood = false;
                }
            }
        }
    }
    
    counter = 0;
    for (std::vector<std::string>::iterator p = cols.begin(); p != cols.end(); p++){
        if (*p == keyname) break;
        counter++;
    }
    
    posKey = counter;
    
}

Table::~Table(){
    freeTree(head);
}

void Table::freeTree(Node* node){
    if (node == nullptr)
           return;

       freeTree(node->left);
       freeTree(node->right);
       delete node;
}

void Table::parse(std::string input, std::vector<std::string>& results) const{
    size_t i = 0;
    while (i < input.length()) {
        while (i < input.length() && (input[i] == ' ' || input[i] == '\t' || input[i] == '\n' || input[i] == '\r')) ++i;
        
        if (i >= input.length()) break;
            
        std::string addition;
        if (input[i] == '\''){
            ++i;
            while (i < input.length()) {
                if (input[i] == '\''){
                    if (i + 1 < input.length() && input[i+1] == '\''){
                        addition += '\'';
                        i = i + 2;
                    }
                    else {
                        ++i;
                        break;
                    }
                }
                else addition += input[i++];
            }
        }
        else {
            while (i < input.length() && (input[i] != ' ' && input[i] != '\t' && input[i] != '\n' && input[i] != '\r')) {
                addition += input[i++];
            }
        }
        
        results.push_back(addition);
    }
}

bool Table::insert(const std::string& recordString){
    Node* p = new Node;
    p->left = nullptr;
    p->right = nullptr;
    parse(recordString, p->cols);
    
    if (p->cols.size() != cols.size()){
        delete p;
        return false;
    }
    
    std::vector<std::string>::iterator k = p->cols.begin() + posKey;
    p->m_name = *k;
    
    if (head == nullptr){
        head = p;
    }
    else {
        Node* tracker = head;
        while ((p->m_name >= tracker->m_name && tracker->right != nullptr) || (p->m_name < tracker->m_name && tracker->left != nullptr)){
            if (p->m_name < tracker->m_name) tracker = tracker->left;
            else tracker = tracker->right;
        }
        if (p->m_name >= tracker->m_name){
            tracker->right = p;
        }
        else tracker->left = p;
    }

    return true;
}

void Table::find(std::string key, std::vector<std::vector<std::string>>& records) const{
    Node* tracker = head;
    if (tracker == nullptr) return;
    
    while (tracker != nullptr){
        if (tracker->m_name == key){
            records.push_back(tracker->cols);
            tracker = tracker->right;
        }
        
        else if (tracker->m_name < key){
            tracker = tracker->right;
        }
        else {
            tracker = tracker -> left;
        }
    }
}

char Table::toUpperChar(char c) const{
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A'); // or return c - 32;
    }
    return c;
}

void Table::toUpperCase(std::string& s) const{
    for (std::size_t i = 0; i < s.size(); ++i) {
        s[i] = toUpperChar(s[i]);
    }
}

void Table::traverseNumeric(Node* node, int columnIndex, float val, const std::string& operatort, std::vector<std::vector<std::string>>& records, int &fakecounter) const{
    if (node == nullptr) return;
    
    
    traverseNumeric(node->left, columnIndex, val, operatort, records, fakecounter);
    

    const char* tablecstr = node->cols[columnIndex].c_str();
    char* end;
    float check = std::strtof(tablecstr, &end);
    
    if (end == tablecstr || *end != '\0') {
        fakecounter++;
    }
    
    if ((operatort == "EQ" && check == val) || (operatort == "NE" && check != val) || (operatort == "LT" && check < val) || (operatort == "LE" && check <= val) || (operatort == "GT" && check > val) || (operatort == "GE" && check >= val)){
        if (!(end == tablecstr || *end != '\0')){
            records.push_back(node->cols);
        }
    }
    
    traverseNumeric(node->right, columnIndex, val, operatort, records, fakecounter);
}

void Table::traverseString(Node* node, int columnIndex, const std::string& val, const std::string& operatort, std::vector<std::vector<std::string>>& records) const{
    if (node == nullptr) return;
    
    traverseString(node->left, columnIndex, val, operatort, records);
    
    std::string check = node->cols[columnIndex];
    
    if ((operatort == "==" && check == val) || (operatort == "!=" && check != val) || (operatort == "<" && check < val) || (operatort == "<=" && check <= val) || (operatort == ">" && check > val) || (operatort == ">=" && check >= val)){
        records.push_back(node->cols);
    }
    
    traverseString(node->right, columnIndex, val, operatort, records);
}

int Table::oldselectalgorithm(std::string query, std::vector<std::vector<std::string>>& records) const{
    records.clear();
    std::vector<std::string> queryParse;
    parse(query, queryParse);
    if (queryParse.size() != 3){
        records.clear();
        return -1;
    }
    
    bool validcolumn = false;
    for (std::vector<std::string>::const_iterator p = cols.begin(); p != cols.end(); p++){
        if (queryParse[0] == *p){
            validcolumn = true;
        }
    }
    
    if (validcolumn == false) return -1;
    
    std::string operatorType = queryParse[1];
    toUpperCase(operatorType);
    bool stringsituation = true;
    if (operatorType == "LT" || operatorType == "LE" || operatorType == "GT" || operatorType == "GE" || operatorType == "NE" || operatorType == "EQ"){
        stringsituation = false;
    }
    else if (operatorType == "<" || operatorType == "<=" || operatorType == ">" || operatorType == ">=" || operatorType == "!=" || operatorType == "==" || operatorType == "="){
        stringsituation = true;
        if (operatorType == "=") {
            operatorType = "==";
        }
    }
    else {
        std::cerr << "operatorType was invalid" << std::endl;
        return -1;
    }
    
    int counter = 0;
    for (std::vector<std::string>::const_iterator p = cols.begin(); p != cols.end(); p++){
        if (*p == queryParse[0]) break;
        counter++;
    }
    
    int querycolumn = counter;
    
    std::string term = queryParse[2];
    if (term == ""){
        std::cerr << "Term string empty" << std::endl;
        return -1;
    }
    
    if (!stringsituation){
        
        int failure = 0;
        const char* cstr = term.c_str();
        char* end;
        float val = std::strtof(cstr, &end);

        if (end == cstr || *end != '\0') {
            return -1;
        }
        
        traverseNumeric(head, querycolumn, val, operatorType, records, failure);
        
        return failure;
    }
    
    else traverseString(head, querycolumn, term, operatorType, records);
    
    return 0;
}

void Table::groupQueryTerms(const std::vector<std::string>& input, std::vector<std::string>& grouped) const {
    grouped.clear();
    int i = 0;
    while (i < input.size()) {
        std::string token = input[i];

        // If it's an operator or parenthesis, just add it
        if (token == "&" || token == "|" || token == "(" || token == ")") {
            grouped.push_back(token);
            ++i;
        }
        // If this is the start of a 3-token expression
        else if (i + 2 < input.size()) {
            std::string column = input[i];
            std::string op = input[i + 1];
            std::string value = input[i + 2];

            // Validate that op is one of the comparison operators
            if (op == "==" || op == "!=" || op == "<" || op == "<=" || op == ">" || op == ">=" ||
                op == "=" || op == "EQ" || op == "NE" || op == "LT" || op == "LE" || op == "GT" || op == "GE") {
                std::string combined = column + " " + op + " " + value;
                grouped.push_back(combined);
                i += 3;
            } else {
                // Badly formed query
                grouped.clear();
                return;
            }
        }
        else {
            // Malformed (leftover token that doesn’t form a valid expression)
            grouped.clear();
            return;
        }
    }
}




int Table::select(std::string query, std::vector<std::vector<std::string>>& records) const{
    int nonfloatcount = 0;
    records.clear();
    std::vector<std::string> queryParse;
    parse(query, queryParse);
    
    std::vector<std::string> groupedQuery;
    groupQueryTerms(queryParse, groupedQuery);
    
    std::vector<std::string> parsedQuery = groupedQuery;
    
    std::vector<std::string> postfix;
    std::stack<std::string> operators;
    
    for (std::vector<std::string>::iterator p = parsedQuery.begin(); p != parsedQuery.end(); p++){
        if (precedence(*p) == 0){
            postfix.push_back(*p);
        }
        if (*p == "("){
            operators.push(*p);
        }
        if (*p == ")"){
            while (operators.top() != "("){
                postfix.push_back(operators.top());
                operators.pop();
            }
            operators.pop();
        }
        if (precedence(*p) > 0){
            while (!operators.empty() && operators.top() != "(" && precedence(*p) <= precedence(operators.top())){
                postfix.push_back(operators.top());
                operators.pop();
            }
            operators.push(*p);
        }
    }
    
    while (!operators.empty()){
        postfix.push_back(operators.top());
        operators.pop();
    }
    
    
    std::stack<std::string> operand;
    std::string operand2;
    std::string operand1;
    
    std::stack<std::vector<std::vector<std::string>>> resultStack;
    std::string newquery;
    
    for (std::vector<std::string>::iterator p = postfix.begin(); p != postfix.end(); p++){
        if (precedence(*p) == 0){
            
            std::vector<std::vector<std::string>> result;
            
            
            int returning = oldselectalgorithm(*p, result);
            if (returning == -1) return -1;
            
            nonfloatcount += returning;
            
            resultStack.push(result);
            
        }
        else if (*p == "&" || *p == "|"){
            if (resultStack.size() < 2) return -1;
            
            std::vector<std::vector<std::string>> rhs = resultStack.top();
            resultStack.pop();
            std::vector<std::vector<std::string>> lhs = resultStack.top();
            resultStack.pop();
            
            std::vector<std::vector<std::string>> combined;
            
            if (*p == "&") {
                for (std::vector<std::vector<std::string> >::iterator i = lhs.begin(); i != lhs.end(); ++i) {
                    for (std::vector<std::vector<std::string> >::iterator j = rhs.begin(); j != rhs.end(); ++j) {
                        if (*i == *j) {
                            combined.push_back(*i);
                            break;
                        }
                    }
                }
            } else if (*p == "|") {
                combined = lhs;
                for (std::vector<std::vector<std::string> >::iterator j = rhs.begin(); j != rhs.end(); ++j) {
                    bool found = false;
                    for (std::vector<std::vector<std::string> >::iterator i = combined.begin(); i != combined.end(); ++i) {
                        if (*i == *j) {
                            found = true;
                            break;
                        }
                        
                    }
                    if (!found) {
                        combined.push_back(*j);
                    }
                }
            }
            resultStack.push(combined);
        } else {
            // token is a full 3-token query: like "price < 100"
            std::vector<std::string> tempQueryParse;
            parse(*p, tempQueryParse);  // e.g., turns "price < 100" into 3 tokens
            
            std::vector<std::vector<std::string> > singleResult;
            int code = oldselectalgorithm(*p, singleResult);
            if (code == -1) {
                return -1;  // invalid subquery
            }
            
            resultStack.push(singleResult);
        }
    }
    
    if (resultStack.size() != 1) {
        return -1;  // malformed
    }

    records = resultStack.top();
    return nonfloatcount;
    
}
