print("haha, fistly c++ invokes lua ")

local test = {"kongzhong baolei", 3, "chenkei"}

function add(a, b)
    return a,b, a+b
end

function testmy(a, b)
    local a = myadd(1, 100)
    return a+b
end

--print(test(1,100))
