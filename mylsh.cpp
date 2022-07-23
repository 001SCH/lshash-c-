#include "mylsh.h"



//构造函数
MYLSH::MYLSH(int hashSize,int inputDim,int NumHashtables)
{
    hash_size=hashSize; //10
    input_dim=inputDim;
    num_hashtables=NumHashtables;

    //初始化随机超平面  10*7266
    for(int i=0;i<num_hashtables;i++)
    {
        uniformPlanes.push_back(Eigen::MatrixXd::Random(hash_size,input_dim));
    }
    
    //初始化哈希表
    hash_tables.resize(num_hashtables);
}

//添加索引
void MYLSH::index_lsh(Eigen::MatrixXd input_point,int extra_data)
{
    std::pair<Eigen::MatrixXd,int> value=std::make_pair(input_point,extra_data);

    for(int i=0;i<num_hashtables;i++)
    {
        std::string s_key=_hash(uniformPlanes.at(i),input_point);
        auto iter=hash_tables.at(i).find(s_key);
        if(iter==hash_tables.at(i).end())
        {
            hash_tables.at(i)[s_key].push_back(value);
        }
        else
        {
            hash_tables.at(i)[s_key].push_back(value);
        }
    }
}

bool comp(std::pair<Eigen::Matrix<double,-1,1>,int>p1,std::pair<Eigen::Matrix<double,-1,1>,int>p2)
{
    return p1.first[0]>p2.first[0]; //余弦相似度，越大越好
}

void MYLSH::query(Eigen::MatrixXd query_point ,int num_results,std::vector<int> & candidates_id )
{
    //std::vector<int>  candidates_id;    //检索到的id
    std::vector<std::pair<Eigen::MatrixXd,int>> candidates;
    std::vector<std::pair<Eigen::Matrix<double,-1,1>,int>> consin_score;
    for(int i=0;i<num_hashtables;i++)
    {
        std::string  binary_hash=_hash(uniformPlanes.at(i),query_point);
        candidates.insert(candidates.end(),hash_tables.at(i)[binary_hash].begin(),hash_tables.at(i)[binary_hash].end());
    }
    for (int i = 0; i < candidates.size(); i++)
    {
        Eigen::Matrix<double,-1,1> result=((query_point*candidates.at(i).first.transpose()) /(query_point.norm()*candidates.at(i).first.norm()));
        consin_score.push_back(std::make_pair(result,candidates.at(i).second));
    }
    std::sort(consin_score.begin(),consin_score.end(),comp);

    if(consin_score.size()<num_results) num_results=consin_score.size();

    for (int i = 0; i < num_results; i++)
    {
        candidates_id.push_back(consin_score.at(i).second);
    }
    
}



//哈希
std::string MYLSH::_hash(Eigen::MatrixXd planes,Eigen::MatrixXd input_point)
{
    std::string s_key;
    Eigen::MatrixXd projections=planes* input_point.transpose();    //10*7266 7266*1
    //std::cout<<projections.cols()<<"    "<<projections.rows()<<std::endl;
    for (int i = 0; i < projections.cols(); i++)
    {
        for (int j = 0; j < projections.rows(); j++)
        {
            if(projections(j,i)>0)
            {
                s_key=s_key+"1";
            }
            else
            {
                s_key=s_key+"0";
            }
        }
        
    }
    return s_key;
    
}