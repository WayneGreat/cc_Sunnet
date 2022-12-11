local serviceId
local conns = {}
local sunnet = sunnet
local listenfd

-- 打印conns
function PrintConns()
    local idx = 0
    for clientfd,_ in pairs(conns) do
        print(idx.." clientfd: "..clientfd)
        idx = idx + 1
    end
end

function OnInit(id)
    serviceId = id
    print("[lua] chat Oninit id:".. id)
    listenfd = sunnet.Listen(8002, id)
end

function OnAcceptMsg(listenfd, clientfd)
    print("[lua] chat OnAcceptMsg "..clientfd)
    conns[clientfd] = true
    PrintConns()
end

function OnSocketData(fd, buff)
    print("[lua] chat OnSocketData "..fd)
    buff = string.reverse(buff)
    for clientfd, _ in pairs(conns) do
        sunnet.Write(clientfd, buff)
    end
end

function OnSocketClose(fd)
    print("[lua] chat OnSocketClose "..fd)
    conns[fd] = nil
    PrintConns()

    -- 服务器xxs后关闭监听
    -- sunnet.CloseConn(listenfd, 0)
    -- sunnet.CloseConn(listenfd, 1)
    -- sunnet.CloseConn(listenfd, 15)
    -- sunnet.CloseConn(listenfd, 100)
end