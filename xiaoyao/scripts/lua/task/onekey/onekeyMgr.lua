local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local WindowConfig = require "WindowConfig"
local lua_button1 = require "lua_button1"
local oo = require "class"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"
local ClientControl = require "ClientControl"
local shimen = require "task.onekey.shimen"
local baotu = require "task.onekey.baotu"
local wabaotu = require "task.onekey.wa_bao_tu"
local paobiao = require "task.onekey.paobiao"
local guildtask = require "task.onekey.guildtask"
local shilian = require "task.onekey.shilian"
local paoshang = require "task.onekey.paoshang"
local zy = require "task.onekey.zhenYin"
local cai_ji = require "task.onekey.cai_ji"



local onekeyMgr = oo.class()

function onekeyMgr:ctor()

end

function onekeyMgr:destroy()
	if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
    if self.task then
        self.task:destroy()
        self.task = nil
    end
end

function onekeyMgr:start()
    lua_app.print(7, "onekeyMgr:start 1 ")
    if self:is_all_task_finish() then
        lua_app.print(7, "onekeyMgr:start 2 ")
        return
    end
    lua_app.print(7, "onekeyMgr:start 3 ")
    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)

    self.task:start()
    lua_app.print(7, "onekeyMgr:start end ")

end

function onekeyMgr:onTimer()
    self.work_timer = lua_app.add_timer(1000, "onTimer", self)
    --lua_app.print(7, "onekeyMgr:onTimer ")
end

function onekeyMgr:is_all_task_finish()
    lua_app.print(7, "onekeyMgr:is_all_task_finish 1 ")
    local tasks = {}    
    
    table.insert(tasks, baotu)
    table.insert(tasks, wabaotu)  

    table.insert(tasks, shimen)  

    table.insert(tasks, guildtask) 
    table.insert(tasks, paoshang)     

    table.insert(tasks, shilian)
    table.insert(tasks, paobiao) 
    table.insert(tasks, zy)

    table.insert(tasks, cai_ji)

    for _, test in ipairs(tasks) do
        local task = test.new()
        if false == task:is_finish() then
            self.task = task
            app.show_jing_wu_ui(false)
            return false
        end
    end

    lua_app.print(7, "onekeyMgr:is_all_task_finish end ")
    app.show_jing_wu_ui(true)
    return true
end


return onekeyMgr