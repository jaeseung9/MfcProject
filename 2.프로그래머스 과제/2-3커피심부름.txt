#include <string>
#include <vector>

using namespace std;

int solution(vector<string> order) 
{
    int answer = 0;
    
    for(int i=0; i < order.size(); i++)
    {
        string drink = order[i];
        
        if(drink =="iceamericano"||
          drink =="americanoice"||
          drink =="hotamericano"||
          drink =="americanohot"||
          drink =="americano"||
          drink =="anything")answer += 4500;
        else answer +=5000;
    }
    
    return answer;
}