#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>    //for std::sort

int main()
{
    std::ifstream input("input.txt");
    if(!input)
    {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
        return 1;   //no file, no fun
    }

    std::vector<int> a, b;

    int a_tmp, b_tmp;

    //load from file to vectors
    while (input >> a_tmp >> b_tmp)
    {
        a.emplace_back(a_tmp);
        b.emplace_back(b_tmp);
    }
    
    input.close();  //close file

    //sorting vectors
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    //finding distance
    long sum = 0;
    for(int i=0; i<a.size(); i++)
    {
        sum += abs(a[i]-b[i]);
    }

    std::printf("Sum of the distances is %ld\n", sum);

    long similarityScore = 0;
    for(int i=0; i<a.size(); i++)
    {
        int amount = 0;
        for(int j=0; j<b.size(); j++)
        {
            if(a[i] == b[j])
                amount++;
        }
        similarityScore += a[i]*amount;
    }

    std::printf("Similiarity is %ld", similarityScore);

    return 0;
}