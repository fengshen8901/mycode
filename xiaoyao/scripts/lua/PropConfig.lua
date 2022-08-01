local PropConfig = {}


PropConfig.PROP_ENTITY_ID = 0           --实体句柄
PropConfig.PROP_ENTITY_NAME = 1         --实体名字
PropConfig.PROP_ENTITY_TYPE = 2         --实体类型
PropConfig.PROP_ENTITY_MAPID = 4        --实体地图ID
PropConfig.PROP_ENTITY_POS_X = 5        --地图X坐标
PropConfig.PROP_ENTITY_POS_Y = 6        --地图Y坐标
PropConfig.PROP_ENTITY_BATTLESCENEID = 9    --战斗场景ID
PropConfig.PROP_ENTITY_LEVEL = 15       --等级
PropConfig.PROP_ENTITY_LIFESTATE = 16   --生命状态
PropConfig.PROP_ENTITY_HP = 22          --HP
PropConfig.PROP_ENTITY_HP_MAX = 23      --HPMAX

local PROP_ENTITY_MAX = 157
PropConfig.PROP_ACTOR_ACTORID = PROP_ENTITY_MAX + 1         --角色id
PropConfig.PROP_ACTOR_TEAMID = PROP_ENTITY_MAX + 3          --HPMAX
PropConfig.PROP_ACTOR_NP = PROP_ENTITY_MAX + 9              --怒气
PropConfig.PROP_ACTOR_CAREER = PROP_ENTITY_MAX + 11         --职业
PropConfig.PROP_ACTOR_YINBI = PROP_ENTITY_MAX + 12          --银币
PropConfig.PROP_ACTOR_JINBI = PROP_ENTITY_MAX + 91          --金币

PropConfig.PROP_ACTOR_YAOWANG_REWARD_TIME = PROP_ENTITY_MAX + 189	--千年妖王
PropConfig.PROP_ACTOR_SHIERSHENGXIAO_TIME = PROP_ENTITY_MAX + 213	--十二生肖

PropConfig.PROP_ACTOR_CAIKUANG_COUNT = PROP_ENTITY_MAX + 224    --采矿次数
PropConfig.PROP_ACTOR_CAIKUANG_PROFICIENCY = PROP_ENTITY_MAX + 225    --采矿熟练度
PropConfig.PROP_ACTOR_FISHING_COUNT = PROP_ENTITY_MAX + 226     --钓鱼次数
PropConfig.PROP_ACTOR_FISHING_PROFICIENCY = PROP_ENTITY_MAX + 227    --钓鱼熟练度
PropConfig.PROP_ACTOR_CONNECT_CAOYAO_COUNT = PROP_ENTITY_MAX + 325    --采集草药次数
PropConfig.PROP_ACTOR_CONNECT_CAOYAO_PROFICIENCY = PROP_ENTITY_MAX + 324    --采集草药熟练度

PropConfig.PROP_ENTITY_THUNDER_HEART = PROP_ENTITY_MAX + 148    --雷力之心
PropConfig.PROP_ENTITY_EARTH_HEART = PROP_ENTITY_MAX + 149    --厚土之心





return PropConfig