local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"





local movePoss = {
    {15, 69, 102},
    {15, 84, 75},
    {15, 54, 35},
    {15, 31, 63},
    {17, 50, 40},
    {17, 85, 56},
    {17, 93, 92},
    {17, 54, 93},
    {17, 20, 60},
    {17, 59, 62},
    {16, 55, 85},
    {16, 81, 75},
    {16, 71, 44},
    {16, 40, 37},
    {16, 25, 60},
    {18, 86, 36},
    {18, 119, 65},
    {18, 119, 94},
    {18, 84, 128},
    {18, 45, 100},
    {18, 63, 62},
    {19, 67, 112},
    {19, 35, 81},
    {19, 55, 53},
    {19, 91, 64},
    {19, 104, 91},
    {20, 72, 53},
    {20, 35, 59},
    {20, 41, 29},
}

local kuang_objs = 
{
    ["ͭ��"] = 1,
    ["��ԣ��ͭ��"] = 1,
    ["����"] = 1,
    ["��ԣ������"] = 1,
}

local yao_objs = 
{
    ["������"] = 1,
    ["������"] = 1,
    ["Ѫ��֥"] = 1,
    ["������"] = 1,
    ["���β�"] = 1,
}

local fish_objs = 
{
    --["С��Ⱥ"] = 1,
    --["����Ⱥ"] = 1,
    ["����Ⱥ"] = 1,
    ["����Ⱥ"] = 1,
    ["����Ⱥ"] = 1,
}

-- local kuang_objs = 
-- {
--     -- ["ͭ��"] = 1,
--     -- ["��ԣ��ͭ��"] = 1,
--     -- ["����"] = 1,
--     --["��ԣ������"] = 1,

--     ["����"] = 1,
--     ["��ԣ������"] = 1,
--     ["���"] = 1,
--     ["��ԣ�Ľ��"] = 1, --2000
--     ["���صĽ��"] = 1,
-- }

-- local yao_objs = 
-- {
--     ["������"] = 1,
--     -- ["������"] = 1,
--     -- ["Ѫ��֥"] = 1,
--     -- ["������"] = 1,
--     -- ["���β�"] = 1,

--    ["��ڤ��"] = 1,
--    ["ѩ����"] = 1,
--    ["�����"] = 1,
--    ["ǧ����"] = 1,
--    ["���黨"] = 1,
    
--     ["����"] = 1,
--     ["����"] = 1,
--     ["���"] = 1,
--     ["��β"] = 1,
--     ["����"] = 1,
-- }

-- local fish_objs = 
-- {
--     -- ["С��Ⱥ"] = 1,
--     -- ["����Ⱥ"] = 1,
--     -- ["����Ⱥ"] = 1,

--     ["����Ⱥ"] = 1,
--     ["����Ⱥ"] = 1,
--     ["������Ⱥ"] = 1,
--     ["������Ⱥ"] = 1,
--     ["���ص���Ⱥ"] = 1,
-- }


local cai_ji = oo.class()

function cai_ji:ctor()
end
--�ж��Ƿ������
function cai_ji:is_finish()
    local mainEntityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(mainEntityId)
    local caiKuangCount = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CAIKUANG_COUNT)
    local fishCount = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_FISHING_COUNT)
    local caiYaoCount = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CONNECT_CAOYAO_COUNT)
    if caiKuangCount < 20 or fishCount < 20 or caiYaoCount < 20 then --
        lua_app.print(7, "cai_ji:is_finish ", caiKuangCount, fishCount, caiYaoCount)
        return false
    end
    lua_app.print(11, "�ɼ������")
    return true
end

function cai_ji:destroy()
    eventMgr.unsubAllEvent(self)

    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
end

function cai_ji:init()
    local mainEntityId = scene.get_main_player_entityid()
    local mainplayer = scene.get_entity(mainEntityId)
    local level = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_LEVEL)
    if level > 69 then
        kuang_objs = 
        {
            -- ["ͭ��"] = 1,
            -- ["��ԣ��ͭ��"] = 1,
            -- ["����"] = 1,
            --["��ԣ������"] = 1,

            ["����"] = 1,
            ["��ԣ������"] = 1,
            ["���"] = 1,
            ["��ԣ�Ľ��"] = 1, --2000
            
            ["���صĽ��"] = 1,
        }

        yao_objs = 
        {
            -- ["������"] = 1,
            -- ["������"] = 1,
            -- ["Ѫ��֥"] = 1,
            -- ["������"] = 1,
            -- ["���β�"] = 1,

           ["��ڤ��"] = 1,
           -- ["ѩ����"] = 1,
           -- ["�����"] = 1,
           ["ǧ����"] = 1,
           -- ["���黨"] = 1,
            
            ["����"] = 1,
            --["����"] = 1,
            --["���"] = 1,
            ["��β"] = 1,
            --["����"] = 1,

            ["���صĲ�ҩ"] = 1,
        }

        fish_objs = 
        {
            -- ["С��Ⱥ"] = 1,
            -- ["����Ⱥ"] = 1,
            -- ["����Ⱥ"] = 1,

            ["����Ⱥ"] = 1,
            ["����Ⱥ"] = 1,
            ["������Ⱥ"] = 1,
            ["������Ⱥ"] = 1,

            ["���ص���Ⱥ"] = 1,
        }
    end
end

function cai_ji:start()
    self.init()
    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
    eventMgr.subEvent(eventMgr.event.fishing_bar, self, "onFishingBar")
    self.posIndex = 1
    common.goto_self_house()
    self.delay = 3
end

function cai_ji:onTimer()
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
	lua_app.print(7, "cai_ji:onTimer 1 ")

    if self.delay then
        self.delay = self.delay - 1
        if self.delay <= 0 then
            self.delay = nil
        end
        return
    end
	self:logic()
end

function cai_ji:logic()
    lua_app.print(7, "cai_ji:logic 1 ")
    local mainEntityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(mainEntityId)
    local mapId = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_MAPID)
    local x = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
    local y = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
    local caiKuangCount = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CAIKUANG_COUNT)
    local fishCount = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_FISHING_COUNT)
    local caiYaoCount = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CONNECT_CAOYAO_COUNT)
    if caiKuangCount >= 20 and fishCount >= 20 and caiYaoCount >= 20 then --
        lua_app.print(11, "�ɼ������")
        return
    end
    if ClientControl.is_moving() then
        lua_app.print(7, "cai_ji:logic is_moving ")
        self.delay = 3
        return
    else
        local pos = movePoss[self.posIndex]
        if mapId == pos[1] and math.abs(x - pos[2]) + math.abs(y - pos[3]) <= 5 then
            self.posIndex = self.posIndex + 1
            if self.posIndex > #movePoss then
                self.posIndex = 1
            end
        end
    end
    if not self.targetId then
        lua_app.print(7, "cai_ji:logic 2 ")
        self.targetId, self.targetType = self:find_target()
        if self.targetId then
            local logicEntity = scene.get_entity(self.targetId)
            if false == logicEntity:is_exist() then
                lua_app.print(7, "cai_ji:logic Ŀ�겻����1")
                return
            end
            local logicName = logicEntity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
            local logicX = logicEntity:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
            local logicY = logicEntity:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
            if self.targetType == "kuang" or self.targetType == "yao" then
                lua_app.print(7, "cai_ji:logic �ƶ��� ", logicName, logicX, logicY)
                ClientControl.move_to(logicX, logicY)
                return
            elseif self.targetType == "fish" then
                local newx, newy = common.getNearNoBlockPos(logicX, logicY, 7)
                lua_app.print(7, "cai_ji:logic fish �ƶ��� ", logicName, newx, newy, logicX, logicY)
                ClientControl.move_to(newx, newy)
                return
            end
        end
        local pos = movePoss[self.posIndex]
        if mapId ~= pos[1] then
            lua_app.print(7, "cai_ji:logic ����Ŀ���ͼ")
            ClientControl.move_patch(pos[1], pos[2], pos[3])
            self.delay = 3
            return
        end
        lua_app.print(7, "cai_ji:logic ������� ", mapId, x, y)
        table.print(pos, 7)
        if mapId == pos[1] and math.abs(x - pos[2]) + math.abs(y - pos[3]) <= 5 then
            lua_app.print(7, "cai_ji:logic ��һ�������")
            self.posIndex = self.posIndex + 1
            if self.posIndex > #movePoss then
                self.posIndex = 1
            end
            pos = movePoss[self.posIndex]
            ClientControl.move_patch(pos[1], pos[2], pos[3])
            self.delay = 3
            return
        end
        lua_app.print(7, "cai_ji:logic 4 ")
        ClientControl.move_patch(pos[1], pos[2], pos[3])
        self.delay = 3
        return
    else
        local logicEntity = scene.get_entity(self.targetId)
        if false == logicEntity:is_exist() then
            lua_app.print(7, "cai_ji:logic Ŀ�겻����2")
            self.targetId = nil
            self.targetType = nil
            return
        end
        if self.targetType == "kuang" or self.targetType == "yao" then
            common.operate_logic(self.targetId)
            self.targetId = nil
            self.targetType = nil
            self.delay = 5
            lua_app.RestartIndex = 0--��������������������ԭ��̫����
        elseif self.targetType == "fish" then
            common.operate_logic(self.targetId)
            self.targetId = nil
            self.targetType = nil
            self.delay = 30 --��c++�ṩ���ͷ��ؽӿ�
            lua_app.RestartIndex = 0--��������������������ԭ��̫����
        end
    end
    lua_app.print(7, "cai_ji:logic end ")
end

function cai_ji:find_target()
    local mainEntityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(mainEntityId)
    local caiKuangCount = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CAIKUANG_COUNT)
    local fishCount = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_FISHING_COUNT)
    local caiYaoCount = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CONNECT_CAOYAO_COUNT)
    --Ϊ�˻ؼ�԰�������㣬���ҿ�����ҩ
    if fishCount < 20 then
        lua_app.print(7, "����......")
        for name, _ in pairs(fish_objs) do
            local entityId = common.getNearLogicObjByName(name)
            if entityId then
                return entityId, "fish"
            end
        end
    end
    if caiKuangCount < 20 then
        lua_app.print(7, "�ҿ�......")
        for name, _ in pairs(kuang_objs) do
            local entityId = common.getNearLogicObjByName(name)
            if entityId then
                return entityId, "kuang"
            end
        end
    end
    if caiYaoCount < 20 then
        lua_app.print(7, "��ҩ......")
        for name, _ in pairs(yao_objs) do
            local entityId = common.getNearLogicObjByName(name)
            if entityId then
                return entityId, "yao"
            end
        end
    end
    lua_app.print(7, "�ҿ�������ҩ......ʲôҲû�ҵ�")
end

function cai_ji:onFishingBar()
    lua_app.print(7, "cai_ji:onFishingBar�������")
    self.targetId = nil
    self.targetType = nil
    self.delay = 1
    lua_app.RestartIndex = 0--��������������������ԭ��̫����
end




return cai_ji