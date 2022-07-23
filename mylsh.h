#ifndef MYLSH_H
#define MYLSH_H


#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <Eigen/Eigen>


class MYLSH
{
private:
    int hash_size;
    int input_dim;
    int num_hashtables=1;
    std::vector<Eigen::MatrixXd> uniformPlanes;
    std::vector< std::map<std::string ,std::vector<std::pair<Eigen::MatrixXd,int>>> >  hash_tables;
public:
    MYLSH(int hashSize,int inputDim,int NumHashtables);

    void index_lsh(Eigen::MatrixXd input_point,int extra_data);
    std::string _hash(Eigen::MatrixXd planes,Eigen::MatrixXd input_point);
    void query(Eigen::MatrixXd query_point ,int num_results, std::vector<int> & candidates_id);
};





#endif //MYLSH_H
