#include <iostream>

using namespace std;

class ErrorManagement{
    private:
    static ErrorManagement* instance;
    ErrorManagement(){}
    public:

    static ErrorManagement* getInstance(){
        if(!instance){
            instance = new ErrorManagement;
        }
        return instance;
    }

    void displayError(){
        cout << "Hello Error!" << endl;
    }
};