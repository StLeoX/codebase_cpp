[分布式唯一ID生成的几种方案](https://mp.weixin.qq.com/s/bGaP4u-AIS56waH2itpS-w)
[twitter/snowflake](https://github.com/twitter/snowflake/blob/snowflake-2010/src/main/scala/com/twitter/service/snowflake/IdWorker.scala)
[Leaf——来自美团点评的分布式ID生成系统](https://mp.weixin.qq.com/s/mY6ulc62pP77Iyl3CiK3dw)
[百度UidGenerator](https://github.com/baidu/uid-generator/blob/master/README.zh_cn.md)

之前项目有需要用到唯一ID，且要求尽量短，时间有序，则非snowflake算法莫属，又因为我们是多进程开发模型，于是实现了个多进程版的库。
唯一ID不是什么新鲜的东西，所以这里就不再多说了，有兴趣的参考上面几篇文章基本足已。

## 这个库有什么特点：
1. 多进程多线程可用
2. 时间回退可用，因为共享内存里保存了最后时间，只要最后毫秒内id没分配完都能提供服务（可通过宏关闭）
3. HASH友好，其实大部分服务并发不会太高，会导致每毫秒分配的id都是0、1居多，这里实现的每秒序号的累计（可通过宏关闭）
4. 机器标识不细分数据标识和机器标识

## 机器标识获取的方案
本库保留了机器标识获取接口未实现，需要使用者自行实现，大致建议有以下几种方案，容易到复杂：
1. 直接配置文件配置IP对应的标识，扩缩容都需要手动配置
2. kv、db等管理配置，扩容自动获取标识，缩容手动踢除
3. zookeeper管理配置，扩缩容可以自动管理

## 性能
本库单进程可跑满每毫秒能生成的id