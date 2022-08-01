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

--�Ҽ�ֱ��ʹ�õ���Ʒ
local use_items = 
{
    {1101, 1102},
	{2991, 2997},
	--{4250, 4255},
	{1269, 1270},
}

--ֱ�Ӷ�������Ʒ
local drop_items = 
{
	--{1111, 1114},
}
--�������ҵ���Ʒ
local back_items = 
{
	--{1101, 1102},
	--{1132, 1132},
	--{1141, 1141},
	--{1202, 1202},

	-- {1300, 1306},--����
	-- {1320, 1326},
	-- {1340, 1346},
	-- {1360, 1366},
	-- {1380, 1386},
	-- {1400, 1406},
	-- {1420, 1426},
	-- {1440, 1446},
	-- {1460, 1466},
	-- {1480, 1486},
	-- {1500, 1506},--��ñ
	-- {1520, 1526},--Ůñ
	-- {1540, 1546},--����
	-- {1560, 1566},--Ů��
	-- {1580, 1586},--��Ь
	-- {1600, 1606},--ŮЬ
	-- {1620, 1626},--����
	-- {1640, 1646},--��ָ
	-- {1660, 1666},--����
	-- {1680, 1686},--����

	-- {1703, 1705}, --ͼֽ
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
	{2980, 2980},	--�����
	{2999, 2999},	--�����
	-- {1182, 1183}, --ӡ��
	{4561, 4564},	--����
    --̫����
}
--�̻�����Ʒ
local shang_hui_items = 
{
	--{2801, 2803}, --���
	--{2821, 2823}, --����
	{2841, 2843}, --è��
	--{2861, 2863}, --���
	--{2881, 2883}, --����
	{2901, 2903}, --��ĸ
	{2921, 2923}, --����
	--{2941, 2943}, --��
	{2961, 2963}, --��
	{4601, 4610}, --��Ů���
	{2163, 2167}, --30-70������
	{4211, 4246}, --���ڼҾ�
	{9201, 9239}, --ͥԺ�Ҿ�
}

--����-20%�������Ʒ
local sale_items = 
{
    --[1201] = {8000, "佲ʹ�"},
    -- [1211] = {2250, "ϴ�㵤����"},
    -- [1212] = {2250, "ϴ�㵤����"},
    -- [1213] = {2250, "ϴ�㵤����"},
    -- [1214] = {2250, "ϴ�㵤��ħ"},
    -- [1215] = {2250, "ϴ�㵤����"},
    [1261] = {4500, "ҹ����"},
    [1262] = {4500, "������"},
    [1263] = {4500, "�׻���"},
    [1264] = {4500, "��ȸ��"},
    [1265] = {4500, "�����"},
    --[1271] = {800, "���ﾭ����"},
    -- [2601] = {8000, "��ɱ"},
    -- [2602] = {8000, "����"},
    -- [2603] = {4000, "����"},
    -- [2604] = {4000, "����"},
    -- [2605] = {4000, "׷��"},
    -- [2606] = {6400, "��Ѫ"},
    -- [2607] = {4000, "����"},
    -- [2608] = {6400, "͵Ϯ"},
    -- [2609] = {4000, "����"},
    -- [2610] = {4000, "����"},
    -- [2611] = {4000, "����"},
    -- [2612] = {4000, "����"},
    -- [2613] = {4000, "��׼"},
    -- [2614] = {4000, "ѹ��"},
    -- [2615] = {4000, "в��"},
    -- [2616] = {4000, "��"},
    -- [2617] = {6400, "ǿ��"},
    -- [2618] = {4000, "�¸�"},
    -- [2619] = {8000, "ҹս"},
    -- [2620] = {8000, "��������"},
    -- [2621] = {8000, "����"},
    -- [2622] = {8000, "��������"},
    -- [2623] = {4000, "��������"},
    -- [2624] = {6400, "����"},
    -- [2625] = {4000, "����"},
    -- [2626] = {4000, "ڤ˼"},
    -- [2627] = {4000, "��˪"},
    -- [2628] = {8000, "ǿ׳"},
    -- [2629] = {4000, "����"},
    -- [2630] = {6400, "����"},
    -- [2631] = {4000, "��"},
    -- [2632] = {4000, "��ħ"},
    -- [2633] = {6400, "����"},
    -- [2634] = {4000, "����"},
    -- [2635] = {4000, "��֪"},
    -- [2636] = {4000, "����"},
    -- [2637] = {4000, "����"},
    -- [2638] = {4000, "����"},
    -- [2639] = {4000, "����"},
    -- [2640] = {4000, "�����"},
    -- [2641] = {4000, "����"},
    -- [2642] = {4000, "�ȷ�"},
    -- [2643] = {4000, "��ϵ����"},
    -- [2644] = {4000, "��ϵ����"},
    -- [2645] = {4000, "ˮϵ����"},
    -- [2646] = {4000, "��ϵ����"},
    -- [2647] = {4000, "����"},
    -- [2648] = {4000, "�׵�"},
    -- [2649] = {4000, "����"},
    -- [2650] = {4000, "ˮ��"},
    -- [4421] = {3200, "����"},
    -- [4422] = {3200, "����"},
    -- [4423] = {3200, "����"},
    -- [4424] = {3200, "����"},
    -- [4425] = {3200, "����"},
    -- [4426] = {3200, "����"},
    -- [4427] = {3200, "����"},
    -- [4428] = {3200, "����"},
    [4540] = {4500, "õ�廨"},
    [4541] = {4500, "������"},
    [4624] = {1800, "������"},
    [4625] = {1800, "���ǵ�"},
    [4626] = {1800, "��ǵ�"},
    [4627] = {1800, "������"},
    [4628] = {1800, "����"},
	[2231] = {4800, "һ������ϴ����"},
	
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
				--ͬһʱ��ֻ����һ��
				count = count + 1
				lua_app.print(11, "������Ʒ��... ", count)
				break
			end
		end
        if process then
            count = count + 1
            lua_app.print(11, "������Ʒ��... ", count)
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
        lua_app.print(11, "������Ʒ����")
	    lua_app.show_tips("������Ʒ����")
    end
end


return clean_item