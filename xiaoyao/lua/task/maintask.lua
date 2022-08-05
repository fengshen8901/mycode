local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"
local itemBag = require "itemBag"

--1000-1025  1100-1223  1300-1321  1400-1428   1500-1529

local mainTask = oo.class()

local taskIdList = 
{
    {1000, 1025},
    {1100, 1223},
    {1300, 1321},
    {1400, 1428},
    {1500, 1529},
}
-- function mainTask:ctor()
--     self.taskId = 5026
-- end

function mainTask:destroy()
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

function mainTask:start()
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

    --itemBag.tidy_bag()
    eventMgr.subEvent(eventMgr.event.progress_item_open, self, "onProgressItemOpen")
    eventMgr.subEvent(eventMgr.event.mission_guid_open, self, "onMissionGuidOpen")
end

function mainTask:onTimer()
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
	lua_app.print(7, "mainTask:onTimer 1 ")

	if self.isPatching then
		lua_app.print(7, "mainTask:onTimer isPatching ")
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

function mainTask:logic()
    if common.InBattle() then
        lua_app.print(7, "mainTask:logic InBattle ")
        return
    end
    if ClientControl.is_moving() then
        lua_app.print(7, "mainTask:logic is_moving ")
        return
    end

    for i,v in pairs(taskIdList) do
        for tId = v[1], v[2] do
            local info = ClientControl.get_task_info(tId)
            if info.status == common.missionStatus.accepted 
            or info.status == common.missionStatus.finished then
                --追踪任务，与游戏内点击任务追踪一样的                
                eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
                eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
                self.isPatching = true
                ClientControl.auto_trace_mission(tId)
                lua_app.print(7, "mainTask:logic start tId " .. tId)
            end
        end
    end

    --local info = ClientControl.get_task_info(self.taskId)
    --lua_app.print(7, "mainTask:logic start ")
  --   table.print(info, 7)
  --   if info.status == common.missionStatus.can_accept then
  --       lua_app.print(7, "mainTask:logic can_accept ")
  --       --望仙镇
  --       ClientControl.move_patch(13, 34, 52)
		-- eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEnd")
		-- self.isPatching = true
  --       self.isGoToLingQu = true
  --       return
  --   end
  --   if self.isGoToLingQu then
  --       self.isGoToLingQu = false
  --       eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
  --   end
  --   if info.status == common.missionStatus.accepted 
  --   or info.status == common.missionStatus.finished then
  --       --追踪任务，与游戏内点击任务追踪一样的
  --       ClientControl.auto_trace_mission(self.taskId)
  --       eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
  --       eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
		-- self.isPatching = true
  --   end
end

--接任务
function mainTask:onOpenLingQuMutual(TargetEntityID, mutualID, selects, contexts)
    --eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
	lua_app.print(10, "mainTask:onOpenLingQuMutual ", TargetEntityID, mutualID)
	table.print(selects, 10)
    table.print(contexts, 10)
	--选择交互第一个选项
	if selects[1] then
		ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
	end
    self.isPatching = nil
end

function mainTask:onOpenMutual(TargetEntityID, mutualID, selects, contexts)
    --eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
	lua_app.print(10, "mainTask:onOpenMutual ", TargetEntityID, mutualID)
	table.print(selects, 10)
    table.print(contexts, 10)
	--选择交互第一个选项
	if selects[1] then
		ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
	end
    -- local hasSelect = false
    -- for i, str in ipairs(contexts) do
    --     local s, e = string.find(str, "任务链")
    --     if s then
    --         ClientControl.mutual_select(TargetEntityID, mutualID, selects[i])
    --         hasSelect = true
    --         break
    --     end
    -- end
    --if not hasSelect and selects[1] then
    --    ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
    --end
    self.isPatching = nil
end

-- function mainTask:onPatchEnd()
-- 	eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEnd")
-- 	self.isPatching = nil
-- 	lua_app.print(7, "mainTask:onPatchEnd ")
--     local entityId = common.getNpcEntiyIdByName("宁书生")
--     if entityId then
--         lua_app.print(7, "mainTask:logic 点击 宁书生 ")
--         ClientControl.open_mutual(entityId)
--         eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
--     else
--         lua_app.print(7, "mainTask:logic 找不到 宁书生 ")
--     end
-- end

function mainTask:onPatchEndTrace()
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
	self.isPatching = nil
    lua_app.print(7, "mainTask:onPatchEndTrace ")

end

function mainTask:onNpcShopOpen(st)
    lua_app.print(7, "mainTask:onNpcShopOpen ")
    table.print(st, 10)

    common.buyNpcShopItem(st)
    self.isPatching = nil
end

function mainTask:onGiveUiOpen()
    lua_app.print(7, "mainTask:onGiveUiOpen ")
    ClientControl.on_ok_give_ui()
    self.delay = 3
    self.isPatching = nil
end

function mainTask:onPetTradeCenterOpen(firstCatchId)
    lua_app.print(7, "mainTask:onPetTradeCenterOpen ", firstCatchId)
    common.buyShopPet(firstCatchId)
    self.delay = 5
    self.isPatching = nil
end

function mainTask:onPetListSelectOpen(firstCatchId)
    lua_app.print(7, "mainTask:onPetListSelectOpen ", firstCatchId)
    ClientControl.pet_list_select(firstCatchId)
    self.delay = 3
    self.isPatching = nil
end

function mainTask:onBattleSceneIdChange(prop, old, new)
    lua_app.print(7, "mainTask:onBattleSceneIdChange ", prop, old, new)
    self.delay = 3
    self.isPatching = nil
end

function mainTask:onSaleCenterOpen(isTaskOpen, guids)
    lua_app.print(7, "mainTask:onSaleCenterOpen ", isTaskOpen)
    if isTaskOpen and guids[1] and guids[1] > 0 then
        common.buySaleCenterItem(guids[1])
        ClientControl.show_sale_center(false)
    end
    self.delay = 3
    self.isPatching = nil
end

function mainTask:onShangHuiOpen(itemId, num)
    lua_app.print(7, "mainTask:onShangHuiOpen ", itemId, num)
    common.buyShangHuiItem(itemId, num)
    self.delay = 3
    self.isPatching = nil
end


function mainTask:onProgressItemOpen(itemHandel)
    lua_app.print(7, "mainTask:onProgressItemOpen ")
    itemBag.click_progress_use()
    self.delay = 2
end


function guild_task:onMissionGuidOpen(missionId, itemId)
    lua_app.print(7, "mainTask:onMissionGuidOpen ", missionId, itemId)
    common.missionItemUse(missionId, itemId)
    self.delay = 2
end

return mainTask