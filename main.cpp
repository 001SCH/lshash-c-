#include <Eigen/Eigen>
#include <vector>
#include "mylsh.h"


using namespace std;

int main() {

    MYLSH lsh_my(6,8,1);
    Eigen::Matrix<double,1,8> m1,m2,m3,m4;
    m1<<1,2,3,4,5,6,7,8;
    m2<<2,3,4,5,6,7,8,9;
    m3<<10,12,99,1,5,31,2,3;
    m4<<1,2,3,4,5,6,7,7;

    lsh_my.index_lsh(m1,0);
    lsh_my.index_lsh(m2,1);
    lsh_my.index_lsh(m3,2);
    std::vector<int> candidates_id;
    lsh_my.query(m4,2,candidates_id);

    for (int i = 0; i < candidates_id.size(); i++)
    {
        std::cout<<candidates_id.at(i)<<endl;
    }
    
    return 0;
}
