robj

    typedef struct redisObject {
        unsigned type:4;     // 类型
        unsigned encoding:4;   // 编码
        unsigned lru:REDIS_LRU_BITS; /* lru time (relative to server.lruclock) */ // 对象最后一次被访问的时间
        int refcount;     // 引用计数
        void *ptr;   // 指向实际值的指针
    } robj;

dictEntry

    typedef struct dictEntry {
    void *key;    // 键
    union {    // 值
        void *val;     // 如果不是整型值，那么这里会赋值为 robj  dictAdd(dict *d, void *key, void *val)
        uint64_t u64;
        int64_t s64;
    } v;
    struct dictEntry *next;   // 指向下个哈希表节点，形成链表
    } dictEntry;



list的encoding有REDIS_ENCODING_INTSET(整数集合)或REDIS_ENCODING_HT