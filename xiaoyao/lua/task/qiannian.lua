local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"


local movePoss = {
    {15, 69, 102},  --花果山
    {15, 84, 75},
    {15, 54, 35},
    {15, 31, 63},
    {17, 50, 40},   --江南
    {17, 85, 56},
    {17, 93, 92},
    {17, 54, 93},
    {17, 20, 60},
    {17, 59, 62},
    {16, 55, 85},   --清水湾
    {16, 81, 75},
    {16, 71, 44},
    {16, 40, 37},
    {16, 25, 60},
    {18, 86, 36},   --九龙坡
    {18, 119, 65},
    {18, 119, 94},
    {18, 84, 128},
    {18, 45, 100},
    {18, 63, 62},
    {19, 67, 112},  --昆仑山
    {19, 35, 81},
    {19, 55, 53},
    {19, 91, 64},
    {19, 104, 91},
    {20, 72, 53},   --火焰山
    {20, 35, 59},
    {20, 41, 29},
}

local yao_objs = 
{
    "妖鬼王",
    "血魔王",
    "尸妖王",
    "傀儡王",
    "天妖王",
    "海妖王",
    "火冥王",
    "魅妖王",
}

local sheng_objs = 
{
    -- "子鼠",
    -- "丑牛",
    -- "寅虎",
    -- "卯兔",
    -- "辰龙",
    -- "巳蛇",
    -- "午马",
    -- "未羊",
    -- "申猴",
    -- "酉鸡",
    -- "戌狗",
    -- "亥猪",
}


local qiannian = oo.class()

function qiannian:ctor()
end

--判断是否完成了
function qiannian:is_finish()
    local mainEntityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(mainEntityId)

    local yao = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_YAOWANG_REWARD_TIME)
    local sheng = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_SHIERSHENGXIAO_TIME)
   
    if yao < 10  then --or sheng < 5
        lua_app.print(7, "qiannian:is_finish ", yao, sheng)
        return false
    end
    lua_app.print(11, "千年，12 完成了")
    return true
end

function qiannian:destroy()
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")

    if self.work_timer then
        lua_app.del_timer(self.work_timer)
        self.work_timer = nil
    end
end

function qiannian:start()
    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
    if self.is_finish() then return end

    self.delay = 3
    self.posIndex = 1
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
    eventMgr.subEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
end

function qiannian:onTimer()
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
	lua_app.print(7, "qiannian:onTimer 1 ")

    if self.delay then
        self.delay = self.delay - 1
        if self.delay <= 0 then
            self.delay = nil
        end
        return
    end
	self:logic()
end

function qiannian:logic()
    lua_app.print(7, "qiannian:logic 1 ")
    local mainEntityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(mainEntityId)
    local mapId = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_MAPID)
    local x = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
    local y = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)

    if self.is_finish() then return end

    if ClientControl.is_moving() then
        lua_app.print(7, "qiannian:logic is_moving ")
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
        lua_app.print(7, "qiannian:logic 2 ")
        self.targetId, self.targetType = self:find_target()
        if self.targetId then
            local logicEntity = scene.get_entity(self.targetId)
            if false == logicEntity:is_exist() then
                lua_app.print(7, "qiannian:logic 目标不存在1")
                return
            end
            local logicName = logicEntity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
            local logicX = logicEntity:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
            local logicY = logicEntity:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
            
            lua_app.print(7, "qiannian:logic 移动到 ", logicName, logicX, logicY)
            ClientControl.move_to(logicX, logicY)
            return            
        end
        local pos = movePoss[self.posIndex]
        if mapId ~= pos[1] then
            lua_app.print(7, "qiannian:logic 不在目标地图")
            ClientControl.move_patch(pos[1], pos[2], pos[3])
            self.delay = 3
            return
        end
        lua_app.print(7, "qiannian:logic 玩家坐标 ", mapId, x, y)
        table.print(pos, 7)
        if mapId == pos[1] and math.abs(x - pos[2]) + math.abs(y - pos[3]) <= 5 then
            lua_app.print(7, "qiannian:logic 下一个坐标点")
            self.posIndex = self.posIndex + 1
            if self.posIndex > #movePoss then
                self.posIndex = 1
            end
            pos = movePoss[self.posIndex]
            ClientControl.move_patch(pos[1], pos[2], pos[3])
            self.delay = 3
            return
        end
        lua_app.print(7, "qiannian:logic 4 ")
        ClientControl.move_patch(pos[1], pos[2], pos[3])
        self.delay = 3
        return
    else
        local logicEntity = scene.get_entity(self.targetId)
        if false == logicEntity:is_exist() then
            lua_app.print(7, "qiannian:logic 目标不存在2")
            self.targetId = nil
            self.targetType = nil
            return
        end

        local battleSceneID = logicEntity:get_prop_int(PropConfig.PROP_ENTITY_BATTLESCENEID)
        if battleSceneID > 0 then
            lua_app.print(11, "qiannian:logic 目标战斗中，重新找 ", self.targetId)
            self.targetId = nil
            return
        end
        local x1 = logicEntity:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
        local y1 = logicEntity:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
        if math.abs(x - x1) + math.abs(y - y1) < 5 then
            ClientControl.open_mutual(self.targetId)
        else
            ClientControl.move_to(x1, y1)
        end
    end
    lua_app.print(7, "qiannian:logic end ")
end

function qiannian:find_target()
    local mainEntityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(mainEntityId)
    
    local yao = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_YAOWANG_REWARD_TIME)
    local sheng = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_SHIERSHENGXIAO_TIME)
   
    if yao < 10 then
        lua_app.print(7, "找千年妖王......")
        for _, name in pairs(yao_objs) do
            local entityId = common.getNearNpcEntiyIdByName(name)
            if entityId then
                local entity = scene.get_entity(entityId)
                if entity:is_exist() then
                    local battleSceneID = entity:get_prop_int(PropConfig.PROP_ENTITY_BATTLESCENEID)        
                    if battleSceneID == 0 then
                        return entityId, "yao"
                    end
                end
            end
        end
    end
    if sheng < 5 then
        lua_app.print(7, "找十二生肖......")
        for _, name in pairs(sheng_objs) do
            local entityId = common.getNearNpcEntiyIdByName(name)
            if entityId then
                return entityId, "sheng"
            end
        end
    end
    
    lua_app.print(7, "找千年妖王，找十二生肖......什么也没找到")
end

function qiannian:onOpenMutual(TargetEntityID, mutualID, selects, contexts)
    lua_app.print(7, "qiannian:onOpenMutual ", TargetEntityID, mutualID)
    table.print(selects)
    table.print(contexts)
    --选择交互第一个选项
    if selects[1] then
        ClientControl.mutual_select(TargetEntityID, mutualID, selects[1])
    end
end

return qiannian