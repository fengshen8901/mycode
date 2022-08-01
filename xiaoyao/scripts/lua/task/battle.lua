local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"






local battle = oo.class()

function battle:ctor()

end

function battle:destroy()
	eventMgr.unsubAllEvent(self)
end

function battle:start()
	eventMgr.subEvent(eventMgr.event.actor_ready_ins, self, "onActorReadyIns")
	eventMgr.subEvent(eventMgr.event.pet_ready_ins, self, "onPetReadyIns")
end

function battle:onActorReadyIns(bout)
	lua_app.print(7, "battle:onActorReadyIns ", bout)
	--[[
	local entityIds = ClientControl.get_battle_all_entityid()
	table.print(entityIds, 11)
	local entityId1
	for _, entityId in pairs(entityIds) do
		local entity = scene.get_entity(entityId)
		local side = ClientControl.get_battle_entityid_side(entityId)
		local name = entity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
		local command = entity:get_battle_command_str()
		lua_app.print(7, "side, name, command ", side, name, command)
		if not entityId1 and name == "ÒõÏÕµÄ¼µºÞÄ§" then
			entityId1 = entityId
		end
	end

	--1202 Ë®Áú¾÷
	--1203 Ë«ÁúÏ·Öé
	if entityId1 and false == ClientControl.is_skill_gray(1202) then
		ClientControl.use_skill(1202, entityId1)
		--ClientControl.use_skill(1203, entityId1)
	end
	]]

	local mainEntityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(mainEntityId)
	local name = mainplayer:get_prop_string(PropConfig.PROP_ENTITY_NAME)

	if not self.error and not self.logic then
		local module_name = "task.battle_logic."..name
		local modules = {}
		table.insert(modules, module_name)
		oo.require_module(modules)
		local ret, new_module = pcall(require, module_name)
		if ret and new_module then
			self.logic = new_module
		else
			self.error = true
		end
	end
	if self.logic then
		self.logic.doActorBoutAi(bout)
	end

end

function battle:onPetReadyIns(bout, petEntityID)
	lua_app.print(8, "battle:onPetReadyIns", bout, petEntityID)
	--[[
	--É½¾«¶ñÄ§
	local entityIds = ClientControl.get_battle_all_entityid()
	local entityId1
	for _, entityId in pairs(entityIds) do
		local entity = scene.get_entity(entityId)
		local name = entity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
		if not entityId1 and name == "É½¾«¶ñÄ§" then
			entityId1 = entityId
		end
	end

	--2843 ÌìÀÇÕ¶
	if entityId1 and false == ClientControl.is_skill_gray(1202) then
		lua_app.print(11, "É½¾«¶ñÄ§ ")
		ClientControl.pet_use_skill(2843, entityId1)
	end
	]]
	if self.logic then
		self.logic.doPetBoutAi(bout, petEntityID)
	end
end

lua_app.print(12, "battle re load  ----")

return battle