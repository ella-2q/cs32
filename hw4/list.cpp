void listAll(string path, const MenuItem* m) // two-parameter overload
{
    string nPath;
    if (path.empty()){
         nPath = m->name();
    }
    else if (!m->name().empty()){
         nPath = path + "/" + m->name();
    }
    else  nPath = path;
    
    if (nPath != ""){
        cout << nPath << endl;
    }
    
    
    
    
    const vector<MenuItem*>* insideItems = m->menuItems();
    if (insideItems == nullptr) return;
    else{
        for (int i = 0; i < insideItems->size(); i++){
            listAll(nPath, (*insideItems)[i]);
        }
    }
    
    
}
