//Your declarations and implementations would go here
class Medium {
private:
    std::string m_ID;
public:
    Medium(std::string Name) : m_ID(Name) {};
    virtual ~Medium() {};
    virtual std::string connect() const = 0;
    std::string id() const{
        return m_ID;
    }
    virtual std::string transmit(std::string msg) const {
        std::string completeMsg = "text: " + msg;
        return completeMsg;
    }
};


class EmailAccount: public Medium {
public:
    virtual ~EmailAccount(){
        std::cout << "Destroying the email account " << id() << "." << std::endl;
    }
    EmailAccount(std::string email) : Medium(email) {};
    virtual std::string connect() const{
        return "Email";
    }
};

class Phone : public Medium {
private:
    CallType m_callType;
public:
    Phone(std::string number, CallType callType) : Medium(number), m_callType(callType) {};
    virtual ~Phone(){
        std::cout << "Destroying the phone " << id() << "." << std::endl;
    }
    virtual std::string connect() const{
        return "Call";
    }
    virtual std::string transmit(std::string msg) const{
        if (m_callType == VOICE){
            std::string totalMessage = "voice: " + msg;
            return totalMessage;
        }
        else {
            std::string totalMessage = "text: " + msg;
            return totalMessage;
        }
    }
};

class XAccount: public Medium {
public:
    XAccount(std::string userID) : Medium(userID) {};
    virtual ~XAccount(){
        std::cout << "Destroying the X account " << id() << "." << std::endl;
    }
    virtual std::string connect() const{
        return "Post to X";
    }
};
