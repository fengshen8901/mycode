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
    ["铜矿"] = 1,
    ["富裕的铜矿"] = 1,
    ["银矿"] = 1,
    ["富裕的银矿"] = 1,
}

local yao_objs = 
{
    ["火龙子"] = 1,
    ["生命果"] = 1,
    ["血灵芝"] = 1,
    ["三生草"] = 1,
    ["嗜梦草"] = 1,
}

local fish_objs = 
{
    --["小鱼群"] = 1,
    --["草鱼群"] = 1,
    ["锦鲤群"] = 1,
    ["鲈鱼群"] = 1,
    ["鲑鱼群"] = 1,
}

-- local kuang_objs = 
-- {
--     -- ["铜矿"] = 1,
--     -- ["富裕的铜矿"] = 1,
--     -- ["银矿"] = 1,
--     --["富裕的银矿"] = 1,

--     ["翡翠矿"] = 1,
--     ["富裕的翡翠矿"] = 1,
--     ["金矿"] = 1,
--     ["富裕的金矿"] = 1, --2000
--     ["神秘的金矿"] = 1,
-- }

-- local yao_objs = 
-- {
--     ["火龙子"] = 1,
--     -- ["生命果"] = 1,
--     -- ["血灵芝"] = 1,
--     -- ["三生草"] = 1,
--     -- ["嗜梦草"] = 1,

--    ["幽冥菇"] = 1,
--    ["雪莲花"] = 1,
--    ["地橡果"] = 1,
--    ["千旋草"] = 1,
--    ["迷情花"] = 1,
    
--     ["混沌"] = 1,
--     ["灵蒲"] = 1,
--     ["虫草"] = 1,
--     ["鱼尾"] = 1,
--     ["幽蓝"] = 1,
-- }

-- local fish_objs = 
-- {
--     -- ["小鱼群"] = 1,
--     -- ["草鱼群"] = 1,
--     -- ["锦鲤群"] = 1,

--     ["鲈鱼群"] = 1,
--     ["鲑鱼群"] = 1,
--     ["银龙鱼群"] = 1,
--     ["金龙鱼群"] = 1,
--     ["神秘的鱼群"] = 1,
-- }


local cai_ji = oo.class()

function cai_ji:ctor()
end
--判断是否完成了
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
    lua_app.print(11, "采集完成了")
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
            -- ["铜矿"] = 1,
            -- ["富裕的铜矿"] = 1,
            -- ["银矿"] = 1,
            --["富裕的银矿"] = 1,

            ["翡翠矿"] = 1,
            ["富裕的翡翠矿"] = 1,
            ["金矿"] = 1,
            ["富裕的金矿"] = 1, --2000
            
            ["神秘的金矿"] = 1,
        }

        yao_objs = 
        {
            -- ["火龙子"] = 1,
            -- ["生命果"] = 1,
            -- ["血灵芝"] = 1,
            -- ["三生草"] = 1,
            -- ["嗜梦草"] = 1,

           ["幽冥菇"] = 1,
           -- ["雪莲花"] = 1,
           -- ["地橡果"] = 1,
           ["千旋草"] = 1,
           -- ["迷情花"] = 1,
            
            ["混沌"] = 1,
            --["灵蒲"] = 1,
            --["虫草"] = 1,
            ["鱼尾"] = 1,
            --["幽蓝"] = 1,

            ["神秘的草药"] = 1,
        }

        fish_objs = 
        {
            -- ["小鱼群"] = 1,
            -- ["草鱼群"] = 1,
            -- ["锦鲤群"] = 1,

            ["鲈鱼群"] = 1,
            ["鲑鱼群"] = 1,
            ["银龙鱼群"] = 1,
            ["金龙鱼群"] = 1,

            ["神秘的鱼群"] = 1,
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
        lua_app.print(11, "采集完成了")
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
                lua_app.print(7, "cai_ji:logic 目标不存在1")
                return
            end
            local logicName = logicEntity:get_prop_string(PropConfig.PROP_ENTITY_NAME)
            local logicX = logicEntity:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
            local logicY = logicEntity:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
            if self.targetType == "kuang" or self.targetType == "yao" then
                lua_app.print(7, "cai_ji:logic 移动到 ", logicName, logicX, logicY)
                ClientControl.move_to(logicX, logicY)
                return
            elseif self.targetType == "fish" then
                local newx, newy = common.getNearNoBlockPos(logicX, logicY, 7)
                lua_app.print(7, "cai_ji:logic fish 移动到 ", logicName, newx, newy, logicX, logicY)
                ClientControl.move_to(newx, newy)
                return
            end
        end
        local pos = movePoss[self.posIndex]
        if mapId ~= pos[1] then
            lua_app.print(7, "cai_ji:logic 不在目标地图")
            ClientControl.move_patch(pos[1], pos[2], pos[3])
            self.delay = 3
            return
        end
        lua_app.print(7, "cai_ji:logic 玩家坐标 ", mapId, x, y)
        table.print(pos, 7)
        if mapId == pos[1] and math.abs(x - pos[2]) + math.abs(y - pos[3]) <= 5 then
            lua_app.print(7, "cai_ji:logic 下一个坐标点")
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
            lua_app.print(7, "cai_ji:logic 目标不存在2")
            self.targetId = nil
            self.targetType = nil
            return
        end
        if self.targetType == "kuang" or self.targetType == "yao" then
            common.operate_logic(self.targetId)
            self.targetId = nil
            self.targetType = nil
            self.delay = 5
            lua_app.RestartIndex = 0--重置重启计数，钓鱼在原地太久了
        elseif self.targetType == "fish" then
            common.operate_logic(self.targetId)
            self.targetId = nil
            self.targetType = nil
            self.delay = 30 --等c++提供拉竿返回接口
            lua_app.RestartIndex = 0--重置重启计数，钓鱼在原地太久了
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
    --为了回家园，先找鱼，再找矿，再找药
    if fishCount < 20 then
        lua_app.print(7, "找鱼......")
        for name, _ in pairs(fish_objs) do
            local entityId = common.getNearLogicObjByName(name)
            if entityId then
                return entityId, "fish"
            end
        end
    end
    if caiKuangCount < 20 then
        lua_app.print(7, "找矿......")
        for name, _ in pairs(kuang_objs) do
            local entityId = common.getNearLogicObjByName(name)
            if entityId then
                return entityId, "kuang"
            end
        end
    end
    if caiYaoCount < 20 then
        lua_app.print(7, "找药......")
        for name, _ in pairs(yao_objs) do
            local entityId = common.getNearLogicObjByName(name)
            if entityId then
                return entityId, "yao"
            end
        end
    end
    lua_app.print(7, "找矿找鱼找药......什么也没找到")
end

function cai_ji:onFishingBar()
    lua_app.print(7, "cai_ji:onFishingBar鱼竿拉起")
    self.targetId = nil
    self.targetType = nil
    self.delay = 1
    lua_app.RestartIndex = 0--重置重启计数，钓鱼在原地太久了
end




return cai_ji