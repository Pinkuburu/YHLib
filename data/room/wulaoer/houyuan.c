// File(/data/room/wulaoer/houyuan.c) of wulaoer's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "后院");
	set ("long", @LONG
这是泥巴城堡的后院，正中一个假山，傲然而立、非常雄伟。下
有一水池，环山而走，悠然不息。东面乃是练武之处，西面是厨房。
LONG );

	set("exits", ([
                "south" : __DIR__"zhongting",
                "north" : __DIR__"huayuan",
                "east"  : __DIR__"lianwu",
                "west"  : __DIR__"chufang",
	]));

        set("outdoors", "suzhou");
        set("no_sleep_room", 1);
        setup();

        set("room_owner", "乌老二");
        set("room_name", "泥巴城堡");
        set("room_id", "mud");
        set("room_owner_id", "wulaoer");
        set("room_position", "青石官道");
}
