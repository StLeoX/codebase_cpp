-- 基于expire指令的限速器
-- KEYS[1] 要限制的键，典型如限速ip
-- ARGV[1] 限制的访问次数
-- ARGV[2] 限制的时间

local key = "limit:" .. KEYS[1]
local limit = tonumber(ARGV[1])
local expire_time = ARGV[2]

local is_exists = redis.call("EXISTS", key)
if is_exists == 1 then
    if redis.call("INCR", key) > limit then
        return 0
    else
        return 1
    end
else
    redis.call("SET", key, 1)
    redis.call("EXPIRE", key, expire_time)
    return 1
end
