local app = require "app"
local scene = require "scene"
local lua_app = require "lua_app"
local obuff = require "obuff"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"


local common = {}




common.career = 
{
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
}

common.missionStatus = 
{
    can_accept = 0,         --玩家可以接受，但没接受,这个跟读表相关，别改
    accepted = 1,           --玩家已经接受了任务,这个跟读表相关，别改
    finished = 2,           --完成了还没提交,这个跟读表相关，别改
    over = 3,               --完成过了,这个跟读表相关，别改
    failed = 10,            --任务失败了，留几个空，免得策划要扩展的时候sx了
    cannot_accept = 11,     --这个任务玩家目前还不能接受
    invalid = 12,           --
}

common.side = 
{
    A = 0,
    B = 1,
}




--根据npc名字获取实体
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

--根据npc名字获取最近实体
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

--根据逻辑物件名字获取最近实体
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
102	比武场
103	精英组优胜场
104	精英组普通场
105	勇者组优胜场
106	勇者组普通场
107	霸者组优胜场
108	霸者组普通场
109	王者组优胜场
114	王者组普通场
]]
--[[
115	精英赛准备厅
116	精英赛比武场
212	帮派联赛地图
220	首席活动场地
400	帮派联赛地图
434	精锐组赛场
435	神机组赛场
436	天启组赛场
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
4105	光明试炼5星
4110	黑暗试炼5星

5021	十二生肖-子鼠·5★
5022	十二生肖-丑牛·5★
5023	十二生肖-寅虎·5★
5024	十二生肖-卯兔·5★
5025	十二生肖-辰龙·5★
5026	十二生肖-已蛇·5★
5027	十二生肖-午马·5★
5028	十二生肖-未羊·5★
5029	十二生肖-申猴·5★
5030	十二生肖-酉鸡·5★
5031	十二生肖-戌狗·5★
5032	十二生肖-亥猪·5★

5511	九曜星官-金乌·5★
5512	九曜星官-天后·5★
5513	九曜星官-太岁·5★
5514	九曜星官-荧惑·5★
5515	九曜星官-镇星·5★
5516	九曜星官-长庚·5★
5517	九曜星官-辰星·5★
5518	九曜星官-罗候·5★
5519	九曜星官-计都·5★

8200	决战蚩尤
8201	决战蚩尤
8202	决战蚩尤
8203	决战蚩尤
8204	决战蚩尤
8210	决战蚩尤
8211	决战蚩尤
8212	决战蚩尤
8213	决战蚩尤
8214	决战蚩尤
8215	决战蚩尤

102031	竞武PK
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
	if lua_app.task_type ~= "一条龙" then
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
    --找对面的怪
    local lines = {}
	if side == "A" then
		lines = {0, 1}--B
	else
		lines = {2, 3}--A
	end
    --1339	95-105级10怪3头领+统领或富裕（蟠桃三）
    for _, line in ipairs(lines) do
		for row = 0, 5 do
			local entityId = ClientControl.get_battle_entityid_by_pos(line, row)
			local entity = scene.get_entity(entityId)
            local name = entity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
			local name6 = string.sub(name, 1, 6)
            if name6 == "富裕的" then
                lua_app.print(11, "使用 招财进宝")
                ClientControl.use_skill(1612, entityId)	--1612	招财进宝
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