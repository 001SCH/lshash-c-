### 基于随机超平面方法实现的局部敏感哈希，使用c++的Eigen库实现

使用方式如下

```c++
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
```

目前仅支持余弦距离检索，可自行添加其他检索方式
