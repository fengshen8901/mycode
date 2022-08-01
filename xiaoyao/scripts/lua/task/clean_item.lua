local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local itemBag = require "itemBag"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"



local clean_item = oo.class()


function clean_item:ctor()
end

function clean_item:destroy()
    eventMgr.unsubAllEvent(self)
    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
end

function clean_item:start()
    lua_app.print(7, "clean_item:start 1 ")
    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)

end

--右键直接使用的物品
local use_items = 
{
    {1101, 1102},
	{2991, 2997},
	--{4250, 4255},
	{1269, 1270},
}

--直接丢弃的物品
local drop_items = 
{
	--{1111, 1114},
}
--回收银币的物品
local back_items = 
{
	--{1101, 1102},
	--{1132, 1132},
	--{1141, 1141},
	--{1202, 1202},

	-- {1300, 1306},--武器
	-- {1320, 1326},
	-- {1340, 1346},
	-- {1360, 1366},
	-- {1380, 1386},
	-- {1400, 1406},
	-- {1420, 1426},
	-- {1440, 1446},
	-- {1460, 1466},
	-- {1480, 1486},
	-- {1500, 1506},--男帽
	-- {1520, 1526},--女帽
	-- {1540, 1546},--男衣
	-- {1560, 1566},--女衣
	-- {1580, 1586},--男鞋
	-- {1600, 1606},--女鞋
	-- {1620, 1626},--项链
	-- {1640, 1646},--戒指
	-- {1660, 1666},--玉佩
	-- {1680, 1686},--腰带

	-- {1703, 1705}, --图纸
	-- {1723, 1725},
	-- {1743, 1745},
	-- {1763, 1765},
	-- {1783, 1785},
	-- {1803, 1805},
	-- {1823, 1825},
	-- {1843, 1845},
	-- {1863, 1865},
	-- {1883, 1885},
	-- {1903, 1905},
	-- {1923, 1925},
	-- {1943, 1945},
	-- {1963, 1965},
	-- {1983, 1985},
	-- {2003, 2005},
	-- {2023, 2025},
	-- {2043, 2045},
	-- {2063, 2065},
	-- {2083, 2085},
	{2980, 2980},	--矿产物
	{2999, 2999},	--鱼产物
	-- {1182, 1183}, --印记
	{4561, 4564},	--暗器
    --太多了
}
--商会卖物品
local shang_hui_items = 
{
	--{2801, 2803}, --玛瑙
	--{2821, 2823}, --龙玉
	{2841, 2843}, --猫眼
	--{2861, 2863}, --金刚
	--{2881, 2883}, --月亮
	{2901, 2903}, --祖母
	{2921, 2923}, --黄玉
	--{2941, 2943}, --黑
	{2961, 2963}, --蓝
	{4601, 4610}, --子女玩具
	{2163, 2167}, --30-70百炼钢
	{4211, 4246}, --室内家具
	{9201, 9239}, --庭院家具
}

--寄售-20%卖金币物品
local sale_items = 
{
    --[1201] = {8000, "浣彩菇"},
    -- [1211] = {2250, "洗点丹·体"},
    -- [1212] = {2250, "洗点丹·耐"},
    -- [1213] = {2250, "洗点丹·力"},
    -- [1214] = {2250, "洗点丹·魔"},
    -- [1215] = {2250, "洗点丹·敏"},
    [1261] = {4500, "夜明珠"},
    [1262] = {4500, "青龙鳞"},
    [1263] = {4500, "白虎牙"},
    [1264] = {4500, "朱雀羽"},
    [1265] = {4500, "玄武甲"},
    --[1271] = {800, "人物经验书"},
    -- [2601] = {8000, "必杀"},
    -- [2602] = {8000, "连击"},
    -- [2603] = {4000, "反震"},
    -- [2604] = {4000, "反击"},
    -- [2605] = {4000, "追击"},
    -- [2606] = {6400, "吸血"},
    -- [2607] = {4000, "自愈"},
    -- [2608] = {6400, "偷袭"},
    -- [2609] = {4000, "幸运"},
    -- [2610] = {4000, "敏捷"},
    -- [2611] = {4000, "飞行"},
    -- [2612] = {4000, "灵敏"},
    -- [2613] = {4000, "精准"},
    -- [2614] = {4000, "压制"},
    -- [2615] = {4000, "胁迫"},
    -- [2616] = {4000, "毒"},
    -- [2617] = {6400, "强力"},
    -- [2618] = {4000, "勇敢"},
    -- [2619] = {8000, "夜战"},
    -- [2620] = {8000, "法术暴击"},
    -- [2621] = {8000, "灵性"},
    -- [2622] = {8000, "法术连击"},
    -- [2623] = {4000, "法术波动"},
    -- [2624] = {6400, "巫术"},
    -- [2625] = {4000, "防御"},
    -- [2626] = {4000, "冥思"},
    -- [2627] = {4000, "冰霜"},
    -- [2628] = {8000, "强壮"},
    -- [2629] = {4000, "复仇"},
    -- [2630] = {6400, "神佑"},
    -- [2631] = {4000, "神迹"},
    -- [2632] = {4000, "破魔"},
    -- [2633] = {6400, "气势"},
    -- [2634] = {4000, "隐身"},
    -- [2635] = {4000, "感知"},
    -- [2636] = {4000, "保命"},
    -- [2637] = {4000, "反射"},
    -- [2638] = {4000, "法抗"},
    -- [2639] = {4000, "溅射"},
    -- [2640] = {4000, "鬼魂术"},
    -- [2641] = {4000, "驱鬼"},
    -- [2642] = {4000, "先锋"},
    -- [2643] = {4000, "土系吸收"},
    -- [2644] = {4000, "火系吸收"},
    -- [2645] = {4000, "水系吸收"},
    -- [2646] = {4000, "雷系吸收"},
    -- [2647] = {4000, "火球"},
    -- [2648] = {4000, "雷电"},
    -- [2649] = {4000, "落岩"},
    -- [2650] = {4000, "水攻"},
    -- [4421] = {3200, "天阵"},
    -- [4422] = {3200, "鸟阵"},
    -- [4423] = {3200, "地阵"},
    -- [4424] = {3200, "虎阵"},
    -- [4425] = {3200, "蛇阵"},
    -- [4426] = {3200, "龙阵"},
    -- [4427] = {3200, "风阵"},
    -- [4428] = {3200, "云阵"},
    [4540] = {4500, "玫瑰花"},
    [4541] = {4500, "郁金香"},
    [4624] = {1800, "武力丹"},
    [4625] = {1800, "体魄丹"},
    [4626] = {1800, "筋骨丹"},
    [4627] = {1800, "智力丹"},
    [4628] = {1800, "身法丹"},
	[2231] = {4800, "一级护符洗练丹"},
	
}

function clean_item:onTimer()
    lua_app.print(7, "clean_item:onTimer")
    local count = 0
    local items = itemBag.get_all_items()
    local hasSale = false
    for _, item in pairs(items) do
        local process = false
		if false == process then
			for _, v in ipairs(use_items) do
				if item.itemId >= v[1] and item.itemId <= v[2] then
					process = true
					itemBag.use_item(item.handel)
					break
				end
			end
		end
		if false == process then
			for _, v in ipairs(drop_items) do
				if item.itemId >= v[1] and item.itemId <= v[2] then
					process = true
					itemBag.drop_item(item.handel)
					break
				end
			end
		end
		if false == process then
			for _, v in ipairs(back_items) do
				if item.itemId >= v[1] and item.itemId <= v[2] then
					process = true
					local handels = {item.handel} --key 1-10
					itemBag.back_items(handels)
					break
				end
			end
		end
		if false == process then
			for _, v in ipairs(shang_hui_items) do
				if item.itemId >= v[1] and item.itemId <= v[2] then
					process = true
					itemBag.sell_shanghui_item(item.handel)
					break
				end
			end
		end
		if false == process then
			if sale_items[item.itemId] then
				process = true
				hasSale = true
				itemBag.sale_item(item.handel, sale_items[item.itemId][1])
				--同一时间只能卖一个
				count = count + 1
				lua_app.print(11, "清理物品中... ", count)
				break
			end
		end
        if process then
            count = count + 1
            lua_app.print(11, "清理物品中... ", count)
            if count >= 10 then
                lua_app.print(7, "clean_item:onTimer 5")
                break
            end
        end
    end
    if count > 0 then
        lua_app.print(7, "clean_item:onTimer 7")
        if false == hasSale then
            self.work_timer = lua_app.add_timer(1000, "onTimer", self)
        else
            self.work_timer = lua_app.add_timer(3000, "onTimer", self)
        end
    else
        lua_app.print(11, "清理物品结束")
	    lua_app.show_tips("清理物品结束")
    end
end


return clean_item