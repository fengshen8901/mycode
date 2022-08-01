local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"



--[[
    Keeper = 1,         --凌霄殿
    Killer	= 2,        --天策府
	Shooter = 3,        --水晶宫
	Barbarian = 4,      --云影阁
	New = 5,            --灵台山
	Paladin = 6,        --兽王宗
	Priest = 7,         --天音寺
	Hunter = 8,         --火云洞
	Monk = 9,           --幽冥殿
	KunLun = 10,        --天荒城
]]
local careerPos = 
{
    {31, 56, 73, "二郎神"},
    {32, 47, 25, "秦琼"},
    {33, 54, 31, "东海龙王"},
    {34, 49, 30, "阴影之刃"},
    {35, 42, 30, "菩提老祖"},
    {36, 47, 30, "雷霆之怒"},
    {37, 40, 39, "慧能大师"},
	--{37, 40, 41, "慧能大师"},
    {38, 36, 20, "火神祝融"},
    {39, 23, 57, "阎罗王"},
    {40, 49, 43, "羲启"},
    {43, 21, 52, "金角大王"},
}


local shi_men = oo.class()

function shi_men:ctor()
end
--判断是否完成了
function shi_men:is_finish()
    local info = self:getTaskInfo()
    
    --table.print(info, 7)
    if info.status == common.missionStatus.can_accept then
        return false
    end
    if info.status == common.missionStatus.accepted 
    or info.status == common.missionStatus.finished then
        return false
    end
    if info.status == common.missionStatus.over then
        --师门完成了
        lua_app.print(11, "师门完成了")
        return true
    end
    return true
end

function shi_men:getTaskInfo()
    local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
    local career = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CAREER)
    self.taskId = 5001 + career - 1

    local pos = careerPos[career]
    self.careerNpc = pos[4]
    local info = ClientControl.get_task_info(self.taskId)
    return info
end

function shi_men:destroy()
    --[[
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndLingQu")
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
    eventMgr.unsubEvent(eventMgr.event.npcshop_open, self, "onNpcShopOpen")
    eventMgr.unsubEvent(eventMgr.event.giveui_open, self, "onGiveUiOpen")
    eventMgr.unsubEvent(eventMgr.event.pet_trade_open, self, "onPetTradeCenterOpen")
    eventMgr.unsubEvent(eventMgr.event.pet_list_select_open, self, "onPetListSelectOpen")
    local event = eventMgr.makePropEvent(PropConfig.PROP_ENTITY_BATTLESCENEID)
    eventMgr.unsubEvent(event, self, "onBattleSceneIdChange")
    eventMgr.unsubEvent(eventMgr.event.sale_center_open, self, "onSaleCenterOpen")
    eventMgr.unsubEvent(eventMgr.event.shang_hui_open, self, "onShangHuiOpen")
    ]]
    eventMgr.unsubAllEvent(self)

    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
end

function shi_men:start()
    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)

    eventMgr.subEvent(eventMgr.event.npcshop_open, self, "onNpcShopOpen")
    eventMgr.subEvent(eventMgr.event.giveui_open, self, "onGiveUiOpen")
    eventMgr.subEvent(eventMgr.event.pet_trade_open, self, "onPetTradeCenterOpen")
    eventMgr.subEvent(eventMgr.event.pet_list_select_open, self, "onPetListSelectOpen")

    local event = eventMgr.makePropEvent(PropConfig.PROP_ENTITY_BATTLESCENEID)
    eventMgr.subEvent(event, self, "onBattleSceneIdChange")
    eventMgr.subEvent(eventMgr.event.sale_center_open, self, "onSaleCenterOpen")
    eventMgr.subEvent(eventMgr.event.shang_hui_open, self, "onShangHuiOpen")

end

function shi_men:onTimer()
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
	lua_app.print(7, "shi_men:onTimer 1 ")

    if self.isGather then
		lua_app.print(7, "shi_men:onTimer isGather ")
        local info = self:getTaskInfo()
        table.print(info, 10)
        if info.eTargetType == 48 or info.eTargetType == 55 or info.eTargetType == 56 then
            self.isGather = true
            return
        else
            self.isGather = false
        end
	end
    if self.delay then
        self.delay = self.delay - 1
        if self.delay <= 0 then
            self.delay = nil
        end
        return
    end
	self:logic()
end

function shi_men:logic()
    if common.InBattle() then
        lua_app.print(7, "shi_men:logic InBattle ")
        return
    end
    if ClientControl.is_moving() then
        lua_app.print(7, "shi_men:logic is_moving ")
        return
    end
    local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
    local career = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CAREER)
    local info = self:getTaskInfo()
    --table.print(info, 10)
    if info.status == common.missionStatus.can_accept then
        lua_app.print(7, "去接师门任务 ")
        local pos = careerPos[career]
        table.print(pos, 7)
        ClientControl.move_patch(pos[1], pos[2], pos[3])
		eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEndLingQu")
        return
    end
    if info.status == common.missionStatus.accepted 
    or info.status == common.missionStatus.finished then
        --追踪任务，与游戏内点击任务追踪一样的
        ClientControl.auto_trace_mission(self.taskId)
        eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
        eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
        --48 采集 55 收集 56 清理
        if info.eTargetType == 48 or info.eTargetType == 55 or info.eTargetType == 56 then
            self.isGather = true
        end
        return
    end
    if info.status == common.missionStatus.over then
        --师门完成了
        lua_app.print(9, "师门完成了")
    end
end

--接任务
function shi_men:onOpenLingQuMutual(TargetEntityID, mutualID, selects, contexts)
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
	lua_app.print(10, "shi_men:onOpenLingQuMutual ", TargetEntityID, mutualID)
	table.print(selects, 10)
    table.print(contexts, 10)
	local hasSelect = false
	--选择交互第一个选项
	for i, str in ipairs(contexts) do
        local s, e = string.find(str, "师门")
        if s then
            ClientControl.mutual_select(TargetEntityID, mutualID, selects[i])
            hasSelect = true
            break
        end
    end
	if not hasSelect and selects[1] then
		ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
	end
    self.isPatching = nil
	self.delay = 3
end

function shi_men:onOpenMutual(TargetEntityID, mutualID, selects, contexts)
    --师门有些交互需要点两下，这里就不解注册了
    --eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
	lua_app.print(10, "shi_men:onOpenMutual ", TargetEntityID, mutualID)
	table.print(selects, 10)
    table.print(contexts, 10)
	local hasSelect = false
	--选择交互第一个选项
	for i, str in ipairs(contexts) do
        local s, e = string.find(str, "师门")
        if s then
            ClientControl.mutual_select(TargetEntityID, mutualID, selects[i])
			lua_app.print(10, "shi_men:onOpenMutual select ", i)
            hasSelect = true
            break
        end
    end
	if not hasSelect and selects[1] then
		ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
		lua_app.print(10, "shi_men:onOpenMutual select ", 1)
	end
    self.isPatching = nil
	self.delay = 3
end

function shi_men:onPatchEndLingQu()
	eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndLingQu")
	self.isPatching = nil
	lua_app.print(7, "shi_men:onPatchEndLingQu 1")
    --local entityId = common.getNpcEntiyIdByName(self.careerNpc)
	local entityId = common.getNearNpcEntiyIdByName(self.careerNpc)
    if entityId then
        lua_app.print(7, "shi_men:logic 点击 ", self.careerNpc, entityId)
        ClientControl.open_mutual(entityId)
        eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
		lua_app.print(7, "shi_men:onPatchEndLingQu 2")
    else
        lua_app.print(7, "shi_men:logic 找不到 ", self.careerNpc)
    end
	self.delay = 3
end

function shi_men:onPatchEndTrace()
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
	self.isPatching = nil
    lua_app.print(7, "shi_men:onPatchEndTrace ")

end

function shi_men:onNpcShopOpen(st)
    lua_app.print(7, "shi_men:onNpcShopOpen ")
    table.print(st, 10)

    common.buyNpcShopItem(st)
    self.isPatching = nil
end

function shi_men:onGiveUiOpen()
    lua_app.print(7, "shi_men:onGiveUiOpen ")
    ClientControl.on_ok_give_ui()
    self.delay = 3
    self.isPatching = nil
end

function shi_men:onPetTradeCenterOpen(firstCatchId)
    lua_app.print(7, "shi_men:onPetTradeCenterOpen ", firstCatchId)
    common.buyShopPet(firstCatchId)
    self.delay = 5
    self.isPatching = nil
end

function shi_men:onPetListSelectOpen(firstCatchId)
    lua_app.print(7, "shi_men:onPetListSelectOpen ", firstCatchId)
    ClientControl.pet_list_select(firstCatchId)
    self.delay = 3
    self.isPatching = nil
end

function shi_men:onBattleSceneIdChange(prop, old, new)
    lua_app.print(7, "shi_men:onBattleSceneIdChange ", prop, old, new)
    self.delay = 3
    self.isPatching = nil
end

function shi_men:onSaleCenterOpen(isTaskOpen, guids)
    lua_app.print(7, "shi_men:onSaleCenterOpen ", isTaskOpen)
    if isTaskOpen and guids[1] and guids[1] > 0 then
        common.buySaleCenterItem(guids[1])
        ClientControl.show_sale_center(false)
    end
    self.delay = 3
    self.isPatching = nil
end

function shi_men:onShangHuiOpen(itemId, num)
    lua_app.print(7, "shi_men:onShangHuiOpen ", itemId, num)
    common.buyShangHuiItem(itemId, num)
    self.delay = 3
    self.isPatching = nil
end




return shi_men