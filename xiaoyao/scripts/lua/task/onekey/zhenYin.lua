local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"



local zhen_yin = oo.class()

function zhen_yin:ctor()
end
--�ж��Ƿ������
function zhen_yin:is_finish()
    local indexs = ClientControl.get_zy_indexs()
    --lua_app.print(7, "zhen_yin:is_finish 1 ")
    --table.print(indexs, 10)
    if #indexs >= 1 then
        return false
    end
    self.taskId = 0
    local lists = {{4100, 4131}, {4135, 4142}, {4150, 4151}}
    for _, list in pairs(lists) do
        for taskId = list[1], list[2] do
            local info = ClientControl.get_task_info(taskId)
            --�ѽ�����
            if info.status == common.missionStatus.accepted then
                self.taskId = taskId
                return false
            end
            --�ɽ�����״̬
            if info.status == common.missionStatus.finished then
                self.taskId = taskId
                return false
            end
        end
    end
    if self.taskId > 0 then
        --lua_app.print(7, "zhen_yin:is_finish self.taskId ", self.taskId)
        return false
    end
    --lua_app.print(11, "��Ӫ��������� ")
    return true
end

function zhen_yin:getTaskInfo()
    self.taskId = 0
    local lists = {{4100, 4131}, {4135, 4142}, {4150, 4151}}
    for _, list in pairs(lists) do
        for taskId = list[1], list[2] do
            local info = ClientControl.get_task_info(taskId)
            --�ѽ�����
            if info.status == common.missionStatus.accepted then
                self.taskId = taskId
                return info
            end
            --�ɽ�����״̬
            if info.status == common.missionStatus.finished then
                self.taskId = taskId
                return info
            end
        end
    end
    return {}
end

function zhen_yin:destroy()
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

function zhen_yin:start()
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
    eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
    eventMgr.subEvent(eventMgr.event.mission_guid_open, self, "onMissionGuidOpen")

end

function zhen_yin:onTimer()
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
	--lua_app.print(7, "zhen_yin:onTimer 1 ")

    if self.isGather then
		--lua_app.print(7, "zhen_yin:onTimer isGather ")
        local info = self:getTaskInfo()
        --table.print(info, 10)
        if info.misstype == 6 or info.eTargetType == 48 or info.eTargetType == 55 or info.eTargetType == 56 then
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

function zhen_yin:logic()
    if common.InBattle() then
        --lua_app.print(7, "zhen_yin:logic InBattle ")
        return
    end
    if ClientControl.is_moving() then
        --lua_app.print(7, "zhen_yin:logic is_moving ")
        return
    end
    local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
    local career = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CAREER)
    local info = self:getTaskInfo()
    --table.print(info, 10)
    if not info.status then
        local indexs = ClientControl.get_zy_indexs()
        local taskIndex = indexs[1]
        if not taskIndex then
            --lua_app.print(11, "��Ӫ��������� ")
            return
        end
        --lua_app.print(7, "����Ӫ���� ", taskIndex)
        common.lingQuZyTaskByIndex(taskIndex)
        self.delay = 3
        return
    end
    if info.status == common.missionStatus.accepted 
    or info.status == common.missionStatus.finished then
        --lua_app.print(11, "׷������ ")
        if info.eTargetType == 0 then
            if info.misstype == 1 then
                --MissionTarget_Dialog ��npc�Ի�
                ClientControl.auto_trace_mission(self.taskId)
            elseif info.misstype == 6 then
                --MissionTarget_LogicItem �����߼����
                ClientControl.auto_trace_mission(self.taskId)
                self.isGather = true
            else
                local target = ClientControl.get_mission_target_info(self.taskId)
                --table.print(target, 10)
                ClientControl.auto_trace_npc(target.mapId, target.x, target.y, target.npcId, target.missionId)
            end
        else
            ClientControl.auto_trace_mission(self.taskId)
            --48 �ɼ� 55 �ռ� 56 ����
            if info.eTargetType == 48 or info.eTargetType == 55 or info.eTargetType == 56 then
                self.isGather = true
            end
        end
        return
        --[[
        --׷����������Ϸ�ڵ������׷��һ����
        ClientControl.auto_trace_npc(11, 77, 79, 1201, 4103)
        --ClientControl.auto_trace_mission(self.taskId)
        eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
        eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
        --48 �ɼ� 55 �ռ� 56 ����
        if info.eTargetType == 48 or info.eTargetType == 55 or info.eTargetType == 56 then
            self.isGather = true
        end
        return
        ]]
    end
end

--������
function zhen_yin:onOpenLingQuMutual(TargetEntityID, mutualID, selects, contexts)
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
	--lua_app.print(10, "zhen_yin:onOpenLingQuMutual ", TargetEntityID, mutualID)
	--table.print(selects, 10)
    --table.print(contexts, 10)
	local hasSelect = false
	--ѡ�񽻻���һ��ѡ��
	for i, str in ipairs(contexts) do
        local s, e = string.find(str, "��Ӫ")
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

function zhen_yin:onOpenMutual(TargetEntityID, mutualID, selects, contexts)
    --��Ӫ��Щ������Ҫ�����£�����Ͳ���ע����
    --eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
	lua_app.print(10, "zhen_yin:onOpenMutual ", TargetEntityID, mutualID)
	table.print(selects, 10)
    table.print(contexts, 10)
	local hasSelect = false
	--ѡ�񽻻���һ��ѡ��
	for i, str in ipairs(contexts) do
        local s, e = string.find(str, "��Ӫ�ճ�")
        if s then
            ClientControl.mutual_select(TargetEntityID, mutualID, selects[i])
			lua_app.print(10, "zhen_yin:onOpenMutual select ", i)
            hasSelect = true
            break
        end
    end
	if not hasSelect and selects[1] then
		ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
		lua_app.print(10, "zhen_yin:onOpenMutual select ", 1)
	end
    self.isPatching = nil
	self.delay = 3
end

function zhen_yin:onPatchEndLingQu()
	eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndLingQu")
	self.isPatching = nil
	lua_app.print(7, "zhen_yin:onPatchEndLingQu ")
    local entityId = common.getNpcEntiyIdByName(self.careerNpc)
    if entityId then
        lua_app.print(7, "zhen_yin:logic ��� ", self.careerNpc)
        ClientControl.open_mutual(entityId)
        eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
    else
        lua_app.print(7, "zhen_yin:logic �Ҳ��� ", self.careerNpc)
    end
	self.delay = 3
end

function zhen_yin:onPatchEndTrace()
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
	self.isPatching = nil
    lua_app.print(7, "zhen_yin:onPatchEndTrace ")

end

function zhen_yin:onNpcShopOpen(st)
    lua_app.print(7, "zhen_yin:onNpcShopOpen ")
    table.print(st, 10)

    common.buyNpcShopItem(st)
    self.isPatching = nil
end

function zhen_yin:onGiveUiOpen()
    lua_app.print(7, "zhen_yin:onGiveUiOpen ")
    ClientControl.on_ok_give_ui()
    self.delay = 2
    self.isPatching = nil
end

function zhen_yin:onPetTradeCenterOpen(firstCatchId)
    lua_app.print(7, "zhen_yin:onPetTradeCenterOpen ", firstCatchId)
    common.buyShopPet(firstCatchId)
    self.delay = 2
    self.isPatching = nil
end

function zhen_yin:onPetListSelectOpen(firstCatchId)
    lua_app.print(7, "zhen_yin:onPetListSelectOpen ", firstCatchId)
    ClientControl.pet_list_select(firstCatchId)
    self.delay = 2
    self.isPatching = nil
end

function zhen_yin:onBattleSceneIdChange(prop, old, new)
    lua_app.print(7, "zhen_yin:onBattleSceneIdChange ", prop, old, new)
    self.delay = 2
    self.isPatching = nil
end

function zhen_yin:onSaleCenterOpen(isTaskOpen, guids)
    lua_app.print(7, "zhen_yin:onSaleCenterOpen ", isTaskOpen)
    if isTaskOpen and guids[1] and guids[1] > 0 then
        common.buySaleCenterItem(guids[1])
        ClientControl.show_sale_center(false)
    end
    self.delay = 2
    self.isPatching = nil
end

function zhen_yin:onShangHuiOpen(itemId, num)
    lua_app.print(7, "zhen_yin:onShangHuiOpen ", itemId, num)
    common.buyShangHuiItem(itemId, num)
    self.delay = 2
    self.isPatching = nil
end

function zhen_yin:onMissionGuidOpen(missionId, itemId)
    lua_app.print(7, "zhen_yin:onMissionGuidOpen ", missionId, itemId)
    common.missionItemUse(missionId, itemId)
    self.delay = 6
end




return zhen_yin