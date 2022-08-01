local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"


local pao_huan = oo.class()

function pao_huan:ctor()
    self.taskId = 5026
end

function pao_huan:destroy()
    --[[
	eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEnd")
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
    self.isPatching = nil
end

function pao_huan:start()
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

function pao_huan:onTimer()
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
	--lua_app.print(7, "pao_huan:onTimer 1 ")

	if self.isPatching then
		lua_app.print(7, "pao_huan:onTimer isPatching ")
		return
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

function pao_huan:logic()
    if common.InBattle() then
        lua_app.print(7, "wa_bao_tu:logic InBattle ")
        return
    end
    if ClientControl.is_moving() then
        lua_app.print(7, "wa_bao_tu:logic is_moving ")
        return
    end
    local info = ClientControl.get_task_info(self.taskId)
    --lua_app.print(7, "pao_huan:logic start ")
    table.print(info, 7)
    if info.status == common.missionStatus.can_accept then
        lua_app.print(7, "pao_huan:logic can_accept ")
        --望仙镇
        ClientControl.move_patch(13, 34, 52)
		eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEnd")
		self.isPatching = true
        self.isGoToLingQu = true
        return
    end
    if self.isGoToLingQu then
        self.isGoToLingQu = false
        eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
    end
    if info.status == common.missionStatus.accepted 
    or info.status == common.missionStatus.finished then
        --追踪任务，与游戏内点击任务追踪一样的
        ClientControl.auto_trace_mission(self.taskId)
        eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
        eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
		self.isPatching = true
    end
end

--接任务
function pao_huan:onOpenLingQuMutual(TargetEntityID, mutualID, selects, contexts)
    --eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
	lua_app.print(10, "pao_huan:onOpenLingQuMutual ", TargetEntityID, mutualID)
	table.print(selects, 10)
    table.print(contexts, 10)
	--选择交互第一个选项
	if selects[1] then
		ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
	end
    self.isPatching = nil
end

function pao_huan:onOpenMutual(TargetEntityID, mutualID, selects, contexts)
    --eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
	lua_app.print(10, "pao_huan:onOpenMutual ", TargetEntityID, mutualID)
	table.print(selects, 10)
    table.print(contexts, 10)
	--选择交互第一个选项
	--if selects[1] then
	--	ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
	--end
    local hasSelect = false
    for i, str in ipairs(contexts) do
        local s, e = string.find(str, "任务链")
        if s then
            ClientControl.mutual_select(TargetEntityID, mutualID, selects[i])
            hasSelect = true
            break
        end
    end
    --if not hasSelect and selects[1] then
    --    ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
    --end
    self.isPatching = nil
end

function pao_huan:onPatchEnd()
	eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEnd")
	self.isPatching = nil
	lua_app.print(7, "pao_huan:onPatchEnd ")
    local entityId = common.getNpcEntiyIdByName("宁书生")
    if entityId then
        lua_app.print(7, "pao_huan:logic 点击 宁书生 ")
        ClientControl.open_mutual(entityId)
        eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
    else
        lua_app.print(7, "pao_huan:logic 找不到 宁书生 ")
    end
end

function pao_huan:onPatchEndTrace()
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
	self.isPatching = nil
    lua_app.print(7, "pao_huan:onPatchEndTrace ")

end

function pao_huan:onNpcShopOpen(st)
    lua_app.print(7, "pao_huan:onNpcShopOpen ")
    table.print(st, 10)

    common.buyNpcShopItem(st)
    self.isPatching = nil
end

function pao_huan:onGiveUiOpen()
    lua_app.print(7, "pao_huan:onGiveUiOpen ")
    ClientControl.on_ok_give_ui()
    self.delay = 3
    self.isPatching = nil
end

function pao_huan:onPetTradeCenterOpen(firstCatchId)
    lua_app.print(7, "pao_huan:onPetTradeCenterOpen ", firstCatchId)
    common.buyShopPet(firstCatchId)
    self.delay = 5
    self.isPatching = nil
end

function pao_huan:onPetListSelectOpen(firstCatchId)
    lua_app.print(7, "pao_huan:onPetListSelectOpen ", firstCatchId)
    ClientControl.pet_list_select(firstCatchId)
    self.delay = 3
    self.isPatching = nil
end

function pao_huan:onBattleSceneIdChange(prop, old, new)
    lua_app.print(7, "pao_huan:onBattleSceneIdChange ", prop, old, new)
    self.delay = 3
    self.isPatching = nil
end

function pao_huan:onSaleCenterOpen(isTaskOpen, guids)
    lua_app.print(7, "pao_huan:onSaleCenterOpen ", isTaskOpen)
    if isTaskOpen and guids[1] and guids[1] > 0 then
        common.buySaleCenterItem(guids[1])
        ClientControl.show_sale_center(false)
    end
    self.delay = 3
    self.isPatching = nil
end

function pao_huan:onShangHuiOpen(itemId, num)
    lua_app.print(7, "pao_huan:onShangHuiOpen ", itemId, num)
    common.buyShangHuiItem(itemId, num)
    self.delay = 3
    self.isPatching = nil
end





return pao_huan