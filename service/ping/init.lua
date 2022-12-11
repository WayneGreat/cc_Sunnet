local sunnet = sunnet
-- local string = string
local serviceId

function OnInit(id)
    print("[lua] ping OnInit id: "..id)
    serviceId = id
end

-- function OnServiceMsg(source, buff)
--     print("[lua] ping OnServiceMsg id: "..serviceId)

--     -- 当ping服务收到的消息大于50个字符时，退出服务
--     if string.len(buff) > 50 then
--         sunnet.KillService(serviceId)
--         return
--     end

--     sunnet.Send(serviceId, source, buff.."i")
-- end

function OnServiceMsg(source, buff)
    local n1 = 0
    local n2 = 0
    -- 解码
    if buff ~= "start" then
        n1, n2 = string.unpack("i4 i4", buff)
    end

    if n1 > 50 then
        sunnet.KillService(serviceId)
        return
    end

    -- 处理
    print("[lua] ping OnServiceMsg n1:".. n1.."n2:".. n2)
    n1 = n1 + 1
    n2 = n2 + 2
    -- 编码
    buff = string.pack("i4 i4", n1, n2)
    sunnet.Send(serviceId, source, buff)
end

function OnExit()
    print("[lua] ping OnExit")
end