// 1st column - Succeeded, put '+' sign if Average mark >= 4 and number of attended lessons >= 5, else put nothing, align to center
// 2nd column - Name, all names should be aligned vertically
// 3rd column - Surname, all surnames should be aligned vertically
// 4th column - Avg mark, all values should be aligned vertically right side, number of decimals should be 2
// 5th column - Attended, all values should be aligned to the center of column

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

// convenient usage of numbers (0,1,2) so that later we'll be able to distribute reasonable information 
// from file to according arrays
enum Fields{
    NAME,
    SURNAME,
    AVG_MARK
};

//this function is similar to std::getline(stream,string,delimiter), but works with two strings and a special delimiter
bool getReasonablePart(const std::string& text,std::string& reasonablePart,const char delimiter){
    std::string tmp;
    for(static int pos = 0; pos<text.size(); ++pos){
        if(text[pos] == delimiter){
            ++pos;
            reasonablePart = tmp;
            return true;
        }   
        tmp+= text[pos];
    }
    return false;
}

void sortInformation(std::vector<std::string>& n,std::vector<std::string>& sn,std::vector<float>& am,std::vector<int>& a,std::ifstream& in){
    std::string fullText,tmp;
    // copy the content of our file to variable and also adding special delimiter 
    // so that in the future we'll get a chance to grab reasonable information properly
    while(std::getline(in,tmp)){
        fullText += tmp +",";
    }
     std::string reasonablePart;
    // variable below is used too distinguish the fields of file (name,surname, etc.)
    int currentField{};
    //loop which is being used for packing reasonable info into according arrays
    while(getReasonablePart(fullText,reasonablePart,',')){
        if(static_cast<Fields>(currentField) == NAME) {
            n.push_back(reasonablePart); 
            ++currentField;
        }
        else if(static_cast<Fields>(currentField) == SURNAME) {
            sn.push_back(reasonablePart);
            ++currentField;
        }
        else if(static_cast<Fields>(currentField) == AVG_MARK) {
        
        am.push_back(std::stof(reasonablePart));
        ++currentField;
        }
        else {
            a.push_back(std::stoi(reasonablePart));
            currentField = 0;
        }
    }
}

const int getMaxNameLength(std::vector<std::string>& n){
    int tmp{};
    for(int i = 0;i<n.size();++i){
        if(n[i].size()>tmp)
            tmp = n[i].size();
    }
    return tmp;
}

const int getMaxSurnameLength(std::vector<std::string>& sn){
    int tmp{};
    for(int i = 0;i<sn.size();++i){
        if(sn[i].size()>tmp)
            tmp = sn[i].size();
    }
    return tmp;
}

std::string getSpaces(int amountOfSpaces){
    std::string spaces;
    for(int i = 0;i<amountOfSpaces;++i){
        spaces += " ";
    }
    return spaces;
}

void printTableFormat(std::ifstream& in){

    // arrays that'll be storing our reasonable info
    std::vector<std::string> names,surnames; 
    std::vector<float> avgMarks;
    std::vector<int> attendances;

    //sorting our information into arrays for convenient usage
    sortInformation(names,surnames,avgMarks,attendances,in);
    const int maxNameLength = getMaxNameLength(names);
    const int maxSurnameLength = getMaxSurnameLength(surnames);

    //getSpaces is used for output formatting. We need to count required amount of " ", so that 
    //all output will be shown correctly
    std::cout<<"Succeeded Name"<<getSpaces(std::abs(maxNameLength-4 + 1))<<"Surname"
    <<getSpaces(std::abs(maxSurnameLength-7 + 1))<<"Avg mark Attended\n";

    //special I/O manipulators which we use to format floating point according to requirements
    std::cout.precision(2);
    std::cout<<std::fixed;

    //printing all values in a proper way
    for(int i =0;i < names.size();++i){
        char succeeded[2] = {' ','\0'};
        if(avgMarks[i] >=4 && attendances[i] >= 5) succeeded[0] = '+';
        std::cout<<"    "<<succeeded[0]<<"     "<<names[i]
        <<getSpaces(std::abs(maxNameLength-static_cast<int>(names[i].size()) + 1))
        <<surnames[i]<<getSpaces(std::abs(maxSurnameLength-static_cast<int>(surnames[i].size()) + 1))
        <<std::setw(8)<<std::right<<avgMarks[i]<<' '<<std::setw(5)<<std::right<<attendances[i]<<'\n';      
    }  
}

int main(){
    std::ifstream in("text.txt");
    printTableFormat(in);
    return 0;
}