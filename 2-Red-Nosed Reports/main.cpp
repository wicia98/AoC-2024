#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>      //for std:string


/*
** returns 1 if increasing by 1 or 2 or 3
** returns 2 if decreasing by 1 or 2 or 3
*/
int compareNumbers(int a, int b)
{
    if(a==b)
        return 0;
    
    if(abs(a-b)>3)
        return 0;

    if(a>b)
        return 1;
    else
        return 2;
}


bool test(std::vector<int> v)
{
    int prev, next, state;
    for(int j=1; j<v.size(); j++)
    {
        prev = v[j-1];
        next = v[j];
        if(!compareNumbers(prev, next))
            return false;
        
        if(j==1)
            state = compareNumbers(prev, next);
        else
        {
            if(state != compareNumbers(prev, next))
                return false;
            else
                state = compareNumbers(prev, next);
        }
        
    }
    return true;
}


int main()
{
    std::ifstream input("input.txt");
    if(!input)
    {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
        return 1;   //no file, no fun
    }

    std::vector<std::vector<int>> data; //vector of int vectors

    std::string line;

    while(std::getline(input, line))
    {
        std::stringstream ss(line); 
        std::vector<int> row;
        int num;

        while (ss>>num)
        {
            row.push_back(num); //read line to row (only works for space as separator)
        }
        data.push_back(row); //save row (int vector) into vector of vectors
    }

    int safe = 0;
    for(int i=0; i<data.size(); i++)    //vector of vectors
    {
        for(int j=0; j<data[i].size(); j++) //checking each vector
        {
            std::vector<int> tmp = data[i];
            tmp.erase(tmp.begin() + j);
            
            if(test(tmp))
            {
                safe++;
                break;
            }
        }
    }

    std::printf("There are %d safe levels \n", safe);

    return 0;
}