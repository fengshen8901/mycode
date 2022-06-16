local socket = require("socket.core")
g_client = nil
g_lf=string.char(10)


function output(msg)
	io.stdout:write(msg)
end

function print_prompt()
	output("\n编译终端>")
end

function exit()
	g_client:send("<close>"..g_lf)
	os.exit(0)
end


g_local_cmd ={ 
	["exit"]= exit
}

function close_connect()
	g_client:close()
	output("与编译服务器断开连接")
	end
	function send_request( msg)
	local c,err=g_client:send(msg..g_lf)
	if err then
		close_connect()
		os.exit(1)
	end
end
function process_request()
	local line = io.read("*l")
	if g_local_cmd[line] then 
		g_local_cmd[line]()
		print_prompt()
	else
		send_request(line)
		process_response()
	end
	
end

--receive server echo,print
function process_response()
	while true do 
			echo = g_client:receive("*l") 
			if echo then 
				if echo=="<send_over>" then break
				else
				output(echo)
				output("\n")
				end
			else break	end
	end
	print_prompt()
end

function init(host, port)
	local username = arg[1]
	local password = arg[2]
	if username == nil then
		print(" 请输入用户名!")
		os.exit(1)
	end
	if password == nil then
		print(" 请输入密码!")
		os.exit(1)
	end
	host = arg[3] or "127.0.0.1"
	port = arg[4] or 6060
				
	g_client = socket.tcp()
	g_client:setoption("tcp-nodelay",true)

	if g_client:connect(host, port) then
		g_client:send(username.." "..password..g_lf)
		local msg, err = g_client:receive("*l")
		if err then 
			print(string.format("不能连接编译服务器,%s.", msg or err ))
			os.exit(1)
		elseif msg == "<logon>" then
			print(string.format("成功连接编译服务器,%s,%s.",host,port))
		elseif msg == "<logon_build>" then
			print(string.format("成功连接编译服务器,%s,%s.",host,port))
			process_response();
		else
			print(string.format("不能连接编译服务器,%s.", msg or err ))
			os.exit(1)
		end
	else
		print(string.format("不能连接编译服务器,%s,%s,请检查编译服务器是否启动.",host,port))
		os.exit(1)
	end
	print_prompt()
end

function main_loop()
	while true do
		process_request()
	end	
end

init(host,port)
main_loop()


