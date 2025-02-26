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

int main()
{
    std::ifstream input("input.txt");
    if(!input)
    {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
        return 1;   //no file, no fun
    }

    std::vector<std::vector<int>> data; //wektor wektorów intów

    std::string line;

    while(std::getline(input, line))
    {
        std::stringstream ss(line); 
        std::vector<int> row;
        int num;

        while (ss>>num)
        {
            row.push_back(num); //wczytujemy linijkę do row jako inty oddzielone spacją
        }
        data.push_back(row); //wpisujemy wektor intów w wektor wektorów
    }

    int safe = 0;
    for(int i=0; i<data.size(); i++)
    {
        int prev, next, state;
        for(int j=1; j<data[i].size(); j++)
        {
            prev = data[i][j-1];
            next = data[i][j];
            if(!compareNumbers(prev, next))
                break;
            
            if(j==1)
                state = compareNumbers(prev, next);
            else
            {
                if(state != compareNumbers(prev, next))
                    break;
                else
                    state = compareNumbers(prev, next);
            }
            
            if(j==data[i].size()-1)
                safe++;
        }
    }

    std::printf("There are %d safe levels \n", safe);

    return 0;
}