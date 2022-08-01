require "lua.loader"
local app = require "app"
local ClientControl = require "ClientControl"



local lua_app = {}

lua_app.show_tips = app.show_tips
lua_app.now_ms = app.now_ms


local co_create = coroutine.create
local co_yield = coroutine.yield
local co_resume = coroutine.resume
local co_running = coroutine.running

local co_pool = {}
local session_to_co = {}

local g_session = 0


--lua_app.show_log = true
lua_app.print = function(color, ...)
	local t = {...}
	for i = 1,#t do
		t[i] = tostring(t[i])
	end
	local str = table.concat(t," ")
	if lua_app.show_log then
		app.sprint(color, str)
	end
end

if not table.unpack then
	table.unpack = unpack --5.1
end

table.print = function(t, color, n)
	color = color or 7
    if "table" ~= type(t) then
		lua_app.print(color, tostring(t))
        return 0;
    end
    n = n or 0;
    local str_space = "";
    for i = 1, n do
        str_space = str_space.."  ";
    end
    lua_app.print(color, str_space.."{");
    for k, v in pairs(t) do
        local str_k_v = str_space.."  ["..tostring(k).."] = ";
        if "table" == type(v) then
            lua_app.print(color, str_k_v);
            table.print(v, color, n + 1);
        else
            str_k_v = str_k_v..tostring(v);
            lua_app.print(color, str_k_v);
        end
    end
    lua_app.print(color, str_space.."}");
end

--for c++
__G__TRACKBACK__ = function(msg)
	local debugmsg = debug.traceback(msg)
	--local debugmsg = debug.traceback(msg, 3)
    lua_app.print(4, debugmsg)
    return debugmsg
end
lua_app.timer_mgr = {}
--for c++
__G__UPDATE__ = function(ticket)
	local now = ticket
	for session, data in pairs(lua_app.timer_mgr) do
		if data.time_end <= now then
			if type(data.func) == "function" then
				local ret, errormsg
				if data.target then
					ret, errormsg = pcall(data.func, data.target, table.unpack(data.args))
				else
					ret, errormsg = pcall(data.func, table.unpack(data.args))
				end
				if not ret then
					lua_app.print(4, "timer error 1 call ", errormsg)
				end
			elseif type(data.func) == "string" then
				local func = data.target[data.func]
				local ret, errormsg
				ret, errormsg = pcall(func, data.target, table.unpack(data.args))
				if not ret then
					lua_app.print(4, "timer error 2 call ", errormsg)
				end
			end
			lua_app.timer_mgr[session] = nil
			--data.time_end = now + data.millisec
			--lua_app.print(7, "timer_mgr proc session ", session)
			--[[
			local co = session_to_co[session]
			session_to_co[session] = nil
			if co then
				lua_app.print(7, "timer_mgr run session ", session)
				co_resume(co)
			end
			]]
		end
	end
	--collectgarbage("collect")
	lua_app.check_key()
end


function new_session()
	g_session = g_session + 1
	return g_session
end

function new_co(f)

	local co = table.remove(co_pool)

	if co == nil then
		lua_app.print(7, "new_co 1")
		co = co_create(function(...)
			lua_app.print(7, "co_create 1")
			f(...)
			lua_app.print(7, "co_create 2")
			while true do
				f = nil
				co_pool[#co_pool+1] = co
				f = co_yield "EXIT"
				f(co_yield())
			end
		end)
	else
		lua_app.print(7, "new_co 2")
		co_resume(co,f)
	end
	return co
end

local g_handel = 0
lua_app.add_timer = function(delay_ms, func, target, ...)
	local args = {...}
	--local session = clib.run_after(delay_ms)
	local session = new_session()
	--[[
	table.insert(args,1,session)

	local co = new_co(function()
		lua_app.print(7, "co = new_co")
		func(table.unpack(args))
	end)

	assert(session_to_co[session] == nil)
	session_to_co[session] = co
	]]

	local now = lua_app.now_ms()
	lua_app.timer_mgr[session] = {}
	lua_app.timer_mgr[session].func = func
	lua_app.timer_mgr[session].target = target
	lua_app.timer_mgr[session].millisec = delay_ms
	lua_app.timer_mgr[session].time_start = now
	lua_app.timer_mgr[session].time_end = now + delay_ms
	lua_app.timer_mgr[session].args = args
	return session
	--[[
	g_handel = g_handel + 1
	local now = lua_app.now_ms()
	lua_app.timer_mgr[g_handel] = {}
	lua_app.timer_mgr[g_handel].func = func
	lua_app.timer_mgr[g_handel].millisec = millisec
	lua_app.timer_mgr[g_handel].time_start = now
	lua_app.timer_mgr[g_handel].time_end = now + millisec
	return g_handel
	]]
end

lua_app.del_timer = function(session)
	if session then
		lua_app.timer_mgr[session] = nil
	end
end

lua_app.keydownMap = {}
lua_app.reg_key_down = function(keycode, func)
	lua_app.keydownMap[keycode] = func
end

lua_app.check_key = function()
	local keydown_ctrl = app.is_key_down(0x11)
	local keydown_menu = app.is_key_down(0x12)
	if keydown_menu then
		for keycode, func in pairs(lua_app.keydownMap) do
			local keydown = app.is_key_down(keycode)
			if keydown then
				local ret, errormsg = pcall(func)
				if not ret then
					lua_app.print(4, "check_key error call ", errormsg)
				end
			end
		end
	end
end




return lua_app