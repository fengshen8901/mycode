local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"



local bao_tu = oo.class()

function bao_tu:ctor()
end
--判断是否完成了
function bao_tu:is_finish()
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
        --宝图完成了
        --lua_app.print(11, "宝图完成了")
        return true
    end
    return true
end

function bao_tu:getTaskInfo()
    local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
    local career = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CAREER)
    self.taskId = 5023
    local info = ClientControl.get_task_info(self.taskId)
    return info
end

function bao_tu:destroy()
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
    eventMgr.unsubEvent(eventMgr.event.progress_item_open, self, "onProgressItemOpen")
    ]]
    eventMgr.unsubAllEvent(self)

    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
end

function bao_tu:start()
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
    eventMgr.subEvent(eventMgr.event.progress_item_open, self, "onProgressItemOpen")

end

function bao_tu:onTimer()
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
	--lua_app.print(7, "bao_tu:onTimer 1 ")

    if self.isGather then
		--lua_app.print(7, "bao_tu:onTimer isGather ")
        local info = self:getTaskInfo()
        --table.print(info, 10)
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

function bao_tu:logic()
    if common.InBattle() then
        --lua_app.print(7, "bao_tu:logic InBattle ")
        return
    end
    if ClientControl.is_moving() then
        --lua_app.print(7, "bao_tu:logic is_moving ")
        return
    end
    local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
    local career = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CAREER)
    local info = self:getTaskInfo()
    --table.print(info, 10)
    if info.status == common.missionStatus.can_accept then
        --lua_app.print(7, "去接宝图任务 ")
        ClientControl.move_patch(12, 176, 86)
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
        --宝图完成了
        --lua_app.print(9, "宝图完成了")
    end
end

--接任务
function bao_tu:onOpenLingQuMutual(TargetEntityID, mutualID, selects, contexts)
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
	--lua_app.print(10, "bao_tu:onOpenLingQuMutual ", TargetEntityID, mutualID)
	--table.print(selects, 10)
    --table.print(contexts, 10)
	--选择交互第一个选项
	if selects[1] then
		ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
	end
    self.isPatching = nil
end

function bao_tu:onOpenMutual(TargetEntityID, mutualID, selects, contexts)
    --eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
	--lua_app.print(10, "bao_tu:onOpenMutual ", TargetEntityID, mutualID)
	--table.print(selects, 10)
    --table.print(contexts, 10)
	--选择交互第一个选项
	if selects[1] then
		ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
	end
    self.isPatching = nil
end

function bao_tu:onPatchEndLingQu()
	eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndLingQu")
	self.isPatching = nil
	--lua_app.print(7, "bao_tu:onPatchEndLingQu ")
    local entityId = common.getNpcEntiyIdByName("店小二")
    if entityId then
        --lua_app.print(7, "bao_tu:logic 点击 店小二 ")
        ClientControl.open_mutual(entityId)
        eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
    else
        --lua_app.print(7, "bao_tu:logic 找不到 店小二 ")
    end
end

function bao_tu:onPatchEndTrace()
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
	self.isPatching = nil
    lua_app.print(7, "bao_tu:onPatchEndTrace ")

end

function bao_tu:onNpcShopOpen(st)
    --lua_app.print(7, "bao_tu:onNpcShopOpen ")
    --table.print(st, 10)

    common.buyNpcShopItem(st)
    self.isPatching = nil
end

function bao_tu:onGiveUiOpen()
    --lua_app.print(7, "bao_tu:onGiveUiOpen ")
    ClientControl.on_ok_give_ui()
    self.delay = 2
    self.isPatching = nil
end

function bao_tu:onPetTradeCenterOpen(firstCatchId)
    lua_app.print(7, "bao_tu:onPetTradeCenterOpen ", firstCatchId)
    common.buyShopPet(firstCatchId)
    self.delay = 2
    self.isPatching = nil
end

function bao_tu:onPetListSelectOpen(firstCatchId)
    --lua_app.print(7, "bao_tu:onPetListSelectOpen ", firstCatchId)
    ClientControl.pet_list_select(firstCatchId)
    self.delay = 2
    self.isPatching = nil
end

function bao_tu:onBattleSceneIdChange(prop, old, new)
    --lua_app.print(7, "bao_tu:onBattleSceneIdChange ", prop, old, new)
    self.delay = 2
    self.isPatching = nil
end

function bao_tu:onSaleCenterOpen(isTaskOpen, guids)
    --lua_app.print(7, "bao_tu:onSaleCenterOpen ", isTaskOpen)
    if isTaskOpen and guids[1] and guids[1] > 0 then
        common.buySaleCenterItem(guids[1])
        ClientControl.show_sale_center(false)
    end
    self.delay = 2
    self.isPatching = nil
end

function bao_tu:onShangHuiOpen(itemId, num)
    --lua_app.print(7, "bao_tu:onShangHuiOpen ", itemId, num)
    common.buyShangHuiItem(itemId, num)
    self.delay = 2
    self.isPatching = nil
end

function bao_tu:onProgressItemOpen(itemHandel)
    --lua_app.print(7, "bao_tu:onProgressItemOpen ", itemHandel)
end





return bao_tu