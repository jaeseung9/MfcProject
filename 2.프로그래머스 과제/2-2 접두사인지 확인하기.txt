#include <string>
#include <vector>

using namespace std;

int solution(string my_string, string is_prefix)
{
    int answer = 1;
    
    if(my_string.size() < is_prefix.size()) return 0;
    
    for(int i=0; i<is_prefix.size(); i++)
    {
        if(my_string[i] != is_prefix[i]) return 0;
    }
    
    return answer;
}