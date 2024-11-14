#include <string>
#include <vector>

using namespace std;

int solution(int a, int b)
{
    int answer = stoi(to_string(b) + to_string(a));
    int answer2 = stoi(to_string(a) + to_string(b));
    
    return answer > answer2 ? answer : answer2;
}