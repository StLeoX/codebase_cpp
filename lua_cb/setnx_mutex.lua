-- 基于setnx指令的分布式互斥锁

-- mutex impl01
-- args:
-- KEYS[1] 锁键
-- ARGV[1] 锁值
-- ARGV[2] 持锁时间
-- RET 1==succ 0=fail
if redis.call('SETNX', KEYS[1], ARGV[1])
then
    if redis.call('GET', KEYS[1]) == ARGV[1]
    then
        return redis.call('EXPIRE', KEYS[1], ARGV[2])
    else
        return 0
    end
else
    return 0
end


-- mutex impl02
-- args:
-- KEYS[1] 锁键
-- ARGV[1] 锁值
-- ARGV[2] 持锁时间
-- RET 1==succ 0=fail
-- pattern: set "$key" "$value" NX EX $time
if redis.call('SETNX', KEYS[1], ARGV[1], 'NX', 'EX', ARGV[2])
then
    return redis.call('GET', KEYS[1]) == ARGV[1]
else
    return 0
end

-- unlock
-- args:
-- KEYS[1] 锁键
-- ARGV[1] 期望锁值（期望未修改）
-- RET 1==succ 0=fail
if redis.call('GET', KEYS[1]) == ARGV[1]
then
    return redis.call('DEL', KEYS[1]) -- 并清除
else
    return 0
end
