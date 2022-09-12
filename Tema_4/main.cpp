#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

class NumberFormatException: public exception{
    string message_;
public:
    const char* what() const noexcept override{
        return message_.c_str();
    }
    NumberFormatException(const string& value){
        message_ = "Value " + value + " is not a valid number.";
    }
};

/*class Number{
public:
    static int64_t stoi(const string & myString){
        int64_t numFromString = 0;
        uint32_t k = 1;
        for(int32_t i = myString.size() - 1; i >= 0; i--){
            if(myString[i] >= '0' && myString[i] <= '9'){
                numFromString += (myString[i] - '0') * k;
                k *= 10;
            }
        }
        if(k == 1){
            throw NumberFormatException(myString);
        }
        return numFromString;
    }
};*/

class Number{
public:
    static int64_t stoi(const string & myString){
        int64_t numFromString = 0;
        bool sign = 1;
        string nums;
        for(uint32_t i = 0; i < myString.size(); i++){
            if(myString[i] == ' ') continue;
            if(myString[i] == '+'){
                sign = 1;
                i++;
                uint32_t ct = i;
                while(myString[i] <= '9' && myString[i] >= '0'){
                    nums.push_back(myString[i]);
                    i++;
                }
                if(i == ct){
                    throw(NumberFormatException(myString));
                }
                break;
            }
            else if(myString[i] == '-'){
                sign = 0;
                i++;
                uint32_t ct = i;
                while(myString[i] <= '9' && myString[i] >= '0'){
                    nums.push_back(myString[i]);
                    i++;
                }
                if(i == ct){
                    throw(NumberFormatException(myString));
                }
                break;
            }
        }
        if(nums.size() == 0){
            throw(NumberFormatException(myString));
        }
        else{
            if(nums.size() > 19){
                if(sign == 1) numFromString = INT64_MAX;
                else numFromString = INT64_MIN;

            }
            else{
                uint32_t k = 1;
                for(int32_t i = nums.size() - 1; i >= 0; i--){
                    numFromString += (nums[i] - '0') * k;
                    k *= 10;
                }
            }
            if(sign == 0){
                return 0 - numFromString;
            }
            else return numFromString;
        }
    }
};

class FileException: public exception{
protected:
    string message_;
public:
    const char* what() const noexcept override{
        return message_.c_str();
    }
};

class OpenFileException: public FileException{
public:
    OpenFileException(const string& fileName){
        message_ = "Cannot open file " + fileName + ".";
    }
};

class InputFile: public ifstream {
public:
    InputFile() = default;
    InputFile(const string &fileName){
        ifstream filein(fileName);
        if(!filein.is_open()) throw OpenFileException(fileName);
    }
    void open(const string& fileName){
        ifstream f;
        f.open(fileName);
        if(!f.is_open()){
            throw OpenFileException(fileName);
        }
    }
};

int main(){
    Number a;
    string st = "          +7356473264873245873245732848732648732643254354353266432dd3";
    cout << a.stoi(st);
    cout << ' ' << INT64_MAX << ' ' << INT64_MIN;
}