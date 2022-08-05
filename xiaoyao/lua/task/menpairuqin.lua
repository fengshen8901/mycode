local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"


local huanjing = oo.class()

function huanjing:ctor()

end

function huanjing:destroy()
	eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
	if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
end

function huanjing:start()
	if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
	self.work_timer = lua_app.add_timer(1000, "onTimer", self, "aa", "bb", "cc")

	local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
	local mapId = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_MAPID)
	local x = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
	local y = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
	local name = mainplayer:get_prop_string(PropConfig.PROP_ENTITY_NAME)
	lua_app.print(7, "huanjing:start ", mapId, x, y, name)
	self.mapId = mapId
	self.x = x
	self.y = y
	self.targetId = nil
	eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
end

function huanjing:onTimer(a, b, c)
	self.work_timer = lua_app.add_timer(1000, "onTimer", self, "aa", "bb", "cc")

	if self.isPatching then
		lua_app.print(7, "huanjing:onTimer isPatching ")
		return
	end
	self:logic()
end

function huanjing:logic()
	local mainEntityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(mainEntityId)
	local mapId = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_MAPID)
	local x = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
	local y = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
	local mainBattleSceneID = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_BATTLESCENEID)
	if mainBattleSceneID > 0 then
		return
	end
	local entitys = scene.get_all_monster()
	local names = {"九黎战神", "九黎鹏将军", "九黎熊将军", "九黎象将军", "九黎勇士", "九黎小妖"}
	for _, findname in ipairs(names) do
		local minDistance = 9999999
		lua_app.print(7, "huanjing:logic 开始找 ", findname)
		for _, entityId in pairs(entitys) do
			local entity = scene.get_entity(entityId)
			local x1 = entity:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
			local y1 = entity:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
			local battleSceneID = entity:get_prop_int(PropConfig.PROP_ENTITY_BATTLESCENEID)
			local name = entity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
			if battleSceneID == 0 and name == findname then
				local distance = math.abs(x - x1) + math.abs(y - y1)
				if not self.targetId or distance < minDistance then
					minDistance = distance
					self.targetId = entityId
				end
			end
		end
		if self.targetId then
			break
		end
	end
	if self.targetId and false == ClientControl.is_moving() then
		local entity = scene.get_entity(self.targetId)
		if false == entity:is_exist() then
			lua_app.print(11, "huanjing:logic 目标不存在了，重新找 ", self.targetId)
			self.targetId = nil
			return
		end
		local battleSceneID = entity:get_prop_int(PropConfig.PROP_ENTITY_BATTLESCENEID)
		if battleSceneID > 0 then
			lua_app.print(11, "huanjing:logic 目标战斗中，重新找 ", self.targetId)
			self.targetId = nil
			return
		end
		local x1 = entity:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
		local y1 = entity:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
		if math.abs(x - x1) + math.abs(y - y1) < 5 then
			ClientControl.open_mutual(self.targetId)
		else
			ClientControl.move_to(x1, y1)
		end
		return
	end

end

function huanjing:onOpenMutual(TargetEntityID, mutualID, selects, contexts)
	--eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
	lua_app.print(7, "huanjing:onOpenMutual ", TargetEntityID, mutualID)
	table.print(selects)
	table.print(contexts)
	--选择交互第一个选项
	if selects[1] then
		ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
	end
end

lua_app.print(12, "huanjing re load  ----")

return huanjing