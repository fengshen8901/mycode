local app = require "app"
local scene = require "scene"
local lua_app = require "lua_app"
local obuff = require "obuff"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"


local common = {}




common.career = 
{
    Keeper = 1,         --������
    Killer	= 2,        --��߸�
	Shooter = 3,        --ˮ����
	Barbarian = 4,      --��Ӱ��
	New = 5,            --��̨ɽ
	Paladin = 6,        --������
	Priest = 7,         --������
	Hunter = 8,         --���ƶ�
	Monk = 9,           --��ڤ��
	KunLun = 10,        --��ĳ�
}

common.missionStatus = 
{
    can_accept = 0,         --��ҿ��Խ��ܣ���û����,�����������أ����
    accepted = 1,           --����Ѿ�����������,�����������أ����
    finished = 2,           --����˻�û�ύ,�����������أ����
    over = 3,               --��ɹ���,�����������أ����
    failed = 10,            --����ʧ���ˣ��������գ���ò߻�Ҫ��չ��ʱ��sx��
    cannot_accept = 11,     --����������Ŀǰ�����ܽ���
    invalid = 12,           --
}

common.side = 
{
    A = 0,
    B = 1,
}




--����npc���ֻ�ȡʵ��
common.getNpcEntiyIdByName = function (npcName)
    local entitys = scene.get_all_monster()
	for _, entityId in pairs(entitys) do
		local entity = scene.get_entity(entityId)
		local name = entity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
		if name == npcName then
            return entityId
        end
	end
    return nil
end

--����npc���ֻ�ȡ���ʵ��
common.getNearNpcEntiyIdByName = function (npcName)
    local mainEntityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(mainEntityId)
	local playerx = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
    local playery = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)

    local minDistance
    local minEntityId
    local entitys = scene.get_all_monster()
	for _, entityId in pairs(entitys) do
		local entity = scene.get_entity(entityId)
		local name = entity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
		if name == npcName then
            local x = entity:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
            local y = entity:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
            local distance = math.abs(playerx - x) + math.abs(playery - y)
            if not minDistance or distance < minDistance then
                minDistance = distance
                minEntityId = entityId
            end
        end
	end
    return minEntityId
end

--�����߼�������ֻ�ȡ���ʵ��
common.getNearLogicObjByName = function (logicName)
    local mainEntityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(mainEntityId)
	local playerx = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
    local playery = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)

    local minDistance
    local minEntityId
    local entitys = scene.get_all_entitys()
	for _, entityId in pairs(entitys) do
		local entity = scene.get_entity(entityId)
		local name = entity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
        local entityType = entity:get_prop_int(PropConfig.PROP_ENTITY_TYPE)
		if entityType == 4 and name == logicName then
            local x = entity:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
            local y = entity:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
            local distance = math.abs(playerx - x) + math.abs(playery - y)
            if not minDistance or distance < minDistance then
                minDistance = distance
                minEntityId = entityId
            end
        end
	end
    return minEntityId
end

common.getNearNoBlockPos = function (x, y, range)
    local retx = x
    local rety = y
    local isFirst = true
    for xx = x-range, x+range do
        for yy = y-range, y+range do
            if false == scene.is_block(xx, yy) then
                local distance1 = (retx - x) * (retx - x) + (rety - y) * (rety - y)
                local distance2 = (xx - x) * (xx - x) + (yy - y) * (yy - y)
                --lua_app.print(7, "distance1 distance2 ", xx, yy, x, y, distance1, distance2)
                if isFirst or (distance2 < distance1 and xx ~= 94 and yy ~= 55) then
                    isFirst = false
                    lua_app.print(7, "retx rety ", retx, rety)
                    retx = xx
                    rety = yy
                end
            end
        end
    end
    return retx, rety
end

common.canAutoAcceptInvite = function (inviterName)
    if lua_app.team_invites then
        if lua_app.team_invites[inviterName] then
            return true
        else
            return false
        end
    else
        return false
    end
    return false
end






local PIPE_ENTITY = 2
local PIPE_PETTRADECENTER = 33

local MSG_CL_ENTITY_SHOP_SYSTEM = 65
local MSG_CL_ENTITY_WAR_SYSTEM = 186

local MSG_CL_ENTITY_SHOP_SYSTEM_BUY_MSG = 8
local MSG_CL_PETTRADECENTER_BUY = 0
local MSG_CL_ENTITY_JINBI_CENTER_SYSTEM = 132
local MSG_CL_BUY_ITEM = 3

local MSG_CL_ENTITY_MISSION_SYSTEM = 47
local MSG_CL_MISSION_ITEM_USE_SUCCESS = 42

local MSG_CL_ENTITY_TEAMSYSTEM = 9
local MSG_CL_TEAM_RESPOND_INVITE = 3

local PIPE_LOGICITEM = 8
local MSG_CL_ENTITY_LOGICOBJ_SYSTEM = 44
local MSG_CL_ENTITY_LOGIICOBJ_SYSTEM_OPERATE = 6
local MSG_CL_HOUSE_SYSTEM = 188
local MSG_CL_HOUSE_GOTO_MY_HOUSE = 23

--warsystem
local enWarType_ActorSale = 2
local enWarType_PetCamp = 51
local enSaleEntityMsg_buy_item_request = 32
local enWarType_PetCamp_LingQuMission_CL = 306






common.InBattle = function ()
    local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
	local battleSceneID = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_BATTLESCENEID)
    if battleSceneID > 0 then
        return true
    end
    return false
end

common.IsPvP = function ()
    local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
	local mapId = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_MAPID)
    local maps = {}
--[[
102	���䳡
103	��Ӣ����ʤ��
104	��Ӣ����ͨ��
105	��������ʤ��
106	��������ͨ��
107	��������ʤ��
108	��������ͨ��
109	��������ʤ��
114	��������ͨ��
]]
--[[
115	��Ӣ��׼����
116	��Ӣ�����䳡
212	����������ͼ
220	��ϯ�����
400	����������ͼ
434	����������
435	���������
436	����������
]]

    table.insert(maps, {102, 114})
    table.insert(maps, {115, 116})
    table.insert(maps, {212, 212})
    table.insert(maps, {220, 220})
    table.insert(maps, {400, 400})
    table.insert(maps, {434, 436})
    for _, v in ipairs(maps) do
        if mapId >= v[1] and mapId <= v[2] then
            return true
        end
    end
    return false
end

common.IsPvE = function ()
    local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
    local battleCfgId = ClientControl.get_battle_cfgid()

--[[
4105	��������5��
4110	�ڰ�����5��

5021	ʮ����Ф-����5��
5022	ʮ����Ф-��ţ��5��
5023	ʮ����Ф-������5��
5024	ʮ����Ф-î�á�5��
5025	ʮ����Ф-������5��
5026	ʮ����Ф-���ߡ�5��
5027	ʮ����Ф-����5��
5028	ʮ����Ф-δ��5��
5029	ʮ����Ф-��5��
5030	ʮ����Ф-�ϼ���5��
5031	ʮ����Ф-�繷��5��
5032	ʮ����Ф-����5��

5511	�����ǹ�-���ڡ�5��
5512	�����ǹ�-���5��
5513	�����ǹ�-̫�ꡤ5��
5514	�����ǹ�-ӫ��5��
5515	�����ǹ�-���ǡ�5��
5516	�����ǹ�-������5��
5517	�����ǹ�-���ǡ�5��
5518	�����ǹ�-�޺�5��
5519	�����ǹ�-�ƶ���5��

8200	��ս���
8201	��ս���
8202	��ս���
8203	��ս���
8204	��ս���
8210	��ս���
8211	��ս���
8212	��ս���
8213	��ս���
8214	��ս���
8215	��ս���

102031	����PK
]]

    lua_app.print(11, "battleCfgId = ", battleCfgId)
    local battleScenes = {}
    table.insert(battleScenes, {4101, 4110})
    table.insert(battleScenes, {5021, 5032})
    table.insert(battleScenes, {5511, 5519})
    table.insert(battleScenes, {8200, 8215})
    table.insert(battleScenes, {102031, 102031})
    for _, v in ipairs(battleScenes) do
        if battleCfgId >= v[1] and battleCfgId <= v[2] then
            return true
        end
    end
    return false
end

common.IsChiYou = function ()
    local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
    local battleCfgId = ClientControl.get_battle_cfgid()
    if battleCfgId >= 8200 and battleCfgId <= 8215 then
        return true
    end
    return false
end

common.IsUseBattleAI = function ()
    if lua_app.auto_battle then
        return true
    end
    return false
    --[[
	if lua_app.task_type ~= "һ����" then
		return false
	end
	return true
    ]]
end

common.GetBattleEntityIdByName = function (targetName)
    local entityIds = ClientControl.get_battle_all_entityid()
    for _, entityId in pairs(entityIds) do
		local entity = scene.get_entity(entityId)
		local name = entity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
		if name == targetName then
			return entityId
		end
	end
    return 0
end

common.GetBattleEntityIdByCommand = function (targetCommand)
    local entityIds = ClientControl.get_battle_all_entityid()
    for _, entityId in pairs(entityIds) do
		local entity = scene.get_entity(entityId)
        local command = entity:get_battle_command_str()
		if command == targetCommand then
			return entityId
		end
	end
    return 0
end

common.GetSelfSide = function ()
	local mainEntityId = scene.get_main_player_entityid()
	for line = 0, 3 do
		for row = 0, 5 do
			local entityId = ClientControl.get_battle_entityid_by_pos(line, row)
			if mainEntityId == entityId then
				if line <= 1 then
					return "B"
				else
					return "A"
				end
			end
		end
	end
end

common.GetSelfSideLostHpCount = function (lost)
	local side = common.GetSelfSide()
	if not side then
		return 0
	end
	local lines = {}
	if side == "A" then
		lines = {2, 3}--A
	else
		lines = {0, 1}--B
	end
	local count = 0
	for _, line in ipairs(lines) do
		for row = 0, 5 do
			local entityId = ClientControl.get_battle_entityid_by_pos(line, row)
			local entity = scene.get_entity(entityId)
			local hp = entity:get_prop_int(PropConfig.PROP_ENTITY_HP)
			local hpmax = entity:get_prop_int(PropConfig.PROP_ENTITY_HP_MAX)
			if hp > 0 and hpmax - hp >= lost then
				count = count + 1
			end
		end
	end
	return count
end

common.doZhaoCaiJinBao = function ()
    local side = common.GetSelfSide()
	if not side then
		return false
	end
    --�Ҷ���Ĺ�
    local lines = {}
	if side == "A" then
		lines = {0, 1}--B
	else
		lines = {2, 3}--A
	end
    --1339	95-105��10��3ͷ��+ͳ���ԣ���������
    for _, line in ipairs(lines) do
		for row = 0, 5 do
			local entityId = ClientControl.get_battle_entityid_by_pos(line, row)
			local entity = scene.get_entity(entityId)
            local name = entity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
			local name6 = string.sub(name, 1, 6)
            if name6 == "��ԣ��" then
                lua_app.print(11, "ʹ�� �вƽ���")
                ClientControl.use_skill(1612, entityId)	--1612	�вƽ���
                return true
            end
		end
	end
    return false
end




--socket
common.buyNpcShopItem = function (st)
    obuff.clear()
    --MsgHead
    obuff.write_uint8(PIPE_ENTITY)
    obuff.write_uint8(MSG_CL_ENTITY_SHOP_SYSTEM)
    --subMsgId
    obuff.write_uint8(MSG_CL_ENTITY_SHOP_SYSTEM_BUY_MSG)

    obuff.write_int32(st.shopItemId)
    obuff.write_int32(st.shopId)
    obuff.write_int32(st.buyCount)
    obuff.write_int8(st.useMoneyType)

    obuff.send_to_server()
end

common.buyShopPet = function (firstCatchId)
    obuff.clear()
    --MsgHead
    obuff.write_uint8(PIPE_PETTRADECENTER)
    obuff.write_uint8(MSG_CL_PETTRADECENTER_BUY)

    local moneyType = 1
    local shopType = 0
    obuff.write_int32(firstCatchId)
    obuff.write_uint8(moneyType)
    obuff.write_uint8(shopType)

    obuff.send_to_server()
end

common.buySaleCenterItem = function (itemGuid)
    obuff.clear()
    --MsgHead
    obuff.write_uint8(PIPE_ENTITY)
    obuff.write_uint8(MSG_CL_ENTITY_WAR_SYSTEM)
    --WarHead
    obuff.write_int16(enWarType_ActorSale)
    obuff.write_int32(enSaleEntityMsg_buy_item_request)
    --data
    obuff.write_int64(itemGuid)

    obuff.send_to_server()
end

common.buyShangHuiItem = function (itemId, num)
    if num <= 0 then
        num = 1
    end
    obuff.clear()
    --MsgHead
    obuff.write_uint8(PIPE_ENTITY)
    obuff.write_uint8(MSG_CL_ENTITY_JINBI_CENTER_SYSTEM)
    --subMsgId
    obuff.write_uint8(MSG_CL_BUY_ITEM)
    --data
    obuff.write_int32(itemId)
    obuff.write_int32(num)

    obuff.send_to_server()
end

common.missionItemUse = function (missionId, itemId)
    obuff.clear()
    --MsgHead
    obuff.write_uint8(PIPE_ENTITY)
    obuff.write_uint8(MSG_CL_ENTITY_MISSION_SYSTEM)
    --ST_MSG_Mission
    obuff.write_int16(MSG_CL_MISSION_ITEM_USE_SUCCESS)
    obuff.write_int32(missionId)
    obuff.write_int32(0)

    --ST_MSG_CL_MISSION_ITEM_USE_SUCCESS
    obuff.write_int32(itemId)

    obuff.send_to_server()
end

common.teamRespondInvite = function (intvitTeamId, inviterName)
    obuff.clear()
    --MsgHead
    obuff.write_uint8(PIPE_ENTITY)
    obuff.write_uint8(MSG_CL_ENTITY_TEAMSYSTEM)
    --ST_MSG_CL_TEAM_RESPOND_INVITE
    obuff.write_uint8(MSG_CL_TEAM_RESPOND_INVITE)
    obuff.write_int32(intvitTeamId)
    obuff.write_bool(true)

    obuff.send_to_server()
end

common.lingQuZyTaskByIndex = function (index)
    obuff.clear()
    --MsgHead
    obuff.write_uint8(PIPE_ENTITY)
    obuff.write_uint8(MSG_CL_ENTITY_WAR_SYSTEM)
    --WarHead
    obuff.write_int16(enWarType_PetCamp)
    obuff.write_int32(enWarType_PetCamp_LingQuMission_CL)
    --data
    obuff.write_int32(index)
    obuff.write_int16(1)
    obuff.write_int16(0)

    obuff.send_to_server()
end

common.operate_logic = function (logicEntityId)
    obuff.clear()
    --MsgHead
    obuff.write_uint8(PIPE_LOGICITEM)
    obuff.write_uint8(MSG_CL_ENTITY_LOGICOBJ_SYSTEM)
    --subMsgid
    obuff.write_uint8(MSG_CL_ENTITY_LOGIICOBJ_SYSTEM_OPERATE)
    obuff.write_int32(logicEntityId)
    local mainEntityId = scene.get_main_player_entityid()
    obuff.write_int32(mainEntityId)
    obuff.send_to_server()
end

common.goto_self_house = function ()
    obuff.clear()
    --MsgHead
    obuff.write_uint8(PIPE_ENTITY)
    obuff.write_uint8(MSG_CL_HOUSE_SYSTEM)
    --subMsgid
    obuff.write_uint8(MSG_CL_HOUSE_GOTO_MY_HOUSE)
    obuff.send_to_server()
end


return common