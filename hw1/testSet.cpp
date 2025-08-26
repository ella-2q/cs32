#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

   int main()
{
       Set s;
       assert(s.empty());
       ItemType x = "arepa";
       assert( !s.get(42, x)  &&  x == "arepa"); // x unchanged by get failure
       s.insert("chapati");
       assert(s.size() == 1);
       assert(s.get(0, x)  &&  x == "chapati");
       s.dump();
       Set s2;
       s2.insert("frog");
       s2.insert("frog");
       s2.insert("toad");
       s2.insert("cow");
       s2.insert("toad");
       s2.dump();
       assert(s2.size() == 3);
       s.swap(s2);
       assert(s.size() == 3); // check sizes after swap
       assert(s2.size() == 1);
       s.dump();
       s2.dump();
       
       //check erase functions
       assert(s.erase("frog") == true);
       assert(s.size() == 2);
       assert(s.erase("handyman") == false);
       
       //check contains function
       assert(s.contains("cow") == true);
       assert(s.contains("jalebi") == false);
       
       //check get function
       Set ss;
       ss.insert("lavash");
       ss.insert("roti");
       ss.insert("chapati");
       ss.insert("injera");
       ss.insert("roti");
       ss.insert("matzo");
       ss.insert("injera");
       assert(ss.size() == 5);  // duplicate "roti" and "injera" were not added
       string y;
       ss.dump();
       ss.get(0, y);
       assert(y == "chapati");  // "chapati" is greater than exactly 0 items in ss
       ss.get(4, y);
       assert(y == "roti");  // "roti" is greater than exactly 4 items in ss
       ss.get(2, y);
       assert(y == "lavash");  // "lavash" is greater than exactly 2 items in ss
       
       
       Set s3;
       s3.insert("dosa");
       assert(!s3.contains(""));
       s3.insert("laobing");
       s3.insert("");
       s3.insert("focaccia");
       assert(s3.contains(""));
       s3.erase("dosa");
       assert(s3.size() == 3  &&  s3.contains("focaccia")  &&  s3.contains("laobing")  &&
              s3.contains(""));
       string v;
       assert(s3.get(0, v)  &&  v == "");
       assert(s3.get(1, v)  &&  v == "focaccia");
       assert(s3.get(2, v)  &&  v == "laobing");
       
       cout << "Passed all tests" << endl;
   }
