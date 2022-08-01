local PropConfig = {}


PropConfig.PROP_ENTITY_ID = 0           --ʵ����
PropConfig.PROP_ENTITY_NAME = 1         --ʵ������
PropConfig.PROP_ENTITY_TYPE = 2         --ʵ������
PropConfig.PROP_ENTITY_MAPID = 4        --ʵ���ͼID
PropConfig.PROP_ENTITY_POS_X = 5        --��ͼX����
PropConfig.PROP_ENTITY_POS_Y = 6        --��ͼY����
PropConfig.PROP_ENTITY_BATTLESCENEID = 9    --ս������ID
PropConfig.PROP_ENTITY_LEVEL = 15       --�ȼ�
PropConfig.PROP_ENTITY_LIFESTATE = 16   --����״̬
PropConfig.PROP_ENTITY_HP = 22          --HP
PropConfig.PROP_ENTITY_HP_MAX = 23      --HPMAX

local PROP_ENTITY_MAX = 157
PropConfig.PROP_ACTOR_ACTORID = PROP_ENTITY_MAX + 1         --��ɫid
PropConfig.PROP_ACTOR_TEAMID = PROP_ENTITY_MAX + 3          --HPMAX
PropConfig.PROP_ACTOR_NP = PROP_ENTITY_MAX + 9              --ŭ��
PropConfig.PROP_ACTOR_CAREER = PROP_ENTITY_MAX + 11         --ְҵ
PropConfig.PROP_ACTOR_YINBI = PROP_ENTITY_MAX + 12          --����
PropConfig.PROP_ACTOR_JINBI = PROP_ENTITY_MAX + 91          --���

PropConfig.PROP_ACTOR_YAOWANG_REWARD_TIME = PROP_ENTITY_MAX + 189	--ǧ������
PropConfig.PROP_ACTOR_SHIERSHENGXIAO_TIME = PROP_ENTITY_MAX + 213	--ʮ����Ф

PropConfig.PROP_ACTOR_CAIKUANG_COUNT = PROP_ENTITY_MAX + 224    --�ɿ����
PropConfig.PROP_ACTOR_CAIKUANG_PROFICIENCY = PROP_ENTITY_MAX + 225    --�ɿ�������
PropConfig.PROP_ACTOR_FISHING_COUNT = PROP_ENTITY_MAX + 226     --�������
PropConfig.PROP_ACTOR_FISHING_PROFICIENCY = PROP_ENTITY_MAX + 227    --����������
PropConfig.PROP_ACTOR_CONNECT_CAOYAO_COUNT = PROP_ENTITY_MAX + 325    --�ɼ���ҩ����
PropConfig.PROP_ACTOR_CONNECT_CAOYAO_PROFICIENCY = PROP_ENTITY_MAX + 324    --�ɼ���ҩ������

PropConfig.PROP_ENTITY_THUNDER_HEART = PROP_ENTITY_MAX + 148    --����֮��
PropConfig.PROP_ENTITY_EARTH_HEART = PROP_ENTITY_MAX + 149    --����֮��





return PropConfig