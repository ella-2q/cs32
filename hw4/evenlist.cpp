    void removeEven(list<int>& li)
    {

        for (list<int>::iterator p = li.begin(); p != li.end(); ){
            if (*p % 2 == 0){
                p = li.erase(p);
            }
            else p++;
        }
    }

