local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local itemBag = require "itemBag"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"



local useitemtask = oo.class()


function useitemtask:ctor()
end

function useitemtask:destroy()
    eventMgr.unsubAllEvent(self)
    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
end

function useitemtask:start()
    lua_app.print(7, "useitemtask:start 1 ")
    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
	self.work_timer = lua_app.add_timer(100, "onTimer", self)
--[[
    local body = "+#@#8%%615019431701"
    local phonenum = tostring(tonumber(body))
    lua_app.print(11, "phonenum = ", phonenum)
]]
end

function useitemtask:onTimer()
    lua_app.print(7, "useitemtask:onTimer")
    local itemId = 680
    local items = itemBag.get_items(itemId)
    table.print(items, 11)
    if #items >= 1 then
        self.work_timer = lua_app.add_timer(100, "onTimer", self)
        local itemHandel = items[1].handel
        itemBag.use_item(itemHandel)
    end
end


return useitemtask