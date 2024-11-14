#include <string>
#include <sstream>
#include <vector>

using namespace std;

int solution(string s) 
{
    int answer = 0;
    int temp = 0;
    
    stringstream ss(s);
    string score;
    
    while (ss >> score) 
    {
        if (score == "Z") 
        {
            answer -= temp;
        } 
        else 
        {
            int num = stoi(score);
            answer += num;
            temp = num;
        }
    }
    
    return answer;
}
