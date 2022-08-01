local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"



local pao_shang_step = "��֪��"
local pao_shang = oo.class()

function pao_shang:ctor()
end
--�ж��Ƿ������
function pao_shang:is_finish()
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
        lua_app.print(11, "���������")
        return true
    end
    return true
end

function pao_shang:getTaskInfo()
    local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
    local career = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CAREER)
    self.taskId = 5440
    local info = ClientControl.get_task_info(self.taskId)
    return info
end

function pao_shang:destroy()
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
    eventMgr.unsubEvent(eventMgr.event.mission_guid_open, self, "onMissionGuidOpen")
    ]]
    eventMgr.unsubAllEvent(self)

    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
end

function pao_shang:start()
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
    eventMgr.subEvent(eventMgr.event.mission_guid_open, self, "onMissionGuidOpen")

end

function pao_shang:onTimer()
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
	lua_app.print(7, "pao_shang:onTimer 1 ")

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

function pao_shang:logic()
    if common.InBattle() then
        lua_app.print(7, "pao_shang:logic InBattle ")
        return
    end
    if ClientControl.is_moving() then
        lua_app.print(7, "pao_shang:logic is_moving ")
        return
    end
    local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
    local career = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CAREER)
    local info = self:getTaskInfo()
    table.print(info, 10)
    if info.status == common.missionStatus.can_accept then
        lua_app.print(7, "ȥ���������� ")
        ClientControl.move_patch(101, 63, 37)
		eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEndLingQu")
        pao_shang_step = "ȥ����������"
        return
    end
    if info.status == common.missionStatus.accepted then
        eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEndTalkShangRen")
        eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
        self.delay = 3
        if pao_shang_step == "��֪��" then
            pao_shang_step = "ȥ����������"
        end
        lua_app.print(7, pao_shang_step)
        if pao_shang_step == "ȥ����������" then
            lua_app.print(7, "12, 149, 87")
            ClientControl.move_patch(12, 149, 87)
        elseif pao_shang_step == "ȥ¥������" then
            lua_app.print(7, "14, 93, 79")
            ClientControl.move_patch(14, 93, 79)
        end
        lua_app.print(7, "----------------info.eTargetType ---------------- ", info.eTargetType)
        return
    end
    if info.status == common.missionStatus.finished then
        lua_app.print(9, "���̻�ȥ��������")
        local mapId = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_MAPID)
        lua_app.print(9, "mapId ", mapId)
        if mapId ~= 101 then
            pao_shang_step = "ȥ���ɽ�����"
            ClientControl.move_patch(12, 135, 88)
            eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEndGuildEnter")
        else
            --����ʦү
            if pao_shang_step ~= "�ذ���ʦү������" then
                pao_shang_step = "�ذ���ʦү������"
                ClientControl.move_patch(101, 63, 37)
		        eventMgr.subEvent(eventMgr.event.patch_end, self, "onPatchEndSumit")
            end
        end
        return
    end
    if info.status == common.missionStatus.over then
        --���������
        lua_app.print(9, "���������")
        pao_shang_step = "��֪��"
    end
end

--������
function pao_shang:onOpenLingQuMutual(TargetEntityID, mutualID, selects, contexts)
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
	lua_app.print(10, "pao_shang:onOpenLingQuMutual ", TargetEntityID, mutualID)
	table.print(selects, 10)
    table.print(contexts, 10)

    for i, str in ipairs(contexts) do
        local s, e = string.find(str, "��������")
        if s then
            ClientControl.mutual_select(TargetEntityID, mutualID, selects[i])
            return
        end
    end
    self.delay = 2
end
--pao_shang_step = "ȥ¥������"
--�����˶Ի�
function pao_shang:onPatchEndTalkShangRen()
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndTalkShangRen")
	lua_app.print(10, "pao_shang:onPatchEndTalkShangRen ")
	local entityId = common.getNearNpcEntiyIdByName("�ز�����")
    if entityId then
        lua_app.print(7, "���ز����� ����", entityId)
        ClientControl.open_mutual(entityId)
        if pao_shang_step == "ȥ����������" then
            pao_shang_step = "ȥ¥������"
        elseif pao_shang_step == "ȥ¥������" then
            pao_shang_step = "ȥ����������"
        end
        self.delay = 5
    else
        lua_app.print(12, "�Ҳ��� �ز����� ")
        self.delay = 3
    end
end


function pao_shang:onOpenMutual(TargetEntityID, mutualID, selects, contexts)
    --eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
	lua_app.print(10, "pao_shang:onOpenMutual ", TargetEntityID, mutualID)
	table.print(selects, 10)
    table.print(contexts, 10)
	--ѡ�񽻻���һ��ѡ��
	if selects[1] then
		ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
	end
    self.isPatching = nil
    self.delay = 2
end

function pao_shang:onOpenEnterMutual(TargetEntityID, mutualID, selects, contexts)
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenEnterMutual")
	lua_app.print(10, "pao_shang:onOpenEnterMutual ", TargetEntityID, mutualID)
	table.print(selects, 10)
    table.print(contexts, 10)
    local hasSelect = false
    for i, str in ipairs(contexts) do
        if str == "�������" then
            ClientControl.mutual_select(TargetEntityID, mutualID, selects[i])
            hasSelect = true
            break
        end
    end
    if not hasSelect and selects[1] then
        ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
    end
    self.isPatching = nil
    self.delay = 2
end

function pao_shang:onOpenSumitMutual(TargetEntityID, mutualID, selects, contexts)
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenSumitMutual")
	lua_app.print(10, "pao_shang:onOpenSumitMutual ", TargetEntityID, mutualID)
	table.print(selects, 10)
    table.print(contexts, 10)
    local hasSelect = false
    for i, str in ipairs(contexts) do
        if str == "�Ͻ���Ʊ" then
            ClientControl.mutual_select(TargetEntityID, mutualID, selects[i])
            hasSelect = true
            break
        end
    end
    if not hasSelect and selects[1] then
        ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
    end
    self.isPatching = nil
    self.delay = 2
end


function pao_shang:onPatchEndLingQu()
	eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndLingQu")
	self.isPatching = nil
	lua_app.print(7, "pao_shang:onPatchEndLingQu ")
    local entityId = common.getNpcEntiyIdByName("����ʦү")
    if entityId then
        lua_app.print(7, "pao_shang:logic ��� ����ʦү ")
        ClientControl.open_mutual(entityId)
        eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
    else
        lua_app.print(7, "pao_shang:logic �Ҳ��� ����ʦү ")
    end
end

function pao_shang:onPatchEndGuildEnter()
	eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndGuildEnter")
    lua_app.print(7, "pao_shang:onPatchEndGuildEnter ")
    local entityId = common.getNpcEntiyIdByName("���ɽ�����")
    if entityId then
        lua_app.print(7, "pao_shang:logic ��� ���ɽ����� ")
        eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenEnterMutual")
        ClientControl.open_mutual(entityId)
        self.delay = 3
    else
        lua_app.print(7, "pao_shang:logic �Ҳ��� ���ɽ����� ")
    end
end

function pao_shang:onPatchEndSumit()
	eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndSumit")
    lua_app.print(7, "pao_shang:onPatchEndSumit ")
    local entityId = common.getNpcEntiyIdByName("����ʦү")
    if entityId then
        lua_app.print(7, "pao_shang:logic ��� ����ʦү ")
        eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenSumitMutual")
        ClientControl.open_mutual(entityId)
        self.delay = 3
    else
        lua_app.print(7, "pao_shang:logic �Ҳ��� ����ʦү ")
    end
end

function pao_shang:onPatchEndTrace()
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
	self.isPatching = nil
    lua_app.print(7, "pao_shang:onPatchEndTrace ")
    self.delay = 2
end

function pao_shang:onNpcShopOpen(st)
    lua_app.print(7, "pao_shang:onNpcShopOpen ")
    table.print(st, 10)

    common.buyNpcShopItem(st)
    self.delay = 2
    self.isPatching = nil
end

function pao_shang:onGiveUiOpen()
    lua_app.print(7, "pao_shang:onGiveUiOpen ")
    ClientControl.on_ok_give_ui()
    self.delay = 2
    self.isPatching = nil
end

function pao_shang:onPetTradeCenterOpen(firstCatchId)
    lua_app.print(7, "pao_shang:onPetTradeCenterOpen ", firstCatchId)
    common.buyShopPet(firstCatchId)
    self.delay = 2
    self.isPatching = nil
end

function pao_shang:onPetListSelectOpen(firstCatchId)
    lua_app.print(7, "pao_shang:onPetListSelectOpen ", firstCatchId)
    ClientControl.pet_list_select(firstCatchId)
    self.delay = 2
    self.isPatching = nil
end

function pao_shang:onBattleSceneIdChange(prop, old, new)
    lua_app.print(7, "pao_shang:onBattleSceneIdChange ", prop, old, new)
    self.delay = 2
    self.isPatching = nil
end

function pao_shang:onSaleCenterOpen(isTaskOpen, guids)
    lua_app.print(7, "pao_shang:onSaleCenterOpen ", isTaskOpen)
    if isTaskOpen and guids[1] and guids[1] > 0 then
        common.buySaleCenterItem(guids[1])
        ClientControl.show_sale_center(false)
    end
    self.delay = 2
    self.isPatching = nil
end

function pao_shang:onShangHuiOpen(itemId, num)
    lua_app.print(7, "pao_shang:onShangHuiOpen ", itemId, num)
    common.buyShangHuiItem(itemId, num)
    self.delay = 2
    self.isPatching = nil
end

function pao_shang:onProgressItemOpen(itemHandel)
    lua_app.print(7, "pao_shang:onProgressItemOpen ", itemHandel)
end

function pao_shang:onMissionGuidOpen(missionId, itemId)
    lua_app.print(7, "pao_shang:onMissionGuidOpen ", missionId, itemId)
    common.missionItemUse(missionId, itemId)
    self.delay = 5
end





return pao_shang